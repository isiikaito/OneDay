/*!
@file HungerGage.h
@author isii kaito
@brief ゲージの背景の表示
*/

#pragma once
#include "stdafx.h"

namespace basecross {

		enum class EatCondition {
		notEat,
		firstEat,
		secondEat,
		thirdEat
	};
	class HungerGage : public GameUI {
	private:
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		Vec3 m_firstEatScale; //!ゲージが一個溜まったとき
		Vec3 m_firstEatPos;   //!ゲージが一個溜まったとき
		Vec3 m_secondEatScale;//!ゲージが二個溜まったとき
		Vec3 m_secondEatPos;  //!ゲージが二個溜まったとき
		Vec3 m_thirdEatScale; //!満タンの時
		Vec3 m_thirdEatPos;   //!満タンの時


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		HungerGage(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~HungerGage() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲージの変更
		*/
		void ChangeGage();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate()override;

	};
}
//end basecross

