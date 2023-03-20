/*!
@file PlayerHeartSpriteLeft.h
@author Kaito Isii
@brief プレイヤーのハートの表示
*/

#pragma once
#include "stdafx.h"
#include "GameUI.h"

namespace basecross {

	
	class PlayerHurteSprite : public GameUI {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		int m_RustLife;       //!右のハート
		float m_Time;         // !切り替える時間
		int m_hurtCount;      // !HPの点滅回数
		bool m_hurt;          // !ハートのありなし
		bool m_hurtDefise;    //!ハートを消す
		float m_dedTime;      //!点滅している時間
		bool m_GameOver;      //!ゲームオーバーしたかどうか
		int m_currentHp;


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		PlayerHurteSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos,int currentHp,bool hurtDefise);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerHurteSprite(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ライフのテクスチャの表示を点滅させる
		*/
		//--------------------------------------------------------------------------------------
		void FlashingHurteSprite(int currentHp);
			
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
//end basecross
