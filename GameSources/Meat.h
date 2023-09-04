/*!
@file Meat.h
@brief 肉の作成
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Meat : public GameObject {
	private:
		float m_Time;	 //!y軸回転
		StaticModelDeta m_meatModelData;			//!肉のモデルデータ

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		Meat(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~Meat() {}

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
