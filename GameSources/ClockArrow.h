/*!
@file ClockArrow.h
@author Kaito Isii
@brief 矢印の表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class ClockArrow : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		int m_RustLife;
		float m_rotationZ;//!回転のz軸を変える

	public:

		ClockArrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const float& RotationZ, const Vec2& StartPos);
		//!破棄
		virtual ~ClockArrow(){}
		//!初期化
		virtual void OnCreate() override;
		

	};



}
//end basecross
