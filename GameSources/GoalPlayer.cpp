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
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		GameObject(StagePtr)
	{
	}

	

	//!初期化
	void GoalPlayer::OnCreate()
	{
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);		//!大きさ
		ptrTrans->SetRotation(m_Rotation);	//!回転
		ptrTrans->SetPosition(m_Position);	//!位置

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),  //!回転
			Vec3(0.0f, -1.0f, 0.0f)  //!位置
		);

		AddComponent<Gravity>(); //!重力をつける
		auto Coll = AddComponent<CollisionCapsule>();					//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();						//!影をつける（シャドウマップを描画する）
		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);					//影のマトリックス
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();			//!描画コンポーネントの設定
		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");//タンジェント付きメッシュの設定
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");				//!法線マップ


	}

	//!更新
	void GoalPlayer::OnUpdate()
	{
	}

}
//end basecros