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
			float m_surprisedTime = 0.0f;

			//!シングルトンパターン
			SeekState(const SeekState&) = delete;//!関数を削除する
			SeekState& operator=(const SeekState&) = delete;//!operatorの中にある=を削除（コピーされないように）
			float SeekArriveRange = 30.0f;//!追いかけるステートのステート変更の長さ
			float BrettGramRange = 10.0f;
			float m_SurprisedTime=0.0f;

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
			const float PatrolArriveRange = 30.0f;//!ステートを変更する条件の長さ
			float m_lostTime = 0.0f;
			bool m_IspositionLiset=false;
		public:
			static PatrolState* Instance();
			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};

		//!-------------------------------------------------------------
		
		//!ブレットグラム経路探索ステート-------------------------------------------------
		class BrettGramState :public State<BaseEnemy>
		{
		private:
			BrettGramState(){}
			BrettGramState(const BrettGramState&) = delete;
			BrettGramState& operator=(const BrettGramState&) = delete;

			
			const float BrettGramArriveRange = 10.0f;//!ポイントまでの距離
			int BrettGramindex = 0;//!ブレットクラムの配列の要素数
			int maxBrettGramindex = 40;
			std::vector<Vec3>m_BrettGramPoint;//!ブレットクラムの配列
			float Neardistance = FLT_MAX;//!一番近い距離
			Vec3 start = Vec3(0);//!ブレットクラムの始まりのポイント
			float m_lostTime = 0.0f;

		public:
			static BrettGramState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy) override;
			virtual void Exit(BaseEnemy* Enemy)override;
			void HitStageBuildingObb(BaseEnemy* Enemy);
		};

		//!殺されたときのステート-------------------------------------------
		class DedState :public State<BaseEnemy>
		{

		private:
			DedState() {}

			//!シングルトンパターン
			DedState(const DedState&) = delete;//!関数を削除する
			DedState& operator=(const DedState&) = delete;//!operatorの中にある=を削除（コピーされないように）
		
		public:
			static DedState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};
		//!-------------------------------------------------------------

		//!見失った後のステート-----------------------------------------
		class LostStata :public State<BaseEnemy>
		{
		private:
			LostStata(){}
			//!シングルトンパターン
			LostStata(const LostStata&) = delete;//!関数を削除する
			LostStata& operator=(const LostStata&) = delete;//!operatorの中にある=を削除（コピーされないように）
			float m_lostTime = 0.0f;
			float m_MaxlostTime = 2.0f;
		public:
			static LostStata* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;
		};
		//!---------------------------------------------------------------

	}
}