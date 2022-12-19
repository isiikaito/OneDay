/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "EfkInterfece.h"
namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	private:
		CsvFile m_GameStageCsvA; // !建物の配置
		CsvFile m_GameStageCsvB; // !建物の配置2
		CsvFile m_GameStageCsvC; // !建物の配置3
		CsvFile m_GameStageCsvD;// !建物の配置4
		CsvFile m_KeyPositon; // !鍵の配置
		CsvFile m_StageCsv;          //!ステージCSVファイル
		float m_TotalTime;//!トータル時間(タイマーの作成)
		const float m_GameTime;
		int m_keyNamber; //!鍵の配置
		
		InputHandler<GameStage> m_InputHandler;//!入力ハンドラー
		shared_ptr<EfkInterface> m_EfkInterface;

	public:
		//構築と破棄
		GameStage() :Stage(),m_TotalTime(31.0f), m_GameTime(31.0f), m_keyNamber(0) {}
		virtual ~GameStage() {}

		void CreateViewLight();  //!ビューの作成
		void CreateStageFloor(); //!ステージの床
		void CreatePlayer();//!プレイヤーの作成
		void CreateStageWall(); //!ステージの壁
		void CreateStageBuilding(); //!ステージの建物
		void CreateKey();//!鍵の作成
		void CreateClockSprite(); //!時計のスプライトの作成
		void CreateCircleClockSprite(); //!時計の円盤のスプライト
		void CreateStageGate(); //!ステージの門
		void CerateVillager();//!村人の作成
		void CerateHunter();//!ハンターの作成
		void CreateAlertlevelGauge();//!警戒度ゲージの作成
		void CreateLightingCol();//!ライトの色を変える処理
		void CreateWoodenBox();//!木箱の作成
		void CreateWood();//木の作成
		void CreateTimerSprite();//!タイマースプライト作成
		shared_ptr<SoundItem>m_BGM;
		void CreatePlayBGM();//!BGM作成
		void CreateHeartSprite();//!ハンターのライフの作成
		void CreateArrow();//!矢印の作成
		void CreateGameOver();//!ゲームオーバースプライト

		void GameTime();//!昼と夜を変える時間
		//初期化
		virtual void OnCreate()override;

		shared_ptr<EfkInterface> GetEfkInterface() const
		{
			return m_EfkInterface;
		}

		virtual void OnUpdate()override;

		virtual void OnDraw() override;

		virtual void OnDestroy() override;

		
		void OnPushA();//!Aボタン
		
		

	};
}
//end basecross

