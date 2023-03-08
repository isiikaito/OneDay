/*!
@file PlayerHeartSprite.h
@author Kaito Isii
@brief プレイヤーのハートの表示
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{

	class PlayerHeartSpriteRight : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		int m_RustLife;
		float m_Time; // !切り替える時間
		int m_hurtCount; // !HPの点滅回数
		bool m_hurt; // !ハートのありなし
		bool m_hurtDefise;
		bool m_IsGameOver;
		float m_dedTime;
		bool m_GameOver;

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		PlayerHeartSpriteRight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerHeartSpriteRight();

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

