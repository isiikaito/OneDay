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
		int m_MiddleLife;


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
