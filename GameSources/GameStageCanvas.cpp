/*!
@file GameStageCanvas.cpp
@author Kaito Isii
@brief  ゲームステージで使うUIの管理
*/


#include "stdafx.h"
#include "Project.h"
#include "GameStageCanvas.h"
#include "GameUI.h"
#include "PlayerHurteSprite.h"
#include "HungerGage.h"
#include "DateChangeCommentDay.h"
#include "DateChangeCommentNight.h"
#include "KeySprite.h"

namespace basecross
{
	constexpr int MAXKEYCOUNT = 3;//!カギを取得できる最大個数
	//--------------------------------------------------------------------------------------
	///	ゲームキャンバス
	//--------------------------------------------------------------------------------------

	GameStageCanvas::GameStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	//!テクスチャの(スケール,ローテーション,ポジション)の構造体
	struct TextureTransformCreateDate
	{
		//!構造体テンプレート
		Vec2 scale = Vec2(0.0f);//!大きさ
		Vec3 position = Vec3(0.0f);//!位置

		TextureTransformCreateDate() :
			TextureTransformCreateDate(Vec2(0.0f), Vec3(0.0f))
		{}
		//!構造体の初期化
		TextureTransformCreateDate(
			const Vec2& scale,
			const Vec3& position
		) :
			scale(scale),
			position(position)
		{}
	};

	//!csvからデータの取り出し
	std::vector<TextureTransformCreateDate>GameStageTextureTransformDate(const wstring& FolderName, const wstring& csvName, const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;//!トランスフォームのデータを保存する配列
		vector<wstring>LineVec;//!変数名

		auto& app = App::GetApp();//!アプリの取得
		wstring DateDir;
		App::GetApp()->GetDataDirectory(DateDir);
		auto fullPass = DateDir + L"csvFolder\\" + FolderName + csvName;

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');//!トークン(カラム)単位で文字列を抽出(',')

			//!トークン(カラム)をスケール、回転、位置に読み込む
			Vec2 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			//!位置
			Vec3 Pos(
				(float)_wtof(Tokens[3].c_str()),
				(float)_wtof(Tokens[4].c_str()),
				(float)_wtof(Tokens[5].c_str())
			);

			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y, Pos.z)));

		}
		return result;
	}


	// !時計のスプライトの作成
	void GameStageCanvas::CreateClockSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"clockSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"Clock_TX",	//!テクスチャ
					true,			//!透明処理
					data.scale,		//!大きさ 
					data.position	//!位置(x,y,z)z奥行きは0.0f～1.0fの間
					);
		}


	}

	// !時計の円盤のスプライトの作成
	void GameStageCanvas::CreateCircleClockSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"circleClockSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<CircleClockSprite>
				(
					L"Circle_TX",//!テクスチャ
					true,		 //!透明処理
					data.scale,  //!大きさ 
					data.position//!位置(x,y,z)z奥行きは0.0f～1.0fの間 
					);
		}

	}

	void GameStageCanvas::CreateAlertlevelGauge()
	{

		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"AlertlevelGaugeTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"AlertlevelGaugeGauge_TX",//!テクスチャ
					true,					   //!透明処理
					data.scale,				   //!大きさ
					data.position			   //!位置(x,y,z)z奥行きは0.0f～1.0fの間
					);
		}

	}

	//スコアスプライト作成
	void GameStageCanvas::CreateTimerSprite() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TimerSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<Timer>(2,
				L"NUMBER_TX",//!テクスチャ
				true,		 //!透明処理
				data.scale,  //!大きさ
				data.position//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);
		}

	}

	void GameStageCanvas::CreateHeartSprite()
	{

		auto leftHurteSpriteTexture = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"LeftHurteSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : leftHurteSpriteTexture)
		{
			//!左側のハート
			GetStage()->AddGameObject<PlayerHurteSprite>
				(
					L"PlayerHp_TX",		//!テクスチャ
					true,				//!透明処理
					data.scale,			//!大きさ
					data.position,		//!位置(x,y,z)z奥行きは0.0f～1.0fの間
					LeftHurteS,			//!現在のライフ
					true				//!表示されているかどうか
					);
		}

		auto centralHurteSpriteTexture = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"CentralHurteSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : centralHurteSpriteTexture)
		{
			//!中央側のハート
			GetStage()->AddGameObject<PlayerHurteSprite>
				(
					L"PlayerHp_TX",		//!テクスチャ
					true,				//!透明処理
					data.scale,			//!大きさ
					data.position,		//!位置(x,y,z)z奥行きは0.0f～1.0fの間
					CentraHurte,		//!現在のライフ
					true				//!表示されているかどうか
					);
		}

		auto rightHurteSpriteTexture = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"RightHurteSpriteTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : rightHurteSpriteTexture)
		{

			//!右側のハート
			GetStage()->AddGameObject<PlayerHurteSprite>
				(
					L"PlayerHp_TX",//!テクスチャ
					true,		   //!透明処理
					data.scale,		//!大きさ
					data.position,	//!位置(x,y,z)z奥行きは0.0f～1.0fの間
					RightHurte,		//!現在のライフ
					true			//!表示されているかどうか
					);
		}

	}

	void GameStageCanvas::CreateArrow()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"ArrowTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			//!矢印の作成
			GetStage()->AddGameObject<Arrow>
				(
					L"Arrow_TX", //!テクスチャ
					true,		 //!透明処理
					data.scale,  //!大きさ
					data.position//!位置(x,y,z)z奥行きは0.0f～1.0fの間
					);
		}

	}

	void GameStageCanvas::CreateKeyFrame()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"KeyFrameTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>(
				L"ItemField_TX",//!テクスチャ
				true,			//!透明処理
				data.scale,		//!大きさ
				data.position	//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);
		}


	}

	void GameStageCanvas::CreateMeatGageBackGround()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"MeatGageBackGroundTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"Background_TX",	//!テクスチャ
					true,				//!透明処理
					data.scale,			//大きさ
					data.position		//座標
					);
		}


	}

	void GameStageCanvas::CreateMeatGageFrame()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"MeatGageFrameTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>(
				L"Frame_TX",	//!テクスチャ
				true,			//!透明処理
				data.scale,		//大きさ
				data.position	//座標
				);
		}
	}


	void GameStageCanvas::CreateHungerGage()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"HungerGageTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<HungerGage>(
				L"Full_TX",		//!テクスチャ
				true,			//!透明処理
				data.scale,		//大きさ
				data.position	//座標
				);
		}
	}

	void GameStageCanvas::CreateClockArrow()
	{
		Vec3 rotation = Vec3(0.0f, 0.0f, 90.0f);
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"ClockArrowTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"Arrow_TX",	//!テクスチャ
					true,			//!透明処理
					data.scale,		//!大きさ
					rotation,		//!回転
					data.position	//!位置
					);
		}

	}

	void GameStageCanvas::CreateDateChangeCommentDay()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"DateChangeCommentDayTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<DateChangeCommentDay>(
				L"CommentDay_TX",	//!テクスチャ
				true,				//!透明処理
				data.scale,			//大きさ
				data.position		//座標
				);
		}
	}

	void GameStageCanvas::CreateDateChangeCommentNight()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"DateChangeCommentNightTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<DateChangeCommentNight>(
				L"CommentNignt_TX",	//!テクスチャ
				true,				//!透明処理
				data.scale,			//大きさ
				data.position		//座標
				);

		}
	}


	void GameStageCanvas::CreateGameOver()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"GameOverTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameOverSprite>(
				L"GAMEOVER_TX",//!テクスチャ
				false,		   //!透明処理
				data.scale,    //!大きさ
				data.position  //!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);
		}

	}

	
	void GameStageCanvas::CreateKeySprite()
	{
	
		for (int i = 0; i < MAXKEYCOUNT; i++)
		{
			auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"KeySpriteTexture"+ Util::IntToWStr(i));//!csvの最初の行の文字の取得
			//!データ分回す
			for (auto& data : datas)
			{
					GetStage()->AddGameObject<KeySprite>(
						L"KEY_TX",		//!テクスチャ
						true,			//!透明処理
						data.scale,		//!大きさ//!大きさ
						data.position,	//!位置(x,y,z)z奥行きは0.0f～1.0fの間
						i				//!カギの個数
				    );
			}
		}
		
	}

	void GameStageCanvas::CreateFadeOut()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"FadeOutTexture");//!csvの最初の行の文字の取得
		//!データ分回す
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<FadeOut>(
				true,			//!透明処理//!大きさ
				data.scale,		//!大きさ//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				data.position);	//!位置(x,y,z)z奥行きは0.0f～1.0fの間
		}						
	}
	
	
	
	void GameStageCanvas::OnCreate()
	{
		CreateClockSprite();			
		CreateCircleClockSprite();		
		CreateAlertlevelGauge();		
		CreateTimerSprite();			
		CreateHeartSprite();			
		CreateArrow();					
		CreateKeyFrame();				
		CreateMeatGageBackGround();		
		CreateMeatGageFrame();			
		CreateHungerGage();				
		CreateClockArrow();				
		CreateDateChangeCommentDay();	
		CreateDateChangeCommentNight();	
		CreateGameOver();				
		CreateKeySprite();				
		CreateFadeOut();				
	}

	
}