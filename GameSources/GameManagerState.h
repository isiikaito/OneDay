#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "GameManager.h"
namespace basecross
{
	namespace kaito
	{
		//!オープニングカメラ-----------------------
		class OpeningCameraPlayState :public State<GameManager>
		{
		private:
			OpeningCameraPlayState() {}

			OpeningCameraPlayState(const OpeningCameraPlayState&) = delete;
			OpeningCameraPlayState& operator=(const OpeningCameraPlayState&) = delete;
		public:
			static OpeningCameraPlayState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(GameManager* gamaManager) override;

		};

		class MiddayState :public State<GameManager>
		{
		private:

			float m_middayTime = 0.0f;		//!変更する時間
			CsvFile m_MeatPositon;			//!肉のポジションのCSVファイル
			int m_MeatNumber = 0;			//!肉の位置が保存されたCSVファイルの番号
			CsvFile m_GameStageCsvD;		// !建物の配置4
			float m_meatTime = 0.0f;		//!肉の時間



			MiddayState() {}
			MiddayState(const MiddayState&) = delete;
			MiddayState& operator=(const MiddayState&) = delete;

			//!肉の生成
			void CreateMeat();
			//!木箱の生成
			void CreateWoodBox();
			//!csvの取得
			void ReadCsv(const wstring& FileNume);
		public:
			static MiddayState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(GameManager* gamaManager) override;

		};

		

		class NightState :public State<GameManager>
		{
		private:

			float m_nightTime = 0.0f;//!夜の時間
			int m_Date = 0;//!日付
			NightState() {}
			NightState(const NightState&) = delete;
			NightState& operator=(const NightState&) = delete;

			//!肉の位置リセット
			void RemoveMeat();
			//!木箱のリセット
			void RemoveWoodBox();

		public:
			static NightState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(GameManager* gamaManager) override;

		};

		

		//!ゲームオーバー-----------------------
		class GameOverState :public State<GameManager>
		{
		private:
			GameOverState() {}
			float m_dedTime = 0.0f;								//!プレイヤーが死んでからの時間

			GameOverState(const GameOverState&) = delete;
			GameOverState& operator=(const GameOverState&) = delete;

		public:
			static GameOverState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに常に呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(GameManager* gamaManager) override;
		};
	}

	
}


