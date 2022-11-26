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
		m_MaxSpeed(10),
		m_StateChangeSize(20.0f),
		m_Enemypatorolindex(0)
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

	shared_ptr<GameObject>BaseEnemy::GetTarget()const {
		return GetStage()->GetSharedObject(L"Player");
	}

	void BaseEnemy::OnUpdate()
	{
		m_StateMachine->Update();
		ApplyForce();
		m_Force = Vec3(0);

		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
	}

}