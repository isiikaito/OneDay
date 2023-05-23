/*!
@file DescriptionStage.h
@brief説明書ステージ
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class PageNumber {
		farst,
		second,
		three,
		four
	};


	class DescriptionSpriteFront;
	
	
	class DescriptionStage : public Stage {
	private:
		
		InputHandler<DescriptionStage> m_InputHandler;
		InputHandlerCrossKey<DescriptionStage> m_InputHandlerCrossKey;//入力ハンドラー


		Vec3 m_startEye;					//!カメラの位置
		Vec3 m_startAt;						//!カメラの視点
		shared_ptr<SoundItem>m_BGM;			//!音
		float m_keyTime;					//!カギをランダムに配置する時間
		int m_descriptionStageNumber;		//!説明書のページ数
		int m_keyNumber;					//!カギの配置が読み込んでいるCSVの数字
		float m_timeItTakesToTurnThePage;	//!ページをめくっている時間
		bool m_IsmoveForwardInaPage;		//!ページを進めているかどうか
		bool m_IspageBackTo;				//!ページを戻しているかどうか
		std::vector<shared_ptr<DescriptionSpriteFront>> DescriptionSprites;//!説明書を保管する配列
	    public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューの作成
		*/
		void CreateViewLight();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　BGM作成
		*/
		void CreatePlayBGM();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		DescriptionStage() :Stage(), m_IsmoveForwardInaPage(false),m_IspageBackTo(false), m_timeItTakesToTurnThePage(0.0f), m_descriptionStageNumber(0), m_keyTime(0.0f), m_keyNumber(0), m_startEye(Vec3(0.0f, 2.0f, -3.0f)), m_startAt(Vec3(0.0f, 0.0f, 0.0f)) {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		virtual ~DescriptionStage() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新
		*/
		virtual void OnUpdate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief 削除
		*/
		virtual void OnDestroy() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief　Aボタンの処理
		*/
		void OnPushA();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　十字キーの右ボタンの処理
		*/
		void PushHandleCrossRight();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　十字キーの左ボタンの処理
		*/
		void PushHandleCrossLeft();

		
		
	};


}
//end basecross

