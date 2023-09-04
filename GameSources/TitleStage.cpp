/*!
@file TitleStage.cpp
@brief 
*@author isii kaito
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "TitleStageCanvas.h"

namespace basecross {
	
	constexpr int RANDOMSPEED = 22;			//乱数の時間
	constexpr int RANDOMNUMBER = 3;			//ランダムに選ぶ数字
	constexpr float BUTTONVOLUME = 1.0f;	//音量
	constexpr float TITLEVOLUME = 0.5f;		//タイトルBGM
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(m_startEye);
		PtrCamera->SetAt(m_startAt);
		auto PtrMultiLight = CreateLight<MultiLight>();//マルチライトの作成
		PtrMultiLight->SetDefaultLighting();//デフォルトのライティングを指定
	}

	

	//!初期化
	void TitleStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleStageCanvas>();
		CreatePlayBGM();//!BGMの作成
		auto scene = App::GetApp()->GetScene<Scene>();
		scene->SetGameOver(false);
	    scene->SetGameStrat(true);
		scene->SetGameOverSprite(false);

	}

	//!更新
	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();//!アプリの取得
		auto scene = app->GetScene<Scene>();//!シーンの取得
		
		auto deltaTime = app->GetElapsedTime();//!デルタタイムの取得
		m_keyTime += deltaTime * RANDOMSPEED;
		srand((unsigned)std::time(0));
		m_keyNumber = rand() % RANDOMNUMBER;
		scene->SetKeyNamber(m_keyNumber);


		//!コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}

	//!BGMの再生
	void TitleStage::CreatePlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, TITLEVOLUME);
	}

	//! BGMのストップ
	void TitleStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//!Aボタン
	void TitleStage::OnPushA() {
		//!サウンド再生
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"decision", 0, BUTTONVOLUME);
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToDescriptionStage");
	}


}
//end basecross
