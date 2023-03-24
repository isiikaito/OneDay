/*!
@file TitleStage.h
@brief 
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
	private:
		//--------------------------------------------------------------------------------------
		/*!
		@brief　入力ハンドラー
		*/
		//--------------------------------------------------------------------------------------
		InputHandler<TitleStage> m_InputHandler;
		shared_ptr<SoundItem>m_BGM;//!音
		float m_keyTime;//!カギをランダムに配置する時間
		int m_keyNumber;//!カギの配置が読み込んでいるCSVの数字
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ビューの作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateViewLight();

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief　BGM作成
		*/
		//--------------------------------------------------------------------------------------
		void CreatePlayBGM();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		TitleStage() :Stage(),m_keyTime(0.0f),m_keyNumber(0) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TitleStage() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief 削除
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDestroy() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　Aボタンの処理
		*/
		//--------------------------------------------------------------------------------------
		void OnPushA();
	};


}
//end basecross
