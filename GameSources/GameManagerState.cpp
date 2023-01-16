#include "stdafx.h"
#include "Project.h"
#include "GameManagerState.h"
#include "GameManager.h"

namespace basecross
{
	namespace kaito
	{
		//!ゲームマネージャー
		GamePayState* GamePayState::Instance()
		{
			static GamePayState instance;
			return &instance;
		}

		void GamePayState::Enter(GameManager* GameManager)
		{
			
		}

		void GamePayState::Execute(GameManager* GameManager)
		{

		}

		void GamePayState::Exit(GameManager* GameManager)
		{

		}

	}
}