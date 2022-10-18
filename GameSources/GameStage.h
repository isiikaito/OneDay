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

		CsvFile m_CsvC;          //!CSVファイルそのC
		void CreateViewLight();  //!ビューの作成
		void CreateStageFloor(); //!ステージの床
		void CreatePlayer();//!プレイヤーの作成
		void CreateStageWall(); //!ステージの壁

		void CerateHunter();//!ハンターの作成

		void CreateTimerSprite();//!タイマースプライト作成
		void CreateTraceSprite();//!半透明のスプライト作成
		void CreateWallSprite();//!壁模様のスプライト作成
		void CreateScrollSprite();//!スクロールするスプライト作成
		void CreateScoreSprite();//!スコアスプライト作成

		float m_TotalTime;//!トータル時間(タイマーの作成)


	public:
		//構築と破棄
		GameStage() :Stage(),m_TotalTime(30.0f) {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;
	};


}
//end basecross

