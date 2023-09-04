/*!
@file DescriptionStageCanvas.h
@author Kaito Isii
@brief 説明書ステージで使うUIの生成管理
*/

#pragma once
#include "stdafx.h"
#include "DescriptionSpriteFront.h"

namespace basecross {


	class DescriptionStageCanvas : public GameObject {
	private:

		std::vector<shared_ptr<DescriptionSpriteFront>> m_DescriptionSprites;//!説明書のデータを入れた配列

		//--------------------------------------------------------------------------------------
		/*!
		@brief	表の説明書のスプライトの作成
		*/
		void CreateDescriptionSpriteFront();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		DescriptionStageCanvas(const shared_ptr<Stage>& StagePtr);


		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~DescriptionStageCanvas() {}

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief	説明書の取得
		*/
		std::vector<shared_ptr<DescriptionSpriteFront>>GetDescriptionSprites() const
		{
			return m_DescriptionSprites;
		}
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


