/**
*@file Wood.h
*@brief 木の実装が定義されているヘッダーファイル
*@author kanazawa yuuma
*@details 木の実装
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross共通のネームペース*/
namespace basecross {
	

	class Wood : public GameObject {
	private:
		StaticModelDeta m_woodModelData;//!家のモデルデータ

	public:
		/**
		* コンストラクタ
		*/
		Wood(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~Wood() {}

		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
