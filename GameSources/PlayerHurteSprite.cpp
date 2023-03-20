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
	constexpr int m_MaxhurteCount = 3; // !HP点滅の回数制限
	constexpr float m_feadOutTime = 0.5;//!ハートの点滅時に消える時間
	constexpr float m_feadInTime = 1.0f;//!ハートの点滅時が付く時間
	//--------------------------------------------------------------------------------------
	///	左側のハートスプライト
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
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player"); //!プレイヤーの取得
		auto PlayrHp = GetPlayer->GetPlayerHp(); //!プレイヤーのHpの取得
		
		if (PlayrHp <= currentHp && m_hurtDefise == true) //!プレイヤーのHpが0の時かつ右ライフが表示されているとき
		{

			m_hurt = true; //!ライフの点滅をtrue
			if (m_hurt == true)
			{
				// !HP表示のハートが点滅する処理
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				if (m_Time >= m_feadOutTime)
				{
					SetDrawActive(false);

					if (m_Time >= m_feadInTime)
					{
						SetDrawActive(true);
						m_hurtCount++; //!点滅した回数
						m_Time = 0;
					}
					return;
				}
			}

			// !ハートの点滅回数が最大になった時
			if (m_hurtCount == m_MaxhurteCount) //!一定の回数点滅したら
			{
				m_hurtDefise = false;
				
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
