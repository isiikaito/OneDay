/*!
@file Hunter.cpp
@brief �n���^�[�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross
{
	constexpr float EYERANGE = 50.0f;				//!���E�̒���
	constexpr float MAXPLAYERCATCH = 10.0f;			//!�v���C���[��߂܂��鋗��
	constexpr float dividedNumber = 9.0f;			//!����̍L�������߂�



	Hunter::Hunter(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const std::vector<Vec3>& patrolPoints
	) :

		BaseEnemy(StagePtr),
		m_patrolPoints(patrolPoints),
		m_playerChange(0),
		m_Speed(22.0f),
		m_patrolindex(0),
		m_enemyBoneModelDeta(
			{ 
			Scale ,
			Rotation,
			Position,
			Vec3(0.4f, 0.4f, 0.4f),	
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 59.7f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f),
			L"EnemyHunter_Animation_MESH",
			L"EnemyHunter_Animation_MESH_WITH_TAN",
			L"OBJECT_NORMAL_TX"
			})

	{
	}



	void Hunter::OnCreate()
	{
		
		AddComponent<BoneModelComponent>(m_enemyBoneModelDeta);
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");								//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Hunter>());															//!�O���[�v�Ɏ������g��ǉ�

		//!�����ڂƓ����蔻��
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();											//!�`��R���|�[�l���g�̐ݒ�
		AddComponent<AnimationComponent>(L"Hunter", L"Move");									//!�A�j���[�V�����̓ǂݍ���

		//!����|�C���g�̎擾
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);									//!����|�C���g�̏��𖖔��ɒǉ�����
		}

		SetpatorolPoints(patrolPoints);
		SetEyeRang(EYERANGE);


	}

	void Hunter::PlayerCatch()
	{

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");		//!�v���C���[�̎擾
		auto playerPosition = ptrPlayer->GetComponent<Transform>()->GetPosition();	//!�v���C���[�̃|�W�V�����̎擾
		auto hunterPosition = GetComponent<Transform>()->GetPosition();				//!�n���^�[�̃|�W�V�����̎擾
		auto phdistans = playerPosition - hunterPosition;							//!�n���^�[�ƃv���C���[�̃x�N�g�����v�Z
		auto playerCatch = bsm::length(phdistans);									//!�v�Z�����x�N�g���������ɕϊ�
		auto Enemyfront = GetComponent<Transform>()->GetForword();					//!�G�̐��ʂ��擾
		auto angle = angleBetweenNormals(Enemyfront, phdistans);					//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
		auto chk = XM_PI / dividedNumber;											//!360��9�Ŋ����Ċp�x���o���B

		//!�v���C���[��ǂ��Ă����Ԃ̎�
		if (m_seekCondition == true)
		{
			//!�G���猩��+40�x��-40�x�Ƀv���C���[����������
			if (angle <= chk && angle >= -chk)
			{
				//!�v���C���[��߂܂���͈͂̒��Ƀv���C���[��������
				if (playerCatch <= MAXPLAYERCATCH)
				{
					ptrPlayer->SetIsplayerDed(true);								//!�v���C���[��|��
				}

			}
		}

	}

	void Hunter::HunterDed()
	{
		auto elapasedime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		auto hunterDed = GetIsEnemyDed();				   //!�����������Ă��邩�ǂ����̎擾

		//!�|�ꂽ��
		if (hunterDed == true)
		{

			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();					//�A�j���[�V�����̎擾
			auto& AnimationName = ptrDraw->GetCurrentAnimation();					//!���݂̃A�j���[�V�������擾
			auto AnimationEnd = ptrDraw->UpdateAnimation(elapasedime);				//!�A�j���[�V�����̍X�V
			//�����A�j���[�V�����̎�
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Ded");							//!�|���A�j���[�V�����ɕύX
				
			}
			else
			{
				//!�A�j���[�V�������I�������
				if (AnimationEnd)
				{
					SetDedAnimationEnd(true);										//!���̂���������
				}
			}
		}
	}
	//!�X�V
	void Hunter::OnUpdate()
	{
		//HunterDed();
		PlayerCatch();
		SetMaxSpeed(m_Speed);
		BaseEnemy::OnUpdate();//!�e�N���X�̏��𗘗p����		
	}

}
//!end basecross
