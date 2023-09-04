/*!
@file Villager.cpp
@brief ���l�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross
{
	constexpr float EYERANGE = 20.0f;				//!����̒���
	
	Villager::Villager(const shared_ptr<Stage>& StagePtr,
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
		m_dedDecision(false),
		m_damage(1),
		m_enemyBoneModelDeta(
			{
			Scale ,
			Rotation,
			Position,
			Vec3(0.4f, 0.4f, 0.4f),			
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),			
			Vec3(0.0f, -1.0f, 0.0f),		
			L"EnemyVillager_WalkAnimation_MESH",
			L"EnemyVillager_WalkAnimation_MESH_WITH_TAN",
			L"OBJECT_NORMAL_TX"
			})
	{
	}

		void Villager::OnCreate()
	{
		AddComponent<BoneModelComponent>(m_enemyBoneModelDeta);
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");	//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Villager>());									//!�O���[�v�Ɏ������g��ǉ�
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();					//!�`��R���|�[�l���g�̐ݒ�
		AddComponent<AnimationComponent>(L"Villager", L"Move");									//!�A�j���[�V�����̓ǂݍ���

		//!����|�C���g�̎擾
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);										//!����|�C���g�̏��𖖔��ɒǉ�����
		}

		SetpatorolPoints(patrolPoints);		
		SetEyeRang(EYERANGE);

	}
	


	
	void Villager::OnUpdate()
	{
		SetMaxSpeed(m_Speed);
		SetEyeRang(EYERANGE);
		BaseEnemy::OnUpdate();
	}

	//!���l���v���C���[��߂܂�����
	void Villager::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		//!�����������Ă��邩�ǂ����̎擾
		auto villagerDed = GetIsEnemyDed();
		//!�����Ă�����
		if (villagerDed == false)
		{
			auto ptrPlayer = dynamic_pointer_cast<Player>(Other);//!�v���C���[�̎擾
			auto seekCondition = GetseekCondition();			 //!�ǂ������Ă��邩�ǂ�
			//!�v���C���[�ɓ������Ă���
			if (ptrPlayer)
			{
				//!�ǂ������Ă���Ƃ�
				if (seekCondition == true)
				{
					auto playerDed = ptrPlayer->GetIsplayerDed();//!�v���C���[���|��Ă��邩�ǂ���
					playerDed = true;							 //!�v���C���[��|��
					ptrPlayer->SetIsplayerDed(playerDed);		 //!�v���C���[��|������Ԃɐݒ肷��

				}
			}
		}
	}
}
//!end basecross
