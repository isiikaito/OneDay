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

		

		CsvFile m_StageCsv;          //!ステージCSVファイル
		CsvFile m_EnemyCsv;//!敵のトランスフォームcsvファイル
		CsvFile m_Point;//!巡回ポイントcsvファイル
		void CreateViewLight();  //!ビューの作成
		void CreateStageFloor(); //!ステージの床
		void CreatePlayer();//!プレイヤーの作成
		void CreateStageWall(); //!ステージの壁
		void CreateStageBuilding(); //!ステージの建物
		void CerateHunter();//!ハンターの作成
		void CreateTimerSprite();//!タイマースプライト作成
		

		float m_TotalTime;//!トータル時間(タイマーの作成)

		const float m_GameTime = 31.0f;


	public:
		//構築と破棄
		GameStage() :Stage(),m_TotalTime(m_GameTime) {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;
	};
}
//end basecross

