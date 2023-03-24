/*!
@file ClearStageCanvas.cpp
@author Kaito Isii
@brief  �N���A�X�e�[�W�Ŏg��UI�̊Ǘ�
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "ClearStageCanvas.h"


namespace basecross
{
	constexpr float m_clearTime = 6.0f;
	//--------------------------------------------------------------------------------------
	///	�Q�[���L�����o�X
	//--------------------------------------------------------------------------------------

	ClearStageCanvas::ClearStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_clearTime(0.0f)
	{}

	//�X�v���C�g�̍쐬
	void ClearStageCanvas::CreateGameClearSprite()
	{
		auto gameClearSprite = GetStage()->AddGameObject<GameUI>(L"GAMECLEAR_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.0f));
		GetStage()->SetSharedGameObject(L"gameClearSprite", gameClearSprite);

	}


	void ClearStageCanvas::OnCreate()
	{
		CreateGameClearSprite();
	}

	void ClearStageCanvas::OnUpdate()
	{
		auto gameClearSprite = GetStage()->GetSharedGameObject<GameUI>(L"gameClearSprite");
		auto elapsedTIme = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		m_clearTime += elapsedTIme;//!���Ԃ̕ϐ��ɃG���p�\�^�C���𑫂�
		if (m_clearTime <= m_clearTime)
		{        
		gameClearSprite->SetDrawActive(true);
		}
		else {
			gameClearSprite->SetDrawActive(false);

		}
		

	}

}