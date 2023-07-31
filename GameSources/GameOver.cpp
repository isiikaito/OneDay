/*!
@file GameOver.cpp
@brief ゲームオーバー
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	ゲームオーバースプライト
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
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
		auto gameOver=player->GetGameOverDrawActive();					//!ゲームオーバースプライトを表示させるかどうか
		//!表示させるとき
		if (gameOver == true)
		{
			SetDrawActive(true);//!描画する
			auto scene=App::GetApp()->GetScene<Scene>();	//!シーンの取得
			auto gameOverSprite=scene->GetGameOverSprite(); //!ゲームオーバースプライトの表示を取得
			gameOverSprite = true;							//!ゲームオーバースプライトの表示をtrueにする
			scene->SetGameOverSprite(gameOverSprite);		//!ゲームオーバースプライトの表示を設定
		}

		else
		{
			SetDrawActive(false);//!ゲームオーバースプライトの表示をfalseにする
		}
	}
}
//end basecross