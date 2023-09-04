/**
*@file StageBuilding.h
*@brief ゲームステージの建物の実装が定義されているヘッダーファイル
*@author Ayumu Muroi
*@details ゲームステージの建物の実装
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross共通のネームペース*/
namespace basecross {




	class StageBuilding : public GameObject {
	private:
		float m_Time;									//!切り替える時間
		int m_oneday;									//!朝と夜に変化する
		StaticModelDeta m_buildingModelData;			//!家のモデルデータ
		std::weak_ptr<PNTStaticModelDraw> m_ptrDrow;	//!描画処理

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	このコンポーネントを所持するゲームオブジェクト
		*/
		StageBuilding(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~StageBuilding() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームステージの床の初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームステージの床の更新
		*/
		virtual void OnUpdate() override;
	};
}