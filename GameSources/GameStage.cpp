/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "HeadManComment.h"
#include "Meat.h"
#include "KeyFrame.h"
#include "MeatGageBackground.h"
#include "MeatGageFrame.h"
#include "HungerGage.h"


namespace basecross {

	constexpr int alertlevelFirst = 1;
	constexpr int randomNumber = 4;
	constexpr float m_MeatTimeSpeed = 22.0f;
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

	// !ステージの建物
	void GameStage::CreateStageBuilding()
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


	//!カギ
	void GameStage::CreateKey()
	{
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto group = CreateSharedObjectGroup(L"key_ObjGroup");
		auto& LineVec = m_KeyPositon.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//XとZの位置を計算
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"2")//2の時にゲームステージに追加
				{
					AddGameObject<Key>(Vec3(2.0f, 4.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
				}
			}
		}
	}

	//!木箱の作成
	void GameStage::CreateWoodenBox()
	{
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto& LineVec = m_GameStageCsvD.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//XとZの位置を計算
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"3")//3の時にゲームステージに追加
				{
					AddGameObject<WoodenBox>(Vec3(5.0f, 5.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
				}
			}
		}
	}

	//!木の作成
	void GameStage::CreateWood()
	{
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto& LineVec = m_GameStageCsvD.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//XとZの位置を計算
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"4")//4の時にゲームステージに追加
				{
					AddGameObject<Wood>(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
				}
			}
		}
	}

	void GameStage::CreateMeat()
	{
		//CSVの全体の配列
		//CSVからすべての行を抜き出す
		auto& LineVec = m_MeatPositon.GetCsvVec();
		auto group = CreateSharedObjectGroup(L"Meat_ObjGroup");

		for (size_t i = 0; i < LineVec.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//XとZの位置を計算
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"5")//5の時にゲームステージに追加
				{
					AddGameObject<Meat>(Vec3(5.0f, 5.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 4.0f, ZPos));
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
			auto ptrGate=AddGameObject<StageGate>(Scale, Rot, Pos);
			SetSharedGameObject(L"Gate", ptrGate);
		}

	}

	void GameStage:: CreateGameOver()
	{

		auto GameOver=AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
		SetSharedGameObject(L"GameOverSprite", GameOver);
	}
	//スコアスプライト作成
	void GameStage::CreateTimerSprite() {
		AddGameObject<Timer>(2,
			L"NUMBER_TX",
			true,
			Vec2(50.0f, 40.0f),
			Vec3(-400.0f, 265.0f, 10.0f));

	}


	//!プレイヤーの作成
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();//!プレイヤーの作成
		SetSharedGameObject(L"Player", ptrPlayer);
	}

	//!敵(スケール、ローテイション、ポジション)の構造体
	struct TransformCreateDate {
		//!構造体テンプレート
		Vec3 scale = Vec3(0.0f);//!大きさ
		Vec3 rotation = Vec3(0.0f);//!回転
		Vec3 position = Vec3(0.0f);//!位置
		wstring EnemykeyName = L"";//!村人の巡回ルートのキーフレームを取得

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

	//!敵(スケール、ローテイション、ポジション)の関数
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

		csvFile.GetSelect(LineVec, 0, keyName);//!0番目のカラムがL"Villager"である行を抜き出す

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

			//!村人の位置
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
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0);

		PointCreateDate() :
			PointCreateDate(vector<Vec3>(0)) {}
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
	void GameStage::CreateMeatGageFrame()
	{
		AddGameObject<MeatGageFrame>(
			L"Frame_TX",//!テクスチャ
			true,
			Vec2(350.0f, 150.0f),//大きさ
			Vec2(-440.0f, -300.0f)//座標
			);
	}

	void GameStage::CreateHungerGage()
	{
		AddGameObject<HungerGage>(
			L"Full_TX",//!テクスチャ
			true,
			Vec2(300.0f, 120.0f),//大きさ
			Vec2(-440.0f, -300.0f)//座標
			);
	}

	void GameStage::CreateMeatGageBackGround()
	{
		AddGameObject<MeatGageBackGround>
			(
			L"Background_TX",//!テクスチャ
			true,
			Vec2(350.0f, 150.0f),//大きさ
			Vec2(-440.0f, -300.0f)//座標
			);
	}

	void GameStage::CreateKeyFrame()
	{
		AddGameObject<KeyFrame>(
			L"KEY_TX",//!テクスチャ
			true,
			Vec2(150.0f, 150.0f),//大きさ
			Vec2(300.0f , -320.0f)//座標
			);
	}

	void GameStage::CreateHeartSprite()
	{
		AddGameObject<PlayerHeartSpriteRight>
			(
			L"PlayerHp_TX",
			true,
			Vec2(70.0f, 70.0f),
			Vec2(550.0f, 270.0f)
			);

		AddGameObject<PlayerHeartSpriteMiddle>
			(
				L"PlayerHp_TX",
				true,
				Vec2(70.0f, 70.0f),
				Vec2(460.0f, 270.0f)
				);

		AddGameObject<PlayerHeartSpriteLeft>
			(
				L"PlayerHp_TX",
				true,
				Vec2(70.0f, 70.0f),
				Vec2(370.0f, 270.0f)
				);


	}

	void GameStage::CreateAlertlevelGauge()
	{

		AddGameObject<AlertlevelGauge>
			(
				L"AlertlevelGaugeGauge_TX",
				true,
				Vec2(300.0f, 100.0f),
				Vec2(460.0f, 350.0f)
				);
	}

	void GameStage::CreateArrow()
	{
		//!矢印の作成
		AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(50.0f, 70.0f),
				Vec2(390.0f, 330.0f)
				);

		AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(50.0f, 70.0f),
				Vec2(-550.0f, 200.0f)
				);

	}

	// !時計のスプライトの作成
	void GameStage::CreateClockSprite()
	{
		AddGameObject<ClockSprite>
			(
				L"Clock_TX",
				true,
				Vec2(350.0f, 250.0f),
				Vec2(-460.0f, 290.0f)
				);

	}

	// !時計の円盤のスプライトの作成
	void GameStage::CreateCircleClockSprite()
	{
		AddGameObject<CircleClockSprite>
			(
				L"Circle_TX",
				true,
				Vec2(130.0f, 130.0f),
				Vec2(-553.0f, 263.0f)
				);

	}

	//!村人の作成
	void GameStage::CerateVillager()
	{
		auto group = CreateSharedObjectGroup(L"Villager_ObjGroup");//!グループを取得

		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"Villager");//!Excelのデータ指定
		
		for (auto& data : datas) {

		
			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", data.EnemykeyName);//!村人の大きさをいじってたCSVからキーネームを取り出すそこから行動を選ぶ
			

			auto VillagerPtr=AddGameObject<Villager>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);
		
			
			
			AddGameObject<LoseSightOf>(VillagerPtr);
			AddGameObject<SurprisedSprite>(VillagerPtr);
			
		}
		
	}

	//!ハンターの作成
	void GameStage::CerateHunter()
	{
		auto group = CreateSharedObjectGroup(L"Hunter_ObjGroup");//!グループを取得

		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"Hunter");//!Excelのデータ指定
		
		for (auto data : datas) {


			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", data.EnemykeyName);//!村人の大きさをいじってたCSVからキーネームを取り出すそこから行動を選ぶ


			auto HunterPtr = AddGameObject<Hunter>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);


			AddGameObject<LoseSightOf>(HunterPtr);
			AddGameObject<SurprisedSprite>(HunterPtr);
		}

	}

	void GameStage::CreateHeadMan()
	{
		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"HeadMan");//!Excelのデータ指定

		for (auto& data : datas) 
		{

			auto HeadManPtr = AddGameObject<HeadMan>(data.scale, data.rotation,data.position );
			SetSharedGameObject(L"HeadMan", HeadManPtr);

			AddGameObject<HeadManComment>(HeadManPtr);

		}

	}

	void GameStage::GameTime()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime;
		if (m_TotalTime <= 0.0f) {
			m_TotalTime = m_GameTime;
		}
		////スコアを更新する
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_TotalTime);

		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		scene->SetGameTime(elapsedTime);

	}
	

	void GameStage::CreateLightingCol()
	{
		////ステージに置く場合
		//auto ptrMulti = dynamic_pointer_cast<MultiLight>(GetLight());
		//auto light0 = ptrMulti->GetLight(0);
		//auto light1 = ptrMulti->GetLight(1);
		//auto light2 = ptrMulti->GetLight(2);
		////この後light0などを変更
		//light2.m_DiffuseColor = Col4(1, 1, 1, 1);
		//light2.m_SpecularColor = Col4(1, 1, 1, 1);
		//ptrMulti->SetLight(1, light2);

	}

	void GameStage::OnCreate() {
		try {

			//!エフェクト作成
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			SetPhysicsActive(true);//物理計算有効
			//! 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto scene = App::GetApp()->GetScene<Scene>();
			//!シーンの取得
			auto m_keyNamber = scene->GetKeyNamber();

			// フォルダの指定
			auto csvDirectory = DataDir + L"csvFolder\\";

			//!ステージファイルの読み込み
			m_StageCsv.SetFileName(csvDirectory + L"stage1.csv");
			m_StageCsv.ReadCsv();

			//!Buildingファイルの読み込み
			m_GameStageCsvA.SetFileName(csvDirectory + L"GameStageA.csv");
			m_GameStageCsvA.ReadCsv();
		
			//!Buildingファイルの読み込み2
			m_GameStageCsvB.SetFileName(csvDirectory + L"GameStageB.csv");
			m_GameStageCsvB.ReadCsv();

			//!Buildingファイルの読み込み3
			m_GameStageCsvC.SetFileName(csvDirectory + L"GameStageC.csv");
			m_GameStageCsvC.ReadCsv();

			//!Buildingファイルの読み込み4
			m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");
			m_GameStageCsvD.ReadCsv();

			//!KeyPositonファイルの読み込み4-1
			m_KeyPositon.SetFileName(csvDirectory + L"KeyPosition" + Util::IntToWStr(m_keyNamber) + L".csv");
			m_KeyPositon.ReadCsv();

			//!MetaPositonファイルの読み込み
			m_MeatPositon.SetFileName(csvDirectory + L"MeatPosition" + Util::IntToWStr(m_MeatNumber) + L".csv");
			m_MeatPositon.ReadCsv();

            CreateTimerSprite();//!時間のスプライトの作成
			CreateViewLight();//ビューとライトの作成
			CreateStageFloor();//!ステージの床の作成
			CreateStageWall(); //!ステージの壁の作成
			CreateStageBuilding(); //!ステージの建物の作成
			CreateKey();//!カギの作成
			CreateStageGate(); //!ステージの門の作成
			CreatePlayer();//!プレーヤーの作成
			CerateVillager();//!村人の作成
			//CreatePlayBGM();//!BGMの作成
			CreateHeartSprite();//!プレイヤーのHPの作成
			CerateHunter();//!ハンターの作成
			CreateAlertlevelGauge();//!警戒度のゲージの作成
			CreateArrow();//!矢印の作成
			CreateClockSprite(); //!時計のスプライトの作成
			CreateCircleClockSprite(); //!時計の円盤のスプライトの作成
			CreateWoodenBox();//!箱の作成
			CreateWood();//!木の作成
			CreateHeadMan();//!村長の作成
			CreateMeat();//!肉の作成
			CreateGameOver();//!ゲームオーバー
			CreateMeatGageBackGround();//!空腹ゲージの背景
			CreateMeatGageFrame();//!空腹ゲージの枠
			CreateHungerGage();//!空腹ゲージ
			
			auto gameOver = scene->GetGameOver();
			if (gameOver == true)
			{
				CreateGameOverBGM();

			}
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {

		m_EfkInterface->OnUpdate();

		

		
		auto scene = App::GetApp()->GetScene<Scene>();

		auto& app = App::GetApp();
		auto time = app->GetElapsedTime();
		m_MeatTime += time* m_MeatTimeSpeed;
		srand(m_MeatTime);
		m_MeatNumber = rand() % randomNumber;
		
		scene->SetMeatNamber(m_MeatNumber);

		GameTime();
		CreateLightingCol();
		
		//auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto gameOver = scene->GetGameOver();
		if (gameOver == true)
		{
			OnDestroy();

		}
		//else { DestroyGameOverBGM(); }

		m_InputHandler.PushHandle(GetThis<GameStage>());

	}

	//!ゲームオーバーはステージを変えない。
	//! 倒れるモーションが入ってフェードアウトして一枚絵になる。
	void GameStage::OnDraw()
	{
		auto& camera = GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}
	

	// !BGMの再生
	void GameStage::CreatePlayBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"bgm", XAUDIO2_LOOP_INFINITE, 0.3f);
	}

	// !ゲームオーバーのBGMの再生
	void GameStage::CreateGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_GameOverBGM = XAPtr->Start(L"GameOver", XAUDIO2_LOOP_INFINITE, 0.3f);

	}

	// !BGMのストップ
	void GameStage::OnDestroy()
	{
        auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);	
	}

	// !ゲームオーバーBGMの削除
	void GameStage::DestroyGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_GameOverBGM);
	}

	void GameStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto gameOver = scene->GetGameOverSprite();
		if (gameOver == true)
		{
			auto gameOver = scene->GetGameOver();
			gameOver = false;
			scene->SetGameOver(gameOver);

			//サウンド再生
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"decision", 0, 1.0f);
			PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			gameOver = false;
			scene->SetGameOverSprite(gameOver);
		}
	}
}
//end basecross
