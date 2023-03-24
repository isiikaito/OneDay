/*!
@file DescriptionStageCanvas.cpp
@author Kaito Isii
@brief  �������X�e�[�W�Ŏg��UI�̊Ǘ�
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "DescriptionStageCanvas.h"
#include "DescriptionSpriteFront.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�Q�[���L�����o�X
	//--------------------------------------------------------------------------------------

	DescriptionStageCanvas::DescriptionStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	//�\�̐������̃X�v���C�g�̍쐬
	void DescriptionStageCanvas::CreateDescriptionSpriteFront() {

		m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(L"DescriptionSprite1_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.1f)));

		m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(L"DescriptionSprite2_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.2f)));


	}

	void DescriptionStageCanvas::OnCreate()
	{
		//�X�v���C�g�̍쐬
		CreateDescriptionSpriteFront();
	}

	void DescriptionStageCanvas::OnUpdate()
	{


	}


}