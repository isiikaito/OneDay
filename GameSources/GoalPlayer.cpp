/**
*@file GoalPlayer.cpp
*@brief �S�[�����̃v���C���[�̃\�[�X�t�@�C��
*@author  Ayumiu Muroi
*@details �S�[�����̃v���C���[�̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "GoalPlayer.h"

namespace basecross {

	GoalPlayer::GoalPlayer(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		GameObject(StagePtr)
	{
	}

	

	//!������
	void GoalPlayer::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);		//!�傫��
		ptrTrans->SetRotation(m_Rotation);	//!��]
		ptrTrans->SetPosition(m_Position);	//!�ʒu

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),  //!��]
			Vec3(0.0f, -1.0f, 0.0f)  //!�ʒu
		);

		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();					//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();						//!�e������i�V���h�E�}�b�v��`�悷��j
		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);					//�e�̃}�g���b�N�X
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();			//!�`��R���|�[�l���g�̐ݒ�
		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");//�^���W�F���g�t�����b�V���̐ݒ�
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");				//!�@���}�b�v


	}

	//!�X�V
	void GoalPlayer::OnUpdate()
	{
	}

}
//end basecros