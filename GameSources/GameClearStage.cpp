/**
*@file GameClear.cpp
*@brief ゲームクリア画面のソースファイル
*@author Kanazawa yuma
*@details ゲームクリア画面の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//--------------------------------------------------------------------------------------
//	ゲームオーバーステージクラス
//--------------------------------------------------------------------------------------
	void GameClearStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//スプライトの作成
	void GameClearStage::CreateGameClearSprite() {
		AddGameObject<GameClearSprite>(L"GAMECLEAR_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 0.0f));

	}

	//初期化
	void GameClearStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateGameClearSprite();
	}

	void GameClearStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameClearStage>());
	}

	//Aボタン
	void GameClearStage::OnPushA() {
		PostEvent(0.0f, GetThis<GameClearStage>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
	}
}
//end basecros