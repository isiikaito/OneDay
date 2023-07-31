/**
*@file GameClear.cpp
*@brief ゲームクリア画面のソースファイル
*@author  Ayumiu Muroi
*@details ゲームクリア画面の実装
*/

#include "stdafx.h"
#include "Project.h"
#include "GoalPlayer.h"
#include "ClearStageCanvas.h"

namespace basecross {
//--------------------------------------------------------------------------------------
//	ゲームクリアステージクラス
//--------------------------------------------------------------------------------------
	void GameClearStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(10.0f, 20.0f, 130.0f));
		PtrCamera->SetAt(Vec3(10.0f, 10.0f, 100.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	

	// !ステージの床
	void GameClearStage::CreateStageFloor()
	{
		
		//CSVの行単位の配列
		vector<wstring>LineVec;

		//0番目のカラムがL"stageObject"である行を抜き出す
		m_StageCsv.GetSelect(LineVec, 0, L"StageFloor");
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

	
	//!ゴール時のプレイヤーの作成
	void GameClearStage::CerateGoalPlayer()
	{
	AddGameObject<GoalPlayer>(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f, 50.0f, 80.0f)); //!ゴールプレイヤーの作成
	}

	// !ステージの建物
	void GameClearStage::CreateStageBuilding()
	{
		auto group = CreateSharedObjectGroup(L"StageBuilding_Group");

		
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto& LineVec = m_GameStageCsvD.GetCsvVec(); // csvファイルをセットする
		for (size_t i = 0; i < LineVec.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//XとZの位置を計算
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"1")
				{
					AddGameObject<StageBuilding>(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 5.0f, ZPos));
				}
			}
		}

	}

	// !ステージの壁
	void GameClearStage::CreateStageWall()
	{
		auto group = CreateSharedObjectGroup(L"StageWall_Group");
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_StageCsv.GetSelect(LineVec, 0, L"StageWall");
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
			AddGameObject<StageWall>(Scale, Rot, Pos);
		}

	}

	// !ステージの門の作成
	void GameClearStage::CreateStageGate()
	{

		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_StageCsv.GetSelect(LineVec, 0, L"StageGate");
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
			auto ptrGate = AddGameObject<StageGate>(Scale, Rot, Pos);
			SetSharedGameObject(L"Gate", ptrGate);
			
		}

	}

	//初期化
	void GameClearStage::OnCreate() {
		CreateViewLight();
		
		SetPhysicsActive(true);//物理計算有効
		auto scene = App::GetApp()->GetScene<Scene>();

		scene->SetGoleGateParameter(true);//!門のパラメーターの適応

		//!BGM
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GameClear", XAUDIO2_LOOP_INFINITE, 0.2f);
		
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		// フォルダの指定
		auto csvDirectory = DataDir + L"csvFolder\\";

		m_StageCsv.SetFileName(csvDirectory + L"ClearStage.csv");
		m_StageCsv.ReadCsv();
		//!Buildingファイルの読み込み4
		m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");
		m_GameStageCsvD.ReadCsv();

		CerateGoalPlayer(); //! プレイヤーの追加
		CreateStageFloor();	//!ステージの追加
		CreateStageBuilding(); //!建物の追加
		CreateStageWall(); //!壁の追加
		CreateStageGate(); //!門の追加
		AddGameObject<ClearStageCanvas>();
	}

	void GameClearStage::OnUpdate() {
		
		//!コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameClearStage>());
	}
	// !BGMのストップ
	void GameClearStage::OnDestroy()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//Aボタン
	void GameClearStage::OnPushA() {
		PostEvent(0.0f, GetThis<GameClearStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		OnDestroy();
	}

	
}
//end basecros