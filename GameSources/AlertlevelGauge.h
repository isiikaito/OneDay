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
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		int m_RustLife;


	public:

		AlertlevelGauge(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//!破棄
		virtual ~AlertlevelGauge();
		//!初期化
		virtual void OnCreate() override;
	
	};



}
//end basecross

