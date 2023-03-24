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

namespace basecross {
	constexpr float m_MaxwolfHowlingTime = 0.1f;
	constexpr float m_maxDedTime = 1.0f;
	constexpr float m_vibrationMaxTime = 1.0f;
	constexpr int m_Day = 7;
	constexpr float m_escapeSphereRadius = 10.0f;
	constexpr float m_villagerkillerSphereRadius = 5.0f;
	constexpr float m_breakWoodBoxSphereRadius = 5.0f;
	constexpr float m_hunterkillerSphereRadius = 5.0f;
	constexpr float m_angleEqual = 6.0f;
	constexpr WORD  m_maxVibration = 65535;
	
	

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//!�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Speed(20.0f),
		m_ChangeTime(0.0f),
		m_playerChange(static_cast<int>(PlayerModel::human)),
		m_humanTime(31.0f),
		m_wolfTime(61.0f),
		m_reset(0),
		m_KeyCount(0),
		m_MaxKeyCount(3),
		m_Ded(0.0f),
		m_GetPlayerPositionTime(0.8f),
		m_PlayerPositionTime(0.0f),
		m_PlayerPositionOnSecondMax(39),
		m_PlayerHp(3),
		m_IsPlayerFound(false),
		m_wolfPlayerSpeed(21.0f),
		m_humanPlayerSpeed(20.0f),
		m_AlertleveCount(0),
		m_IsFastHowling(false),
		m_wolfHowlingTime(0),
		m_dedTime(0.0f),
		m_IsPlayerDed(0.0f),
		m_gameOverDrawActive(false),
		m_vibration(0),
		m_gameTime(0.0f),
		m_meatCount(0),
		m_vibrationTime(0.0f),
		m_IsvibrationOn(false),
		m_playerTaskDay(true),
		m_playerTaskNight(false),
		m_IsPlayerChangeEffect(true)
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());
	}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//!�R���g���[���̎擾
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}

		return ret;
	}

	//!�v���C���[�̃x�N�g���̎擾
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);

		//!���͂̎擾
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;

		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//!���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();
			auto& ptrCamera = OnGetDrawCamera();

			//!�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();

			float frontAngle = atan2(front.z, front.x);//!�i�s������������̊p�x���Z�o

			//!�R���g���[���̌����v�Z
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();

			float cntlAngle = atan2(-moveX, moveZ);//!�R���g���[���̌�������p�x���v�Z

			float totalAngle = frontAngle + cntlAngle;//!�g�[�^���̊p�x���Z�o

			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));//!�p�x����x�N�g�����쐬

			angle.normalize();//!���K������

			angle *= moveSize;//!�ړ��T�C�Y��ݒ�B

			angle.y = 0;//!Y���͕ω������Ȃ�
		}
		return angle;
	}

	//!�v���C���[�𓮂�������
	void Player::MovePlayer() {

		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);

			//�����A�j���[�V����
			if (AnimationName == L"Default" || AnimationName == L"Change") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//�������Đ�
				auto& XAptr = App::GetApp()->GetXAudio2Manager();
				m_Wolk = XAptr->Start(L"WalkBGM", 1, 0.5f);
			}
		}

		else {
			//�����~�܂�A�j���[�V����
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto& XAptr = App::GetApp()->GetXAudio2Manager();
				XAptr->Stop(m_Wolk);
			}
		}

		//!��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}

	//!������
	void Player::OnCreate() {

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring keyEffectStr = DataDir + L"Effects\\key.efk";//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		auto EfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();//!�G�t�F�N�g�̃C���^�[�t�F�[�X�̎擾
		m_KeyEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, keyEffectStr);//!�擾�����G�t�F�N�g�ō��

		wstring ScratchEffectStr = DataDir + L"Effects\\kill.efk";//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		m_ScratchEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, ScratchEffectStr);//!�擾�����G�t�F�N�g�ō��

		wstring TransformEffectStr = DataDir + L"Effects\\Transform2.efk";//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		m_TransformEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, TransformEffectStr);//!�擾�����G�t�F�N�g�ō��

		
		wstring MeatEffectStr = DataDir + L"Effects\\smoke.efk";//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		m_MeatEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, MeatEffectStr);//!�擾�����G�t�F�N�g�ō��


		//!�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(3.0f, 3.0f, 3.0f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0.0f, 4.0f, -90.0f));


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -1.0f, 0.0f)  //!�ʒu
		);

		auto ptrColl = AddComponent<CollisionCapsule>();//!CollisionSphere�Փ˔����t����

		ptrColl->SetDrawActive(false);
		auto ptrGra = AddComponent<Gravity>();//!�d�͂�����


		auto shadowPtr = AddComponent<Shadowmap>();//!�e������i�V���h�E�}�b�v��`�悷��j

		shadowPtr->SetMeshResource(L"Player_WalkAnimation2_MESH");//!�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̐ݒ�

		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"Player_WalkAnimation2_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 20.0f);
		ptrDraw->AddAnimation(L"Default", 31, 30, true, 10.0f);
		ptrDraw->AddAnimation(L"Ded", 61, 30, false, 30.0f);
		ptrDraw->AddAnimation(L"Change", 91, 60, false, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");

			//!�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());//!MyCamera�ł���
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));//!MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
		}
	}

	

	void Player::PlayerGameOver()
	{
		auto scene=App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		gameOver = true;
		scene->SetGameOver(gameOver);

		
		float Time = App::GetApp()->GetElapsedTime();
		m_dedTime += Time;
		if (m_dedTime >= m_maxDedTime)
		{
			m_gameOverDrawActive = true;
		}

	}

	void Player::PlayerDed()
	{
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//�����~�܂�A�j���[�V����
		if (AnimationName == L"Move" || AnimationName == L"Default")
		{
			ptrDraw->ChangeCurrentAnimation(L"Ded");
			auto& XAptr = App::GetApp()->GetXAudio2Manager();
			XAptr->Stop(m_Wolk);

		}

		PlayerGameOver();
	}

	

	void Player::EnemyDedSound()
	{
		//�T�E���h�Đ�
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"kill", 0, 1.0f);
		ptrXA->Start(L"scream", 0, 1.0f);
	}

	void Player::Hunterkiller()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_hunterkillerSphereRadius);//!�v���C���[�̍��W�𒆐S�ɔ��a5�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		int alertlevelCount = scene->GetAlertlevelCount();//!�x���x�̎擾
		//!�n���^�[���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		auto& vecHunter = group->GetGroupVector();
		//!�n���^�[�̔z��I�u�W�F�N�g�̔z��for���ŉ�
		for (auto& v : vecHunter)
		{
			auto HunterPtr = v.lock();//!�n���^�[�̃O���[�v����1���b�N����
			Vec3 ret;//!�ŋߐړ_�̑��
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);//!���b�N�����������o��

			auto HunterTrans = GetComponent<Transform>();//!�n���^�[�̃g�����X�t�H�[���̎擾
			auto HunterPosition = HunterTrans->GetPosition();//!�n���^�[�̃|�W�V�����̎擾
			Vec3 PEvector = position - HunterPosition;//!�v���C���[�ƓG�̃x�N�g�����擾
			PEvector.normalize();//!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto Enemyfront = HunterTrans->GetForword();//!�G�̐��ʂ��擾
			auto angle = angleBetweenNormals(-Enemyfront, PEvector);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / m_angleEqual;
			;//!360��6�Ŋ����Ċp�x���o���B

			//!�v���C���[�͈̔͂ɓG���͂�������
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!�n���^-��Obb�I�u�W�F�N�g���擾
                
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������)
				{
					
						auto HunterSpeed = ptrHunter->GetSpeed();//!���l�̃X�s�[�h���擾
						if (HunterSpeed != m_Ded)
						{
							HunterSpeed = m_Ded;//!���l�̃X�s�[�h���O�ɂ���
							ptrHunter->SetSpeed(HunterSpeed);//!���l�̃X�s�[�h��ݒ�
							alertlevelCount++;
							scene->SetAlertlevelCount(alertlevelCount);

							//�T�E���h�Đ�
							EnemyDedSound();
						}
					
				}
			}

		}
	}

	void Player::OneWeek()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto Date = scene->GetDate();
		if (Date == m_Day)
		{
			PlayerGameOver();
		}

	}

	void Player::BreakWoodBox()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_breakWoodBoxSphereRadius);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();
		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup");
		auto& vecWoodBox = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecWoodBox)
		{
			auto WoodBox = v.lock();//!���l�̃O���[�v����1���b�N����
			Vec3 ret;//!�ŋߐړ_�̑��
			auto ptrWoodBox = dynamic_pointer_cast<WoodenBox>(WoodBox);//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������
			if (ptrWoodBox)
			{
				auto WoodBoxOBB = ptrWoodBox->GetComponent<CollisionObb>()->GetObb();//!�n���^-��Obb�I�u�W�F�N�g���擾
				if (HitTest::SPHERE_OBB(playerSp, WoodBoxOBB, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				{
					GetStage()->RemoveGameObject<WoodenBox>(ptrWoodBox);
					//�T�E���h�Đ�
					auto& ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"WoodBoxBreak", 0, 1.0f);
					
				}
			}
		}
	}

	//!���l��|������
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_villagerkillerSphereRadius);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();
		int alertlevelCount = scene->GetAlertlevelCount();
		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");
		auto& vecVillager = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecVillager)
		{
			auto VillagerPtr = v.lock();//!���l�̃O���[�v����1���b�N����
			Vec3 ret;//!�ŋߐړ_�̑��
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������
			if (ptrVillager)
			{
				auto VillagerCapsrul = ptrVillager->GetComponent<CollisionCapsule>()->GetCapsule();//!�n���^-��Obb�I�u�W�F�N�g���擾
				if (HitTest::SPHERE_CAPSULE(playerSp, VillagerCapsrul, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				{
					
					auto VillagerSpeed = ptrVillager->GetSpeed();//!���l�̃X�s�[�h���擾
					if (VillagerSpeed != m_Ded)
					{
						VillagerSpeed = m_Ded;//!���l�̃X�s�[�h���O�ɂ���
						ptrVillager->SetSpeed(VillagerSpeed);//!���l�̃X�s�[�h��ݒ�
						alertlevelCount++;
						scene->SetAlertlevelCount(alertlevelCount);

						//�T�E���h�Đ�
						EnemyDedSound();
					}
				}
			}
		}
	}
	
	//!���݂̃|�W�V�������擾����
	void Player::GetPlayerPositionBrett()
	{
		
		
		auto PlayerTrans = GetComponent<Transform>();//!�v���C���[�̃g�����X�t�H�[�����擾
		auto PlayerPosition = PlayerTrans->GetPosition();//!�v���C���[�̃|�W�V�������擾
		auto Time = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C�����擾
		m_PlayerPositionTime += Time;//!���Ԃ̍쐬

		//!�v���C���[���|�W�V������ۑ����鎞��
		if (m_PlayerPositionTime >= m_GetPlayerPositionTime)
		{
			m_PlayerPositionOnSecond.push_back(PlayerPosition);//!�|�W�V������ۑ�

			//!��萔�ۑ�������
			if (m_PlayerPositionOnSecond.size() >= m_PlayerPositionOnSecondMax)
			{
				//!�Â������폜����
				m_PlayerPositionOnSecond.erase(m_PlayerPositionOnSecond.begin());
			}
		}
	}

	void Player::Escape()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_escapeSphereRadius);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");
		Vec3 ret;
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();
			XAptr->Stop(m_Wolk);
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!�Q�[���N���A�X�e�[�W�ɑJ��
		}
	}

	

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);
	}

	//!�R���g���[���̐U������
	void Player::Controllervibration()
	{
		

		//!�U�����I���ɂȂ��Ă���Ƃ�
		if (m_IsvibrationOn == true)
		{
			auto Time = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
			m_vibrationTime += Time;
             m_vibration = m_maxVibration;
			
			if (m_vibrationTime >= m_vibrationMaxTime)
			{
				
				m_IsvibrationOn = false;
			}
		}
		if (m_IsvibrationOn == false)
		{
			m_vibrationTime = 0.0f;
			m_vibration = 0;
		}

		//�R���g���[���[�̐U��
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = m_vibration; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = m_vibration; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}

	//�X�V
	void Player::OnUpdate() {

		
		if (m_playerChange == static_cast<int>(PlayerModel::human))
		{
			//!�v���C���[�����������Ă�����
			if (m_KeyCount == m_MaxKeyCount)
			{
				Escape();
			}
		}

		m_StateMachine->Update();

		OneWeek();

		Controllervibration();

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		auto gameTime = scene->GetGameTime();
		m_gameTime += gameTime;

		
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);

		
		
		auto playerChange = scene->GetPlayerChangeDirecting();//!�v���C���[�̕ϐg���J�n����
		auto gameStrat = scene->GetGameStrat();
	
		//!�Q�[���I�[�o�[�ɂȂ��ĂȂ�����
		if (!gameOver)
		{
			GetPlayerPositionBrett();
			
			if (!playerChange)
			{
				if (!gameStrat)
				{
					MovePlayer();
				}

			}

			if(playerChange|| gameStrat)
			{
				auto& XAptr = App::GetApp()->GetXAudio2Manager();
				XAptr->Stop(m_Wolk);
			}
				

		}
		

		if (m_IsPlayerDed == true)
		{
			PlayerDed();
		}


		

		if (m_PlayerHp == m_Ded)
		{
			PlayerGameOver();
		}
            m_InputHandlerB.PushHandleB(GetThis<Player>());//!B�{�^���̃C���v�b�g�n���h���̒ǉ�
	    }



	//!�v���C���[������ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{

		auto ptrKey = dynamic_pointer_cast<Key>(Other);

		if (m_playerChange == static_cast<int>(PlayerModel::wolf))
		{
			//!�v���C���[�����ɓ���������
			if (ptrKey)
			{
				m_KeyCount++;
				GetStage()->RemoveGameObject<Key>(Other);//!���I�u�W�F�N�g�̍폜
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"acquisition", 0, 9.0f);

				//�G�t�F�N�g�̃v���C
				auto Ptr = ptrKey->GetComponent<Transform>();
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
				m_KeyEfkPlay = ObjectFactory::Create<EfkPlay>(m_KeyEfkEffect, Ptr->GetPosition());

			}


		}

		auto ptrMeat = dynamic_pointer_cast<Meat>(Other);

		if (m_playerChange == static_cast<int>(PlayerModel::human))
		{
			//!�v���C���[�����ɓ���������
			if (ptrMeat)
			{
				m_meatCount++;
				GetStage()->RemoveGameObject<Meat>(Other);//!���I�u�W�F�N�g�̍폜
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"MeatEat", 0, 9.0f);
                //�G�t�F�N�g�̃v���C
				auto Ptr = GetComponent<Transform>();
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
				m_MeatEfkPlay = ObjectFactory::Create<EfkPlay>(m_MeatEfkEffect, Ptr->GetPosition());
				auto manager=ShEfkInterface->GetManager();
				
			}


		}

	}

	void Player::AttackEffect()
	{
		//�G�t�F�N�g�̃v���C
		auto Ptr = GetComponent<Transform>();
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		auto playerPosition = Ptr->GetPosition();
		m_ScratchEfkPlay = ObjectFactory::Create<EfkPlay>(m_ScratchEfkEffect, playerPosition);
	}

	void Player::OnPushB()
	{
		

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		//!�Q�[���I�[�o�[�ɂȂ��ĂȂ�����
		if (gameOver == false)
		{
			if (m_playerChange == static_cast<int>(PlayerModel::wolf))
			{
				Villagerkiller();//!���l��|������
				Hunterkiller();//!�n���^�[��|������
				BreakWoodBox();//!�{�b�N�X����
				AttackEffect();//!�U���G�t�F�N�g���o��
			}

			

		}
	}
}
//end basecross

