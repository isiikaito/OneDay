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
	constexpr int m_MaxKeyCount = 3;//!カギを取得できる最大個数
	//--------------------------------------------------------------------------------------
	///	ゲームキャンバス
	//--------------------------------------------------------------------------------------

	GameStageCanvas::GameStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	// !時計のスプライトの作成
	void GameStageCanvas::CreateClockSprite()
	{
		GetStage()->AddGameObject<GameUI>
			(
				L"Clock_TX",
				true,
				Vec2(170.0f, 128.0f),
				Vec3(-460.0f, 290.0f, 0.3f)
				);



	}

	// !時計の円盤のスプライトの作成
	void GameStageCanvas::CreateCircleClockSprite()
	{
		GetStage()->AddGameObject<CircleClockSprite>
			(
				L"Circle_TX",
				true,
				Vec2(65.0f, 70.0f),
				Vec3(-550.0f, 263.0f, 1.0f)
				);

	}

	void GameStageCanvas::CreateAlertlevelGauge()
	{

		GetStage()->AddGameObject<GameUI>
			(
				L"AlertlevelGaugeGauge_TX",
				true,
				Vec2(150.0f, 50.0f),       //!大きさ
				Vec3(460.0f, 350.0f, 1.0f) //!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);


	}

	//スコアスプライト作成
	void GameStageCanvas::CreateTimerSprite() {
		GetStage()->AddGameObject<Timer>(2,
			L"NUMBER_TX",
			true,
			Vec2(50.0f, 40.0f),
			Vec3(-400.0f, 265.0f, 10.0f));

	}

	void GameStageCanvas::CreateHeartSprite()
	{


		//!左側のハート
		GetStage()->AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),        //!大きさ
				Vec3(370.0f, -250.0f, 0.2f),//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				2,//!現在のライフ
				true//!表示されているかどうか
				);

		//!中央側のハート
		GetStage()->AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!大きさ
				Vec3(460.0f, -250.0f, 0.2f),//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				1,//!現在のライフ
				true//!表示されているかどうか
				);

		//!右側のハート
		GetStage()->AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!大きさ
				Vec3(550.0f, -250.0f, 0.2f),//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				0,//!現在のライフ
				true//!表示されているかどうか
				);

	}

	void GameStageCanvas::CreateArrow()
	{
		//!矢印の作成
		GetStage()->AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),       //!大きさ
				Vec3(390.0f, 330.0f, 0.8f)//!位置(x,y,z)z奥行きは0.0f～1.0fの間
				);

	}

	void GameStageCanvas::CreateKeyFrame()
	{
		GetStage()->AddGameObject<GameUI>(
			L"ItemField_TX",//!テクスチャ
			true,
			Vec2(200.0f, 150.0f), //!大きさ
			Vec3(-450.0f, -280.0f, 0.2f)//!位置(x,y,z)z奥行きは0.0f～1.0fの間
			);


	}

	void GameStageCanvas::CreateMeatGageBackGround()
	{
		GetStage()->AddGameObject<GameUI>
			(
				L"Background_TX",//!テクスチャ
				true,
				Vec2(200.0f, 50.0f),//大きさ
				Vec3(420.0f, -320.0f, 1.0f)//座標
				);


	}

	void GameStageCanvas::CreateMeatGageFrame()
	{
		GetStage()->AddGameObject<GameUI>(
			L"Frame_TX",//!テクスチャ
			true,
			Vec2(200.0f, 50.0f),//大きさ
			Vec3(420.0f, -320.0f, 0.2f)//座標
			);
	}


	void GameStageCanvas::CreateHungerGage()
	{
		GetStage()->AddGameObject<HungerGage>(
			L"Full_TX",//!テクスチャ
			true,
			Vec2(200.0f, 50.0f),//大きさ
			Vec3(420.0f, -320.0f, 0.2f)//座標
			);
	}

	void GameStageCanvas::CreateClockArrow()
	{
		GetStage()->AddGameObject<GameUI>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),//!大きさ
				Vec3(0.0f, 0.0f, 90.0f),//!回転
				Vec3(-500.0f, 300.0f, 0.2f)//!位置
				);


	}

	void GameStageCanvas::CreateDateChangeCommentDay()
	{
		GetStage()->AddGameObject<DateChangeCommentDay>(
			L"CommentDay_TX",//!テクスチャ
			true,
			Vec2(450.0f, 200.0f),//大きさ
			Vec3(0.0f, 200.0f, 0.1f)//座標
			);
	}

	void GameStageCanvas::CreateDateChangeCommentNight()
	{
		GetStage()->AddGameObject<DateChangeCommentNight>(
			L"CommentNignt_TX",//!テクスチャ
			true,
			Vec2(450.0f, 200.0f),//大きさ
			Vec3(0.0f, 200.0f, 0.1f)//座標
			);


	}


	void GameStageCanvas::CreateGameOver()
	{
		GetStage()->AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.0f));

	}

	//!鍵のスプライトの作成
	void GameStageCanvas::CreateKeySprite()
	{
		for (int i = 0; i < m_MaxKeyCount; i++)
		{
			GetStage()->AddGameObject<KeySprite>(
				L"KEY_TX",//!テクスチャ
				true,
				Vec2(60.0f, 60.0f),//大きさ
				Vec3(-565.0f + (110.0f * (i)), -280.0f, 0.2f),//座標
				i//!カギの個数
				);
		}
		
	}

	void GameStageCanvas::CreateFadeOut()
	{
        GetStage()->AddGameObject<FadeOut>(true,
		Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.1f));
	}
	
	
	
	void GameStageCanvas::OnCreate()
	{
		CreateClockSprite();//!時計のスプライト
		CreateCircleClockSprite(); //!時計の円盤のスプライトの作成
		CreateAlertlevelGauge();//!警戒度のゲージの作成
		CreateTimerSprite();//!時間のスプライトの作成
		CreateHeartSprite();//!プレイヤーのHPの作成
		CreateArrow();//!矢印の作成
		CreateKeyFrame();//!カギの枠の作成
		CreateMeatGageBackGround();//!空腹ゲージの背景
		CreateMeatGageFrame();//!空腹ゲージの枠
		CreateHungerGage();//!空腹ゲージ
		CreateClockArrow();//!時計の針
		CreateDateChangeCommentDay();//!夜から昼にでるテクスチャ
		CreateDateChangeCommentNight();//!昼から夜にでるテクスチャ
		CreateGameOver();//!ゲームオーバー
		CreateKeySprite();//!カギのスプライトの作成
		CreateFadeOut();//!フェードアウトの作成
	}

	void GameStageCanvas::OnUpdate()
	{
		

	}

}