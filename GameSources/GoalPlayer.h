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
		BoneModelDeta m_goalPlayerBoneModelDeta;				//!プレイヤーのモデルデータ

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


	};
}
//end basecross
