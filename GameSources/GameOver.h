/*!
@file GameOver.h
@brief ゲームオーバー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	ゲームオーバースプライト
//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameObject {
	private:
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:

		GameOverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~GameOverSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};
}
//end basecross
