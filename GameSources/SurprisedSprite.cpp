/*!
@file SurprisedSprite.cpp
@author Kaito Isii
@brief ビックリマークの表示
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	ビックリマークスプライト
	//--------------------------------------------------------------------------------------

	SurprisedSprite::SurprisedSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_SurprisedTime(0.0f)

	{}

	SurprisedSprite::~SurprisedSprite() {}
	void SurprisedSprite::OnCreate()
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
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(false);


	}

	void SurprisedSprite::OnUpdate()
	{
		auto GetPlayer=GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerFound=GetPlayer->GetPlayerFound();
		//!プレイヤーが見つかったら
		if (PlayerFound == true)
		{
			float Time = App::GetApp()->GetElapsedTime();//!時間の取得
			m_SurprisedTime += Time;
			
			auto PtrDraw = GetComponent<PCTSpriteDraw>();//!描画コンポーネント
				SetDrawActive(true);
				//!2秒たったら
			if (m_SurprisedTime >= 2)
			{

				PlayerFound = false;//!発見をやめる
				GetPlayer->SetPlayerFound(PlayerFound);
			}
			
		}
		//!見つけることをやめたら
		if (PlayerFound == false)
		{
			m_SurprisedTime = 0.0f;//!驚く時間を0秒にする
			SetDrawActive(false);
			
		}
		
	}
}
