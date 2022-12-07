
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
		wstring strTexture = dataDir +L"Texture\\"+ L"Nomber_3.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		//!タイトル画面
		strTexture = dataDir + L"Texture\\"+L"Title.jpg";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		//!ゲームオーバー画面
		strTexture = dataDir + L"Texture\\" + L"GameOver.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		//!ゲームクリア画面
		strTexture = dataDir + L"Texture\\"+ L"GameClear.png";
		App::GetApp()->RegisterTexture(L"GAMECLEAR_TX", strTexture);
		//!キースプライト
		strTexture = dataDir + L"Texture\\" + L"key.png";
		App::GetApp()->RegisterTexture(L"KEY_TX", strTexture);
		//!プレイヤーのHPスプライト
		strTexture = dataDir + L"Texture\\" + L"PlayerHp.png";
		App::GetApp()->RegisterTexture(L"PlayerHp_TX", strTexture);
		//!時計のスプライト
		strTexture = dataDir + L"Texture\\" + L"testTime.png";
		App::GetApp()->RegisterTexture(L"testTime_TX", strTexture);
		//!ビックリマークのスプライト
		strTexture = dataDir + L"Texture\\" + L"Surprised.png";
		App::GetApp()->RegisterTexture(L"Surprised_TX", strTexture);
		//!はてなマークのスプライト
		strTexture = dataDir + L"Texture\\" + L"LoseSightOf.png";
		App::GetApp()->RegisterTexture(L"LoseSightOf_TX", strTexture);
		//!危険度のゲージのスプライト
		strTexture = dataDir + L"Texture\\" + L"testGauge.png";
		App::GetApp()->RegisterTexture(L"AlertlevelGaugeGauge_TX", strTexture);
		//!危険度のゲージのスプライト
		strTexture = dataDir + L"Texture\\" + L"Arrow.png";
		App::GetApp()->RegisterTexture(L"Arrow_TX", strTexture);


		//!床のモデル読み込み
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir,L"MayaModel\\" L"StageFloor.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh1);

	
		//!壁のモデル読み込み
		auto staticModelMesh3 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageWall.bmf");
		App::GetApp()->RegisterResource(L"STAGEWALL_MESH", staticModelMesh3);
	
		//!建物のモデル読み込み
		auto staticModelMesh4 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"House.bmf");
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

		//!プレイヤーのモデルの読み込み
		auto staticModelMesh8 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"PlayerWolf.bmf");
		App::GetApp()->RegisterResource(L"PLAYER_Wolf", staticModelMesh8);

		//!プレイヤーのモデルの読み込み
		auto staticModelMesh10 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"MainCharacter.bmf");
		App::GetApp()->RegisterResource(L"PLAYER_HUMAN", staticModelMesh10);


		//!柵のモデルの読み込み
		auto staticModelMesh9 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageFence.bmf");
		App::GetApp()->RegisterResource(L"STAGE_FENCE", staticModelMesh9);

		//モデル
		//ボーンモデルの通常リソース
		auto humanMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"Enemy_Animation.bmf");
		App::GetApp()->RegisterResource(L"Player_WalkAnimation_MESH", humanMultiModelMesh);

		//ボーンモデルのタンジェント付きリソース
		humanMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"Enemy_Animation.bmf");
		App::GetApp()->RegisterResource(L"Player_WalkAnimation_MESH_WITH_TAN", humanMultiModelMesh);

		//モデル
		//ボーンモデルの通常リソース
		auto playrWolfMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"Wolf_Animation.bmf");
		App::GetApp()->RegisterResource(L"PlayerWolf_WalkAnimation_MESH", playrWolfMultiModelMesh);

		//ボーンモデルのタンジェント付きリソース
		playrWolfMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"Wolf_Animation.bmf");
		App::GetApp()->RegisterResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN", playrWolfMultiModelMesh);

		//モデル
		//ボーンモデルの通常リソース
		auto EnemyHunterMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"EnemyHunter_Animation.bmf");
		App::GetApp()->RegisterResource(L"Enemy_WalkAnimation_MESH", EnemyHunterMultiModelMesh);

		//ボーンモデルのタンジェント付きリソース
		EnemyHunterMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"EnemyHunter_Animation.bmf");
		App::GetApp()->RegisterResource(L"Enemy_WalkAnimation_MESH_WITH_TAN", EnemyHunterMultiModelMesh);


		//モデル
	//ボーンモデルの通常リソース
		auto EnemyVillagerMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"EnemyVillager_Animation.bmf");
		App::GetApp()->RegisterResource(L"EnemyVillager_WalkAnimation_MESH", EnemyVillagerMultiModelMesh);

		//ボーンモデルのタンジェント付きリソース
		EnemyVillagerMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"EnemyVillager_Animation.bmf");
		App::GetApp()->RegisterResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN", EnemyVillagerMultiModelMesh);

		//法線マップ
		strTexture = dataDir + L"PlalyerBanpMap.png";
		App::GetApp()->RegisterTexture(L"OBJECT_NORMAL_TX", strTexture);

		//!BGM
		wstring strMusic = dataDir + L"Sound\\" L"BGM.wav";//ゲーム中のBGM
		App::GetApp()->RegisterWav(L"bgm", strMusic);

		strMusic = dataDir + L"Sound\\" L"Title.wav";//タイトル画面のBGM
		App::GetApp()->RegisterWav(L"TitleBGM", strMusic);

		strMusic = dataDir + L"Sound\\" L"walk.wav";//タイトル画面のBGM
		App::GetApp()->RegisterWav(L"WalkBGM", strMusic);

		wstring decisionWav = dataDir + "Sound\\" L"decision.wav";//ボタンを押したときの音
		App::GetApp()->RegisterWav(L"decision", decisionWav);

		wstring killWav = dataDir + "Sound\\" L"kill.wav";//敵を殺した時の音
		App::GetApp()->RegisterWav(L"kill", killWav);

		


	}

	//!駆け付けた敵の作成

	//!敵(スケール、ローテイション、ポジション)の構造体
	struct TransformCreate {
		//!構造体テンプレート
		Vec3 scale = Vec3(0.0f);//!大きさ
		Vec3 rotation = Vec3(0.0f);//!回転
		Vec3 position = Vec3(0.0f);//!位置
		wstring EnemykeyName = L"";//!村人の巡回ルートのキーフレームを取得

		TransformCreate() :
			TransformCreate(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), wstring(L""))
		{}
		//!構造体の初期化
		TransformCreate(
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
	std::vector<TransformCreate>TransformDate(const wstring& folderName, const wstring& fileName, const wstring& keyName) {
		std::vector<TransformCreate>result;//!変数名
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
			result.push_back(TransformCreate(Scale, Rot, Pos, EnemykeyName));

		}

		return result;
	}



	//!パトロールポイントの構造体
	struct PointCreate {
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0.0f);

		PointCreate() :
			PointCreate(vector<Vec3>(0.0f)) {}
		PointCreate(const std::vector<Vec3>& patrolPoints) :
			m_patorlPositions(patrolPoints)
		{}
	};

	//!パトロールポイント
	PointCreate PointDate(const wstring& folderName, const wstring& fileName, const wstring& keyName)
	{
		PointCreate PatorlPoint;

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


	void Scene::CreateEnemy()
	{
		
		auto datasHunter = TransformDate(L"csvFolder\\", L"RushedEnemy.csv", L"Hunter");//!ハンターのExcelのデータ
		for (auto dataHunter : datasHunter)
		{
			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", dataHunter.EnemykeyName);//!敵の巡回ポイントの名前を取り出す
			auto HunterPtr = GetActiveStage()->AddGameObject<Hunter>(dataHunter.scale, dataHunter.rotation, dataHunter.position, pointData.m_patorlPositions);//!増員されるハンターの作成
			GetActiveStage()->AddGameObject<LoseSightOf>(HunterPtr);
			GetActiveStage()->AddGameObject<SurprisedSprite>(HunterPtr);

		}
		
	}

	void Scene::SetAlertlevelCount(int AlertlevelCount)
	{
		//m_alertLevelCountと違うなら
		if (m_AlertlevelCount != AlertlevelCount) {

			//アラートレベルが1なら
			if (AlertlevelCount == 1) {

				//敵の生成
				CreateEnemy();
			}

		}


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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
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
