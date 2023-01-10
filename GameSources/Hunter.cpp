/*!
@file Villager.cpp
@brief ���l�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float eyeRang = 50.0f;
	constexpr float maxPlayerCatch = 10.0f;
	constexpr float m_maxdedTime = 1.0f;
	constexpr float dividedNumber = 9.0f;
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
		m_Speed(22.0f),
		m_patrolindex(0),
		m_IsGameOver(false),
		m_dedTime(0),
		m_playerDed(false),
		m_damage(1)

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
			Vec3(0.4f, 0.4f, 0.4f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 59.7f, 0.0f),   //!��]
			Vec3(0.0f, -1.0f, 0.0f)  //!�ʒu
		);


		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Hunter>());//!�O���[�v�Ɏ������g��ǉ�
		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p

		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();  //!�e������i�V���h�E�}�b�v��`�悷��j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"EnemyHunter_Animation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"EnemyHunter_Animation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->AddAnimation(L"Ded", 60, 30, false, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Move");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");

	
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);
		}

		SetpatorolPoints(patrolPoints);
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));

		SetEyeRang(eyeRang);


	}

	void Hunter::PlayerCatch()
	{

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		auto playerPosition = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto hunterPosition = GetComponent<Transform>()->GetPosition();
		auto phdistans = playerPosition - hunterPosition;
		auto playerCatch = bsm::length(phdistans);
		auto Enemyfront = GetComponent<Transform>()->GetForword();//!�G�̐��ʂ��擾
		auto angle = angleBetweenNormals(Enemyfront, phdistans);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
		auto chk = XM_PI / dividedNumber;//!360��6�Ŋ����Ċp�x���o���B

		if (m_seekCondition == true)
		{

			if (angle <= chk && angle >= -chk)//!�G���猩��+40�x��-40�x�Ƀv���C���[����������
			{
				if (playerCatch <= maxPlayerCatch)
				{

					auto playerDed = ptrPlayer->GetIsplayerDed();
					playerDed = true;
					ptrPlayer->SetIsplayerDed(playerDed);


				}

			}
		}

	}

	void Hunter::HunterDed()
	{
		auto hunterDed = GetIsEnemyDed();
		if (hunterDed == true)
		{
			//�A�j���[�V����
			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
			auto& AnimationName = ptrDraw->GetCurrentAnimation();
			//�����~�܂�A�j���[�V����
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Ded");
				auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
				auto playerHp = ptrPlayer->GetPlayerHp();
				playerHp += m_damage;
				ptrPlayer->SetPlayerHp(playerHp);
			}
		}
	}
	//!�X�V
	void Hunter::OnUpdate()
	{
		HunterDed();
		PlayerCatch();

		auto MaxSpeed = GetMaxSpeed();
		MaxSpeed = m_Speed;
		SetMaxSpeed(MaxSpeed);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		BaseEnemy::OnUpdate();

	
		
	}

	
}
//!end basecross
