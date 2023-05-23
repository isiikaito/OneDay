/*!
@file GameUI.h
@author Kaito Isii
@brief ゲーム画面のUIの表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class GameUI : public GameObject {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartRotation;//!回転
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale,Vec3&Rotation, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ポリゴンの生成とテクスチャの決定
		*/
		void CreateGameUI( const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos);
	

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		virtual ~GameUI();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　透明度の設定
		*/
		//--------------------------------------------------------------------------------------
		void SetTrace(bool trace)
		{
			m_Trace = trace;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　大きさの設定
		*/
		//--------------------------------------------------------------------------------------
		void SetScale(Vec2 scale)
		{
			m_StartScale = scale;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 位置の設定
		*/
		//--------------------------------------------------------------------------------------
		void SetPos(Vec3 pos)
		{
			m_StartPos = pos;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief テクスチャネームの設定
		*/
		//--------------------------------------------------------------------------------------
		void SetTexturekey(wstring texturekey)
		{
			m_TextureKey = texturekey;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		 void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		 void OnUpdate();
	};



}
//end basecross