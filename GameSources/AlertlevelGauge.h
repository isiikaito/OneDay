/*!
@file AlertlevelGauge.h
@author Kaito Isii
@brief 警戒度のケージの表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class AlertlevelGauge : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec2 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		const Vec2 m_LeftUpperSummit;	//!左上の頂点
		const Vec2 m_LeftLowerSummit;	//!左下の頂点
		const Vec2 m_RightUpperSummit;	//!右上の頂点
		const Vec2 m_RightLowerSummit;	//!右下の頂点
		Col4 m_TextureColor;			//!テクスチャの色

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		AlertlevelGauge(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~AlertlevelGauge();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
	
	};



}
//end basecross

