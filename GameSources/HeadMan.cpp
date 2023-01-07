/*!
@file HeadMan.cpp
@brief �����̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
namespace basecross
{

	HeadMan::HeadMan(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :

		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_IsheadManCommentOn(false)
	{
	}

	void HeadMan::OnCreate()
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

		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();  //!�e������i�V���h�E�}�b�v��`�悷��j

		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->AddAnimation(L"Default", 31, 30, true, 10.0f);
		ptrDraw->AddAnimation(L"Ded", 60, 30, false, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		Coll->SetDrawActive(false);
	}

	void HeadMan::HeadManComment()
	{
		auto position = GetComponent<Transform>()->GetPosition();//!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE headManSp(position, 30);//!�v���C���[�̍��W�𒆐S�ɔ��a2�Z���`�̉~�̍쐬
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		Vec3 ret;
		auto playerCapsrul=player->GetComponent<CollisionCapsule>()->GetCapsule();//!�v���C���[�̃J�v�Z���I�u�W�F�N�g���擾
				if (HitTest::SPHERE_CAPSULE(headManSp, playerCapsrul, ret))//!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				{
					m_IsheadManCommentOn = true;
				}
				else
				{
					m_IsheadManCommentOn = false;
				}
			
	}

	void HeadMan::HeadManAnimation()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void HeadMan::OnUpdate()
	{
		HeadManAnimation();

		HeadManComment();
	}
}