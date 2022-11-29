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
			float SeekArriveRange = 30.0f;//!追いかけるステートのステート変更の長さ

		public:
			static SeekState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

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
			const float PatrolArriveRange = 20.0f;//!ステートを変更する条件の長さ

		public:
			static PatrolState* Instance();
			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};

		//!-------------------------------------------------------------
		
		class BrettGramState :public State<BaseEnemy>
		{
		private:
			BrettGramState(){}
			BrettGramState(const BrettGramState&) = delete;
			BrettGramState& operator=(const BrettGramState&) = delete;

			
			const float BrettGramArriveRange = 5.0f;//!ポイントまでの距離
			int BrettGramindex = 0;//!ブレットクラムの配列の要素数
			std::vector<Vec3>m_BrettGramPoint;//!ブレットクラムの配列
			float Neardistance = FLT_MAX;//!一番近い距離
			Vec3 start = Vec3(0);//!ブレットクラムの始まりのポイント

		public:
			static BrettGramState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy) override;
			virtual void Exit(BaseEnemy* Enemy)override;
		};

	}
}