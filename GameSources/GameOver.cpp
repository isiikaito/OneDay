/*!
@file GameOver.cpp
@brief �Q�[���I�[�o�[
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Q�[���I�[�o�[�X�v���C�g
	//--------------------------------------------------------------------------------------
	GameOverSprite::GameOverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	GameOverSprite::~GameOverSprite() {}
	void GameOverSprite::OnCreate() 
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
		SetDrawActive(false);//!�Q�[���I�[�o�[�X�v���C�g�̕\����false�ɂ���
		GetStage()->SetSharedGameObject(L"GameOverSprite",GetThis<GameOverSprite>());
	}
	
	void GameOverSprite::OnUpdate()
	{
	
		

	}
}
//end basecross