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
	
	enum class CameraSelect {
		openingCamera,
		myCamera
	};


	enum class Oneday {
		midday,
		night
	};
	
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
		float m_totalTime;//!トータル時間(タイマーの作成)
		const float m_GameTime;//!ゲームの時間
		float m_playerChangeTime;//!プレイヤーの変身時間
		float m_MeatTime;//!肉の位置をランダムにする時間
		int m_MeatNumber;//!肉の位置を保存したCSVの番号
		int m_Date;//!日付
		int m_oneday;//!現在の状況
		bool m_gameStrat;//!ゲームのスタート状態
		bool m_heartSpriteDraw;//!ハートのスプライトを表示する処理をしているかどうか
		float m_gameStartTime;//!ゲームのスタートしてからの時間
		float m_dayTime;//!一日の時間
		float m_emissiveChangeTime;//!ライトの時間
		InputHandler<GameStage> m_InputHandler;//!入力ハンドラー
		shared_ptr<EfkInterface> m_EfkInterface;

		//!OpeningCamera用のビュー
		shared_ptr<SingleView> m_openingCameraView;
        //!MyCamera用のビュー
		shared_ptr<SingleView>m_myCameraView;
		//!現在のカメラ設定
		CameraSelect m_CameraSelect;


	public:
		//構築と破棄
		GameStage() :Stage(), m_heartSpriteDraw(false),m_totalTime(31.0f), m_oneday(0), m_emissiveChangeTime(1.0f), m_dayTime(0.0f), m_GameTime(31.0f), m_MeatNumber(0), m_MeatTime(0.0f), m_Date(0), m_playerChangeTime(0.0f), m_gameStrat(true), m_gameStartTime(0.0f), m_CameraSelect(CameraSelect::openingCamera) {}
		virtual ~GameStage() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ビューの作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateViewLight();  

		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージの床
		*/
		//--------------------------------------------------------------------------------------
		void CreateStageFloor(); 

		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーの作成
		*/
		//--------------------------------------------------------------------------------------
		void CreatePlayer();

		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージの壁
		*/
		//--------------------------------------------------------------------------------------
		void CreateStageWall(); 

		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージの建物
		*/
		//--------------------------------------------------------------------------------------
		void CreateStageBuilding(); 

		//--------------------------------------------------------------------------------------
		/*!
		@brief　鍵の作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateKey();


		//--------------------------------------------------------------------------------------
		/*!
		@brief　ステージの門
		*/
		//--------------------------------------------------------------------------------------
		void CreateStageGate(); 

		//--------------------------------------------------------------------------------------
		/*!
		@brief　村人の作成
		*/
		//--------------------------------------------------------------------------------------
		void CerateVillager();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ハンターの作成
		*/
		//--------------------------------------------------------------------------------------
		void CerateHunter();

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief　木箱の作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateWoodenBox();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　木の作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateWood();

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief　BGM作成
		*/
		//--------------------------------------------------------------------------------------
		void CreatePlayBGM();

		//--------------------------------------------------------------------------------------
		/*!
		@briefゲームオーバーのBGM
		*/
		//--------------------------------------------------------------------------------------
		void CreateGameOverBGM(); 

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ゲームオーバーのBGMの削除
		*/
		//--------------------------------------------------------------------------------------
		void DestroyGameOverBGM(); 

		
		//--------------------------------------------------------------------------------------
		/*!
		@brief　村長の作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateHeadMan();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　昼と夜を変える時間
		*/
		//--------------------------------------------------------------------------------------
		void GameTime();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　肉の作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateMeat();
	
		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　エフェクトのインターフェース
		@retrun エフェクトインターフェース
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<EfkInterface> GetEfkInterface() const
		{
			return m_EfkInterface;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief 消す
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDestroy() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　Aボタンの処理
		*/
		//--------------------------------------------------------------------------------------
		void OnPushA();
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief　カメラマンの作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateCameraman();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　カメラをプレイヤーに戻す
		*/
		//--------------------------------------------------------------------------------------
		void ToMyCamera(); 
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief　UIの表示非表示
		*/
		//--------------------------------------------------------------------------------------
		void UIDrawActive(bool t);

		//--------------------------------------------------------------------------------------
		/*!
		@brief　オープニングカメラ起動時の処理
		*/
		//--------------------------------------------------------------------------------------
		void OpeningCameraBooting(float time);

		
	};
}
//end basecross

