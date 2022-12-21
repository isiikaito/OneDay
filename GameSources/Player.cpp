/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerState.h"

namespace basecross {
	constexpr float m_maxDisappearTime = 2.0f;
	constexpr float m_MaxwolfHowlingTime = 0.1f;
	constexpr float m_maxDedTime = 1.0f;

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
		m_disappearTime(0.0f),
		m_IsPlayerDed(0.0f),
		m_gameOverDrawActive(false),
		m_vibration(0.0f),
		m_gameTime(0.0f)
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());
	}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//!�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
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
			if (AnimationName == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//�������Đ�
				auto XAptr = App::GetApp()->GetXAudio2Manager();
				m_BGM = XAptr->Start(L"WalkBGM", 0, 1.0f);
			}
		}
		else {
			//�����~�܂�A�j���[�V����
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto XAptr = App::GetApp()->GetXAudio2Manager();
				XAptr->Stop(m_BGM);


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
		wstring TestEffectStr = DataDir + L"Effects\\test1.efk";//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();//!�G�t�F�N�g�̃C���^�[�t�F�[�X�̎擾
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);//!�擾�����G�t�F�N�g�ō��

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

		shadowPtr->SetMeshResource(L"Player_WalkAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̐ݒ�

		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"Player_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 20.0f);
		ptrDraw->AddAnimation(L"Default", 31, 30, true, 10.0f);
		ptrDraw->AddAnimation(L"Ded", 61, 30, false, 30.0f);
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
		GetStage()->AddGameObject<FadeOut>(true,
			Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.1f));
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
		auto AnimationName = ptrDraw->GetCurrentAnimation();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//�����~�܂�A�j���[�V����
		if (AnimationName == L"Move" || AnimationName == L"Default")
		{
			ptrDraw->ChangeCurrentAnimation(L"Ded");
			auto XAptr = App::GetApp()->GetXAudio2Manager();
			XAptr->Stop(m_BGM);

		}

		PlayerGameOver();
	}

	void Player::EnmeyDisappear()
	{
		auto position = GetComponent<Transform>()->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, 50);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");
		auto& vecHnter = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecHnter)
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
					auto VillagerDedDecision = ptrVillager->GetDedDecision();//!���l�̐����̔���̎擾
					ptrVillager->SetDedDecision(VillagerDedDecision);//!���l�̐����̐ݒ�
					auto VillagerSpeed = ptrVillager->GetSpeed();//!���l�̃X�s�[�h���擾
					if (VillagerSpeed == m_Ded)
					{
						float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
						m_disappearTime += elapsedTime;//���Ԃ�ϐ��ɑ���
						if (m_disappearTime >= m_maxDisappearTime)
						{
							GetStage()->RemoveGameObject<Villager>(VillagerPtr);
							m_disappearTime = 0;
						}
					}


				}
			}
		}
	}

	//!���l��|������
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, 5.0f);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();
		int alertlevelCount = scene->GetAlertlevelCount();
		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");
		auto& vecHnter = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecHnter)
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
					auto VillagerDedDecision = ptrVillager->GetDedDecision();//!���l�̐����̔���̎擾
					VillagerDedDecision = true;//!���l�̐��������ɂ���

					ptrVillager->SetDedDecision(VillagerDedDecision);//!���l�̐����̐ݒ�
					auto VillagerSpeed = ptrVillager->GetSpeed();//!���l�̃X�s�[�h���擾
					if (VillagerSpeed != m_Ded)
					{
						VillagerSpeed = m_Ded;//!���l�̃X�s�[�h���O�ɂ���
						ptrVillager->SetSpeed(VillagerSpeed);//!���l�̃X�s�[�h��ݒ�
						alertlevelCount++;
						scene->SetAlertlevelCount(alertlevelCount);

						//�T�E���h�Đ�
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						ptrXA->Start(L"kill", 0, 9.0f);
						ptrXA->Start(L"scream", 0, 9.0f);
					}
				}
			}
		}
	}

	void Player::GetPlayerPositionBrett()
	{
		

		auto PlayerTrans = GetComponent<Transform>();
		auto PlayerPosition = PlayerTrans->GetPosition();
		auto Time = App::GetApp()->GetElapsedTime();
		m_PlayerPositionTime += Time;

		if (m_PlayerPositionTime >= m_GetPlayerPositionTime)
		{
			m_PlayerPositionOnSecond.push_back(PlayerPosition);

			if (m_PlayerPositionOnSecond.size() >= m_PlayerPositionOnSecondMax)
			{
				m_PlayerPositionOnSecond.erase(m_PlayerPositionOnSecond.begin());
			}
		}
	}

	void Player::Escape()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, 10.0f);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");
		Vec3 ret;
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
		{
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!�Q�[���N���A�X�e�[�W�ɑJ��
		}
	}

	//!���̃X�v���C�g�̍쐬
	void Player::CreateKeySprite()
	{
		GetStage()->AddGameObject<KeySprite>(
			L"KEY_TX",//!�e�N�X�`��
			true,
			Vec2(150.0f, 150.0f),//�傫��
			Vec2(300.0f + (100.0f * (m_KeyCount - 1)), -320.0f)//���W
			);
	}

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);
	}

	//�X�V
	void Player::OnUpdate() {

		m_StateMachine->Update();

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		auto gameTime = scene->GetGameTime();
		m_gameTime += gameTime;

		//!�G�̐e�N���X���擾�ł���
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);

		
		//!�Q�[���I�[�o�[�ɂȂ��ĂȂ�����
		if (gameOver == false)
		{
        GetPlayerPositionBrett();
		EnmeyDisappear();
		 MovePlayer();
    
		
		//�R���g���[���[�̐U��
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = m_vibration; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = m_vibration; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
		
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
				CreateKeySprite();
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"acquisition", 0, 9.0f);
			}


		}


	}
	void Player::OnPushB()
	{

		auto Ptr = GetComponent<Transform>();
		//�G�t�F�N�g�̃v���C
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, Ptr->GetPosition());

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		//!�Q�[���I�[�o�[�ɂȂ��ĂȂ�����
		if (gameOver == false)
		{
			if (m_playerChange == static_cast<int>(PlayerModel::wolf))
			{
				Villagerkiller();//!���l��|������
			}

			if (m_playerChange == static_cast<int>(PlayerModel::human))
			{
				//!�v���C���[�����������Ă�����
				if (m_KeyCount == m_MaxKeyCount)
				{
					Escape();
				}
			}

		}
	}
}
//end basecross

