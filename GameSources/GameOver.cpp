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
	}
	
	void GameOverSprite::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		auto gameOver=player->GetGameOverDrawActive();					//!�Q�[���I�[�o�[�X�v���C�g��\�������邩�ǂ���
		//!�\��������Ƃ�
		if (gameOver == true)
		{
			SetDrawActive(true);//!�`�悷��
			auto scene=App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
			auto gameOverSprite=scene->GetGameOverSprite(); //!�Q�[���I�[�o�[�X�v���C�g�̕\�����擾
			gameOverSprite = true;							//!�Q�[���I�[�o�[�X�v���C�g�̕\����true�ɂ���
			scene->SetGameOverSprite(gameOverSprite);		//!�Q�[���I�[�o�[�X�v���C�g�̕\����ݒ�
		}

		else
		{
			SetDrawActive(false);//!�Q�[���I�[�o�[�X�v���C�g�̕\����false�ɂ���
		}
	}
}
//end basecross