/*!
@file TitleStageCanvas.h
@author Kaito Isii
@brief タイトルステージで使うUIの生成管理
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class TitleStageCanvas : public GameObject {

		//--------------------------------------------------------------------------------------
		/*!
		@brief	タイトル画面のスプライトの作成
		*/
		void CreateTitleSprite();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		TitleStageCanvas(const shared_ptr<Stage>& StagePtr);

		
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~TitleStageCanvas() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		void OnUpdate(){}
	};



}
//end basecross

