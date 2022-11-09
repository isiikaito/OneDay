/*!
@file Key.h
@brief カギに関する処理
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Key : public GameObject {
		Vec3 m_Scale;   //!大きさ
		Vec3 m_Rotation;//!回転
		Vec3 m_Position;//!位置

	public:
		/**
		* コンストラクタ
		*/
		Key(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~Key() {}

		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;
	

		
	};
}

//end basecross
