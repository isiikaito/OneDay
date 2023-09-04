/*!
@file PlayerState.h
@brief プレイヤーのステート
@author Kaito Isii
*/
#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "Player.h"

namespace basecross
{
	namespace kaito
	{
		enum class EatCondition {
			notEat,
			firstEat,
			secondEat,
			thirdEat
		};
		//!プレイヤーが人間状態の時のステート---------------------------
		class HumanState :public State<Player>
		{
		private:
			HumanState() {}
			float m_HumanChangeTime = 0.0f;	//!変更する時間
			

			
			//!シングルトンパターン
			HumanState(const HumanState&) = delete;//!関数を削除する
			HumanState& operator=(const HumanState&) = delete;//!operatorの中にある=を削除（コピーされないように）

		public:
			static HumanState* Instance();

			
			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------


		//!プレイヤーが狼男状態の時のステート---------------------------
		class WolfState :public State<Player>
		{
		private:
			WolfState() {}
			WolfState(const WolfState&) = delete;//!関数を削除する
			WolfState& operator=(const WolfState&) = delete;//!operatorの中にある=を削除(コピーされないように)
			float m_WolfChangeTime = 0.0f;						//!変身するまでの時間
			InputHandlerB<Player> m_InputHandlerB;				//!コントローラーのボタンの取得B

			weak_ptr<Player> m_player;
		public:
			static WolfState* Instance();
			
			void MeatEat(Player* Player);

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------

		//!プレイヤーが人間から狼に変身するときのステート--------------------

		class HumanChangeDirectingState :public State<Player>
		{
		private:

			float m_humanChangeDirectingTiem = 0.0f;//!変身時間
			HumanChangeDirectingState(){}

			HumanChangeDirectingState(const HumanChangeDirectingState&) = delete;//!関数を削除する
			HumanChangeDirectingState& operator=(const HumanChangeDirectingState&) = delete;//!operatorの中にある=を削除(コピーされないように)
		
		public:
			static HumanChangeDirectingState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------

		//!プレイヤーが狼から人間に変身するときのステート--------------------
		class WolfChangeDirectingState :public State<Player>
		{
		private:

			float m_wolfChangeDirectingTiem = 0.0f;//!変身時間
			WolfChangeDirectingState() {}

			WolfChangeDirectingState(const WolfChangeDirectingState&) = delete;//!関数を削除する
			WolfChangeDirectingState& operator=(const WolfChangeDirectingState&) = delete;//!operatorの中にある=を削除(コピーされないように)

		public:
			static WolfChangeDirectingState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(Player* Player)override;
		};
		//-------------------------------------------------------------------


		//プレイヤーが死んだときのステート
		class PlayerDedState :public State<Player>
		{
		private:

			PlayerDedState() {}

			PlayerDedState(const PlayerDedState&) = delete;//!関数を削除する
			PlayerDedState& operator=(const PlayerDedState&) = delete;//!operatorの中にある=を削除(コピーされないように)

		public:
			static PlayerDedState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(Player* Player)override;
		};
		//-------------------------------------------------------------------


	}
}