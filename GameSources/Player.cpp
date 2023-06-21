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
	constexpr float m_maxDedTime = 1.0f;			    //!�|���܂ł̎���
	constexpr float m_vibrationMaxTime = 1.0f;			//!�U�����鎞��
	constexpr int m_Day = 7;							//!�Q�[���I�[�o�[�܂ł̓��ɂ�
	constexpr int m_soundLoop = 1;						//!���̃��[�v
	constexpr int m_notsoundLoop = 0;					//!�T�E���h���[�v����
	constexpr float m_escapeSphereRadius = 10.0f;		//!�v���C���[�𒆐S�Ƃ����~�̔��a
	constexpr float m_villagerkillerSphereRadius = 5.0f;//!���l��|�����̉~�̔��a
	constexpr float m_breakWoodBoxSphereRadius = 5.0f;	//!�ؔ���|�����̉~�̔��a
	constexpr float m_hunterkillerSphereRadius = 5.0f;	//!�n���^�[��|�����̉~�̔��a
	constexpr float m_angleEqual = 6.0f;				//!����̐���
	constexpr float m_rotToHead = 1.0f;					//!����
	constexpr float m_targetToAtY = 0.25f;				//!�J�����̎��_�ʒu��y
	constexpr WORD  m_maxVibration = 65535;				//!�U���̑傫��
	constexpr int m_movestartSample = 0;				//!�����A�j���[�V�����̊J�n�t���[��
	constexpr int m_movesampleLength = 30;				//!�����A�j���[�V�����̒���
	constexpr float m_movesamplesParSecond = 20.0f;		//!�����A�j���[�V�����̍Đ����x
	constexpr int m_defaultstartSample = 31;			//!�ҋ@�A�j���[�V�����̊J�n�t���[��
	constexpr int m_defaultsampleLength = 30;			//!�ҋ@�A�j���[�V�����̒���
	constexpr float m_defaultsamplesParSecond = 10.0f;	//!�ҋ@�A�j���[�V�����̍Đ����x
	constexpr int m_dedstartSample = 61;				//!�|���A�j���[�V�����̊J�n�t���[��
	constexpr int m_dedsampleLength = 45;				//!�|���A�j���[�V�����̒���
	constexpr float m_dedsamplesParSecond = 30.0f;		//!�|���A�j���[�V�����̍Đ����x
	constexpr int m_changestartSample = 91;				//!�ϐg�A�j���[�V�����̊J�n�t���[��
	constexpr int m_changesampleLength = 60;			//!�ϐg�A�j���[�V�����̒���
	constexpr float m_changesamplesParSecond = 30.0f;	//!�ϐg�A�j���[�V�����̍Đ����x
	

	

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
		m_IsPlayerChangeEffect(true),
		m_scale(Vec3(3.0f, 3.0f, 3.0f)),
		m_rotation(Vec3(0.0f, 0.0f, 0.0f)),
		m_position(Vec3(0.0f, 4.0f, -90.0f))
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());	//!���݂̃X�e�[�g
	}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//!�R���g���[���̎擾
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		//!�ڑ�����Ă���R���g���[��
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;//!���X�e�B�b�Nx���W
			ret.y = cntlVec[0].fThumbLY;//!���X�e�B�b�Ny���W
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
			float moveLength = 0;											//!���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();					//!�g�����X�t�H�[���̎擾
			auto& ptrCamera = OnGetDrawCamera();							//!�J�����̎擾
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();	//!�i�s�����̌������v�Z
			front.y = 0;
			front.normalize();												//!�i�s�����̌����𐳋K��
			float frontAngle = atan2(front.z, front.x);						//!�i�s������������̊p�x���Z�o
			Vec2 moveVec(moveX, moveZ);										//!�R���g���[���̌����v�Z
			float moveSize = moveVec.length();								//!�����傫��
			float cntlAngle = atan2(-moveX, moveZ);							//!�R���g���[���̌�������p�x���v�Z
			float totalAngle = frontAngle + cntlAngle;						//!�g�[�^���̊p�x���Z�o
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));				//!�p�x����x�N�g�����쐬
			angle.normalize();												//!���K������
			angle *= moveSize;												//!�ړ��T�C�Y��ݒ�
			angle.y = 0;													//!Y���͕ω������Ȃ�
		}
		return angle;
	}

	
	void Player::MovePlayer() {

		
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();			 //�A�j���[�V����
		auto& AnimationName = ptrDraw->GetCurrentAnimation();			 //!���݂̃A�j���[�V����
		float elapsedTime = App::GetApp()->GetElapsedTime();			 //!�G���p�\�^�C���̎擾
		auto angle = GetMoveVector();									 //!�x�N�g���̎擾
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʉ���
		//!�X�e�B�b�N���X���Ă�����
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();		 //!���g�̃|�W�V�����̎擾
			pos += angle * elapsedTime * m_Speed;						 //!�|�W�V�����̍X�V
			GetComponent<Transform>()->SetPosition(pos);				 //!�|�W�V�����̐ݒ�

			//�����A�j���[�V����
			//!�ҋ@���[�V�������ϐg���[�V�����̎�
			if (AnimationName == L"Default" || AnimationName == L"Change") {
				ptrDraw->ChangeCurrentAnimation(L"Move");				//!�A�j���[�V������ς���
				auto& XAptr = App::GetApp()->GetXAudio2Manager();		//!�T�E���h�}�l�[�W���[�̎擾
				m_Wolk = XAptr->Start(L"WalkBGM", m_soundLoop, volume);	//�������Đ�
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
			utilPtr->RotToHead(angle, m_rotToHead);		//!���ʂ�����
		}
	}

	//!������
	void Player::OnCreate() {

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring keyEffectStr = DataDir + L"Effects\\key.efk";										//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		auto EfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();							//!�G�t�F�N�g�̃C���^�[�t�F�[�X�̎擾
		m_KeyEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, keyEffectStr);				//!�擾�����G�t�F�N�g�ō��

		wstring ScratchEffectStr = DataDir + L"Effects\\kill.efk";									//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		m_ScratchEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, ScratchEffectStr);		//!�擾�����G�t�F�N�g�ō��

		wstring TransformEffectStr = DataDir + L"Effects\\Transform2.efk";							//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		m_TransformEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, TransformEffectStr);	//!�擾�����G�t�F�N�g�ō��

		wstring MeatEffectStr = DataDir + L"Effects\\smoke.efk";									//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		m_MeatEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, MeatEffectStr);			//!�擾�����G�t�F�N�g�ō��


		//!�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_scale);			//!�傫��
		ptr->SetRotation(m_rotation);	//!��]
		ptr->SetPosition(m_position);	//!�ʒu


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),		//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),		//!��]
			Vec3(0.0f, -1.0f, 0.0f)		//!�ʒu
		);

		auto ptrColl = AddComponent<CollisionCapsule>();																//!CollisionSphere�Փ˔����t����
		auto ptrGra = AddComponent<Gravity>();																			//!�d�͂�����
		auto shadowPtr = AddComponent<Shadowmap>();																		//!�e������i�V���h�E�}�b�v��`�悷��j
		shadowPtr->SetMeshResource(L"Player_WalkAnimation2_MESH");														//!�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshToTransformMatrix(spanMat);																	//!���b�V���̑傫���ݒ�
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();															//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetMeshResource(L"Player_WalkAnimation2_MESH_WITH_TAN");												//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);																		//!���b�V���̑傫���ݒ�
		ptrDraw->AddAnimation(L"Move", m_movestartSample, m_movesampleLength, true, m_movesamplesParSecond);			//!�����A�j���[�V�����̓o�^
		ptrDraw->AddAnimation(L"Default", m_defaultstartSample, m_defaultsampleLength, true, m_defaultsamplesParSecond);//!�ҋ@�A�j���[�V�����̓o�^
		ptrDraw->AddAnimation(L"Ded", m_dedstartSample, m_dedsampleLength, false, m_dedsamplesParSecond);				//!�|���A�j���[�V�����̓o�^
		ptrDraw->AddAnimation(L"Change", m_changestartSample, m_changesampleLength, false, m_changesamplesParSecond);	//!�ϐg�A�j���[�V�����̓o�^
		ptrDraw->ChangeCurrentAnimation(L"Default");																	//!���݂̃A�j���[�V�����̐ݒ�
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");														//!�@���}�b�v�̐ݒ�

		

			//!�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());	//!MyCamera�ł���
			ptrCamera->SetTargetToAt(Vec3(0, m_targetToAtY, 0));//!MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
		}
	}

	

	void Player::PlayerGameOver()
	{
		auto scene=App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto gameOver = scene->GetGameOver();		//!�Q�[���I�[�o�[����̎擾
		gameOver = true;							//!�Q�[���I�[�o�[�ɂ���
		scene->SetGameOver(gameOver);				//!�Q�[���I�[�o�[�ɂ���

		
		float Time = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		m_dedTime += Time;							 //!�|��鎞�Ԃɉ��Z
		//!�|��鎞�ԂɂȂ�����
		if (m_dedTime >= m_maxDedTime)
		{
			m_gameOverDrawActive = true;			//!�Q�[���I�[�o�[��ʂ�\��
		}

	}

	void Player::PlayerDed()
	{
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();	//!�`��R���|�[�l���g�̎擾
		auto& AnimationName = ptrDraw->GetCurrentAnimation();	//!���݂̃A�j���[�V�����̎擾
		float elapsedTime = App::GetApp()->GetElapsedTime();	//!�G���p�\�^�C���̎擾

		//�����~�܂�A�j���[�V����
		if (AnimationName == L"Move" || AnimationName == L"Default")
		{
			ptrDraw->ChangeCurrentAnimation(L"Ded");			//!�A�j���[�V������Ded�ɕύX
			auto& XAptr = App::GetApp()->GetXAudio2Manager();	//!�T�E���h�}�l�[�W���[�̎擾
			XAptr->Stop(m_Wolk);								//!�����T�E���h���~�߂�

		}
		PlayerGameOver();
	}

	

	void Player::EnemyDedSound()
	{
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʉ��ʂ̎擾
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();				 //!�T�E���h�}�l�[�W���[�̎擾
		ptrXA->Start(L"kill", m_notsoundLoop, volume);					 //!�|�����Ƃ��̃T�E���h�̊J�n
		ptrXA->Start(L"scream", m_notsoundLoop, volume);				 //!�U���̃T�E���h�̊J�n
	}

	void Player::Hunterkiller()
	{
		auto transComp = GetComponent<Transform>();						  //!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();						  //!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_hunterkillerSphereRadius);			  //!�v���C���[�̍��W�𒆐S�ɔ��a5�Z���`�̉~�̍쐬
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
			auto HunterTrans = GetComponent<Transform>();				 //!�n���^�[�̃g�����X�t�H�[���̎擾
			auto HunterPosition = HunterTrans->GetPosition();            //!�n���^�[�̃|�W�V�����̎擾
			Vec3 PEvector = position - HunterPosition;					 //!�v���C���[�ƓG�̃x�N�g�����擾
			PEvector.normalize();										 //!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto Enemyfront = HunterTrans->GetForword();				 //!�G�̐��ʂ��擾
			auto angle = angleBetweenNormals(-Enemyfront, PEvector);     //!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / m_angleEqual;							 //!360��6�Ŋ����Ċp�x���o���B
		

			//!�v���C���[�͈̔͂ɓG���͂�������
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!�n���^-��Obb�I�u�W�F�N�g���擾
                
				//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))
				{
					
						auto HunterSpeed = ptrHunter->GetSpeed();//!���l�̃X�s�[�h���擾
						//!�n���^�[�̑��x��0�ł͂Ȃ��Ƃ�
						if (HunterSpeed != m_Ded)
						{
							HunterSpeed = m_Ded;						//!���l�̃X�s�[�h���O�ɂ���
							ptrHunter->SetSpeed(HunterSpeed);			//!���l�̃X�s�[�h��ݒ�
							alertlevelCount++;							//!�댯�x���グ��
							scene->SetAlertlevelCount(alertlevelCount); //!�댯�x���X�V
							EnemyDedSound();
						}
					
				}
			}

		}
	}

	void Player::OneWeek()
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
		auto Date = scene->GetDate();					//!���t�̎擾
		//!�Q�[���I�[�o�[�̓��t�ɂȂ�����
		if (Date == m_Day)
		{
			PlayerGameOver();//!�Q�[���I�[�o�[
		}

	}

	void Player::BreakWoodBox()
	{
		auto transComp = GetComponent<Transform>();							//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();							//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_breakWoodBoxSphereRadius);				//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
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
				auto WoodBoxOBB = ptrWoodBox->GetComponent<CollisionObb>()->GetObb();//!�n���^-��Obb�I�u�W�F�N�g���擾
				//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				if (HitTest::SPHERE_OBB(playerSp, WoodBoxOBB, ret))					 
				{
					auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʉ��ʂ̎擾
					GetStage()->RemoveGameObject<WoodenBox>(ptrWoodBox);			 //!�ؔ�������
					
					auto& ptrXA = App::GetApp()->GetXAudio2Manager();				 //�T�E���h�Đ�
					ptrXA->Start(L"WoodBoxBreak", m_notsoundLoop, volume);
					
				}
			}
		}
	}

	//!���l��|������
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();							//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();							//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_villagerkillerSphereRadius);			//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
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
					
					auto VillagerSpeed = ptrVillager->GetSpeed();									//!���l�̃X�s�[�h���擾
					//!���l�̑��x����~���Ă��Ȃ�������
					if (VillagerSpeed != m_Ded)
					{
						VillagerSpeed = m_Ded;						//!���l�̃X�s�[�h���O�ɂ���
						ptrVillager->SetSpeed(VillagerSpeed);		//!���l�̃X�s�[�h��ݒ�
						alertlevelCount++;							//!�댯�x���グ��
						scene->SetAlertlevelCount(alertlevelCount); //!�댯�x��ݒ�

						EnemyDedSound();
					}
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
		auto transComp = GetComponent<Transform>();						//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();						//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, m_escapeSphereRadius);				//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");//!����擾
		Vec3 ret;														//!�ŋߐړ_�̑��
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();	//!�R���W�����̏Փ˔���
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))				//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();			//!�T�E���h�}�l�[�W���[�̎擾
			XAptr->Stop(m_Wolk);										//!�������̒�~
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!�Q�[���N���A�X�e�[�W�ɑJ��
		}
	}

	

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!�X�e�[�g��ύX����
	}

	
	void Player::Controllervibration()
	{
		

		//!�U�����I���ɂȂ��Ă���Ƃ�
		if (m_IsvibrationOn == true)
		{
			auto Time = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
			m_vibrationTime += Time;					//!�U�������鎞��
             m_vibration = m_maxVibration;				//!���݂̐U���̑傫��
			//!�U�����鎞�Ԍo������
			if (m_vibrationTime >= m_vibrationMaxTime)
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

		m_StateMachine->Update();							//!�X�e�[�g�}�V���̍X�V
		OneWeek();
		Controllervibration();
		auto scene = App::GetApp()->GetScene<Scene>();		//!�V�[���̎擾
		auto gameOver = scene->GetGameOver();				//!�Q�[���I�[�o�[���ǂ����̎擾
		auto gameTime = scene->GetGameTime();				//!�Q�[�����Ԃ̎擾
		m_gameTime += gameTime;								//!���Ԃ̉��Z

		
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);				//!�A�j���[�V�����̍X�V

		
		
		auto playerChange = scene->GetPlayerChangeDirecting();//!�v���C���[�̕ϐg���J�n����
		auto gameStrat = scene->GetGameStrat();				  //!�I�[�v�j���O�J�����̎����ǂ���
	
		//!�Q�[���I�[�o�[�ɂȂ��ĂȂ�����
		if (!gameOver)
		{
			GetPlayerPositionBrett();
			//!�v���C���[���ϐg���Ă��Ȃ���
			if (!playerChange)
			{
				//!�I�[�v�j���O�J�����ł͂Ȃ���
				if (!gameStrat)
				{
					MovePlayer();
				}

			}
			//!�ϐg���Ă��邩�I�[�v�j���O�J�����̎�
			if(playerChange|| gameStrat)
			{
				auto& XAptr = App::GetApp()->GetXAudio2Manager();//!�T�E���h�}�l�[�W���[�̎擾
				XAptr->Stop(m_Wolk);							 //!���������~�߂�
			}
				
		}
		
		//!�v���C���[���|�ꂽ��
		if (m_IsPlayerDed == true)
		{
			PlayerDed();
		}

		//!HP�������Ȃ����Ƃ�
		if (m_PlayerHp == m_Ded)
		{
			PlayerGameOver();
		}
            m_InputHandlerB.PushHandleB(GetThis<Player>());//!B�{�^���̃C���v�b�g�n���h���̒ǉ�
	    }



	//!�v���C���[������ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		
		auto ptrKey = dynamic_pointer_cast<Key>(Other);//!���̎擾

		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʉ��ʂ̎擾
		if (m_playerChange == static_cast<int>(PlayerModel::wolf))
		{
			//!�v���C���[�����ɓ���������
			if (ptrKey)
			{

				m_KeyCount++;																		//!���̃J�E���g
				GetStage()->RemoveGameObject<Key>(Other);											//!���I�u�W�F�N�g�̍폜
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!�T�E���h�}�l�[�W���[�̎擾
				ptrXA->Start(L"acquisition", m_notsoundLoop, volume);								//!�T�E���h�̍Đ�
				auto Ptr = ptrKey->GetComponent<Transform>();										//!�G�t�F�N�g�̃v���C
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					//!�G�t�F�N�g�C���^�[�t�F�[�X�̎擾
				m_KeyEfkPlay = ObjectFactory::Create<EfkPlay>(m_KeyEfkEffect, Ptr->GetPosition());	//!�G�t�F�N�g�̃|�W�V����

			}


		}

		auto ptrMeat = dynamic_pointer_cast<Meat>(Other);//!���̎擾

		if (m_playerChange == static_cast<int>(PlayerModel::human))
		{
			//!�v���C���[�����ɓ���������
			if (ptrMeat)
			{
				m_meatCount++;
				GetStage()->RemoveGameObject<Meat>(Other);											//!���I�u�W�F�N�g�̍폜
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!�T�E���h�}�l�[�W���[�̎擾
				ptrXA->Start(L"MeatEat", m_notsoundLoop, volume);									//!����H�ׂ�T�E���h�̍Đ�
				auto Ptr = GetComponent<Transform>();												//!�g�����X�t�H�[���̎擾
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					//!�G�t�F�N�g�C���^�[�t�F�[�X�̎擾
				m_MeatEfkPlay = ObjectFactory::Create<EfkPlay>(m_MeatEfkEffect, Ptr->GetPosition());//!�G�t�F�N�g�̍쐬
				auto manager=ShEfkInterface->GetManager();											//!�}�l�[�W���[�̎擾
				
			}


		}

	}

	void Player::AttackEffect()
	{
		//�G�t�F�N�g�̃v���C
		auto Ptr = GetComponent<Transform>();                                                 //!�g�����X�t�H�[���̎擾
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					  //!�G�t�F�N�g�C���^�[�t�F�[�X�̎擾 
		auto playerPosition = Ptr->GetPosition();											  //!�v���C���[�̃|�W�V�����̎擾 
		m_ScratchEfkPlay = ObjectFactory::Create<EfkPlay>(m_ScratchEfkEffect, playerPosition);//!�G�t�F�N�g�̍쐬
	}																						  
																							   
	void Player::OnPushB()																	   
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
		auto gameOver = scene->GetGameOver();			//!�Q�[���I�[�o�[�̎擾
		//!�Q�[���I�[�o�[�ɂȂ��ĂȂ�����
		if (gameOver == false)
		{
			//!�I�I�J�~�̎p�ɂȂ����Ƃ�
			if (m_playerChange == static_cast<int>(PlayerModel::wolf))
			{
				Villagerkiller();
				Hunterkiller();
				BreakWoodBox();
				AttackEffect();
			}

		}
	}
}
//end basecross

