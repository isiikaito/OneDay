/*!
@file DescriptionStageCanvas.cpp
@author Kaito Isii
@brief  説明書ステージで使うUIの管理
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "DescriptionStageCanvas.h"
#include "DescriptionSpriteFront.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	ゲームキャンバス
	//--------------------------------------------------------------------------------------

	DescriptionStageCanvas::DescriptionStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	//表の説明書のスプライトの作成
	void DescriptionStageCanvas::CreateDescriptionSpriteFront() {

		m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(L"DescriptionSprite1_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.1f)));

		m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(L"DescriptionSprite2_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.2f)));


	}

	void DescriptionStageCanvas::OnCreate()
	{
		//スプライトの作成
		CreateDescriptionSpriteFront();
	}

	void DescriptionStageCanvas::OnUpdate()
	{


	}


}