/*!
@file BaseEnemy.cpp
@brief 敵の親の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//!-------------------------------------
	//! 敵のオブジェクトの親
	//! ------------------------------------

	//!構造と破棄
	BaseEnemy::BaseEnemy(const shared_ptr<Stage>&StagePtr):
		GameObject(StagePtr),
		m_Force(0),
		m_Velocity(0),
		m_MaxSpeed(30),
		m_StateChangeSize(20.0f),
		m_Enemypatorolindex(0)
	{
		m_StateMachine = new kaito::StateMachine<BaseEnemy>(this);
		m_StateMachine->SetCurrentState(kaito::BrettGramState::Instance());
	}

	void BaseEnemy::OnCreate()
	{
		//!障害物回避行動
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

	void BaseEnemy::OnUpdate()
	{
		
		m_StateMachine->Update();

		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!障害物を避ける行動
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		m_Force = Vec3(0);

		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
	}

}