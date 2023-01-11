/*!
@file KeyFrame.h
@author isii kaito
@brief カギの枠の表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class KeyFrame : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureClock; //!テクスチャ


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		KeyFrame(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~KeyFrame(){}

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
		virtual void OnUpdate()override {}

	};
}
//end basecross

