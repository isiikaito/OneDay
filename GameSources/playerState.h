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
			float m_HumanChangeTime = 0.0f;
			CsvFile m_MeatPositon;//!肉のポジションのCSVファイル
			int m_MeatNumber = 0;//!肉の位置が保存されたCSVファイルの番号
			CsvFile m_GameStageCsvD;// !建物の配置4
			float m_meatTime = 0.0f;

			shared_ptr<EfkEffect> m_TransformEfkEffect;
			shared_ptr<EfkPlay> m_TransformEfkPlay;

			shared_ptr<EfkEffect> m_MeatEfkEffect;
			shared_ptr<EfkPlay> m_MeatEfkPlay;

			//!シングルトンパターン
			HumanState(const HumanState&) = delete;//!関数を削除する
			HumanState& operator=(const HumanState&) = delete;//!operatorの中にある=を削除（コピーされないように）

		public:
			static HumanState* Instance();

			void CreateMeat();
			void CreateWoodBox();//!木箱の作成
			void ReadCsv(const wstring& FileNume);
			virtual void Enter(Player* Player)override;
			virtual void Execute(Player* Player)override;
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
			float m_WolfChangeTime = 0.0f;
			int m_Date = 0;//!日付



		public:
			static WolfState* Instance();
			//!肉の位置リセット
			void RemoveMeat();
			//!木箱のリセット
			void RemoveWoodBox();
			void MeatEat(Player* Player);
			virtual void Enter(Player* Player)override;
			virtual void Execute(Player* Player)override;
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------

		//!プレイヤーが人間から狼に返信するときのステート--------------------

		class HumanChangeDirectingState :public State<Player>
		{
		private:

			float m_humanChangeDirectingTiem = 0.0f;
			HumanChangeDirectingState(){}

			HumanChangeDirectingState(const HumanChangeDirectingState&) = delete;//!関数を削除する
			HumanChangeDirectingState& operator=(const HumanChangeDirectingState&) = delete;//!operatorの中にある=を削除(コピーされないように)
		
		public:
			static HumanChangeDirectingState* Instance();

			virtual void Enter(Player* Player)override;
			virtual void Execute(Player* Player)override;
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------

		//!プレイヤーが人間から狼に返信するときのステート--------------------



		//-------------------------------------------------------------------

	}
}