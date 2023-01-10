/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "EfkInterfece.h"
namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	private:
		CsvFile m_GameStageCsvA; // !建物の配置
		CsvFile m_GameStageCsvB; // !建物の配置2
		CsvFile m_GameStageCsvC; // !建物の配置3
		CsvFile m_GameStageCsvD;// !建物の配置4
		CsvFile m_KeyPositon; // !鍵の配置
		CsvFile m_StageCsv;   //!ステージCSVファイル
		CsvFile m_MeatPositon;//!肉のポジションのCSVファイル
		shared_ptr<SoundItem>m_BGM; //!BGM
		shared_ptr<SoundItem>m_GameOverBGM; //!ゲームオーバーのBGM
		float m_TotalTime;//!トータル時間(タイマーの作成)
		const float m_GameTime;
		float m_MeatTime;//!肉の位置をランダムにする時間
		int m_MeatNumber;//!肉の位置を保存したCSVの番号
		int m_Date;//!日付
		
		InputHandler<GameStage> m_InputHandler;//!入力ハンドラー
		shared_ptr<EfkInterface> m_EfkInterface;

	public:
		//構築と破棄
		GameStage() :Stage(),m_TotalTime(31.0f), m_GameTime(31.0f), m_MeatNumber(0), m_MeatTime(0.0f), m_Date(0) {}
		virtual ~GameStage() {}

		void CreateViewLight();  //!ビューの作成
		void CreateStageFloor(); //!ステージの床
		void CreatePlayer();//!プレイヤーの作成
		void CreateStageWall(); //!ステージの壁
		void CreateStageBuilding(); //!ステージの建物
		void CreateKey();//!鍵の作成
		void CreateClockSprite(); //!時計のスプライトの作成
		void CreateCircleClockSprite(); //!時計の円盤のスプライト
		void CreateStageGate(); //!ステージの門
		void CerateVillager();//!村人の作成
		void CerateHunter();//!ハンターの作成
		void CreateAlertlevelGauge();//!警戒度ゲージの作成
		void CreateLightingCol();//!ライトの色を変える処理
		void CreateWoodenBox();//!木箱の作成
		void CreateWood();//木の作成
		void CreateTimerSprite();//!タイマースプライト作成
		void CreatePlayBGM();//!BGM作成
		void CreateGameOverBGM(); //!ゲームオーバーのBGM
		void DestroyGameOverBGM(); //!ゲームオーバーのBGMの削除
		void CreateHeartSprite();//!ハンターのライフの作成
		void CreateArrow();//!矢印の作成
		void CreateGameOver();//!ゲームオーバースプライト
		void CreateHeadMan();//!村長の作成
		void GameTime();//!昼と夜を変える時間
		void CreateMeat();//!肉の作成
		void CreateKeyFrame();//!カギのフレーム
		void CreateMeatGageBackGround();//!お肉のゲージの背景
		void CreateHungerGage();//!空腹ゲージの作成
		void CreateMeatGageFrame();//!空腹ゲージの枠の作成
		void CreateClockArrow();//!時計の針
	
		//初期化
		virtual void OnCreate()override;

		shared_ptr<EfkInterface> GetEfkInterface() const
		{
			return m_EfkInterface;
		}

		virtual void OnUpdate()override;

		virtual void OnDraw() override;

		virtual void OnDestroy() override;

		
		void OnPushA();//!Aボタン
		
		

	};
}
//end basecross

