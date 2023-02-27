/*!
@file CircleClockSprite.cpp
@brief ���v�̉~�Ղ̕\��
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	//!�萔
	constexpr float m_TimeSpeed = 30;//!��]���鑬�x
	constexpr float m_startScaleZ = 1.0f;//!�傫��
	constexpr float m_startPosZ = 0.8f;	 //!���s��
	constexpr float m_helfSize = 0.5f;	 //!�����̑傫��
	
	//--------------------------------------------------------------------------------------
	///	�~�Ղ̃X�v���C�g
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
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_startScaleZ);
		PtrTransform->SetRotation(0, 0, 50);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_startPosZ);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureClock);
		SetDrawActive(true);

	}

	void CircleClockSprite::OnUpdate() {

		//!�~�Ղ���]���鏈��
		auto circleTime = GameManager::GetDayTiem();
		//m_CircleTime += elpasedTime / m_TimeSpeed * 3.0f;
		auto SpriteTransform = GetComponent<Transform>();
		SpriteTransform->SetRotation(0, 0, circleTime);
	}

}
//end basecross