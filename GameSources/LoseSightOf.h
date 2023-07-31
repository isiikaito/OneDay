/*!
@file LoseSightOf.h
@author Kaito Isii
@brief 敵のプレイヤーを見失ったときのはてなマークの表示
*/

#pragma once
#include "stdafx.h"
namespace basecross
{
	
	class LoseSightOf :public GameObject
	{
	private:
		std::shared_ptr<GameObject> parent;		//!親オブジェクト
		float m_LoseSeghtOfTime;				//!見ている時間
		const float m_spritePositionY;			//!ポジション
		Vec3 m_scale;							//!テクスチャの大きさ
		const Vec2 m_LeftUpperSummit;			//!左上の頂点
		const Vec2 m_LeftLowerSummit;			//!左下の頂点
		const Vec2 m_RightUpperSummit;			//!右上の頂点
		const Vec2 m_RightLowerSummit;			//!右下の頂点
		Col4 m_TextureColor;					//!テクスチャの色
		float m_tempLength;						//!臨時の長さ
		Vec3 m_defUp;							//!通常


		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;				//!テクスチャとカメラ間のベクトル
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
		LoseSightOf(const std::shared_ptr<Stage>& stage,
			const std::shared_ptr<GameObject>& parent)
		: GameObject(stage), parent(parent),
			m_LoseSeghtOfTime(0.0f), 
			m_spritePositionY(8.0f), 
			m_scale(Vec3(5.0f)),
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
		virtual ~LoseSightOf(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村人がプレイヤーを見失ったら
		*/
		void LoseSight();
	
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