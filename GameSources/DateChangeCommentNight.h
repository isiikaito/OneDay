/*!
@file DateChangeCommentNight.h
@author Kaito Isii
@brief 昼から夜に変わる時のコメントの表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class DateChangeCommentNight : public GameUI {
	private:
		bool m_Trace;								//!透明
		Vec2 m_StartScale;							//!大きさ
		Vec3 m_StartPos;							//!位置
		wstring m_TextureKey;						//!テクスチャ
		float m_textureW;							//!テクスチャアルファ値
		float m_totalTime;							//!フェードアウトインの時間
		bool m_IstexturemaxW;						//!アルファ値が最大の時
		vector<VertexPositionColor>m_BackupVertices;//!バックアップ頂点データ


		//--------------------------------------------------------------------------------------
		/*!
		@brief	フェードイン
		*/
		void TextureFadeIn();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	フェードアウト
		*/
		void TextureFadeOut();
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		DateChangeCommentNight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~DateChangeCommentNight() {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate() override;


		//--------------------------------------------------------------------------------------
		/*!
		@brief	フェードインの開始するかどうかの取得
		*/
		bool GetIstexturemaxW() const
		{
			return m_IstexturemaxW;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	フェードインの開始するかどうかの設定
		*/
		void SetIstexturemaxW(bool IstexturemaxW)
		{
			m_IstexturemaxW = IstexturemaxW;
		}

	};



}
//end basecross
