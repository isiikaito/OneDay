/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateStageFloor()
	{
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"StageFloor");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<StageFloor>(Scale, Rot, Pos);
		}

	}
	//スコアスプライト作成
	void GameStage::CreateTimerSprite() {
		AddGameObject<Timer>(2,
			L"NUMBER_TX",
			true,
			Vec2(160.0f, 80.0f),//元は(320.0f,80,0f)
			Vec3(-550.0f, 330.0f, 10.0f));//元は(0.0f, 0.0f, 0.0f)

	}
	//!プレイヤーの作成
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();//!プレイヤーの作成
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}
	//!ハンターの作成
	void GameStage::CerateHunter()
	{
		 AddGameObject<Hunter>();
	}

	void GameStage::OnCreate() {
		try {

			SetPhysicsActive(true);//物理計算有効
			// 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSVファイルその読み込み
			m_CsvC.SetFileName(DataDir + L"stage0.csv");
			m_CsvC.ReadCsv();
			CreateTimerSprite();

			CreateViewLight();//ビューとライトの作成
			CreateStageFloor();//!ステージの床の作成
			CreatePlayer();//!プレーヤーの作成
			CerateHunter();//!ハンターの作成
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime;
		if (m_TotalTime >= 30.0f) {
			m_TotalTime = 0.0f;
		}
		////スコアを更新する
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_TotalTime);
	}

}
//end basecross
