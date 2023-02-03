/**
*@file GoalPlayer.h
*@brief ゴール時のプレイヤーのヘッダファイル
*@author Ayumu Muroi
*@details ゴール時のプレイヤーの実装
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゴールプレイヤークラス
	//--------------------------------------------------------------------------------------
	class GoalPlayer : public GameObject {
	private:
		Vec3 m_Position; //!位置
		Vec3 m_Rotation; //!回転
		Vec3 m_Scale; //!大きさ

	public:

		//構築と破棄
		GoalPlayer(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~GoalPlayer() {}
		//初期化
		void OnCreate()override;

		//void OnDestroy();

		//更新
		void OnUpdate()override;
	};
}
//end basecross
