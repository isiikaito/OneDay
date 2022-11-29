/*!
@file PlayerHeartSpriteLeft.h
@author Kaito Isii
@brief プレイヤーのハートの表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	
	class PlayerHeartSpriteLeft : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		int m_RustLife;


	public:

		PlayerHeartSpriteLeft(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~PlayerHeartSpriteLeft();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;
	};

	
	
}
//end basecross
