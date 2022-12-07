/*!
@file Arrow.cpp
@author Kaito Isii
@brief  矢印の表示
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr int first = 1;
	constexpr int second = 2;
	//--------------------------------------------------------------------------------------
	///	矢印
	//--------------------------------------------------------------------------------------

	Arrow::Arrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0)
	{}

	Arrow::~Arrow() {}
	void Arrow::OnCreate()
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
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(true);

	}

	void Arrow::OnUpdate()
	{

		//auto alertlevelCount = App::GetApp()->GetScene<Scene>()->GetAlertlevelCount();//!シーンの取得
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayrHp = GetPlayer->GetPlayerHp();
		auto ptrTransform = GetComponent<Transform>();//!矢印のテクスチャの取得
		//!警戒度が1の時
		if (PlayrHp == second)
		{
          ptrTransform->SetPosition(Vec3(460.0f, 330.0f,0.0f));
		}
		if (PlayrHp == first)
		{
			ptrTransform->SetPosition(Vec3(530.0f, 330.0f, 0.0f));
		}
			
	}

}
