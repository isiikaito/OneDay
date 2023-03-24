/*!
@file TitleStageCanvas.cpp
@author Kaito Isii
@brief  �^�C�g���X�e�[�W�Ŏg��UI�̊Ǘ�
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "TitleStageCanvas.h"


namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�Q�[���L�����o�X
	//--------------------------------------------------------------------------------------

	TitleStageCanvas::TitleStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	//!�X�v���C�g�̍쐬
	void TitleStageCanvas::CreateTitleSprite() {

		auto titleSprite =GetStage()->AddGameObject<GameUI>(L"MESSAGE_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.0f));

		titleSprite->SetDrawActive(true);
	}
	

	void TitleStageCanvas::OnCreate()
	{
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
	}

	void TitleStageCanvas::OnUpdate()
	{


	}

}