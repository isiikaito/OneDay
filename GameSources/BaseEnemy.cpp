/*!
@file BaseEnemy.cpp
@brief �G�̐e�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float m_maxRotationTime = 4.0f;//!���n������
	constexpr int m_randomRange = 6;//!�����̏��
	constexpr int m_randomNumber = 4;//!����̗���
	constexpr float m_rotToHead = 1.0f;//!���ʂ������l
	//!-------------------------------------
	//! �G�̃I�u�W�F�N�g�̐e
	//! ------------------------------------

	//!�\���Ɣj��
	BaseEnemy::BaseEnemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Force(0),
		m_Velocity(0),
		m_MaxSpeed(20),
		m_StateChangeSize(20.0f),
		m_Enemypatorolindex(0),
		m_loseSightOfTarget(false),
		m_IsEnemyDed(false),
		m_eyeRange(0),
		m_IspositionLiset(false),
		m_SurprisedSprite(false),
		m_seekCondition(false),
		m_surprisedTime(0.0f),
		m_patrolRotation(false),
		m_rotationTime(0.0f),
		m_randomTime(0.0f),
		m_randomCount(0),
		m_dedAnimationEnd(false)
	{
		m_StateMachine = new kaito::StateMachine<BaseEnemy>(this);
		m_StateMachine->SetCurrentState(kaito::PatrolState::Instance());
	}

	
	void BaseEnemy::ApplyForce()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force * elapsedTime;
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += m_Velocity * elapsedTime;
		ptrTrans->SetPosition(pos);
	}

	void BaseEnemy::ChangeState(kaito::State<BaseEnemy>* NewState)
	{

		m_StateMachine->ChangeState(NewState);
	}

	shared_ptr<Player>BaseEnemy::GetTarget()const {
		return std::dynamic_pointer_cast<Player>(GetStage()->GetSharedObject(L"Player"));
	}


	void BaseEnemy::HunterDisappear()
	{

		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!���l�̃I�u�W�F�N�g�O���[�v�̎擾
		auto& vecHunter = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecHunter)
		{
			auto hunterPtr = v.lock();//!���l�̃O���[�v����1���b�N����
			Vec3 ret;//!�ŋߐړ_�̑��
			auto ptrHunter = dynamic_pointer_cast<Hunter>(hunterPtr);//!���b�N�����������o��
			if (ptrHunter)
			{
				auto hunterSpeed = ptrHunter->GetSpeed();//!���l�̃X�s�[�h���擾
				if (hunterSpeed == 0.0f)
				{

					GetStage()->RemoveGameObject<Hunter>(ptrHunter);
					m_dedAnimationEnd = false;

				}
			}

		}


	}

	void BaseEnemy::VillagerDisappear()
	{


		//!���l���E��
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");
		auto& vecVillager = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecVillager)
		{

			auto VillagerPtr = v.lock();//!���l�̃O���[�v����1���b�N����
			Vec3 ret;//!�ŋߐړ_�̑��
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������
			if (ptrVillager)
			{

				auto VillagerSpeed = ptrVillager->GetSpeed();//!���l�̃X�s�[�h���擾
				if (VillagerSpeed == 0.0f)
				{

					GetStage()->RemoveGameObject<Villager>(VillagerPtr);
					m_dedAnimationEnd = false;

				}
			}
		}

	}

	void BaseEnemy::AnimationUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void BaseEnemy::ObstacleAvoidance()
	{
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!��Q���������s��
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
	}

	void BaseEnemy::Facade()
	{
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(m_rotToHead);
	}

	void BaseEnemy::EnemyRandomRotation()
	{
		auto& app = App::GetApp();//!�A�v���̎擾
		auto time = app->GetElapsedTime();//!���Ԃ̎擾
		m_randomTime += time;//!�����_���^�C���Ɏ��Ԃ𑫂�

		srand(0);//!�����̏�����
		m_randomCount = rand() % m_randomRange;

		//!�����_���ɕς��ϐ�������̐����ɕς�����Ƃ�
		if (m_randomCount == m_randomNumber)
		{
			m_patrolRotation = true;//!�G�̌��n��������true�ɂ���
		}

		if (m_patrolRotation == true)
		{
			auto EnemyTransform = GetComponent<Transform>();//!�G�̃g�����X�R���t�H�[���R���|�[�l���g���擾
			auto elapsdTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
			m_rotationTime += elapsdTime;//!�ϐ��ɖ��t���[���G���p�\�^�C���𑫂�
			EnemyTransform->SetRotation(0, m_rotationTime, 0);//!Y���̉�]��ύX

			//!����I��������]�̏��������s���Ȃ�
			if (m_rotationTime >= m_maxRotationTime)
			{
				m_patrolRotation = false;
			}

			//!�ǂ������Ă���Ƃ��͉�]�̏��������s���Ȃ�
			if (m_seekCondition == true)
			{
				m_patrolRotation = false;
			}

		}

	}

	void BaseEnemy::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto playerChange = scene->GetPlayerChangeDirecting();//!�v���C���[�̕ϐg���J�n����
		auto gameOver = scene->GetGameOver();
		//!�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ��Ƃ�
		if (!gameOver)
		{
			//!�v���C���[���ԐM���Ă��Ȃ��Ƃ�
			if (!playerChange)
			{
				//!�|�ꂽ�A�j���[�V�����I����
				if (m_dedAnimationEnd)
				{
					VillagerDisappear();//!���l������
					HunterDisappear();//!�n���^�[������
				}


				AnimationUpdate();//!�A�j���[�V�����̍X�V

				m_StateMachine->Update();//!�X�e�[�g�}�V���̍X�V

				ObstacleAvoidance();//!��Q�����

				EnemyRandomRotation();//!��������n��
				//!���n���Ă��Ȃ��Ƃ�
				if (m_patrolRotation == false)
				{
					m_rotationTime = 0.0f;
					ApplyForce();//!�K����
				}

				m_Force = Vec3(0);

				Facade();//!�i�s����������

			}
		}
	}

}