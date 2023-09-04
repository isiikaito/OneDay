/*!
@file GameStage.cpp
@brief ゲームステージ実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
#include "GameManagerState.h"


namespace basecross
{


	GameManager::GameManager(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr)
	{
		m_StateMachine = new kaito::StateMachine<GameManager>(this);
		m_StateMachine->SetCurrentState(kaito::OpeningCameraPlayState::Instance());	//!現在のステート
	}
	float GameManager::GetElpasedTiem()
	{
		auto gameElpasedTime = App::GetApp()->GetScene<Scene>()->GetGameTime();//!ゲームの進行時間
		return gameElpasedTime;
	}

	float GameManager::GetDayTiem()
	{
		auto dayTime = App::GetApp()->GetScene<Scene>()->GetDayTime();//!変身する時間
		return dayTime;
	}
	void GameManager::OnUpdate()
	{
		m_StateMachine->Update();//!ステートマシンの更新

	}

	void GameManager::ChangeState(kaito::State<GameManager>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!ステートを変更する
	}

	shared_ptr<Player>GameManager::GetPlayer()const 
	{
		return std::dynamic_pointer_cast<Player>(GetStage()->GetSharedObject(L"Player"));//!プレイヤーの取得
	}
}