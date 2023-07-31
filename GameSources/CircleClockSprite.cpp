/*!
@file CircleClockSprite.cpp
@brief ���v�̉~�Ղ̕\��
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

		
	//--------------------------------------------------------------------------------------
	///	�~�Ղ̃X�v���C�g
	//--------------------------------------------------------------------------------------
	CircleClockSprite::CircleClockSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureClock, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureClock, Trace, StartScale, StartPos),
		m_TextureClock(TextureClock),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_CircleTime(0.0f)
	{}

	CircleClockSprite::~CircleClockSprite() {}
	void CircleClockSprite::OnCreate() {
		
		CreateGameUI(m_TextureClock, m_Trace, m_StartScale, m_StartPos);
	}

	void CircleClockSprite::OnUpdate() {

		GameUI::OnUpdate();
		//!�~�Ղ���]���鏈��
		auto circleTime = GameManager::GetDayTiem();
		auto SpriteTransform = GetComponent<Transform>();
		SpriteTransform->SetRotation(0, 0, circleTime);
	}

}
//end basecross