/*!
@file TitleStageCanvas.cpp
@author Kaito Isii
@brief  タイトルステージで使うUIの管理
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "TitleStageCanvas.h"


namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	ゲームキャンバス
	//--------------------------------------------------------------------------------------

	TitleStageCanvas::TitleStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	//!スプライトの作成
	void TitleStageCanvas::CreateTitleSprite() {

		auto titleSprite =GetStage()->AddGameObject<GameUI>(L"MESSAGE_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.0f));

		titleSprite->SetDrawActive(true);
	}
	

	void TitleStageCanvas::OnCreate()
	{
		//スプライトの作成
		CreateTitleSprite();
	}

	void TitleStageCanvas::OnUpdate()
	{


	}

}