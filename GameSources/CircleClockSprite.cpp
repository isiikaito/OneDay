/*!
@file CircleClockSprite.cpp
@brief 時計の円盤の表示
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	//!定数
	constexpr float m_TimeSpeed = 30;//!回転する速度
	constexpr float m_startScaleZ = 1.0f;//!大きさ
	constexpr float m_startPosZ = 0.8f;	 //!奥行き
	constexpr float m_helfSize = 0.5f;	 //!半分の大きさ
	
	//--------------------------------------------------------------------------------------
	///	円盤のスプライト
	//--------------------------------------------------------------------------------------
	CircleClockSprite::CircleClockSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureClock, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureClock(TextureClock),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_CircleTime(0.0f)
	{}

	CircleClockSprite::~CircleClockSprite() {}
	void CircleClockSprite::OnCreate() {
		float HelfSize = m_helfSize;
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
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_startScaleZ);
		PtrTransform->SetRotation(0, 0, 50);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_startPosZ);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureClock);
		SetDrawActive(true);

	}

	void CircleClockSprite::OnUpdate() {

		//!円盤が回転する処理
		auto circleTime = GameManager::GetDayTiem();
		//m_CircleTime += elpasedTime / m_TimeSpeed * 3.0f;
		auto SpriteTransform = GetComponent<Transform>();
		SpriteTransform->SetRotation(0, 0, circleTime);
	}

}
//end basecross