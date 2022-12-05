/*!
@file Villager.cpp
@brief ���l�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	Villager::Villager(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const std::vector<Vec3>& patrolPoints
	) :

		BaseEnemy(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_patrolPoints(patrolPoints),
		m_StateChangeSize(30.0f),
		m_playerChange(0),
		m_Speed(25),
		m_patrolindex(0),
	    m_dedDecision(false)

	{
	}

	//!�f�X�g���N�^
	Villager::~Villager() {}
	


	//!������
	void Villager::OnCreate()
	{

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);//!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -1.0f, 0.0f)  //!�ʒu
		);

		AddTag(L"Villager_ObjGroup");//!�I�u�W�F�N�g�^�O�̍쐬
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Villager>());//!�O���[�v�Ɏ������g��ǉ�
		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p
		
		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();  //!�e������i�V���h�E�}�b�v��`�悷��j

		ptrShadow->SetMeshResource(L"Player_WalkAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"Player_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->ChangeCurrentAnimation(L"Move");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		Coll->SetDrawActive(false);

		m_patrolPoints[m_patrolindex];
		SetEnemyPatorolindex(m_patrolindex);

		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);
		}

		SetpatorolPoints(patrolPoints);
	
	}

	//!�X�V
	void Villager::OnUpdate()
	{
		
		auto MaxSpeed = GetMaxSpeed();
		MaxSpeed = m_Speed;
		SetMaxSpeed(MaxSpeed);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		m_playerChange = ptrPlayer->GetPlayerCange();//!�v���C���[�̏�Ԃ̎擾
		ptrPlayer->SetPlayerChange(m_playerChange);//!�v���C���[�̎擾������Ԃ̐ݒ�
		BaseEnemy::OnUpdate();
	}
	
	//!���l���v���C���[��߂܂�����
	void Villager::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto seekCondition = GetseekCondition();
		if (ptrPlayer)
		{
			if (seekCondition ==true)
			{
              PostEvent(0.0f, GetThis<Villager>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
	}
}
//!end basecross
