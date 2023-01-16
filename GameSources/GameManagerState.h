#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "GameManager.h"

namespace basecross
{
	namespace kaito
	{
			class GameManager;
		
		//!ゲームマネージャー-----------------------
		class GamePayState :public State<GameManager>
		{
		private:
			GamePayState(){}

			GamePayState(const GamePayState&) = delete;
			GamePayState& operator=(const GamePayState&) = delete;

		public:

			static GamePayState* Instance();

			virtual void Enter(GameManager* GamaManager)override;
			virtual void Execute(GameManager* GameManager)override;
			virtual void Exit(GameManager* GameManager)override;

		};
	}
}