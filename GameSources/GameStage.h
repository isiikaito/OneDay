/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	private:
		CsvFile m_GameStageCsvA; // !建物の配置
		CsvFile m_GameStageCsvB; // !建物の配置2
		CsvFile m_GameStageCsvC; // !建物の配置3
		CsvFile m_StageCsv;          //!ステージCSVファイル
		float m_TotalTime;//!トータル時間(タイマーの作成)
		const float m_GameTime;


	public:
		//構築と破棄
		GameStage() :Stage(),m_TotalTime(31.0f), m_GameTime(31.0f) {}
		virtual ~GameStage() {}

		void CreateViewLight();  //!ビューの作成
		void CreateStageFloor(); //!ステージの床
		void CreatePlayer();//!プレイヤーの作成
		void CreateStageWall(); //!ステージの壁
		void CreateStageBuilding(); //!ステージの建物
		void CreateKey();//!鍵の作成
		void CreateClockSprite(); //!時計のスプライトの作成
		void CreateStageGate(); //!ステージの門
		void CerateVillager();//!村人の作成
		void CerateHunter();//!ハンターの作成
		void CreateAlertlevelGauge();//!警戒度ゲージの作成
		void CreateLightingCol();//!ライトの色を変える処理
		void CreateWoodenBox();//!木箱の作成
		void CreateTimerSprite();//!タイマースプライト作成
		shared_ptr<SoundItem>m_BGM;
		void CreatePlayBGM();//!BGM作成
		void CreateHeartSprite();//!ハンターのライフの作成
		void CreateArrow();//!矢印の作成
		void CreateGameOver();//!ゲームオーバースプライト
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy() override;

		
		//void OnPushA();//!Aボタン
		
		

	};
}
//end basecross

