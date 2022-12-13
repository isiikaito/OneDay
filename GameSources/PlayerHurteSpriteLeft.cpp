/*!
@file PlayerHeartSprite.cpp
@author Kaito Isii
@brief プレイヤーのハートの表示
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr int m_MaxhurteCount = 3.0f; // !HP点滅の回数制限

	//--------------------------------------------------------------------------------------
	///	左側のハートスプライト
	//--------------------------------------------------------------------------------------

	PlayerHeartSpriteLeft::PlayerHeartSpriteLeft(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(2),
		m_hurt(false),
		m_hurtCount(0),
		m_hurtDefise(true),
		m_dedTime(0),
		m_GameOver(false)
	{}

	PlayerHeartSpriteLeft::~PlayerHeartSpriteLeft() {}
	void PlayerHeartSpriteLeft::OnCreate()
	{
		float HelfSize = 0.5f;

		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.8f);

		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(true);


	}

	void PlayerHeartSpriteLeft::OnUpdate()
	{
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player"); //!プレイヤーの取得
		auto PlayrHp = GetPlayer->GetPlayerHp(); //!プレイヤーのHpの取得

		if (PlayrHp == m_RustLife && m_hurtDefise == true) //!プレイヤーのHpが0の時かつ右ライフが表示されているとき
		{

			m_hurt = true; //!ライフの点滅をtrue
			if (m_hurt == true)
			{
				// !HP表示のハートが点滅する処理
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				if (m_Time >= 0.5f)
				{
					auto PtrDraw = GetComponent<PCTSpriteDraw>();
					SetDrawActive(false);

					if (m_Time >= 1.0f)
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

}
