/*!
@file Villager.cpp
@brief ���l�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float eyeRang = 20.0f;			   //!����̒���
	constexpr int m_movestartSample = 0;		   //!�����A�j���[�V�����̊J�n�t���[��
	constexpr int m_movesampleLength = 30;		   //!�����A�j���[�V�����̒���
	constexpr float m_movesamplesParSecond = 40.0f;//!�����A�j���[�V�����̍Đ����x
	constexpr int m_dedstartSample = 60;		   //!�|���A�j���[�V�����̊J�n�t���[��
	constexpr int m_dedsampleLength = 30;		   //!�|���A�j���[�V�����̒���
	constexpr float m_dedsamplesParSecond = 15.0f; //!�|���A�j���[�V�����̍Đ����x
	
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
		m_Speed(22.0f),
		m_patrolindex(0),
		m_dedDecision(false),
		m_damage(1)
	{
	}

		void Villager::OnCreate()
	{

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);		//!�傫��
		ptrTrans->SetRotation(m_Rotation);	//!��]
		ptrTrans->SetPosition(m_Position);	//!�ʒu

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),			//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),			//!��]
			Vec3(0.0f, -1.0f, 0.0f)			//!�ʒu
		);

		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");	//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Villager>());									//!�O���[�v�Ɏ������g��ǉ�
		AddComponent<Gravity>();												//!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();							//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();								//!�e������i�V���h�E�}�b�v��`�悷��j
		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);							//!���b�V���̑傫����ݒ肷��
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();					//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");	//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);								//!���b�V���̑傫����ݒ肷��
		ptrDraw->AddAnimation(L"Move", m_movestartSample, m_movesampleLength, true, m_movesamplesParSecond);//!�����A�j���[�V�����̓ǂݍ���
		ptrDraw->AddAnimation(L"Ded", m_dedstartSample, m_dedsampleLength, false, m_dedsamplesParSecond);	//!�|���A�j���[�V�����̒ǉ�
		ptrDraw->ChangeCurrentAnimation(L"Move");								//!���݂̃A�j���[�V�����̐ݒ�
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");				//!�@���}�b�v�̐ݒ�

		//!����|�C���g�̎擾
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);										//!����|�C���g�̏��𖖔��ɒǉ�����
		}

		SetpatorolPoints(patrolPoints);		
		SetEyeRang(eyeRang);

	}
	

	void Villager::VillagerDed()
	{
		auto elapasedime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		auto villagerDed = GetIsEnemyDed();				   //!�����������Ă��邩�ǂ����̎擾
		
		//!�|�ꂽ��
		if (villagerDed == true)
		{
			
			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();		//�A�j���[�V�����̎擾
			auto& AnimationName = ptrDraw->GetCurrentAnimation();		//!���݂̃A�j���[�V�������擾
			auto AnimationEnd = ptrDraw->UpdateAnimation(elapasedime);	//!�A�j���[�V�����̍X�V
			//�����A�j���[�V�����̎�
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Ded");							//!�|���A�j���[�V�����ɕύX
				auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
				auto playerHp = ptrPlayer->GetPlayerHp();							//!�v���C���[��HP���擾
				playerHp -= m_damage;												//!�v���C���[��HP��1���
				ptrPlayer->SetPlayerHp(playerHp);									//!�v���C���[��HP���X�V����
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

	
	void Villager::OnUpdate()
	{
		VillagerDed();
		SetMaxSpeed(m_Speed);
		SetEyeRang(eyeRang);
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
