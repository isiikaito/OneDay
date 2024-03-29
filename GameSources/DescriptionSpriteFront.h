/*!
@file DescriptionSprite.h
@author Kaito Isii
@brief 説明書の表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	namespace kaito
	{
		//!前方宣言
		template<class entity_type>
		class State;
		//!前方宣言
		template <class entity_type>
		class StateMachine;
	}

	
	class DescriptionSpriteFront : public GameUI {
	private:
		bool m_Trace;												//!透明
		Vec2 m_StartScale;											//!大きさ
		Vec3 m_StartPos;											//!位置
		wstring m_TextureKey;										//!テクスチャ
		bool m_moveTexture;											//!テクスチャの移動するかどうか
		bool m_pageBackTo;											//!ページを戻す処理
		kaito::StateMachine<DescriptionSpriteFront>* m_StateMachine;//!ステートマシンクラスのインスタンスの生成

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		DescriptionSpriteFront(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートマシーンのアクセッサ
		*/
		const kaito::StateMachine<DescriptionSpriteFront>* GetFSM() const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~DescriptionSpriteFront();

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
		@brief	テクスチャを動かすかどうか
		*/
		bool GetMoveTexture() const
		{
			return m_moveTexture;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	テクスチャを動かすか設定する
		*/
		void SetMoveTexture(bool moveTexture)
		{
			m_moveTexture = moveTexture;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ページを戻すかどうかの取得
		*/
		bool GetPageBackTo() const
		{
			return m_pageBackTo;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ページを戻すかどうかの取得
		*/
		void SetPageBackTo(bool pageBackTo)
		{
			m_pageBackTo = pageBackTo;
		}

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートの変更
		*/
		virtual void ChangeState(kaito::State<DescriptionSpriteFront>* NewState);

	};
}
//end basecross
