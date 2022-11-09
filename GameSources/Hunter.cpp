/*!
@file Hunter.cpp
@brief �n���^�[�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	Hunter::Hunter(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const std::vector<Vec3>& patrolPoints
	) :

		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_patrolPoints(patrolPoints),
		m_StateChangeSize(30.0f),
		m_Force(0),
		m_Velocity(0),
		m_PEvector(0),
		m_playerChange(0)

	{
	}

	//!�f�X�g���N�^
	Hunter::~Hunter() {}
	//!�K����
	void Hunter::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
		m_Velocity += m_Force * elapsedTime;//!�s���̗͂Ɏ��Ԃ������đ��x�����߂Ă���
		auto ptrTrans = GetComponent<Transform>();//!�G��Transform���擾���Ă���
		auto pos = ptrTrans->GetPosition();//!�G�̃|�W�V�������擾���Ă���
		pos += m_Velocity * elapsedTime * 2;//!�G�̃|�W�V�����ɑ��x�Ǝ��Ԃ��|�������̂𑫂�
		ptrTrans->SetPosition(pos);//!�G�̃|�W�V�����̐ݒ�
	}

	//!�^�[�Q�b�g(�v���C���[)�̎擾
	shared_ptr<GameObject>  Hunter::GetTarget()const
	{
		return GetStage()->GetSharedObject(L"Player");
	}

	//!������
	void Hunter::OnCreate()
	{

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);//!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.35f, 0.2f, 0.4f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, -0.05f)  //!�ʒu
		);

		AddTag(L"Hunter_ObjGroup");//!�I�u�W�F�N�g�^�O�̍쐬
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Hunter>());//!�O���[�v�Ɏ������g��ǉ�

		//�o�H�����t����
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		list<Vec3> pathList = {};//!����|�C���g�̃��X�g

		for (auto v : m_patrolPoints)//!vector�z��̗v�f�����[�v����
		{
			pathList.push_back(v);//!����o�H�̃��X�g�ɏ���|�C���g������
		}

		ptrFollowPath->SetPathList(pathList);//!���X�g��ݒ肷��
		ptrFollowPath->SetLooped(true);//!����̃��[�v����

		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionObb>();//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();  //!�e������i�V���h�E�}�b�v��`�悷��j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"HUNTER_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();    //!�`��R���|�[�l���g�̐ݒ�            //!�`��R���|�[�l���g

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"HUNTER_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		Coll->SetDrawActive(true);

		//!��Q������s��
		vector<shared_ptr<GameObject>>obObjVec;
		GetStage()->GetUsedTagObjectVec(L"StageBuilding", obObjVec);
		vector<SPHERE>obVec;
		for (auto& v : obObjVec)
		{
			auto TransPtr = v->GetComponent<Transform>();

			SPHERE sp;
			sp.m_Center = TransPtr->GetPosition();
			sp.m_Radius = TransPtr->GetScale().x * 1.414f * 0.5f;
			obVec.push_back(sp);
		}
		auto ptrAvoidandce = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidandce->SetObstacleSphereVec(obVec);
		m_StateMachine.reset(new StateMachine<Hunter>(GetThis<Hunter>()));
		m_StateMachine->ChangeState(FarState::Instance());
	}
	//!�X�V
	void Hunter::OnUpdate()
	{
		m_Force = Vec3(0);//!�s���̗͂��[���ɂ���

		m_StateMachine->Update();//!���̒��ŃX�e�[�g�̐؂�ւ����s����

		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!��Q���������s��
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");             //!�v���C���[�̎擾
		m_playerChange = ptrPlayer->GetPlayerCange();//!�v���C���[�̏�Ԃ̎擾
		ptrPlayer->SetPlayerChange(m_playerChange);//!�v���C���[�̎擾������Ԃ̐ݒ�
	}
	//!����
	//!�X�e�[�g���߂����̏���
	void Hunter::NearBehavior()
	{


		auto ptrArrive = GetBehavior<ArriveSteering>();                                  //!�����X�e�A�����O
		auto ptrTrans = GetComponent<Transform>();                                       //!�G�̃R���|�[�l���g�̎擾
		auto ptrPlayerTrans = GetTarget()->GetComponent<Transform>();                    //!�v���C���[�̃R���|�[�l���g�̎擾
		auto force = GetForce();                                                         //!�s���̗͂̎擾
		force += ptrArrive->Execute(force, GetVelocity(), ptrPlayerTrans->GetPosition());//!���݂̗́A���x�A�ʒu�������Ă���B
		SetForce(force);                                                                 //!�͂�ݒ肷��
		float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition());  //!�v���C���[�̈ʒu�[�G�̈ʒu
		//!���̋������ꂽ��
		if (f > GetStateChangeSize() || m_playerChange == static_cast<int>(PlayerModel::human)) //!�X�e�[�g�̑傫�������ꂽ��܂��̓v���C���[���l�ԏ�ԂɂȂ�����
		{
			GetStateMachine()->ChangeState(FarState::Instance());                        //!�X�e�[�g���`�F���W����
		}
	}

	//!�X�e�[�g���������̏���
	void Hunter::FarBehavior() {

		auto ptrFollowPath = GetBehavior<FollowPathSteering>();//!����s���̃X�e�A�����O
			auto ptrTrans = GetComponent<Transform>();//!�G�̃R���|�[�l���g�̎擾
			auto ptrPlayerTrans = GetTarget()->GetComponent<Transform>();//!�v���C���[�̃R���|�[�l���g�̎擾
			auto force = GetForce();//!�s���̗͂̎擾
		force += ptrFollowPath->Execute(force, GetVelocity());//!���݂̗́A���x�A�ʒu�������Ă���B
		SetForce(force);//!�͂�ݒ肷��
		float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition());//!�v���C���[�̈ʒu�[�G�̈ʒu


		Vec3 PEvector = ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition();//!�v���C���[�ƓG�̃x�N�g�����擾
		auto Enemyfront = ptrTrans->GetForword();//!�G�̐��ʂ��擾
		PEvector.normalize();//!�v���C���[�ƓG�̃x�N�g���𐳋K��
		auto angle = angleBetweenNormals(Enemyfront, PEvector);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
		auto chk = XM_PI / 6.0f;//!360��6�Ŋ����Ċp�x���o���B

		if (m_playerChange == static_cast<int>(PlayerModel::wolf))//!�v���C���[���T�̏�Ԃ̎�
		{
			if (angle <= chk && angle >= -chk)//!�G���猩��+60�x��-60�x�Ƀv���C���[����������
			{
				//!���̋߂Â�����
				if (f <= GetStateChangeSize())
				{
					GetStateMachine()->ChangeState(NearState::Instance());//!�X�e�[�g���`�F���W����

				}
			}
		}





	}

	//--------------------------------------------------------------------------------------
	  //	�v���C���[���牓���Ƃ��̈ړ�
	  //--------------------------------------------------------------------------------------
	shared_ptr<FarState> FarState::Instance() {
		static shared_ptr<FarState> instance(new FarState);
		return instance;
	}
	void FarState::Enter(const shared_ptr<Hunter>& Obj) {
	}
	void FarState::Execute(const shared_ptr<Hunter>& Obj) {
		Obj->FarBehavior();
	}

	void FarState::Exit(const shared_ptr<Hunter>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<NearState> NearState::Instance() {
		static shared_ptr<NearState> instance(new NearState);
		return instance;
	}
	void NearState::Enter(const shared_ptr<Hunter>& Obj) {
	}
	void NearState::Execute(const shared_ptr<Hunter>& Obj) {
		Obj->NearBehavior();
	}
	void NearState::Exit(const shared_ptr<Hunter>& Obj) {
	}


	void Hunter::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrHunter = dynamic_pointer_cast<Player>(Other);
		if (ptrHunter) 
		{
			GetStage()->RemoveGameObject<Hunter>(GetThis<Hunter>());
			PostEvent(0.0f, GetThis<Hunter>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
		}
	}
}
//!end basecross
