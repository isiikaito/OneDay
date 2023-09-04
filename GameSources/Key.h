/*!
@file Key.h
@brief カギに関する処理
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Key : public GameObject {
	private:
		float m_RotationSpeed;	//!回転する速度 
		StaticModelDeta m_keyModelData;			//!カギのモデルデータ

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		Key(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~Key() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化処理
		*/
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		*/
		virtual void OnUpdate()override;

		
	};
}

//end basecross
