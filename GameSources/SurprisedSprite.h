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
		float m_surprisedTime;				//!表示時間
		Vec3 m_scale;						//!大きさ
		float m_SurprisedTime;				//!板ポリを表示する時間
		const float m_spritePositionY;		//!板ポリのY軸のポジション
		bool m_IsFoundPlayer;				//!プレイヤーを発見したとき
		const Vec2 m_LeftUpperSummit;		//!左上の頂点
		const Vec2 m_LeftLowerSummit;		//!左下の頂点
		const Vec2 m_RightUpperSummit;		//!右上の頂点
		const Vec2 m_RightLowerSummit;		//!右下の頂点
		Col4 m_TextureColor;				//!テクスチャの色
		float m_tempLength;					//!臨時の長さ
		Vec3 m_defUp;						//!通常

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < m_tempLength) {
				DefUp = m_defUp;
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		SurprisedSprite(const std::shared_ptr<Stage>& stage,
			const std::shared_ptr<GameObject>& parent)
			: GameObject(stage), 
			parent(parent), 
			m_SurprisedTime(0.0f),
			m_spritePositionY(8.0f),
			m_IsFoundPlayer(false),
			m_surprisedTime(0.0f), 
			m_scale(Vec3(5.0f, 5.0f, 5.0f)),
			m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
			m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
			m_RightUpperSummit(Vec2(1.0f, 0.0f)),
			m_RightLowerSummit(Vec2(1.0f, 1.0f)),
			m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
			m_tempLength(0.1f),
			m_defUp(Vec3(0, 0, 1.0f))
		
		{}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~SurprisedSprite() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村人が見失ったら
		*/
		void Surprised();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビルボード処理
		*/
		void Billboard();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*
		@brief	更新
		*/
		virtual void OnUpdate() override;

	};



}
//end basecross