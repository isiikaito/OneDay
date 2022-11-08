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
		m_idleTime(0.0f),
		m_playerChange(static_cast<int>(PlayerModel::human)),
		m_humanTime(31.0f),
		m_wolfTime(61.0f),
		m_reset(0),
		m_KeyCount(0)
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
		ptr->SetScale(2.0f, 2.0f, 2.0f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(10.0f, 10.0f, -70.0f));


		auto ptrColl = AddComponent<CollisionCapsule>();//!CollisionSphere�Փ˔����t����


		auto ptrGra = AddComponent<Gravity>();//!�d�͂�����

		//!�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));


		auto shadowPtr = AddComponent<Shadowmap>();//!�e������i�V���h�E�}�b�v��`�悷��j

		shadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");//!�e�̌`�i���b�V���j��ݒ�


		auto ptrDraw = AddComponent<BcPNTStaticDraw>();//!�`��R���|�[�l���g�̐ݒ�

		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetFogEnabled(true);


		//!�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {


			ptrCamera->SetTargetObject(GetThis<GameObject>());//!MyCamera�ł���
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));//!MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
		}
	}

	//!�v���C���[�̎p�ω�
	void Player::AppearanceChange()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		m_idleTime += elapsedTime;//���Ԃ�ϐ��ɑ���
		if (m_idleTime >= m_humanTime)
		{

			m_playerChange = static_cast<int>(PlayerModel::wolf);
			auto transComp = AddComponent<Transform>();
			auto ptrDraw = AddComponent<BcPNTStaticDraw>();
			ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
			if (m_idleTime >= m_wolfTime)
			{
				m_playerChange = static_cast<int>(PlayerModel::human);//!�v���C���[�̏�Ԃ͐l��

				ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
				m_idleTime = m_reset;
			}
			return;

		}
	}

	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();//!�g�����X�t�H�[�����擾
		auto position = transComp->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE playerSp(position, 10.0f);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬

		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		auto vecHnter = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		for (auto& v : vecHnter)
		{
			auto HunterPtr = v.lock();
			Vec3 ret;
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);
		
			if (ptrHunter)
			{
				auto HunterObb = ptrHunter->GetComponent<CollisionObb>()->GetObb();
				if (HitTest::SPHERE_OBB(playerSp, HunterObb, ret))
				{
					GetStage()->RemoveGameObject<Hunter>(HunterPtr);

		   }
			}
		}
	}
	//�X�V
	void Player::OnUpdate() {

		m_InputHandler.PushHandle(GetThis<Player>());//!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		MovePlayer();
		AppearanceChange();
		m_InputHandlerB.PushHandleB(GetThis<Player>());

	}

	//!�v���C���[������ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		

			auto ptrKey = dynamic_pointer_cast<Key>(Other);
			//!�v���C���[�����ɓ���������
			if (ptrKey)
			{

				auto keySprite = GetStage()->GetSharedGameObject<KeySprite>(L"KeySprite");
				keySprite->SetDrawActive(true);
				GetStage()->RemoveGameObject<Key>(Other);
				m_KeyCount++;

			}
		

		//!�v���C���[�����������Ă�����
			if (m_KeyCount == 1)
			{
				auto ptrGate = dynamic_pointer_cast<StageGate>(Other);
				if (ptrGate)
				{
					PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");
				}
			}
		

	}
	void Player::OnPushB()
	{
		Villagerkiller();
	}
}
//end basecross

