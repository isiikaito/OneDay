/*!
@file Hunter.cpp
@brief �n���^�[�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	Hunter::Hunter(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		PEvector(0)

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
		pos += m_Velocity * elapsedTime;//!�G�̃|�W�V�����ɑ��x�Ǝ��Ԃ��|�������̂𑫂�
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
		ptrTrans->SetScale(1.0f, 1.4f, 1.4f);//!�傫��
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);//!��]
		ptrTrans->SetPosition(0.0f, 5.0f, 0.0f);//!�ʒu

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.35f, 0.2f, 0.4f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, -0.05f)  //!�ʒu
		);

		AddTag(L"ObjGroup");//!�I�u�W�F�N�g�^�O�̍쐬
		auto group = GetStage()->GetSharedObjectGroup(L"ObjGroup");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Hunter>());//!�O���[�v�Ɏ������g��ǉ�

		//�o�H�����t����
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		list<Vec3> pathList = {
			Vec3(-10,0.125,10),
			Vec3(10,0.125,10),
			Vec3(-10,0.125,-10),
			Vec3(10,0.125,-10),
		};
		ptrFollowPath->SetPathList(pathList);
		ptrFollowPath->SetLooped(true);

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




		//!��Q������s����t����
		vector<shared_ptr<GameObject>>obObjVec;
		GetStage()->GetUsedTagObjectVec(L"StageWall", obObjVec);//!��Q���̎擾
		vector<OBB> obVec;//!���̂̃x�N�g���̎擾
		for (auto& v : obObjVec) {
			auto TransPtr = v->GetComponent<Transform>();//!�O���[�v���̃R���|�[�l���g���擾
			OBB ob;
			ob.m_Center = TransPtr->GetPosition();
			ob.m_Size = TransPtr->GetScale();
			obVec.push_back(ob);
		}
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidance->SetObstacleObbVec(obVec);
		m_StateMachine.reset(new StateMachine<Hunter>(GetThis<Hunter>()));//!�X�e�[�g�}�V���̍\�z
		m_StateMachine->ChangeState(NearState::Instance());
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
		if (f > GetStateChangeSize()) {
			GetStateMachine()->ChangeState(FarState::Instance());                        //!�X�e�[�g���`�F���W����
		}
	}

	//!�X�e�[�g���������̏���
	void Hunter::FarBehavior() {
		auto ptrArrive = GetBehavior<ArriveSteering>();
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
		if (angle <= chk && angle >= -chk)//!�G���猩��+60�x��-60�x�Ƀv���C���[����������
		{
			//!���̋߂Â�����
			if (f <= GetStateChangeSize())
			{
				GetStateMachine()->ChangeState(NearState::Instance());//!�X�e�[�g���`�F���W����

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





}
//!end basecross
