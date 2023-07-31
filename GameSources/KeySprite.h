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
	///	カギのスプライト
	//--------------------------------------------------------------------------------------
	class KeySprite : public GameUI {
	private:
		bool m_Trace;			//!透明度
		Vec2 m_StartScale;		//!最初の大きさ
		Vec3 m_StartPos;		//!最初の位置
		wstring m_TextureKey;	//!テクスチャの名前
		int m_keyCount;			//!カギの数

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		KeySprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos,int keyCount);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~KeySprite(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在持っているカギの数に応じてカギのテクスチャの表示
		*/
		void CurrentKeySpriteDisplay(int keyCount);

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

