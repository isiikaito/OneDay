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

		BaseEnemy(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_patrolPoints(patrolPoints),
		m_StateChangeSize(30.0f),
		m_playerChange(0),
		m_Speed(1),
		m_patrolindex(0),
	    m_DedDecision(false)


	{
	}

	//!�f�X�g���N�^
	Hunter::~Hunter() {}
	


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
		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p
		
		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionObb>();//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();  //!�e������i�V���h�E�}�b�v��`�悷��j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"HUNTER_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();    //!�`��R���|�[�l���g�̐ݒ� 

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"HUNTER_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		Coll->SetDrawActive(true);

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
	void Hunter::OnUpdate()
	{
	

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");             //!�v���C���[�̎擾
		m_playerChange = ptrPlayer->GetPlayerCange();//!�v���C���[�̏�Ԃ̎擾
		ptrPlayer->SetPlayerChange(m_playerChange);//!�v���C���[�̎擾������Ԃ̐ݒ�
		BaseEnemy::OnUpdate();
	}
	
	//!�n���^�[���v���C���[��߂܂�����
	void Hunter::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		if (ptrPlayer)
		{
			if (m_playerChange == static_cast<int>(PlayerModel::wolf)&&m_DedDecision ==false)
			{
              PostEvent(0.0f, GetThis<Hunter>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
	}
}
//!end basecross
