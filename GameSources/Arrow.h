/*!
@file Arrow.h
@author Kaito Isii
@brief 矢印の表示
*/

#pragma once
#include "stdafx.h"
#include "GameUI.h"
namespace basecross {


	class Arrow : public GameUI {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		int m_RustLife;		  //!最後のライフ
		Vec3 m_secondPosition;//!警戒度ゲージがレベル2の時
		Vec3 m_firstPosition; //!警戒度ゲージがレベル3の時

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		Arrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		virtual ~Arrow();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		virtual void OnUpdate()override;

	};



}
//end basecross
