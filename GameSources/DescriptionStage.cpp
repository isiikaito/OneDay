/*!
@file DescriptionStage.cpp
@brief 説明書の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionStage.h"
#include "DescriptionSpriteFront.h"
#include "DescriptionStageCanvas.h"

namespace basecross {

	constexpr int m_page = 1;//!最大ページ数(0を含んでいる)

	//!ビューの作成
	void DescriptionStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();			//!ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();	//!カメラの取得
		PtrView->SetCamera(PtrCamera);						//!カメラの設定
		PtrCamera->SetEye(m_startEye);						//!カメラの位置の設定
		PtrCamera->SetAt(m_startAt);						//!カメラの視点の設定
		auto PtrMultiLight = CreateLight<MultiLight>();		//!マルチライトの作成
		PtrMultiLight->SetDefaultLighting();				//!デフォルトのライティングを指定
	}

	//!初期化
	void DescriptionStage::OnCreate() {
		CreateViewLight();
		auto m_descriptionStageCanvas = AddGameObject<DescriptionStageCanvas>();//!説明書のキャンバスの作成
		DescriptionSprites= m_descriptionStageCanvas->GetDescriptionSprites();	//!ページごとの情報を配列に入れる
		CreatePlayBGM();
	}
	//!更新
	void DescriptionStage::OnUpdate() {
		auto& app = App::GetApp();												//!アプリの取得
		auto scene = app->GetScene<Scene>();									//!シーンの取得	
		m_InputHandler.PushHandle(GetThis<DescriptionStage>());					//!コントローラチェックして入力があればコマンド呼び出し	
		m_InputHandlerCrossKey.PushHandleCrossKey(GetThis<DescriptionStage>()); //!コントローラチェックして入力があればコマンドの呼び出し
		auto DescriptionNumber = scene->GetDescriptionStageNumber();			//!説明書の番号を受け取る

	}
	//!BGM作成
	void DescriptionStage::CreatePlayBGM()
	{
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!音量の取得
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();					//!サウンドマネージャーの取得
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, volume);	//!BGMの再生
	}
	//!音を止める
	void DescriptionStage::OnDestroy()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();	//!サウンドマネージャーの取得
		XAPtr->Stop(m_BGM);									//!BGMのストップ
	}

	//!Aボタンを押す
	void DescriptionStage::OnPushA() {
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!音量の取得
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();					//!サウンドマネージャーの取得
		ptrXA->Start(L"decision", 0, volume);								//!効果音の開始
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//!ステージ移行

	}
	//!十字キー右
	void DescriptionStage::PushHandleCrossRight()
	{
		
		auto scene = App::GetApp()->GetScene<Scene>();				//!シーンの取得
		auto volume = scene->GetSoundvolume();						//!音量の取得
		auto DescriptionNumber = scene->GetDescriptionStageNumber();//!説明書の番号の取得
		//!ページが1以下の時
		if (DescriptionNumber < m_page)
		{
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!音量の取得
			DescriptionNumber++;								//!次のページへ
			scene->SetDescriptionStageNumber(DescriptionNumber);//!現在のページ数を更新
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();	//!サウンドマネージャーの取得
			ptrXA->Start(L"FlipPage", 0, volume);				//!サウンド再生

		}
		//!説明書が2ページの時
		if (DescriptionNumber == static_cast<int>(PageNumber::second))
		{
			DescriptionSprites[static_cast<int>(PageNumber::farst)]->SetMoveTexture(true);//!テクスチャを動かす
		}
		
		
	}

	//!十字キー左
	void DescriptionStage::PushHandleCrossLeft()
	{

	
		auto scene = App::GetApp()->GetScene<Scene>();              //!シーンの取得
		auto DescriptionNumber = scene->GetDescriptionStageNumber();//!説明書の番号の取得
		//!ページが1以上の時
		if (DescriptionNumber >= m_page)							
		{
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!音量の取得
			DescriptionNumber--;											 //!前のページへ
			scene->SetDescriptionStageNumber(DescriptionNumber);			 //!現在のページ数を更新
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();//!サウンドマネージャーの取得
			ptrXA->Start(L"FlipPage", 0, volume);				 //!サウンド再生
		}

		//!説明書が1ページの時
		if (DescriptionNumber == static_cast<int>(PageNumber::farst))
		{
			DescriptionSprites[static_cast<int>(PageNumber::farst)]->SetPageBackTo(true);//!テクスチャを動かす
		}		
		
	}


}
//end basecross
