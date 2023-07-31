/*!
@file PlayerHeartSprite.cpp
@author Kaito Isii
@brief プレイヤーのハートの表示
*/


#include "stdafx.h"
#include "Project.h"
#include "PlayerHurteSprite.h"

namespace basecross
{
	constexpr int MAXHURTECOUNT = 3; // !HP点滅の回数制限
	constexpr float FEADOUTTIME = 0.5;//!ハートの点滅時に消える時間
	constexpr float FEADINTIME = 1.0f;//!ハートの点滅時が付く時間
	//--------------------------------------------------------------------------------------
	///	ハートスプライト
	//--------------------------------------------------------------------------------------

	PlayerHurteSprite::PlayerHurteSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos, int currentHp,bool hurtDefise) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(2),
		m_hurt(false),
		m_hurtCount(0),
		m_hurtDefise(hurtDefise),
		m_dedTime(0),
		m_GameOver(false),
		m_Time(0.0f),
		m_currentHp(currentHp)
	{}


	void PlayerHurteSprite::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
	}

	void PlayerHurteSprite::FlashingHurteSprite(int currentHp)
	{
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");	//!プレイヤーの取得
		auto PlayrHp = GetPlayer->GetPlayerHp();								//!プレイヤーのHpの取得
		
		//!プレイヤーのHpが0の時かつ右ライフが表示されているとき
		if (PlayrHp <= currentHp && m_hurtDefise == true) 
		{

			m_hurt = true; //!ライフの点滅をtrue
			if (m_hurt == true)
			{
				// !HP表示のハートが点滅する処理
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				//!消える時間の時
				if (m_Time >= FEADOUTTIME)
				{
					SetDrawActive(false);//!非表示
					//!表示時間の時
					if (m_Time >= FEADINTIME)
					{
						SetDrawActive(true);//!表示
						m_hurtCount++;		//!点滅した回数
						m_Time = 0;			//!時間のリセット
					}
					
				}
			}

			// !ハートの点滅回数が最大になった時
			if (m_hurtCount == MAXHURTECOUNT) //!一定の回数点滅したら
			{
				m_hurtDefise = false;//!更新をやめる
				
                SetDrawActive(false); //!ライフの表示を完全に消す
				
			}
		}

	}

	void PlayerHurteSprite::OnUpdate()
	{
		if (m_hurtDefise)
		{
		 GameUI::OnUpdate();
		}

		FlashingHurteSprite(m_currentHp);

	}


}
