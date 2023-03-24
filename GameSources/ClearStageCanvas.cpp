/*!
@file ClearStageCanvas.cpp
@author Kaito Isii
@brief  クリアステージで使うUIの管理
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "ClearStageCanvas.h"


namespace basecross
{
	constexpr float m_clearTime = 6.0f;
	//--------------------------------------------------------------------------------------
	///	ゲームキャンバス
	//--------------------------------------------------------------------------------------

	ClearStageCanvas::ClearStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_clearTime(0.0f)
	{}

	//スプライトの作成
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
		auto elapsedTIme = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		m_clearTime += elapsedTIme;//!時間の変数にエルパソタイムを足す
		if (m_clearTime <= m_clearTime)
		{        
		gameClearSprite->SetDrawActive(true);
		}
		else {
			gameClearSprite->SetDrawActive(false);

		}
		

	}

}