/**
*@file GameClear.h
*@brief ゲームクリア画面のヘッダーファイル
*@author Ayumu Muroi
*@details ゲームクリア画面の実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームクリアステージクラス
	//--------------------------------------------------------------------------------------
	class GameClearStage : public Stage {
	private:
		InputHandler<GameClearStage> m_InputHandler;//!入力ハンドラー		
		shared_ptr<SoundItem>m_BGM; //!BGM
		CsvFile m_StageCsv;   //!ステージCSVファイル
		float m_stageChangeTime =0.0f;
		bool m_setTexture=false;

	public:
		
		//ビューの作成
		void CreateViewLight();
		void CreatePlayer(); //!プレイヤーの追加
		//スプライトの作成
		void CreateGameClearSprite();
		void CreateStageFloor(); //!床
		void CreateStageBuilding(); //!建物 
		void CreateStageWall(); //!壁
		void CreateStageGate(); //!門
		void CerateGoalPlayer(); //!ゴールのプレイヤー
		CsvFile m_GameStageCsvD;// !建物の配置4

		//構築と破棄
		GameClearStage() :Stage() {}
		virtual ~GameClearStage() {}
		//初期化
		virtual void OnCreate()override;

		void OnPushA();//!Aボタン
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief 消す
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDestroy() override;
		//更新
		virtual void OnUpdate()override;
	 };
}
//end basecross
