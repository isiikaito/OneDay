/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerState.h"
#include "Meat.h"
#include "GameUI.h"
#include "WoodenBoxState.h"
#include "AnimationComponent.h"



namespace basecross {
	constexpr float VIbRATIONMAXTIME = 1.0f;			//!�U�����鎞��
	constexpr int DAY = 7;								//!�Q�[���I�[�o�[�܂ł̓��ɂ�
	constexpr int SOUNDLOOP = 1;						//!���̃��[�v
	constexpr int NOTSOUNDLOOP = 0;						//!�T�E���h���[�v����
	constexpr float ESCAPESPHERERAKIUS = 10.0f;			//!�v���C���[�𒆐S�Ƃ����~�̔��a
	constexpr float VILLAGERKILLERSPHERERADIUS = 5.0f;	//!���l��|�����̉~�̔��a
	constexpr float BREAKWOODBOXSPHERERADIUS = 5.0f;	//!�ؔ���|�����̉~�̔��a
	constexpr float HUNTERKILLERSPHERERADIUS = 5.0f;	//!�n���^�[��|�����̉~�̔��a
	constexpr float ANGLEEQUAL = 6.0f;					//!����̐���
	constexpr float ROTTOHEAD = 1.0f;					//!����
	constexpr float TARGETTOATY = 0.25f;				//!�J�����̎��_�ʒu��y
	constexpr WORD  MAXVIBRATION = 65535;				//!�U���̑傫��
	
	//!�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_playerBoneModelDeta({ 
		Vec3(3.0f, 3.0f, 3.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 4.0f, -90.0f),
		Vec3(0.4f, 0.4f, 0.4f) ,
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, -1.0f, 0.0f),
		L"Player_WalkAnimation2_MESH" ,
		L"Player_WalkAnimation2_MESH_WITH_TAN",
		L"OBJECT_NORMAL_TX" }),
		m_playerChange(PlayerModel::human),
		m_reset(0),
		m_KeyCount(0),
		m_Ded(0.0f),
		m_GetPlayerPositionTime(0.8f),
		m_PlayerPositionTime(0.0f),
		m_PlayerPositionOnSecondMax(39),
		m_PlayerHp(3),
		m_IsPlayerDed(0.0f),
		m_vibration(0),
		m_meatCount(0),
		m_vibrationTime(0.0f),
		m_IsvibrationOn(false),
		m_playerTaskDay(true),
		m_playerTaskNight(false),
		m_effectManager(NULL)
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());	//!���݂̃X�e�[�g
	}

	//�v���C���[�𓮂���
	void Player::MovePlayer() {

		
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();				//�A�j���[�V����
		auto& AnimationName = ptrDraw->GetCurrentAnimation();				//!���݂̃A�j���[�V����
		float elapsedTime = App::GetApp()->GetElapsedTime();				//!�o�ߎ��Ԃ̎擾
		auto angle = m_playermove.lock()->GetMoveVector();					//!�x�N�g���̎擾
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!���ʉ���
		//!�X�e�B�b�N���X���Ă�����
		if (angle.length() > 0.0f) {
			
			//�����A�j���[�V����
			//!�ҋ@���[�V�������ϐg���[�V�����̎�
			if (AnimationName == L"Default" || AnimationName == L"Change") {
				ptrDraw->ChangeCurrentAnimation(L"Move");						//!�A�j���[�V������ς���
				auto& XAptr = App::GetApp()->GetXAudio2Manager();				//!�T�E���h�}�l�[�W���[�̎擾
				m_Wolk = XAptr->Start(L"WalkBGM", SOUNDLOOP, volume);			//�������Đ�
			}
		}

		else {
			//�����~�܂�A�j���[�V����
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");		//!�A�j���[�V������ς���
				auto& XAptr = App::GetApp()->GetXAudio2Manager();	//!�T�E���h�}�l�[�W���[�̎擾
				XAptr->Stop(m_Wolk);								//���������~�߂�
			}
		}

		//!��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, ROTTOHEAD);		//!���ʂ�����
		}
	}

	void Player::OnCreate() {

		m_effectManager = EffectManager::Instance();

		AddComponent<PlayerMoveComponent>();														//!�v���C���[�̓�������
		m_playermove = GetComponent<PlayerMoveComponent>();
		AddComponent<BoneModelComponent>(m_playerBoneModelDeta);									//!�v���C���[�̃��f���쐬
		AddComponent<BcPNTnTBoneModelDraw>();														//!���f���̕`��R���|�[�l���g�̒ǉ�
		m_draw = GetComponent<BcPNTnTBoneModelDraw>();												//!�`�揈��
		AddComponent<AnimationComponent>(L"Player", L"Default");									//!�A�j���[�V�����̓ǂݍ���

			//!�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());	//!MyCamera�ł���
			ptrCamera->SetTargetToAt(Vec3(0, TARGETTOATY, 0));//!MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
		}
	}

	
	

	void Player::EnemyDedSound()
	{
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!���ʉ��ʂ̎擾
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();					//!�T�E���h�}�l�[�W���[�̎擾
		ptrXA->Start(L"kill", NOTSOUNDLOOP, volume);						//!�|�����Ƃ��̃T�E���h�̊J�n
		ptrXA->Start(L"scream", NOTSOUNDLOOP, volume);						//!�U���̃T�E���h�̊J�n
	}

	void Player::Hunterkiller()
	{
		auto transComp = GetComponent<Transform>();						  //!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();						  //!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, HUNTERKILLERSPHERERADIUS);			  //!�v���C���[�̍��W�𒆐S�ɔ��a5�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();					  //!�V�[���̎擾
		int alertlevelCount = scene->GetAlertlevelCount();				  //!�x���x�̎擾
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!�n���^�[�O���[�v�̎擾
		auto& vecHunter = group->GetGroupVector();						  //!�O���[�v�̎擾
		//!�n���^�[�̔z��I�u�W�F�N�g�̔z��for���ŉ�
		for (auto& v : vecHunter)
		{
			auto HunterPtr = v.lock();									 //!�n���^�[�̃O���[�v����1���b�N����
			Vec3 ret;													 //!�ŋߐړ_�̑��
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);    //!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG���͂�������
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!�n���^-��Obb�I�u�W�F�N�g���擾
                
				//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))
				{
					
					ptrHunter->SetIsEnemyDed(true);				//!�G�����񂾃X�e�[�g�ɕύX����
					alertlevelCount++;							//!�댯�x���グ��
					scene->SetAlertlevelCount(alertlevelCount); //!�댯�x���X�V
					EnemyDedSound();
						
				}
			}

		}
	}

	void Player::OneWeek()
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
		auto Date = scene->GetDate();					//!���t�̎擾
		//!�Q�[���I�[�o�[�̓��t�ɂȂ�����
		if (Date == DAY)
		{
			m_PlayerHp = 0;//!�Q�[���I�[�o�[
		}

	}
	//!�ؔ���j�󂷂�
	void Player::BreakWoodBox()
	{
		auto transComp = GetComponent<Transform>();							//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();							//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, BREAKWOODBOXSPHERERADIUS);				//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup"); //!�O���[�v�̎擾
		auto& vecWoodBox = group->GetGroupVector();							//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!�ؔ��z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecWoodBox)
		{
			auto WoodBox = v.lock();										//!���l�̃O���[�v����1���b�N����
			Vec3 ret;														//!�ŋߐړ_�̑��
			auto ptrWoodBox = dynamic_pointer_cast<WoodenBox>(WoodBox);		//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������
			if (ptrWoodBox)
			{
				auto woodBoxCollision = ptrWoodBox->GetComponent<CollisionObb>();
				auto WoodenBoxOBB = woodBoxCollision->GetObb();//!�n���^-��Obb�I�u�W�F�N�g���擾

				//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				if (HitTest::SPHERE_OBB(playerSp, WoodenBoxOBB, ret))
				{
					ptrWoodBox->ChangeState(basecross::kaito::WoodenBoxBreakState::Instance());	//!�ؔ���j�󂷂�X�e�[�g�ɕύX
					auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();			//!���ʉ��ʂ̎擾					
					auto& ptrXA = App::GetApp()->GetXAudio2Manager();							//�T�E���h�Đ�
					ptrXA->Start(L"WoodBoxBreak", NOTSOUNDLOOP, volume);
					
				}
			}
		}
	}

	//!���l��|������
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();							//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();							//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, VILLAGERKILLERSPHERERADIUS);				//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
		int alertlevelCount = scene->GetAlertlevelCount();					//!�댯�x�̎擾
		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");//!���l�̃O���[�v���擾
		auto& vecVillager = group->GetGroupVector();						//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecVillager)
		{
			auto VillagerPtr = v.lock();									//!���l�̃O���[�v����1���b�N����
			Vec3 ret;														//!�ŋߐړ_�̑��
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);	//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������v

			if (ptrVillager)
			{
				auto VillagerCapsrul = ptrVillager->GetComponent<CollisionCapsule>()->GetCapsule();	//!�n���^-��Obb�I�u�W�F�N�g���擾
				//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				if (HitTest::SPHERE_CAPSULE(playerSp, VillagerCapsrul, ret))						
				{
						ptrVillager->SetIsEnemyDed(true);			//!�G�����񂾃X�e�[�g�ɕύX����
						alertlevelCount++;							//!�댯�x���グ��
						scene->SetAlertlevelCount(alertlevelCount); //!�댯�x��ݒ�
						EnemyDedSound();
					
				}
			}
		}
	}
	
	
	void Player::GetPlayerPositionBrett()
	{
		
		
		auto PlayerTrans = GetComponent<Transform>();		//!�v���C���[�̃g�����X�t�H�[�����擾
		auto PlayerPosition = PlayerTrans->GetPosition();	//!�v���C���[�̃|�W�V�������擾
		auto Time = App::GetApp()->GetElapsedTime();		//!�G���p�\�^�C�����擾
		m_PlayerPositionTime += Time;						//!���Ԃ̍쐬

		//!�v���C���[���|�W�V������ۑ����鎞��
		if (m_PlayerPositionTime >= m_GetPlayerPositionTime)
		{
			m_PlayerPositionOnSecond.push_back(PlayerPosition);//!�|�W�V������ۑ�

			//!��萔�ۑ�������
			if (m_PlayerPositionOnSecond.size() >= m_PlayerPositionOnSecondMax)
			{
				
				m_PlayerPositionOnSecond.erase(m_PlayerPositionOnSecond.begin());//!�Â������폜����
			}
		}
	}

	void Player::Escape()
	{
		auto transComp = GetComponent<Transform>();														//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();														//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, ESCAPESPHERERAKIUS);													//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");								//!����擾
		Vec3 ret;																						//!�ŋߐړ_�̑��
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();									//!�R���W�����̏Փ˔���
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))												//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();											//!�T�E���h�}�l�[�W���[�̎擾
			XAptr->Stop(m_Wolk);																		//!�������̒�~
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");	//!�Q�[���N���A�X�e�[�W�ɑJ��
		}
	}
		
	

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!�X�e�[�g��ύX����
	}

	
	void Player::Controllervibration()
	{
		auto scene = App::GetApp()->GetScene<Scene>();			//!�V�[���̎擾
		auto gameOverSprite = scene->GetGameOverSprite();		//!�Q�[���I�[�o�[����̎擾
		if (gameOverSprite == false)
		{
			//!�U�����I���ɂȂ��Ă���Ƃ�
			if (m_IsvibrationOn == true)
			{
				auto Time = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
				m_vibrationTime += Time;					//!�U�������鎞��
				m_vibration = MAXVIBRATION;					//!���݂̐U���̑傫��
				//!�U�����鎞�Ԍo������
				if (m_vibrationTime >= VIbRATIONMAXTIME)
				{
					m_IsvibrationOn = false;//!�U������߂�
				}
			}
			if (m_IsvibrationOn == false)
			{
				m_vibrationTime = 0.0f;	//!���Ԃ����Z�b�g
				m_vibration = 0;		//!�U���𖳂���
			}


			XINPUT_VIBRATION vibration;							//!�R���g���[���[�̐U��
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = m_vibration;			// use any value between 0-65535 here
			vibration.wRightMotorSpeed = m_vibration;			// use any value between 0-65535 here
			XInputSetState(0, &vibration);						//!�R���g���[���[�̐U���̐ݒ�
		}

		else
		{
			
				m_vibrationTime = 0.0f;	//!���Ԃ����Z�b�g
				m_vibration = 0;		//!�U���𖳂���
		
			XINPUT_VIBRATION vibration;							//!�R���g���[���[�̐U��
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = m_vibration;			// use any value between 0-65535 here
			vibration.wRightMotorSpeed = m_vibration;			// use any value between 0-65535 here
			XInputSetState(0, &vibration);						//!�R���g���[���[�̐U���̐ݒ�
		}
		
	}

	//�X�V
	void Player::OnUpdate() {
		

		m_StateMachine->Update();								//!�X�e�[�g�}�V���̍X�V
		OneWeek();
		Controllervibration();
		auto scene = App::GetApp()->GetScene<Scene>();			//!�V�[���̎擾
		float elapsedTime = App::GetApp()->GetElapsedTime();	//!�o�ߎ��Ԃ̎擾
		auto ptrDraw = m_draw.lock();							//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);					//!�A�j���[�V�����̍X�V
		auto playerChange = scene->GetPlayerChangeDirecting();	//!�v���C���[�̕ϐg���J�n����
		auto gameStrat = scene->GetGameStrat();					//!�I�[�v�j���O�J�����̎����ǂ���
	
		GetPlayerPositionBrett();
		//!�v���C���[���ϐg���Ă��Ȃ���
		if (!playerChange)
		{
				MovePlayer();
		}
		//!�ϐg���Ă��邩�I�[�v�j���O�J�����̎�
		if(playerChange|| gameStrat)
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();//!�T�E���h�}�l�[�W���[�̎擾
			XAptr->Stop(m_Wolk);							 //!���������~�߂�
		}

	 }



	//!�v���C���[������ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		
		auto ptrKey = dynamic_pointer_cast<Key>(Other);//!���̎擾

		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʉ��ʂ̎擾
		if (m_playerChange == PlayerModel::wolf)
		{
			//!�v���C���[�����ɓ���������
			if (ptrKey)
			{

				m_KeyCount++;																		//!���̃J�E���g
				GetStage()->RemoveGameObject<Key>(Other);											//!���I�u�W�F�N�g�̍폜
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!�T�E���h�}�l�[�W���[�̎擾
				ptrXA->Start(L"acquisition", NOTSOUNDLOOP, volume);									//!�T�E���h�̍Đ�
				auto position = ptrKey->GetComponent<Transform>()->GetPosition();					//!�G�t�F�N�g�̃v���C
				m_effectManager->KeyEfkPlay(position);												//!�G�t�F�N�g�̍Đ�

			
			}


		}

		auto ptrMeat = dynamic_pointer_cast<Meat>(Other);//!���̎擾

		if (m_playerChange == PlayerModel::human)
		{
			//!�v���C���[�����ɓ���������
			if (ptrMeat)
			{
				m_meatCount++;
				GetStage()->RemoveGameObject<Meat>(Other);											//!���I�u�W�F�N�g�̍폜
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!�T�E���h�}�l�[�W���[�̎擾
				ptrXA->Start(L"MeatEat", NOTSOUNDLOOP, volume);										//!����H�ׂ�T�E���h�̍Đ�
				auto Ptr = GetComponent<Transform>();												//!�g�����X�t�H�[���̎擾
				m_effectManager->MeatEfkPlay(Ptr->GetPosition());									//!�G�t�F�N�g�̍Đ�

			}


		}

	}

	void Player::AttackEffect()
	{
		//�G�t�F�N�g�̃v���C
		auto Ptr = GetComponent<Transform>();                                               //!�g�����X�t�H�[���̎擾
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					//!�G�t�F�N�g�C���^�[�t�F�[�X�̎擾 
		auto playerPosition = Ptr->GetPosition();											//!�v���C���[�̃|�W�V�����̎擾 
		m_effectManager->ScratchEfkPlay(playerPosition);									//!�G�t�F�N�g�̍Đ�

	}																						  
																							   
	void Player::OnPushB()																	   
	{
		
			Villagerkiller();
			Hunterkiller();
			BreakWoodBox();
			AttackEffect();
		
	}
}
//end basecross

