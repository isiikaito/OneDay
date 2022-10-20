/*!
@file Title.h
@brief タイトル画面
*/

#pragma once
#include "stdafx.h"

namespace basecross {

//--------------------------------------------------------------------------------------
///	タイトルスプライト
//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		
		TitleSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~TitleSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};
}
//end basecross

