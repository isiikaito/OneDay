/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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
		m_Ded(0),
		m_GetPlayerPositionTime(0.8f),
		m_PlayerPositionTime(0.0f),
		m_PlayerPositionOnSecondMax(39),
		m_PlayerHp(3),
		m_IsPlayerFound(false)

	{}

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
			auto ptrCamera = OnGetDrawCamera();

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
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//!��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}

	//!������
	void Player::OnCreate() {

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

		shadowPtr->SetMeshResource(L"PLAYER_HUMAN");//!�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g�̐ݒ�

		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"PLAYER_HUMAN");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		/*ptrDraw->SetFogEnabled(true);*/
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		
		//!�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());//!MyCamera�ł���
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));//!MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
		}
	}

	void Player::AppearanceChange()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		m_ChangeTime += elapsedTime;//���Ԃ�ϐ��ɑ���
		if (m_ChangeTime >= m_humanTime)//!�l�Ԃ̎��Ԃ��I�������
		{

			m_playerChange = static_cast<int>(PlayerModel::wolf);//!��Ԃ�T�ɂ���

			auto ptrDraw = GetComponent<PNTStaticModelDraw>();//!�v���C���[�̕`��R���|�\�l���g���擾
			auto shadowPtr = GetComponent<Shadowmap>();
			ptrDraw->SetMeshResource(L"PLAYER_Wolf");//!�v���C���[�̃��b�V���̕ύX
			shadowPtr->SetMeshResource(L"PLAYER_Wolf");
			ptrDraw->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));
			if (m_ChangeTime >= m_wolfTime)//!�T�̎��ԂɂȂ�����
			{
				ptrDraw->SetMeshResource(L"PLAYER_HUMAN");//!�v���C���[�̃��b�V���̕ύX
				shadowPtr->SetMeshResource(L"PLAYER_HUMAN");
				m_playerChange = static_cast<int>(PlayerModel::human);//!�v���C���[�̏�Ԃ͐l��
				ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
				/*ptrDraw->SetMeshResource(L"PLAYER_HUMAN");*///!�v���C���[�̃��b�V���̕ύX
				m_ChangeTime = (float)m_reset;//!��ԃ^�C�������Z�b�g����
			}
			return;

		}
	}


	//!���l��|������
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, 10.0f);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬

		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		auto vecHnter = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!�n���^�[�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecHnter)
		{
			auto HunterPtr = v.lock();//!�n���^�[�̃O���[�v����1���b�N����
			Vec3 ret;//!�ŋߐړ_�̑��
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!�n���^-��Obb�I�u�W�F�N�g���擾
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				{
					
					auto HunterDedDecision = ptrHunter->GetDedDecision();//!�n���^�[�̐����̔���̎擾
					HunterDedDecision = true;//!�n���^�[�̐��������ɂ���
					ptrHunter->SetDedDecision(HunterDedDecision);//!�n���^�[�̐����̐ݒ�
					auto HunterSpeed = ptrHunter->GetSpeed();//!�n���^�[�̃X�s�[�h���擾
					if (!HunterSpeed == m_Ded)
					{
                    HunterSpeed = m_Ded;//!�n���^�[�̃X�s�[�h���O�ɂ���
					ptrHunter->SetSpeed(HunterSpeed);//!�n���^�[�̃X�s�[�h��ݒ�
					auto HunterDraw = ptrHunter->GetComponent<PNTStaticModelDraw>();//!�n���^�[�̕`��R���|�[�l���g���擾
					HunterDraw->SetDiffuse(Col4(1, 0, 0, 1));//!�n���^�[�̐F�̐ݒ�
					m_PlayerHp--;
					}
					

				}
			}
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

	

	//�X�V
	void Player::OnUpdate() {
		//!�G�̐e�N���X���擾�ł���
		
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
		

		MovePlayer();
		AppearanceChange();//!�v���C���[�̎p�ω�
		m_InputHandlerB.PushHandleB(GetThis<Player>());//!B�{�^���̃C���v�b�g�n���h���̒ǉ�

	}

	//!�v���C���[������ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrKey = dynamic_pointer_cast<Key>(Other);
		//!�v���C���[�����ɓ���������
		if (ptrKey)
		{
			m_KeyCount++;
			GetStage()->RemoveGameObject<Key>(Other);//!���I�u�W�F�N�g�̍폜
			CreateKeySprite();
		}
		
		//!�v���C���[�����������Ă�����
			if (m_KeyCount == m_MaxKeyCount)
			{
				auto ptrGate = dynamic_pointer_cast<StageGate>(Other);//!��̃I�u�W�F�N�g�擾
				if (ptrGate)//!�v���C���[����ɓ���������
				{
					PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!�Q�[���N���A�X�e�[�W�ɑJ��
				}
			}
	}
	void Player::OnPushB()
	{
		if (m_playerChange == static_cast<int>(PlayerModel::wolf))
		{
          Villagerkiller();//!���l��|������
		}
		
	}
}
//end basecross

