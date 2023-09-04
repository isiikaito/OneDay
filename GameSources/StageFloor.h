/**
*@file StageFloor.h
*@brief ゲームステージの床の実装が定義されているヘッダーファイル
*@author Ayumu Muroi
*@details ゲームステージの床の実装
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross共通のネームペース*/
namespace basecross {
	class StageFloor : public GameObject {
	private:
		StaticModelDeta m_stageFloorModelData;			//!床のモデルデータ

	public:
		/**
		* コンストラクタ
		*/
		StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~StageFloor() {}

		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}