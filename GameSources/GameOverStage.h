/*!
@file GameOverStage.h
@brief ゲームオーバー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームオーバーステージクラス
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		
	private:
		InputHandler<GameOverStage> m_InputHandler;//!入力ハンドラー

	public:
		
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateGameOverSprite();
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//初期化
		virtual void OnCreate()override;

		//void OnPushA();//!Aボタン

		////更新
		//virtual void OnUpdate()override;

	};




}
//end basecross

