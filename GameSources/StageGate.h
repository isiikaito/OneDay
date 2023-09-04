/**
*@file StageGate.h
*@brief ゲームステージの門の実装が定義されているヘッダーファイル
*@author Ayumu Muroi
*@details ゲームステージの門の実装
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross {
	class StageGate : public GameObject {
	private:
		Vec3 m_Scale;				//!大きさ
		Vec3 m_Rotation;			//!回転
		Vec3 m_Position;			//!位置
		Vec3 modelScale;			//!メッシュの大きさ
		Vec3 modelRotOrigin;		//!回転の起源
		Vec3 modelRotation;			//!メッシュの回転
		Vec3 modelPosition;			//!メッシュの位置


	public:
		/**
		* コンストラクタ
		*/
		StageGate(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~StageGate() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief アニメーションの切り替え
		*/
		//--------------------------------------------------------------------------------------
		void AnimationChange();
		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}