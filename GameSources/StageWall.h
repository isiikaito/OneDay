/**
*@file StageWall.h
*@brief ゲームステージの壁の実装が定義されているヘッダーファイル
*@author Ayumu Muroi
*@details ゲームステージの壁の実装
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross {
	class StageWall : public GameObject {
	private:
		Vec3 m_Scale;   //!大きさ
		Vec3 m_Rotation;//!回転
		Vec3 m_Position;//!位置

	public:
		/**
		* コンストラクタ
		*/
		StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~StageWall() {}

		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;
	};
}