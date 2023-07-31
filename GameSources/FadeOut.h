/*!
@file FadeOut.h
@brief フェードアウト
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゲージ
	class FadeOut : public GameObject
	{
		bool m_Trace;			//透明
		Vec2 m_StartScale;		//大きさ
		Vec3 m_StartPos;		//位置
		float m_TotalTime;		//時間の取得
		Col4 m_TextureColor;	//!テクスチャの色


		//バックアップ頂点データ
		vector<VertexPositionColor>m_BackupVertices;


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~FadeOut();

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
