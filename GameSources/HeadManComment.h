/*!
@file HeadManComment.h
@author Kaito Isii
@brief 村長の表示
*/

#pragma once
#include "stdafx.h"
namespace basecross
{
	enum class Day
	{
		FirstDay,
		SecondDay,
		ThirdDay,
		ForceDay,
		FiveDay,
		SixDay
	};

	class HeadManComment :public GameObject
	{
	private:
		std::shared_ptr<GameObject> parent; // 親オブジェクト

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		const float m_spritePositionY;	//!コメントの高さ
		const Vec3 m_scale;				//!大きさ
		const Vec2 m_LeftUpperSummit;	//!左上の頂点
		const Vec2 m_LeftLowerSummit;	//!左下の頂点
		const Vec2 m_RightUpperSummit;	//!右上の頂点
		const Vec2 m_RightLowerSummit;	//!右下の頂点
		Col4 m_TextureColor;			//!テクスチャの色


	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		HeadManComment(const std::shared_ptr<Stage>& stage, 
			const std::shared_ptr<GameObject>& parent)
			: GameObject(stage), parent(parent), 
			m_spritePositionY(17.0f), 
			m_scale(Vec3(15.0f)),
			m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
			m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
			m_RightUpperSummit(Vec2(1.0f, 0.0f)),
			m_RightLowerSummit(Vec2(1.0f, 1.0f)),
			m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
		{}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~HeadManComment() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村人がプレイヤーを見失った時の処理
		*/
		void Comment();

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
		/*!
		@brief	更新
		*/
		virtual void OnUpdate() override;

	};
}