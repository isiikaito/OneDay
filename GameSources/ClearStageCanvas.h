/*!
@file ClearStageCanvas.h
@author Kaito Isii
@brief クリアステージで使うUIの生成管理
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class ClearStageCanvas : public GameObject {
	private:

		float m_clearTime;//!クリアステージの時間

		//--------------------------------------------------------------------------------------
		/*!
		@brief	クリアスプライト
		*/
		void CreateGameClearSprite();
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		ClearStageCanvas(const shared_ptr<Stage>& StagePtr);

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~ClearStageCanvas() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		void OnUpdate();
	};



}
//end basecross

