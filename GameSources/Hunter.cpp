/*!
@file Hunter.cpp
@brief �n���^�[�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float EYERANGE = 50.0f;				//!���E�̒���
	constexpr float MAXPLAYERCATCH = 10.0f;			//!�v���C���[��߂܂��鋗��
	constexpr float dividedNumber = 9.0f;			//!����̍L�������߂�
	constexpr int MOVESTARTSAMPLE = 0;				//!�����A�j���[�V�����̊J�n�t���[��
	constexpr int MOVESAMPLELENGTH = 30;			//!�����A�j���[�V�����̒���
	constexpr float MOVESAMPLESPARSECOND = 40.0f;	//!�����A�j���[�V�����̍Đ����x
	constexpr int DEDSTARTSAMPLE = 60;				//!�|���A�j���[�V�����̊J�n�t���[��
	constexpr int DEDSAMPLELENGTH = 30;				//!�|���A�j���[�V�����̒���
	constexpr float DEDSAMPLESPARSECOND = 15.0f;	//!�|���A�j���[�V�����̍Đ����x



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



	void Hunter::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);	  //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),	//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 59.7f, 0.0f),//!��]
			Vec3(0.0f, -1.0f, 0.0f) //!�ʒu
		);


		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");								//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group->IntoGroup(GetThis<Hunter>());															//!�O���[�v�Ɏ������g��ǉ�
		SetAlphaActive(true);																			//!SetDiffiuse�̃J���[�ύX��K�p

		AddComponent<Gravity>();																		//!�d�͂�����
		auto Coll = AddComponent<CollisionCapsule>();													//!CollisionObb�Փ˔����t����
		auto ptrShadow = AddComponent<Shadowmap>();														//!�e������i�V���h�E�}�b�v��`�悷��j
		ptrShadow->SetMeshResource(L"EnemyHunter_Animation_MESH");										//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);													//!�����ڂƓ����蔻��
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();											//!�`��R���|�[�l���g�̐ݒ�
		ptrDraw->SetMeshResource(L"EnemyHunter_Animation_MESH_WITH_TAN");								//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);														//!���b�V���̑傫���ݒ�
		ptrDraw->AddAnimation(L"Move", MOVESTARTSAMPLE, MOVESAMPLELENGTH, true, MOVESAMPLESPARSECOND);	//!�����A�j���[�V�����̓ǂݍ���
		ptrDraw->AddAnimation(L"Ded", DEDSTARTSAMPLE, DEDSAMPLELENGTH, false, DEDSAMPLESPARSECOND);		//!�|���A�j���[�V�����̒ǉ�
		ptrDraw->ChangeCurrentAnimation(L"Move");														//!���݂̃A�j���[�V�����̐ݒ�
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");										//!�@���}�b�v�̐ݒ�

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
	//!�X�V
	void Hunter::OnUpdate()
	{
		HunterDed();
		PlayerCatch();
		SetMaxSpeed(m_Speed);
		BaseEnemy::OnUpdate();//!�e�N���X�̏��𗘗p����		
	}

}
//!end basecross
