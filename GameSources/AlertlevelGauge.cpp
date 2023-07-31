/*!
@file AlertlevelGauge.cpp
@author Kaito Isii
@brief  警戒度のケージの表示
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float STARTSCALEZ = 1.0f;//!大きさ
	constexpr float STARTPOSZ = 1.0f;	 //!奥行き
	constexpr float HELFSIZE = 0.5f;	 //!半分の大きさ
	//--------------------------------------------------------------------------------------
	///	警戒度のスプライト
	//--------------------------------------------------------------------------------------

	AlertlevelGauge::AlertlevelGauge(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f)),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}

	AlertlevelGauge::~AlertlevelGauge() {}
	void AlertlevelGauge::OnCreate()
	{
		float HelfSize = HELFSIZE;

		//!頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), m_TextureColor,m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0),m_TextureColor, m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), m_TextureColor, m_RightLowerSummit) },
		};

		//!インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, STARTPOSZ);

		//!頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(true);


	}

}
