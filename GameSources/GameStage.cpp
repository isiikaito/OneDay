/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "HeadManComment.h"
#include "Meat.h"
#include "HungerGage.h"
#include "DateChangeCommentDay.h"
#include "DateChangeCommentNight.h"
#include "GameManager.h"
#include "OpeningCamera.h"
#include "OpeningCameraMan.h"
#include "GameUI.h"
#include "PlayerHurteSprite.h"

namespace basecross {

	constexpr int alertlevelFirst = 1;
	constexpr int randomNumber = 4;
	constexpr float m_MeatTimeSpeed = 22.0f;
	constexpr float m_playerChangeMaxTime = 2.0f;
	constexpr float m_gameStartMaxTime = 6.0f;
	constexpr float m_circleClockSpeed = 10.0f;
	constexpr float m_opningCameraTime = 6.0f;
	constexpr float m_playerConditionMaxTime = 62.0f;
	constexpr float m_emissiveChangeTimeSpeed = 32.0f;
	constexpr float m_emissiveReset = 1.0f;
	constexpr float m_emissiveChangeMaxTime = 1.0f;
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	//ビューとライトの作成
	void GameStage::CreateViewLight() {

		//OpeningCameraView用のビュー
		m_openingCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_openingCameraView->SetCamera(ptrOpeningCamera);

		//ビューのカメラの設定
		//MyCamera用のビュー
		m_myCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_myCameraView->SetCamera(ptrMyCamera);

		SetView(m_openingCameraView);
		m_CameraSelect = CameraSelect::openingCamera;

		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();


	}

	//!カメラマンの作成 
	void GameStage::CreateCameraman()
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraMan>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(L"OpeningCameraMan", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_openingCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_openingCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	//!カメラをプレイヤーの位置に戻す処理
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_myCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_myCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
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
		auto group = CreateSharedObjectGroup(L"WoodBox_ObjGroup");
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
					AddGameObject<WoodenBox>(Vec3(9.0f, 9.0f, 9.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
					
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

	void GameStage::CreateDateChangeCommentDay()
	{
		AddGameObject<DateChangeCommentDay>(
			L"CommentDay_TX",//!テクスチャ
			true,
			Vec2(700.0f, 300.0f),//大きさ
			Vec2(0.0f, 240.0f)//座標
			);
	}

	void GameStage::CreateDateChangeCommentNight()
	{
		AddGameObject<DateChangeCommentNight>(
			L"CommentNignt_TX",//!テクスチャ
			true,
			Vec2(700.0f, 300.0f),//大きさ
			Vec2(0.0f, 240.0f)//座標
			);

	
	}


	void GameStage:: CreateGameOver()
	{
		AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f,0.0f));
		
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
		auto meatGageFrameSprite = AddGameObject<GameUI>(
			L"Frame_TX",//!テクスチャ
			true,
			Vec2(200.0f, 50.0f),//大きさ
			Vec3(420.0f, -320.0f,0.2f)//座標
			);
		

		


	}

	void GameStage::CreateHungerGage()
	{
		AddGameObject<HungerGage>(
			L"Full_TX",//!テクスチャ
			true,
			Vec2(400.0f, 100.0f),//大きさ
			Vec2(420.0f, -320.0f)//座標
			);
	}

	void GameStage::CreateMeatGageBackGround()
	{
		AddGameObject<GameUI>
			(
			L"Background_TX",//!テクスチャ
			true,
			Vec2(200.0f, 50.0f),//大きさ
			Vec3(420.0f, -320.0f,1.0f)//座標
			);
		

	}

	void GameStage::CreateKeyFrame()
	{
		AddGameObject<GameUI>(
			L"ItemField_TX",//!テクスチャ
			true,
			Vec2(200.0f, 150.0f), //!大きさ
			Vec3(-450.0f, -280.0f,0.2f)//!位置(x,y,z)z奥行きは0.0f～1.0fの間
			);
		

	}

	void GameStage::CreateHeartSprite()
	{
		

		//!左側のハート
		AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),        //!大きさ
				Vec3(370.0f, -250.0f,0.2f),//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				2,//!現在のライフ
				true//!表示されているかどうか
				);

		//!中央側のハート
		AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!大きさ
				Vec3(460.0f, -250.0f, 0.2f),//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				1,//!現在のライフ
				true//!表示されているかどうか
				);

		//!右側のハート
	AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!大きさ
				Vec3(550.0f, -250.0f, 0.2f),//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				0,//!現在のライフ
				true//!表示されているかどうか
				);
		
	}

	void GameStage::CreateAlertlevelGauge()
	{

		auto alertlevelGaugeSprite = AddGameObject<GameUI>
			(
				L"AlertlevelGaugeGauge_TX",
				true,
				Vec2(150.0f, 50.0f),       //!大きさ
				Vec3(460.0f, 350.0f, 1.0f) //!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);
		

	}
	void GameStage::CreateClockArrow()
	{
		auto clockArrowSprite=AddGameObject<GameUI>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),//!大きさ
				Vec3(0.0f,0.0f,90.0f),//!回転
				Vec3(-500.0f, 300.0f,0.2f)//!位置
				);
		

	}

	void GameStage::CreateArrow()
	{
		//!矢印の作成
		AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),       //!大きさ
				Vec3(390.0f, 330.0f, 0.8f)//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);

		

	}

	// !時計のスプライトの作成
	void GameStage::CreateClockSprite()
	{
		auto clockSprite=AddGameObject<GameUI>
			(
				L"Clock_TX",
				true,
				Vec2(170.0f, 128.0f),
				Vec3(-460.0f, 290.0f,0.3f)
				);
		


	}

	// !時計の円盤のスプライトの作成
	void GameStage::CreateCircleClockSprite()
	{
		auto circleClockSprite = AddGameObject<CircleClockSprite>
			(
				L"Circle_TX",
				true,
				Vec2(65.0f, 70.0f),
				Vec3(-550.0f, 263.0f,1.0f)
				);

	}

	

	void GameStage::UIDrawActive(bool t)
	{
		

	
		

		
		

		

		

		//!時間のスプライトの表示
		auto timer = GetSharedGameObject<Timer>(L"Time");
		timer->SetDrawActive(t);

		
		
	

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
		
		for (auto& data : datas) {

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

	void GameStage::OpeningCameraBooting(float time)
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		m_gameStartTime += elapsedTime;//!エルパソタイムを足して時間の生成
		//!オープニングカメラの時間が過ぎたら
		if (m_gameStartTime >= time)
		{
			UIDrawActive(true);
			auto gameStrat = scene->GetGameStrat();//!オープニングカメラの状態を取得
			gameStrat = false;			//!オープニングカメラの状態をオフ
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);//!オープニングカメラの状態を設定

			//m_gameStrat = false;
			if (m_heartSpriteDraw == false)
			{
				
				m_heartSpriteDraw = true;
			}
		}
		else
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			auto m_emissiveChangeTime = scene->GetEmissiveChangeTime();
			m_emissiveChangeTime = m_emissiveReset;
			scene->SetEmissiveChangeTime(m_emissiveChangeTime);
			auto gameStrat = scene->GetGameStrat();
			gameStrat = true;
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);

			//m_gameStrat = true;
			UIDrawActive(false);
			
		}
	    //App::GetApp()->GetScene<Scene>()->SetGameStrat(m_gameStrat);

	}


	void GameStage::GameTime()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得

		OpeningCameraBooting(m_opningCameraTime);//!オープニングカメラの時間中の処理
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStrat = scene->GetGameStrat();


		//!オープニングカメラが終わったとき
		if (!gameStrat)
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			auto m_playerConditionTime = scene->GetPlayerConditionTime();
			//!プレイヤーの変身が開始された
			if (scene->GetPlayerChangeDirecting())
			{
				if (m_playerConditionTime >= m_playerConditionMaxTime)
				{
					
					m_playerConditionTime = 0.0f;
					scene->SetPlayerConditionTime(m_playerConditionTime);

				}
				float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
				m_playerChangeTime += elapsedTime;//!時間を止めている時間
				//!プレイヤーの変身時間が過ぎたら時間を動かす
				if (m_playerChangeTime >= m_playerChangeMaxTime)
				{
					
					m_playerChangeTime = 0.0f;
					scene->SetPlayerChangeDirecting(false);

				}
			}
			//!変身が開始されていないとき
			else
			{

				float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
				m_dayTime += elapsedTime / m_circleClockSpeed;
				m_playerConditionTime += elapsedTime;
				m_totalTime -= elapsedTime;//!ゲーム時間の取得
				auto m_emissiveChangeTime = App::GetApp()->GetScene<Scene>()->GetEmissiveChangeTime();

				if (m_oneday == static_cast<int>(Oneday::midday))
				{
					m_emissiveChangeTime -= elapsedTime / m_emissiveChangeTimeSpeed;//!エミッシブが変わる時間
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);

					if (m_emissiveChangeTime <= 0.0f)
					{
						m_oneday = static_cast<int>(Oneday::night);

					}
				}
				

				if (m_oneday == static_cast<int>(Oneday::night))
				{
					m_emissiveChangeTime += elapsedTime / m_emissiveChangeTimeSpeed;//!エミッシブが変わる時間
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);

					if (m_emissiveChangeTime >= m_emissiveChangeMaxTime)
					{
						m_oneday = static_cast<int>(Oneday::midday);
					}
				}
				

				
				//!30秒経ったらまた30秒に戻す
				if (m_totalTime <= 0.0f)
				{
					m_totalTime = m_GameTime;

				}

				auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
				scene->SetGameTime(elapsedTime);//!ゲームの時間を設定する
				scene->SetDayTime(m_dayTime);//!時計の時間
				scene->SetPlayerConditionTime(m_playerConditionTime);

			}
			

		}

		////スコアを更新する
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_totalTime);

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
			auto scene = App::GetApp()->GetScene<Scene>();

			//auto GameMneager =AddGameObject<GameManager>();
			auto m_playerConditionTime = scene->GetPlayerConditionTime();
			m_playerConditionTime = 0.0f;
			scene->SetPlayerConditionTime(m_playerConditionTime);

			scene->SetGoleGateParameter(false);//!門のパラメーターの適応

			//!エフェクト作成
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			SetPhysicsActive(true);//物理計算有効
			//! 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
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
			CreatePlayBGM();//!BGMの作成
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
			CreateClockArrow();//!時計の針
			CreateDateChangeCommentDay();//!夜から昼にでるテクスチャ
			CreateDateChangeCommentNight();//!昼から夜にでるテクスチャ
			CreateKeyFrame();//!カギの枠の作成
			CreateCameraman(); //!カメラマンの作成

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
		auto deltaTime = app->GetElapsedTime();
		m_MeatTime += deltaTime* m_MeatTimeSpeed;
		srand(std::time(0));
		m_MeatNumber = rand() % randomNumber;//!ランダムの上限の数字で割ることでそれ以上にならない
		
		scene->SetMeatNamber(m_MeatNumber);//!肉の位置の数字が設定される

		GameTime();
		CreateLightingCol();
		
		//auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto gameOver = scene->GetGameOver();
		if (gameOver == true)
		{

			OnDestroy();//!BGMを消す

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
		m_BGM = XAPtr->Start(L"bgm", XAUDIO2_LOOP_INFINITE, 0.2f);
	}

	// !ゲームオーバーのBGMの再生
	void GameStage::CreateGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_GameOverBGM = XAPtr->Start(L"GameOver", XAUDIO2_LOOP_INFINITE, 0.1f);

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
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"decision", 0, 1.0f);
			PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			gameOver = false;
			scene->SetGameOverSprite(gameOver);
		}
	}
}
//end basecross
