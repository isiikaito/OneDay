
/*!
@file EnemyState.h
@brief 敵のステート
@author Kaito Isii
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	namespace kaito
	{

	
		//!追いかけるステート----------------------------------------------------------------------
		class SeekState :public State<BaseEnemy>
		{

		private:
			SeekState() {}
			float m_surprisedTime = 0.0f;

			//!シングルトンパターン
			SeekState(const SeekState&) = delete;			//!関数を削除する
			SeekState& operator=(const SeekState&) = delete;//!operatorの中にある=を削除（コピーされないように）
			float SeekArriveRange = 30.0f;					//!追いかけるステートのステート変更の長さ

		public:
			static SeekState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(BaseEnemy* Enemy)override;
			

		};
		//!----------------------------------------------------------------------------------------

		//!巡回ステート----------------------------------------------------------------------------
		class PatrolState :public State<BaseEnemy>
		{
		private:
			PatrolState() {}
			PatrolState(const PatrolState&) = delete;
			PatrolState& operator=(const PatrolState&) = delete;

			std::vector<Vec3>m_patrol;//!巡回ポイント
			const float PatrolArriveRange = 30.0f;//!ステートを変更する条件の長さ
		public:
			static PatrolState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(BaseEnemy* Enemy)override;

		};

		//!----------------------------------------------------------------------------------------
		
		//!ブレットグラム経路探索ステート----------------------------------------------------------
		class BrettGramState :public State<BaseEnemy>
		{
		private:
			BrettGramState(){}
			BrettGramState(const BrettGramState&) = delete;
			BrettGramState& operator=(const BrettGramState&) = delete;

			
			const float BrettGramArriveRange = 10.0f;	//!ポイントまでの距離
			int BrettGramindex = 0;						//!ブレットクラムの配列の要素数
			int maxBrettGramindex = 40;					//!取得インデックスの最大
			std::vector<Vec3>m_BrettGramPoint;			//!ブレットクラムの配列
			float Neardistance = FLT_MAX;				//!一番近い距離
			Vec3 start = Vec3(0);						//!ブレットクラムの始まりのポイント
			float m_lostTime = 0.0f;					//!見失った時間

		public:
			static BrettGramState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(BaseEnemy* Enemy) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(BaseEnemy* Enemy)override;
			void HitStageBuildingObb(BaseEnemy* Enemy);
		};

		//!殺されたときのステート-------------------------------------------------------------------
		class DedState :public State<BaseEnemy>
		{

		private:
			DedState() {}

			//!シングルトンパターン
			DedState(const DedState&) = delete;//!関数を削除する
			DedState& operator=(const DedState&) = delete;//!operatorの中にある=を削除（コピーされないように）
		
		public:
			static DedState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(BaseEnemy* Enemy)override;

		};
		//!-----------------------------------------------------------------------------------------

		//!見失った後のステート---------------------------------------------------------------------
		class LostStata :public State<BaseEnemy>
		{
		private:
			LostStata(){}
			//!シングルトンパターン
			LostStata(const LostStata&) = delete;//!関数を削除する
			LostStata& operator=(const LostStata&) = delete;//!operatorの中にある=を削除（コピーされないように）
			float m_lostTime = 0.0f;			//!見失った時間
			const float m_MaxlostTime = 2.0f;	//!見失う時間
		public:
			static LostStata* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(BaseEnemy* Enemy)override;
		};
		//!----------------------------------------------------------------------------------------

	}
}