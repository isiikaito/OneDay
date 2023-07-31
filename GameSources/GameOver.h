/*!
@file GameOver.h
@brief ゲームオーバー
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"
#include "GameUI.h"
namespace basecross {
//--------------------------------------------------------------------------------------
///	ゲームオーバースプライト
//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameUI {
	private:
		bool m_Trace;			//!表示するかどうか
		Vec2 m_StartScale;		//スタートの大きさ
		Vec3 m_StartPos;		//スタート位置
		wstring m_TextureKey;	//!使用テクスチャの名前

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		GameOverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~GameOverSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate()override;
	};
}
//end basecross
