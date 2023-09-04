/*!
@file HeadMan.cpp
@brief �����̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "AnimationComponent.h"

namespace basecross
{
	constexpr float HEADMANSP = 30.0f;			//!�����蔻������X�t�B�A�̔��a
	
		

	HeadMan::HeadMan(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :

		GameObject(StagePtr),
		m_IsheadManCommentOn(false),
		m_headManBoneModelDeta(
			{
				Scale,
				Rotation,
				Position,
				Vec3(0.4f, 0.4f, 0.4f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -1.0f, 0.0f),
				L"EnemyVillager_WalkAnimation_MESH",
				L"EnemyVillager_WalkAnimation_MESH_WITH_TAN",
				L"OBJECT_NORMAL_TX"
			}
		)
	{
	}

	void HeadMan::OnCreate()
	{

		AddComponent<BoneModelComponent>(m_headManBoneModelDeta);										//!�v���C���[�̃��f���쐬
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();				                       //!�`��R���|�[�l���g�̐ݒ�
		AddComponent<AnimationComponent>(L"HeadMan", L"Default");									//!�A�j���[�V�����̓ǂݍ���

	}

	void HeadMan::HeadManComment()
	{
		auto position = GetComponent<Transform>()->GetPosition();				  //!���݂̃v���C���[�̈ʒu�̎擾
		SPHERE headManSp(position, HEADMANSP);									  //!�v���C���[�̍��W�𒆐S�ɔ��a30�Z���`�̉~�̍쐬
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