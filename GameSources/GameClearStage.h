/**
*@file GameClear.h
*@brief ゲームクリア画面のヘッダーファイル
*@author Kanazawa yuma
*@details ゲームクリア画面の実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームクリアステージクラス
	//--------------------------------------------------------------------------------------
	class GameClearStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateGameClearSprite();

		InputHandler<GameClearStage> m_InputHandler;//!入力ハンドラー

	public:
		//構築と破棄
		GameClearStage() :Stage() {}
		virtual ~GameClearStage() {}
		//初期化
		virtual void OnCreate()override;

		void OnPushA();//!Aボタン

		//更新
		virtual void OnUpdate()override;
	 };
}
//end basecross
