/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"



namespace basecross {

	//!インスタンスの生成(実体の作成)
	GameManager* GameManager::Instance()
	{
		static GameManager instance;
		return&instance;
	}

	void GameManager::GetStage()
	{
		GameManager::Instance()->GetStage();
	}

	
	
	void GameManager::ChangeState(kaito::State<GameManager>* NewState)
	{

		m_StateMachine->ChangeState(NewState);
	}

	void GameManager::OnUpdate()
	{


		m_StateMachine->Update();

	}
	
	 float GameManager::GetElpasedTiem()
	{
		auto gameElpasedTime = App::GetApp()->GetScene<Scene>()->GetGameTime();
		return gameElpasedTime;
	}
	

}