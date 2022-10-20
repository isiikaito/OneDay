/**
*@file StageBuilding.h
*@brief ゲームステージの建物の実装が定義されているヘッダーファイル
*@author Ayumu Muroi
*@details ゲームステージの建物の実装
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross {
	class StageBuilding : public GameObject {
		Vec3 m_Scale;   //!大きさ
		Vec3 m_Rotation;//!回転
		Vec3 m_Position;//!位置

	public:
		/**
		* コンストラクタ
		*/
		StageBuilding(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~StageBuilding() {}

		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;
	};
}