/*!
@file TitleStage.h
@brief 
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
	private:
		//入力ハンドラー
		InputHandler<TitleStage> m_InputHandler;

	public:
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

		//Aボタン
		void OnPushA();
	};


}
//end basecross
