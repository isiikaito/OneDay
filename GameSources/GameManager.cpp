/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"



namespace basecross {

	//!�C���X�^���X�̐���(���̂̍쐬)
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