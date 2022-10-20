/*!
@file Hunter.cpp
@brief �n���^�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		PEvector(0)

	{
	}

	//!�f�X�g���N�^
	Enemy::~Enemy() {}
	//!�K����
	void Enemy::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
		m_Velocity += m_Force * elapsedTime;//!�s���̗͂Ɏ��Ԃ������đ��x�����߂Ă���
		auto ptrTrans = GetComponent<Transform>();//!�G��Transform���擾���Ă���
		auto pos = ptrTrans->GetPosition();//!�G�̃|�W�V�������擾���Ă���
		pos += m_Velocity * elapsedTime;//!�G�̃|�W�V�����ɑ��x�Ǝ��Ԃ��|�������̂𑫂�
		ptrTrans->SetPosition(pos);//!�G�̃|�W�V�����̐ݒ�
	}

	//!�^�[�Q�b�g(�v���C���[)�̎擾
	shared_ptr<GameObject>  Enemy::GetTarget()const
	{
		return GetStage()->GetSharedObject(L"Player");
	}

	//!������
	void Enemy::OnCreate()
	{
		auto group = GetStage()->GetSharedObjectGroup(L"ObjGroup");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Enemy>());//!�O���[�v�Ɏ������g��ǉ�

		//!�����s��������
		auto ptrSep = GetBehavior<SeparationSteering>();
		ptrSep->SetGameObjectGroup(group);

		//!������Ȃ����畷��
		//�ǉ���s����t����(�Q�[���Ղ̊O�ɏo�Ȃ��悤�ɂ���)
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();
		vector<PLANE> planeVec = {
			{
				Vec3(20,0,0),
				Vec3(20,1.0,0),
				Vec3(20,0,-1.0),
			},
			{
				Vec3(0,0,-20),
				Vec3(0,1.0,-20),
				Vec3(-1.0,0,-20),
			},
			{
				Vec3(-20,0,0),
				Vec3(-20,1.0,0),
				Vec3(-20,0,1.0),
			},
			{
				Vec3(0,0,20),
				Vec3(0,1.0,20),
				Vec3(1.0,0,20),
			},
		};
		ptrWall->SetPlaneVec(planeVec);

		//!��Q������s����t����
		vector<shared_ptr<GameObject>>spObjVec;
		GetStage()->GetUsedTagObjectVec(L"StageWall", spObjVec);//!��Q���̎擾
		vector<SPHERE> spVec;//!���̂̃x�N�g���̎擾
		for (auto& v : spObjVec) {
			auto TransPtr = v->GetComponent<Transform>();//!�O���[�v���̃R���|�[�l���g���擾
			SPHERE sp;//!����
			sp.m_Center = TransPtr->GetPosition();
			sp.m_Radius = TransPtr->GetScale().x * 0.5f;
			spVec.push_back(sp);
		}
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidance->SetObstacleSphereVec(spVec);
		m_StateMachine.reset(new StateMachine<Enemy>(GetThis<Enemy>()));//!�X�e�[�g�}�V���̍\�z
		m_StateMachine->ChangeState(NearState::Instance());
	}
	//!�X�V
	void Enemy::OnUpdate()
	{
		m_Force = Vec3(0);//!�s���̗͂��[���ɂ���
		//!���ʂ̃X�e�A�����O1
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();//!�X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ��鏈��
		m_Force += ptrWall->Execute(m_Force, GetVelocity());//!���s����͂Ƒ��x����
		m_StateMachine->Update();//!���̒��ŃX�e�[�g�̐؂�ւ����s����
		//!���ʂ̃X�e�A�����O2
		auto ptrSep = GetBehavior<SeparationSteering>();//!�����s�������s����
		m_Force += ptrSep->Execute(m_Force);//!�����s���̗͂�������
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!��Q���������s��
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);



	}

	//--------------------------------------------------------------------------------------
	  //	�v���C���[���牓���Ƃ��̈ړ�
	  //--------------------------------------------------------------------------------------
	shared_ptr<FarState> FarState::Instance() {
		static shared_ptr<FarState> instance(new FarState);
		return instance;
	}
	void FarState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void FarState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->FarBehavior();
	}

	void FarState::Exit(const shared_ptr<Enemy>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<NearState> NearState::Instance() {
		static shared_ptr<NearState> instance(new NearState);
		return instance;
	}
	void NearState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void NearState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->NearBehavior();
	}
	void NearState::Exit(const shared_ptr<Enemy>& Obj) {
	}


	//--------------------------------------------------------------------------------------
	   //	�p�X�����񂷂�z�u�I�u�W�F�N�g
	   //--------------------------------------------------------------------------------------
	   //�\�z�Ɣj��
	Hunter::Hunter(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		Enemy(StagePtr, StartPos)
	{
	}
	Hunter::~Hunter() {}

	//������
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
		group->IntoGroup(GetThis<Enemy>());//!�O���[�v�Ɏ������g��ǉ�

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
		//!�e�N���X��OnCreate���Ă�
		Enemy::OnCreate();
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

}
//!end basecross
