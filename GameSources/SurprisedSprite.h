/*!
@file SurprisedSprite.h
@author Kaito Isii
@brief ビックリマークの表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {




	class SurprisedSprite :public GameObject
	{
	private:
		std::shared_ptr<GameObject> parent; // 親オブジェクト
		float m_surprisedTime;
		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		Vec3 m_scale;

		float m_SurprisedTime;//!板ポリを表示する時間
		const float m_spritePositionY;//!板ポリのY軸のポジション
		bool m_IsFoundPlayer;//!プレイヤーを発見したとき
		

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief　コンストラクタ
		*/
		SurprisedSprite(const std::shared_ptr<Stage>& stage, const std::shared_ptr<GameObject>& parent)
			: GameObject(stage), parent(parent), m_SurprisedTime(0.0f), m_spritePositionY(8.0f) , m_IsFoundPlayer(false), m_surprisedTime(0.0f), m_scale(Vec3(5.0f, 5.0f, 5.0f)) {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief　デストラクタ
		*/
		virtual ~SurprisedSprite() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　村人が見失ったら
		*/
		void Surprised();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ビルボード処理
		*/
		void Billboard();

		//--------------------------------------------------------------------------------------
		/*!
		@brief　初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*
		@brief　更新
		*/
		virtual void OnUpdate() override;

	};



}
//end basecross