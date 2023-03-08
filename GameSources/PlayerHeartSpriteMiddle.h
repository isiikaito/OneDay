/*!
@file PlayerHeartSprite.h
@author Kaito Isii
@brief プレイヤーのハートの表示
*/

#pragma once

#include "stdafx.h"

namespace basecross 
{
	class PlayerHeartSpriteMiddle : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		bool m_hurt;//!ライフの点滅を開始するかどうか
		int m_MiddleLife;//!現在のHP
		float m_tiem;//!点滅している時間
		int m_hurtCount;//!点滅した回数
		bool m_hurtDefise;//!ハートの表示を消す


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		PlayerHeartSpriteMiddle(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerHeartSpriteMiddle();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};
}
