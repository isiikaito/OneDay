#pragma once
#include "stdafx.h"

namespace basecross
{
	namespace kaito
	{
		//!追いかけるステート-------------------------------------------
		class SeekState :public State<BaseEnemy>
		{

		private:
			SeekState() {}

			//!シングルトンパターン
			SeekState(const SeekState&) = delete;//!関数を削除する
			SeekState& operator=(const SeekState&) = delete;//!operatorの中にある=を削除（コピーされないように）
			float pointdistance = 0.0f;
			float SeekArriveRange = 30.0f;

		public:
			static SeekState* Instance();

			virtual void Enter(BaseEnemy* Enemy);
			virtual void Execute(BaseEnemy* Enemy);
			virtual void Exit(BaseEnemy* Enemy);

		};
		//!-------------------------------------------------------------

		//!巡回ステート-------------------------------------------------
		class PatrolState :public State<BaseEnemy>
		{
		private:
			PatrolState() {}
			PatrolState(const PatrolState&) = delete;
			PatrolState& operator=(const PatrolState&) = delete;

			std::vector<Vec3>m_patrol;//!巡回ポイント
			const float PatrolArriveRange = 10.0f;//!ステートを変更する条件の長さ

		public:
			static PatrolState* Instance();
			virtual void Enter(BaseEnemy* Enemy);
			virtual void Execute(BaseEnemy* Enemy);
			virtual void Exit(BaseEnemy* Enemy);

		};

		//!-------------------------------------------------------------

	}
}