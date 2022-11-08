
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses()
	{
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!テクスチャ
		wstring strTexture = dataDir +L"Texture\\"+ L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		//!タイトル画面
		strTexture = dataDir + L"Texture\\"+L"GameStart.jpg";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		//!ゲームオーバー画面
		strTexture = dataDir + L"Texture\\" + L"GameOver.jpg";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		//!ゲームクリア画面
		strTexture = dataDir + L"Texture\\"+ L"GameClear.png";
		App::GetApp()->RegisterTexture(L"GAMECLEAR_TX", strTexture);
		//!キースプライト
		strTexture = dataDir + L"Texture\\" + L"Key.png";
		App::GetApp()->RegisterTexture(L"KEY_TX", strTexture);
		

		//!床のモデル読み込み
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir,L"MayaModel\\" L"StageFloor.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh1);

		//!ハンターのモデリング
		auto staticModelMesh2 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"Hunter.bmf");
		App::GetApp()->RegisterResource(L"HUNTER_MESH", staticModelMesh2);
		
		//!壁のモデル読み込み
		auto staticModelMesh3 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageWall.bmf");
		App::GetApp()->RegisterResource(L"STAGEWALL_MESH", staticModelMesh3);
	
		//!建物のモデル読み込み
		auto staticModelMesh4 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageBuilding.bmf");
		App::GetApp()->RegisterResource(L"STAGEBUILDING_MESH", staticModelMesh4);

		//!鍵のモデル読み込み
		auto staticModelMesh5 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"Key.bmf");
		App::GetApp()->RegisterResource(L"KEY_MESH", staticModelMesh5);

		//!門のモデルの読み込み
		auto staticModelMesh6 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageGate.bmf");
		App::GetApp()->RegisterResource(L"STAGEGATE_MESH", staticModelMesh6);

		//!地面のモデルの読み込み
		auto staticModelMesh7 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"Ground.bmf");
		App::GetApp()->RegisterResource(L"GROUND_MESH", staticModelMesh7);
	}
	void Scene::OnCreate(){
		try {
			CreateResourses();//!リソース作成
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}

		

	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage")//!タイトルステージ
		{
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToGameOverStage")//!ゲームオーバーステージ
		{
			ResetActiveStage<GameOverStage>();
		}
		else if (event->m_MsgStr == L"ToGameClearStage")//!ゲームクリアステージ
		{
			ResetActiveStage<GameClearStage>();
		}
	}

}
//end basecross
