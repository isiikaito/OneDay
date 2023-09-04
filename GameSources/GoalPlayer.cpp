/**
*@file GoalPlayer.cpp
*@brief ゴール時のプレイヤーのソースファイル
*@author  Ayumiu Muroi
*@details ゴール時のプレイヤーの実装
*/

#include "stdafx.h"
#include "Project.h"
#include "GoalPlayer.h"

namespace basecross {

	GoalPlayer::GoalPlayer(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_goalPlayerBoneModelDeta(
			{
				Scale,
				Rotation,
				Position,
				Vec3(0.4f, 0.4f, 0.4f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -1.0f, 0.0f),
				L"EnemyVillager_WalkAnimation_MESH",
				L"EnemyVillager_WalkAnimation_MESH_WITH_TAN",
				L"OBJECT_NORMAL_TX"
			}
		)
	{
	}

	

	//!初期化
	void GoalPlayer::OnCreate()
	{
		AddComponent<BoneModelComponent>(m_goalPlayerBoneModelDeta);//!プレイヤーのモデル作成
	}


}
//end basecros