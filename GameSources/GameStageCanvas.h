/*!
@file GameStageCanvas.h
@author Kaito Isii
@brief ゲームステージで使うUIの生成管理
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum Hurte
	{
		RightHurte,
		CentraHurte,
		LeftHurteS
	};

	class GameStageCanvas : public GameObject {
	private:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	時計のスプライトの作成
		*/
		void CreateClockSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	時計の円盤のスプライト
		*/
		void CreateCircleClockSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	警戒度ゲージの作成
		*/
		void CreateAlertlevelGauge();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	タイマースプライト作成
		*/
		void CreateTimerSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターのライフの作成
		*/
		void CreateHeartSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	矢印の作成
		*/
		void CreateArrow();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	カギのフレーム
		*/
		void CreateKeyFrame();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	お肉のゲージの背景
		*/
		void CreateMeatGageBackGround();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	空腹ゲージの作成
		*/
		void CreateHungerGage();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	空腹ゲージの枠の作成
		*/
		void CreateMeatGageFrame();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	時計の針
		*/
		void CreateClockArrow();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	夜から昼に変わるときのコメント
		*/
		void CreateDateChangeCommentDay();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	昼から夜に変わるときのコメント
		*/
		void CreateDateChangeCommentNight();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオーバースプライト
		*/
		void CreateGameOver();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	鍵のスプライトの作成
		*/
		void CreateKeySprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	フェードアウトの作成
		*/
		void CreateFadeOut();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		GameStageCanvas(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~GameStageCanvas(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		void OnCreate();

	};



}
//end basecross
