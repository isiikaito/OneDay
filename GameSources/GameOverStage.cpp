/*!
@file GameOverStage.cpp
@brief ゲームオーバー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームオーバーステージクラス
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight()
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
	void GameOverStage::CreateGameOverSprite() {
		AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));

	}

	//初期化
	void GameOverStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateGameOverSprite();
	}

	void GameOverStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
	}

	//1Aボタン
	void GameOverStage::OnPushA() {
		//サウンド再生
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"decision", 0, 1.0f);
		PostEvent(0.0f, GetThis<GameOverStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	}

}
//end basecross
