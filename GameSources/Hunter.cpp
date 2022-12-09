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
	constexpr float MaxPlayerCatch = 10.0f;
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
		m_playerDed(false)

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
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -1.0f, 0.0f)  //!�ʒu
		);


		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Hunter>());//!�O���[�v�Ɏ������g��ǉ�
		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p

		AddComponent<Gravity>(); //!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();  //!�e������i�V���h�E�}�b�v��`�悷��j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Enemy_WalkAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"Enemy_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->ChangeCurrentAnimation(L"Move");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");

	
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);
		}

		SetpatorolPoints(patrolPoints);
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));

		SetEyeRang(60.0f);


	}

	void Hunter::PlayerCatch()
	{

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		auto playerPosition = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto hunterPosition = GetComponent<Transform>()->GetPosition();
		auto phdistans = playerPosition - hunterPosition;
		auto playerCatch = bsm::length(phdistans);
		auto seekCondition = GetseekCondition();
		auto Enemyfront = GetComponent<Transform>()->GetForword();//!�G�̐��ʂ��擾
		auto angle = angleBetweenNormals(Enemyfront, phdistans);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
		auto chk = XM_PI / 9.0f;//!360��6�Ŋ����Ċp�x���o���B



		if (m_seekCondition == true)
		{

			if (angle <= chk && angle >= -chk)//!�G���猩��+40�x��-40�x�Ƀv���C���[����������
			{
				if (playerCatch <= MaxPlayerCatch)
				{

					auto playerDed = ptrPlayer->GetIsplayerDed();


					playerDed = true;
					ptrPlayer->SetIsplayerDed(playerDed);

					ptrPlayer->SetSpeed(0.0f);
					if (playerDed = true)
					{
						
					}

					GetStage()->AddGameObject<FadeOut>(true,
						Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
					m_IsGameOver = true;
					if (m_IsGameOver == true)
					{
						auto& app = App::GetApp();//!�A�v���̎擾
						auto time = app->GetElapsedTime();
						m_dedTime += time;
						if (m_dedTime >= 1.0f)
						{
							PostEvent(0.0f, GetThis<Hunter>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
						}
					}

				}

			}
		}

	}

	//!�X�V
	void Hunter::OnUpdate()
	{
		
		PlayerCatch();
		
		
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		m_playerChange = ptrPlayer->GetPlayerCange();//!�v���C���[�̏�Ԃ̎擾
		ptrPlayer->SetPlayerChange(m_playerChange);//!�v���C���[�̎擾������Ԃ̐ݒ�
		BaseEnemy::OnUpdate();
		

	}

	
}
//!end basecross
