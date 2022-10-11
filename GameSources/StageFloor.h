/**
*@file StageFloor.h
*@brief ゲームステージの床の実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details ゲームステージの床の実装
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross {
	class StageFloor : public GameObject {
		Vec3 m_Scale;   //!大きさ11111
		Vec3 m_Rotation;//!回転
		Vec3 m_Position;//!位置

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
	};
}