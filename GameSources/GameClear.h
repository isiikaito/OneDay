/**
*@file GameClear.h
*@brief ゲームクリア画面のヘッダーファイル
*@author Kanazawa yuma
*@details ゲームクリア画面の実装
*/
#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	ゲームクリアスプライト
//--------------------------------------------------------------------------------------
	class GameClearSprite : public GameObject {
	private:
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:

		GameClearSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~GameClearSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};

}
//end basecross

