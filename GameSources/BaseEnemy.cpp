/*!
@file BaseEnemy.cpp
@brief �G�̐e�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float m_maxRotationTime = 4.0f;
	constexpr int m_randomRange = 6;
	constexpr int m_randomNumber = 4;
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
		m_randomCount(0)
	{
		m_StateMachine = new kaito::StateMachine<BaseEnemy>(this);
		m_StateMachine->SetCurrentState(kaito::PatrolState::Instance());
	}

	void BaseEnemy::OnCreate()
	{
		//!��Q������s��
		vector<shared_ptr<GameObject>>obObjVec;
		GetStage()->GetUsedTagObjectVec(L"StageBuilding", obObjVec);
		vector<SPHERE>obVec;
		for (auto& v : obObjVec)
		{
			auto TransPtr = v->GetComponent<Transform>();

			SPHERE sp;
			sp.m_Center = TransPtr->GetPosition();
			sp.m_Radius = TransPtr->GetScale().x * 1.414f * 0.5f;
			obVec.push_back(sp);
		}
		auto ptrAvoidandce = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidandce->SetObstacleSphereVec(obVec);
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
		ptrUtil->RotToHead(1.0f);
	}

	void BaseEnemy::EnemyRandomRotation()
	{
		auto& app = App::GetApp();//!�A�v���̎擾
		auto time = app->GetElapsedTime();//!���Ԃ̎擾
		m_randomTime += time;//!�����_���^�C���Ɏ��Ԃ𑫂�

		srand(m_randomTime);//!�����̏�����
		m_randomCount = rand() % m_randomRange;

		if (m_randomCount == m_randomNumber)
		{
			m_patrolRotation = true;
		}

		if (m_patrolRotation == true)
		{
			auto EnemyTransform = GetComponent<Transform>();
			auto Time = App::GetApp()->GetElapsedTime();
			m_rotationTime += Time;
			EnemyTransform->SetRotation(0, m_rotationTime, 0);

			if (m_rotationTime >= m_maxRotationTime)
			{
				m_patrolRotation = false;
			}

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
		if (!gameOver)
		{
			if (!playerChange)
			{

				AnimationUpdate();

				m_StateMachine->Update();

				ObstacleAvoidance();

				EnemyRandomRotation();

				if (m_patrolRotation == false)
				{
					m_rotationTime = 0.0f;
					ApplyForce();
				}

				m_Force = Vec3(0);

				Facade();

			}

		}

	}

}