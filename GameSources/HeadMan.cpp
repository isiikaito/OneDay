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
	constexpr float SAMPLESPARSECOND = 10.0f;//!�A�j���[�V�����̍Đ����x
	constexpr int STARTSAMPLE = 31;		   //!�A�j���[�V�����̊J�n�t���[��
	constexpr int SAMPLELENGTH = 30;		   //!�A�j���[�V�����̒���
	constexpr float HEADMANSP = 30.0f;       //!�����蔻������X�t�B�A�̔��a
	
		

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
		ptrTrans->SetScale(m_Scale);	  //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		Mat4x4 spanMat;                // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),    //!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),    //!��]
			Vec3(0.0f, -1.0f, 0.0f)    //!�ʒu
		);

		AddComponent<Gravity>();											                       //!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();						                       //!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();							                       //!�e������i�V���h�E�}�b�v��`�悷��j
		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");	                       //!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);						                       //!���b�V���𓖂��蔻��ƍ��킹��
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();				                       //!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");                    //!�`�悷�郁�b�V����ݒ�
		ptrDraw->AddAnimation(L"Default", STARTSAMPLE, SAMPLELENGTH, true, SAMPLESPARSECOND);//!�A�j���[�V�����̎擾
		ptrDraw->ChangeCurrentAnimation(L"Default");						                       //!���݂̃A�j���[�V�����̐ݒ�
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");			                       //!�@���}�b�v�̐ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);												   //!���b�V���̑傫���̐ݒ�
	}

	void HeadMan::HeadManComment()
	{
		auto position = GetComponent<Transform>()->GetPosition();				  //!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE headManSp(position, HEADMANSP);								  //!�v���C���[�̍��W�𒆐S�ɔ��a30�Z���`�̉~�̍쐬
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");		  //!�v���C���[�̎擾
		Vec3 ret;																  //!�ŋߐړ_
		auto playerCapsrul=player->GetComponent<CollisionCapsule>()->GetCapsule();//!�v���C���[�̃J�v�Z���I�u�W�F�N�g���擾
				if (HitTest::SPHERE_CAPSULE(headManSp, playerCapsrul, ret))		  //!�v���C���[�̎�����͂�ł���X�t�B�A�ɓ���������
				{
					m_IsheadManCommentOn = true;								  //!�������b���Ă���
				}
				else
				{
					m_IsheadManCommentOn = false;								  //!�������b���ĂȂ�
				}
	}

	void HeadMan::HeadManAnimation()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);				//!�A�j���[�V�����̍X�V
	}

	void HeadMan::OnUpdate()
	{
		HeadManAnimation();
		HeadManComment();
	}
}