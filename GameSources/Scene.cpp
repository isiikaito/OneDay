
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionStage.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::RoadTexture(const wstring& TextureName, const wstring& UseTextureName)
	{
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!テクスチャ
		wstring strTexture = dataDir + L"Texture\\" + TextureName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	void Scene::RoadSound(const wstring& soundDataName, const wstring& soundName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);//!サンプルのためメディアディレクトリを取得
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}

	//!スタティックモデルの読み込み
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName)
	{
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,
			MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" + staticModelbmfName + L".bmf")
		);

	}

	//!ボーン付きモデルの読み込み
	void Scene::RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName)
	{
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!ボーンモデルの通常リソース
		App::GetApp()->RegisterResource(BoneModelMeshName,
			MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" + BoneModelbmfName + L".bmf"));

		//! ボーンモデルのタンジェント付きリソース
		App::GetApp()->RegisterResource(BomeModelMeshTangentName,
			MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" + BoneModelbmfName + L".bmf")
		);

	}

	void Scene::CreateResourses()
	{
		//!テクスチャ

		//!時計の円盤のスプライト
		RoadTexture(L"Circle.png", L"Circle_TX");
		//!ゲージの背景
		RoadTexture(L"Background.png", L"Background_TX");
		//!ゲージのフレーム
		RoadTexture(L"Frame.png", L"Frame_TX");
		//!ゲージ
		RoadTexture(L"FullGage.png", L"Full_TX");
		//!村長のコメント
		RoadTexture(L"HeadManCommet1.png", L"HeadManCommet1_TX");
		RoadTexture(L"HeadManCommet2.png", L"HeadManCommet2_TX");
		RoadTexture(L"HeadManCommet3.png", L"HeadManCommet3_TX");
		//!夜から昼になったときに出るテクスチャ
		RoadTexture(L"QuestMessage_Noon.png", L"CommentDay_TX");
		//!昼から夜になったらでるテクスチャ
		RoadTexture(L"QuestMessage_Night.png", L"CommentNignt_TX"); 
		//!数字の取得
		RoadTexture(L"Nomber_3.png", L"NUMBER_TX");
		//!危険度のゲージのスプライト
		RoadTexture(L"Arrow.png", L"Arrow_TX");
		//!警戒度ゲージ
		RoadTexture(L"testGauge.png", L"AlertlevelGaugeGauge_TX");
		//!はてなマークのスプライト
		RoadTexture(L"LoseSightOf.png", L"LoseSightOf_TX");
		//!ビックリマークのスプライト
		RoadTexture(L"Surprised.png", L"Surprised_TX");
		//!時計のスプライト
		RoadTexture(L"Clock.png", L"Clock_TX");
		//!プレイヤーのHPスプライト
		RoadTexture(L"PlayerHp.png", L"PlayerHp_TX");
		//!キースプライト
		RoadTexture(L"key.png", L"KEY_TX");
		//!ゲームクリア画面
		RoadTexture(L"GameClear.png", L"GAMECLEAR_TX");
		//!ゲームオーバー画面
		RoadTexture(L"GameOver.png", L"GAMEOVER_TX");

		RoadTexture(L"Title.jpg", L"MESSAGE_TX");
		//!カギの枠
		RoadTexture(L"ItemField.png", L"ItemField_TX");
		//!説明書1のテクスチャ
		RoadTexture(L"Explanation_01.png", L"DescriptionSprite1_TX");
		//!説明書2のテクスチャ
		RoadTexture(L"Explanation_02.png", L"DescriptionSprite2_TX");
		//!法線マップのテクスチャ
		RoadTexture(L"PlalyerBanpMap.png", L"OBJECT_NORMAL_TX");
	    //!床のモデル
		RoadStaticModelMesh(L"StageFloor", L"STAGEFLOOR_MESH");
		//!ボックスの追加
		RoadStaticModelMesh(L"Box", L"BOX_MESH");
		
		//!壁のモデル読み込み
		RoadStaticModelMesh(L"StageWall", L"STAGEWALL_MESH");
		//!建物のモデル読み込み
		RoadStaticModelMesh(L"House", L"STAGEBUILDING_MESH");
		//!鍵のモデル読み込み
		RoadStaticModelMesh(L"Key", L"KEY_MESH");
		//!地面のモデルの読み込み
		RoadStaticModelMesh(L"Ground", L"GROUND_MESH");
		//!柵のモデルの読み込み
		RoadStaticModelMesh(L"StageFence", L"STAGE_FENCE");
		//!柵のモデルの読み込み
		RoadStaticModelMesh(L"Wood", L"STAGE_WOOD");
		//!肉のモデルの読み込み
		RoadStaticModelMesh(L"Meat", L"MEAT_MESH");
		
		//ボーンモデルの通常リソース
		// プレイヤー（狼）のアニメーション
		RoadBoneModel(L"Wolf_Animation", L"PlayerWolf_WalkAnimation_MESH", L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");
		// ハンターのアニメーション
		RoadBoneModel(L"Hunter_Animation", L"EnemyHunter_Animation_MESH", L"EnemyHunter_Animation_MESH_WITH_TAN");

		// 村人のアニメーション
		RoadBoneModel(L"EnemyVillager_Animation", L"EnemyVillager_WalkAnimation_MESH", L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");

		// プレイヤー（人間）のアニメーション
		RoadBoneModel(L"Player_Animation", L"Player_WalkAnimation2_MESH", L"Player_WalkAnimation2_MESH_WITH_TAN");

		// 扉のアニメーション
		RoadBoneModel(L"Gate_Animation", L"GateAnimation_MESH", L"GateAnimation_MESH_WITH_TAN");
		
		

		//!ゲーム中のBGM
		RoadSound(L"BGM.wav", L"bgm");
		//肉を食べる音
		RoadSound(L"MeatEat.wav", L"MeatEat");
		//木箱破壊音
		RoadSound(L"WoodBoxBreak.wav", L"WoodBoxBreak");
		//タイトル画面のBGM
		RoadSound(L"Title.wav", L"TitleBGM");
		//歩く音
		RoadSound(L"walk.wav", L"WalkBGM");
		//ボタンを押したときの音
		RoadSound(L"decision.wav", L"decision");
		//敵を殺した時の音
		RoadSound(L"kill.wav", L"kill");
		//狼に変身した時の遠吠え
		RoadSound(L"howling.wav", L"howling");
		//村人の叫び声
		RoadSound(L"scream.wav", L"scream");
		//カギを拾う音
		RoadSound(L"acquisition.wav", L"acquisition");
		//攻撃音
		RoadSound(L"firing.wav", L"firing");
		//ゲームクリア音
		RoadSound(L"GameClear.wav", L"GameClear");
		//ゲームオーバー音
		RoadSound(L"GameOver.wav", L"GameOver");
		//!ページめくる音
		RoadSound(L"FlipPage.wav", L"FlipPage");

		

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

		auto& app = App::GetApp();						//!アプリの取得
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);		//!データの取得
		auto fullPass = DataDir + folderName + fileName;//!ファイルの位置の特定
		CsvFile csvFile;
		csvFile.SetFileName(fullPass);					//!ファイルの位置の設定
		csvFile.ReadCsv();								//!csvの読み込み

		csvFile.GetSelect(LineVec, 0, keyName);			//!0番目のカラムがL"Villager"である行を抜き出す

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
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0);

		PointCreate() :
			PointCreate(vector<Vec3>(0)) {}
		PointCreate(const std::vector<Vec3>& patrolPoints) :
			m_patorlPositions(patrolPoints)
		{}
	};

	//!パトロールポイント
	PointCreate PointDate(const wstring& folderName, const wstring& fileName, const wstring& keyName)
	{
		PointCreate PatorlPoint;

		vector<wstring>LineVec;
		auto& app = App::GetApp();						//!アプリの取得
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);		//!データの取得
		auto fullPass = DataDir + folderName + fileName;//!ファイルの位置の特定

		CsvFile csvFile;								//!ファイルの位置の設定
		csvFile.SetFileName(fullPass);					//!csvの読み込み
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
		
		auto datasHunter = TransformDate(L"csvFolder\\" L"EnemyData\\", L"RushedEnemy.csv", L"Hunter");															//!ハンターのExcelのデータ
		for (auto& dataHunter : datasHunter)
		{
			auto pointData = PointDate(L"csvFolder\\" L"EnemyData\\", L"Point.csv", dataHunter.EnemykeyName);													//!敵の巡回ポイントの名前を取り出す
			auto HunterPtr = GetActiveStage()->AddGameObject<Hunter>(dataHunter.scale, dataHunter.rotation, dataHunter.position, pointData.m_patorlPositions);	//!増員されるハンターの作成
			GetActiveStage()->AddGameObject<LoseSightOf>(HunterPtr);																							//!はてなマークの板ポリ生成時にハンターとペアレント化する
			GetActiveStage()->AddGameObject<SurprisedSprite>(HunterPtr);																						//!ビックリマークの板ポリ生成時にハンターとペアレント化する

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
		
			CreateResourses();//!リソース作成
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		

	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage")				//!ゲームステージ
		{
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage")		//!タイトルステージ
		{
			ResetActiveStage<TitleStage>();
		}
		
		else if (event->m_MsgStr == L"ToGameClearStage")	//!ゲームクリアステージ
		{
			ResetActiveStage<GameClearStage>();
		}
		else if (event->m_MsgStr == L"ToDescriptionStage")	//!説明書ステージ
		{
			ResetActiveStage<DescriptionStage>();
		}
	}

}
//end basecross
