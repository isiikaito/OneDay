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

	// !ステージの床
	void GameStage::CreateStageFloor()
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

	// !ステージの壁
	void GameStage::CreateStageWall()
	{
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

	//!カギ
	void GameStage::CreateKey()
	{
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto group = CreateSharedObjectGroup(L"key");
		auto& LineVec = m_GameStageCsvA.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//XとZの位置を計算
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"2")
				{
					AddGameObject<Key>(Vec3(2.0f, 4.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
				}
			}
		}
	}



	// !ステージの建物
	void GameStage::CreateStageBuilding()
	{
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto& LineVec = m_GameStageCsvA.GetCsvVec();
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

	// !ステージの門の作成
	void GameStage::CreateStageGate()
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
			AddGameObject<StageGate>(Scale, Rot, Pos);
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

	//カギスプライト作成
	void GameStage::CreateKeySprite() {
		AddGameObject<KeySprite>(
			L"KEY_TX",
			true,
			Vec2(320.0f, 80.0f),
			Vec2(450.0f, 330.0f ));
	}

	//!プレイヤーの作成
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();//!プレイヤーの作成
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	//!ハンター(スケール、ローテイション、ポジション)の構造体
	struct TransformCreateDate {
		//!構造体テンプレート
		Vec3 scale = Vec3(0.0f);//!大きさ
		Vec3 rotation = Vec3(0.0f);//!回転
		Vec3 position = Vec3(0.0f);//!位置
		wstring EnemykeyName = L"";//!ハンターの巡回ルートのキーフレームを取得

		TransformCreateDate() :
			TransformCreateDate(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), wstring(L""))
		{}
		//!構造体の初期化
		TransformCreateDate(
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& EnemykeyName
		) :
			scale(scale),
			rotation(rotation),
			position(position),
			EnemykeyName(EnemykeyName)
		{}
	};

	//!ハンター(スケール、ローテイション、ポジション)の関数
	std::vector<TransformCreateDate>TransformDate(const wstring& folderName, const wstring& fileName, const wstring& keyName) {
		std::vector<TransformCreateDate>result;//!変数名
		vector<wstring>LineVec;//!CSVの行単位の配列

		auto& app = App::GetApp();//!アプリの取得
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto fullPass = DataDir + folderName + fileName;

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);//!0番目のカラムがL"Hunter"である行を抜き出す

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');//!トークン(カラム)単位で文字列を抽出(',')
			//!トークン(カラム)をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//!回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			//!ハンターの位置
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			wstring	EnemykeyName = Tokens[10];
			result.push_back(TransformCreateDate(Scale, Rot, Pos, EnemykeyName));

		}

		return result;
	}

	//!パトロールポイントの構造体
	struct PointCreateDate {
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0.0f);

		PointCreateDate() :
			PointCreateDate(vector<Vec3>(0.0f)) {}
		PointCreateDate(const std::vector<Vec3>& patrolPoints) :
			m_patorlPositions(patrolPoints)
		{}
	};

	//!パトロールポイント
	PointCreateDate PointDate(const wstring& folderName, const wstring& fileName, const wstring& keyName)
	{
		PointCreateDate PatorlPoint;

		vector<wstring>LineVec;
		auto& app = App::GetApp();//!アプリの取得
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto fullPass = DataDir + folderName + fileName;//!

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);//!0番目のカラムがkeyNameである行を抜き出す
		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');//!トークン(カラム)単位で文字列を抽出(',')

			auto& routePositions = PatorlPoint.m_patorlPositions;

			routePositions.push_back(
				Vec3((float)_wtof(Tokens[1].c_str()),
					(float)_wtof(Tokens[2].c_str()),
					(float)_wtof(Tokens[3].c_str())));
		}

		return PatorlPoint;
	}



	//!ハンターの作成
	void GameStage::CerateHunter()
	{
		auto group = CreateSharedObjectGroup(L"Hunter_ObjGroup");//!グループを取得

		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"Hunter");//!Excelのデータ指定

		for (auto data : datas) {

		
			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", data.EnemykeyName);//!ハンターの大きさをいじってたCSVからキーネームを取り出すそこから行動を選ぶ
			

			AddGameObject<Hunter>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);
		}
	}
	void GameStage::OnCreate() {
		try {

			SetPhysicsActive(true);//物理計算有効
			//! 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);

			// フォルダの指定
			auto csvDirectory = DataDir + L"csvFolder\\";

			//!ステージファイルの読み込み
			m_StageCsv.SetFileName(csvDirectory + L"stage1.csv");
			m_StageCsv.ReadCsv();

			//!Buildingファイルの読み込み
			m_GameStageCsvA.SetFileName(csvDirectory + L"GameStageA.csv");
			m_GameStageCsvA.ReadCsv();
		
            CreateTimerSprite();//!時間のスプライトの作成
			CreateViewLight();//ビューとライトの作成
			CreateStageFloor();//!ステージの床の作成
			CreateStageWall(); //!ステージの壁の作成
			CreateStageBuilding(); //!ステージの建物の作成
			CreateKey();//!カギの作成
			CreateStageGate(); //!ステージの門の作成
			CreatePlayer();//!プレーヤーの作成
			CerateHunter();//!ハンターの作成
			CreateKeySprite();//キーの作成
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime;
		if (m_TotalTime <= 0.0f) {
			m_TotalTime = m_GameTime;
		}
		////スコアを更新する
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_TotalTime);

		m_InputHandler.PushHandle(GetThis<GameStage>());
		
	}
	//Aボタン
	void GameStage::OnPushA() {
		PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
	}
	
}
//end basecross
