/*!
@file GameStage.cpp
@brief ゲームステージ実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "HeadManComment.h"
#include "Meat.h"
#include "OpeningCamera.h"
#include "OpeningCameraMan.h"
#include "GameUI.h"
#include "GameStageCanvas.h"
#include "GameManager.h"

namespace basecross {

	constexpr int RANDOMNUMBER = 4;					  //!ランダムの最大値
	constexpr float MEATTIMESPEED = 22.0f;		  //!肉をランダムにする値の変化するスピード
	constexpr float PLAYERCHANGEMAXTIME = 2.0f;	  //!プレイヤーを変身する時間
	constexpr float CIRCLECLOCKSPEED = 10.0f;		  //!時計を回転させるスピード
	constexpr float OPNINGCAMERATIME = 6.0f;		  //!オープニングカメラの時間
	constexpr float PLAYERCONDITIONMAXTIME = 62.0f; //!プレイヤーの状態の最大時間
	constexpr float EMISSIVECHANGETIMESPEED = 32.0f;//!明るさを変える時間
	constexpr float EMISSIVERESET = 1.0f;			  //!明るさのリセット
	constexpr float EMISSIVECHANGEMAXTIME = 1.0f;   //!昼夜の変更
	constexpr float CELLADJUSMENT = 8.6f;		  //!セルの幅調整
	constexpr float CELLPOSADJUSTMENT = 10.0f;	  //!セルのポジションを調整
	constexpr float BGMVOLUME=0.2f;				  //!BGMの音量
	
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	//ビューとライトの作成
	void GameStage::CreateViewLight() {

		//OpeningCameraView用のビュー
		m_openingCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_openingCameraView->SetCamera(ptrOpeningCamera);//!オープニングカメラの設定

		//ビューのカメラの設定
		//MyCamera用のビュー
		m_myCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(m_startEye);				//!カメラの初期位置
		ptrMyCamera->SetAt(m_startAt);					//!カメラの視点
		m_myCameraView->SetCamera(ptrMyCamera);			//!マイカメラの設定
		SetView(m_openingCameraView);					//!オープニングカメラのビューに設定する
		m_CameraSelect = CameraSelect::openingCamera;	//!現在のカメラの状態

		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();


	}

	//!カメラマンの作成 
	void GameStage::CreateCameraman()
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraMan>();//!カメラマンの作成
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(L"OpeningCameraMan", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_openingCameraView->GetCamera());//!オープニングカメラの取得
		//!オープニングカメラがある時
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);	//!オープニングカメラに設定
			SetView(m_openingCameraView);							//!オープニングカメラをビューに設定
			m_CameraSelect = CameraSelect::openingCamera;			//!現在のカメラの状態
		}


	}
	//!カメラをプレイヤーの位置に戻す処理
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_myCameraView->GetCamera());//!マイカメラの取得
		//!マイカメラがある時
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);//!ターゲットオブジェクトの設定
			SetView(m_myCameraView);				//!m_MyCameraViewを使う
			m_CameraSelect = CameraSelect::myCamera;//!カメラの状態
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
				float XPos = (float)((int)j - CELLADJUSMENT) * CELLPOSADJUSTMENT;
				float Ypos = 5.0f;
				float ZPos = (float)(CELLADJUSMENT - (int)i) * CELLPOSADJUSTMENT;
				if (Tokens[j] == L"1")
				{
					AddGameObject<StageBuilding>(m_BuildingScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
				}
			}
		}
	}


	//!鍵の作成
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
				float XPos = (float)((int)j - CELLADJUSMENT) * CELLPOSADJUSTMENT;
				float Ypos = 3.0f;
				float ZPos = (float)(CELLADJUSMENT - (int)i) * CELLPOSADJUSTMENT;
				if (Tokens[j] == L"2")//2の時にゲームステージに追加
				{
					AddGameObject<Key>(Vec3(2.0f, 4.0f, 1.0f), Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
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
				float XPos = (float)((int)j - CELLADJUSMENT) * CELLPOSADJUSTMENT;
				float Ypos = 3.0f;
				float ZPos = (float)(CELLADJUSMENT - (int)i) * CELLPOSADJUSTMENT;
				if (Tokens[j] == L"3")//3の時にゲームステージに追加
				{
					AddGameObject<WoodenBox>(m_woodenBoxScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
					
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
				float XPos = (float)((int)j - CELLADJUSMENT) * CELLPOSADJUSTMENT;
				float Ypos = 3.0f;
				float ZPos = (float)(CELLADJUSMENT - (int)i) * CELLPOSADJUSTMENT;
				if (Tokens[j] == L"4")//4の時にゲームステージに追加
				{
					AddGameObject<Wood>(m_woodScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
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

		auto& app = App::GetApp();						//!アプリの取得
		wstring DataDir;								//!データ
		App::GetApp()->GetDataDirectory(DataDir);		//!データを取得
		auto fullPass = DataDir + folderName + fileName;//!ファイルの特定

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);					//!特定したcsvファイルを読み込む
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);			//!0番目のカラムがL"Villager"である行を抜き出す
		//!取得した行の情報
		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;						//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');	//!トークン(カラム)単位で文字列を抽出(',')
			//!大きさ
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

			//!位置
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
		PointCreateDate PatorlPoint;//!巡回ポイントを保存する

		vector<wstring>LineVec;
		auto& app = App::GetApp();//!アプリの取得
		wstring DataDir;								//!アプリの取得
		App::GetApp()->GetDataDirectory(DataDir);		//!データ
		auto fullPass = DataDir + folderName + fileName;//!ファイルの特定
		//!データを取得								 
		CsvFile csvFile;								
		csvFile.SetFileName(fullPass);					//!特定したcsvファイルを読み込む
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);			//!0番目のカラムがkeyNameである行を抜き出す
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


	void GameStage::UIDrawActive(bool t)
	{
		//!時間のスプライトの表示
		auto timer = GetSharedGameObject<Timer>(L"Time");
		timer->SetDrawActive(t);


	}
	//!村人の作成
	void GameStage::CerateVillager()
	{
		auto group = CreateSharedObjectGroup(L"Villager_ObjGroup");				//!グループを取得

		auto datas = TransformDate(L"csvFolder\\" L"EnemyData\\", L"Enemy.csv", L"Villager");	//!Excelのデータ指定
		
		for (auto& data : datas) {

		
			auto pointData = PointDate(L"csvFolder\\" L"EnemyData\\", L"Point.csv", data.EnemykeyName);//!村人の大きさをいじってたCSVからキーネームを取り出すそこから行動を選ぶ
			

			auto VillagerPtr=AddGameObject<Villager>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);
		
		
			AddGameObject<LoseSightOf>(VillagerPtr);	//!見失ったときの板ポリの作成
			AddGameObject<SurprisedSprite>(VillagerPtr);//!見つけたときの板ポリの作成
			
		}
		
	}

	//!ハンターの作成
	void GameStage::CerateHunter()
	{
		auto group = CreateSharedObjectGroup(L"Hunter_ObjGroup");//!グループを取得

		auto datas = TransformDate(L"csvFolder\\" L"EnemyData\\", L"Enemy.csv", L"Hunter");//!Excelのデータ指定
		
		for (auto& data : datas) {

			auto pointData = PointDate(L"csvFolder\\" L"EnemyData\\", L"Point.csv", data.EnemykeyName);//!村人の大きさをいじってたCSVからキーネームを取り出すそこから行動を選ぶ

			auto HunterPtr = AddGameObject<Hunter>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);

			AddGameObject<LoseSightOf>(HunterPtr);		//!見失ったときの板ポリの作成
			AddGameObject<SurprisedSprite>(HunterPtr);	//!見つけたときの板ポリの作成
		}

	}
	//!村長の作成
	void GameStage::CreateHeadMan()
	{
		auto datas = TransformDate(L"csvFolder\\" L"EnemyData\\", L"Enemy.csv", L"HeadMan");//!Excelのデータ指定

		for (auto& data : datas) 
		{
			auto HeadManPtr = AddGameObject<HeadMan>(data.scale, data.rotation,data.position );
			SetSharedGameObject(L"HeadMan", HeadManPtr);

			AddGameObject<HeadManComment>(HeadManPtr);

		}
	}

	//!オープニングカメラの設定
	void GameStage::OpeningCameraBooting(float time)
	{
		auto scene = App::GetApp()->GetScene<Scene>();		//!シーンの取得
		float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		m_gameStartTime += elapsedTime;						//!エルパソタイムを足して時間の生成
		//!オープニングカメラの時間が過ぎたら
		if (m_gameStartTime >= time)
		{
			UIDrawActive(true);						//!テクスチャの表示をしない
			auto gameStrat = scene->GetGameStrat();	//!オープニングカメラの状態を取得
			gameStrat = false;						//!オープニングカメラの状態をオフ
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);//!オープニングカメラの状態を設定

			
		}
		else
		{
			auto scene = App::GetApp()->GetScene<Scene>();				//!シーンの取得
			auto m_emissiveChangeTime = scene->GetEmissiveChangeTime();	//!明るさを変更する時間の取得
			m_emissiveChangeTime = EMISSIVERESET;						//!明るさを変更する時間のリセット
			scene->SetEmissiveChangeTime(m_emissiveChangeTime);			//!明るさを変更する時間の設定
			auto gameStrat = scene->GetGameStrat();						//!ゲームスタートしているかの取得
			gameStrat = true;											//!ゲームスタートする				
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);	//!ゲームスタートしているかの設定
			UIDrawActive(false);										//!テクスチャの表示をする
			
		}

	}


	void GameStage::GameTime()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		OpeningCameraBooting(OPNINGCAMERATIME);			//!オープニングカメラの時間中の処理
		auto scene = App::GetApp()->GetScene<Scene>();		//!シーンの取得
		auto gameStrat = scene->GetGameStrat();				//!スタートしているかどうかの取得


		//!オープニングカメラが終わったとき
		if (!gameStrat)
		{
			auto scene = App::GetApp()->GetScene<Scene>();				 //!シーンの取得
			auto m_playerConditionTime = scene->GetPlayerConditionTime();//!プレイヤーの変身時間の取得
			//!プレイヤーの変身が開始された
			if (scene->GetPlayerChangeDirecting())
			{
				//!プレイヤーの変身が終わったら
				if (m_playerConditionTime >= PLAYERCONDITIONMAXTIME)
				{
					m_playerConditionTime = 0.0f;						 //!変身時間のリセット
					scene->SetPlayerConditionTime(m_playerConditionTime);//!変身時間のリセット設定
				}
				float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
				m_playerChangeTime += elapsedTime;					//!時間を止めている時間

				//!プレイヤーの変身時間が過ぎたら時間を動かす
				if (m_playerChangeTime >= PLAYERCHANGEMAXTIME)
				{
					
					m_playerChangeTime = 0.0f;				//!時間を止めている時間のリセット
					scene->SetPlayerChangeDirecting(false);//!時間を止めている時間の設定

				}
			}

			//!変身が開始されていないとき
			else
			{
				float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
				m_dayTime += elapsedTime / CIRCLECLOCKSPEED;		//!時間を回転させるスピードで割る
				m_playerConditionTime += elapsedTime;				//!変身の時間に加算
				m_totalTime -= elapsedTime;							//!ゲーム時間の取得
				auto m_emissiveChangeTime = App::GetApp()->GetScene<Scene>()->GetEmissiveChangeTime();//!明るさの変更

				//!昼の時
				if (m_oneday == static_cast<int>(Oneday::midday))
				{
					m_emissiveChangeTime -= elapsedTime / EMISSIVECHANGETIMESPEED;//!エミッシブが変わる時間
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);				//!エミッシブが変わる時間の設定
					
					//!夜の時間になったら
					if (m_emissiveChangeTime <= 0.0f)
					{
						m_oneday = static_cast<int>(Oneday::night);//!夜に変化

					}
				}
				
				//!夜の時
				if (m_oneday == static_cast<int>(Oneday::night))
				{
					m_emissiveChangeTime += elapsedTime / EMISSIVECHANGETIMESPEED;//!エミッシブが変わる時間
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);				//!エミッシブが変わる時間の設定

					//!昼の時間になったら
					if (m_emissiveChangeTime >= EMISSIVECHANGEMAXTIME)
					{
						m_oneday = static_cast<int>(Oneday::midday);//!昼に変化
					}
				}
				

				
				//!30秒経ったらまた30秒に戻す
				if (m_totalTime <= 0.0f)
				{
					m_totalTime = m_GameTime;//!ゲーム時間リセット

				}

				auto scene = App::GetApp()->GetScene<Scene>();		  //!シーンの取得
				scene->SetGameTime(elapsedTime);					  //!ゲームの時間を設定する
				scene->SetDayTime(m_dayTime);						  //!時計の時間
				scene->SetPlayerConditionTime(m_playerConditionTime); //!プレイヤーの状態時間を設定

			}
			

		}

		////スコアを更新する
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_totalTime);

	}
	

	

	void GameStage::OnCreate() {
		
			m_effectManager = EffectManager::Instance();					//!エフェクトマネージャーの取得
			auto scene = App::GetApp()->GetScene<Scene>();					//!シーンの取得
			auto m_playerConditionTime = scene->GetPlayerConditionTime();	//!プレイヤーの状態の時間
			m_playerConditionTime = 0.0f;									//!プレイヤーの状態の時間の初期化
			scene->SetPlayerConditionTime(m_playerConditionTime);			//!プレイヤーの状態の時間の設定
			scene->SetGoleGateParameter(false);								//!門のパラメーターの適応
			auto meatGroup = CreateSharedObjectGroup(L"Meat_ObjGroup");		//!肉オブジェクトのグループ
			SetPhysicsActive(true);											//物理計算有効

			//! 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();										//!アプリの取得
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//!シーンの取得
			auto m_keyNamber = scene->GetKeyNamber();

			// フォルダの指定
			auto csvDirectory = DataDir + L"csvFolder\\";

			//!ステージファイルの読み込み
			m_StageCsv.SetFileName(csvDirectory +L"StageData\\"+ L"stage.csv");
			m_StageCsv.ReadCsv();
			//!Buildingファイルの読み込み
			m_GameStageCsvD.SetFileName(csvDirectory + L"BuildingPosition\\"+L"GameStageD.csv");
			m_GameStageCsvD.ReadCsv();

			//!KeyPositonファイルの読み込み
			m_KeyPositon.SetFileName(csvDirectory + L"KeyPositions\\"+L"KeyPosition" + Util::IntToWStr(m_keyNamber) + L".csv");
			m_KeyPositon.ReadCsv();

			auto effect = EffectManager::Instance();
			effect->OnCreate();


			CreateViewLight();
			CreateStageFloor();
			CreateStageWall();
			CreateStageBuilding();
			CreateKey();
			CreateStageGate(); 
			CreatePlayer();		
			CerateVillager();	
			CreatePlayBGM();	
			CerateHunter();		
			CreateWoodenBox();	
			CreateWood();		
			CreateHeadMan();	
			CreateCameraman();	

			//!ゲームステージのUIキャンバスの作成
			AddGameObject<GameStageCanvas>();
			AddGameObject<GameManager>();//!ゲームマネージャーの作成

			auto gameOver = scene->GetGameOver();
			if (gameOver == true)
			{
				CreateGameOverBGM();

			}
		
	}

	void GameStage::OnUpdate() {
		m_effectManager->GetEfkInterface()->OnUpdate();
		auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
		auto& app = App::GetApp();						//!アプリの取得
		auto deltaTime = app->GetElapsedTime();			//!エルパソタイムの取得
		m_MeatTime += deltaTime* MEATTIMESPEED;		//!肉の時間に加算
		srand((unsigned)std::time(0));
		m_MeatNumber = rand() % RANDOMNUMBER;			//!ランダムの上限の数字で割ることでそれ以上にならない
		scene->SetMeatNamber(m_MeatNumber);				//!肉の位置の数字が設定される
		GameTime();
		auto gameOver = scene->GetGameOver();			//!ゲームオーバーしているかどうか
		//!ゲームオーバーの時
		if (gameOver == true)
		{

			OnDestroy();//!BGMを消す

		}
		
		m_InputHandler.PushHandle(GetThis<GameStage>());//!コントローラのインプットハンドラの取得
		m_InputHandlerReset.PushHandleReset(GetThis<GameStage>());

	}
	//!エフェクト
	void GameStage::OnDraw()
	{
		auto& camera = GetView()->GetTargetCamera();
		m_effectManager->GetEfkInterface()->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_effectManager->GetEfkInterface()->OnDraw();

	}
	

	// !BGMの再生
	void GameStage::CreatePlayBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"bgm", XAUDIO2_LOOP_INFINITE, BGMVOLUME);
	}

	// !ゲームオーバーのBGMの再生
	void GameStage::CreateGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_GameOverBGM = XAPtr->Start(L"GameOver", XAUDIO2_LOOP_INFINITE, BGMVOLUME);

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
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!音量の取得
		auto scene = App::GetApp()->GetScene<Scene>();					 //!シーンの取得
		auto gameOver = scene->GetGameOver();						 //!ゲームオーバースプライトの取得
		//!ゲームオーバーの時
		if (gameOver == true)
		{
			
			//サウンド再生
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"decision", 0, volume);
			PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");//!タイトルステージに遷移
		}
	}

	//!リセットボタン
	void GameStage::OnPushReset()
	{
		//!タイトル画面の遷移
		PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	}
}
//end basecross
