/**
*@file Wood.h
*@brief 木の実装が定義されているヘッダーファイル
*@author kanazawa yuuma
*@details 木の実装
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross {
	class Wood : public GameObject {
	private:
		Vec3 m_Scale;   //!大きさ
		Vec3 m_Rotation;//!回転
		Vec3 m_Position;//!位置
		float m_shadowbuilding; // !影を付けた家にする
		float m_Time; // !切り替える時間
		int m_oneday; // !朝と夜に変化する

		enum class Oneday {
			midday,
			night
		};

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
