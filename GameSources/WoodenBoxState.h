#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "WoodenBox.h"
namespace basecross
{
	namespace kaito
	{
		class WoodenBoxMiddayState :public State<WoodenBox>
		{
		private:

			float m_middayTime = 0.0f;		//!変更する時間


			WoodenBoxMiddayState() {}
			WoodenBoxMiddayState(const WoodenBoxMiddayState&) = delete;
			WoodenBoxMiddayState& operator=(const WoodenBoxMiddayState&) = delete;

			
		public:
			static WoodenBoxMiddayState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(WoodenBox* woodenBox) override;

		};



		class WoodenBoxNightState :public State<WoodenBox>
		{
		private:

			float m_nightTime = 0.0f;//!夜の時間
			int m_Date = 0;//!日付
			WoodenBoxNightState() {}
			WoodenBoxNightState(const WoodenBoxNightState&) = delete;
			WoodenBoxNightState& operator=(const WoodenBoxNightState&) = delete;

			

		public:
			static WoodenBoxNightState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(WoodenBox* woodenBox) override;

		};

		class WoodenBoxBreakState :public State<WoodenBox>
		{
		private:

			float m_nightTime = 0.0f;//!夜の時間
			WoodenBoxBreakState() {}
			WoodenBoxBreakState(const WoodenBoxBreakState&) = delete;
			WoodenBoxBreakState& operator=(const WoodenBoxBreakState&) = delete;



		public:
			static WoodenBoxBreakState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(WoodenBox* woodenBox) override;

		};
	
	}
}