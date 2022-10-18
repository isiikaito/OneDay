/*!
@file Hunter.cpp
@brief ハンターの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
  Hunter::Hunter(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
		
  {}

  Hunter::~Hunter(){}
  //!初期化
  void Hunter::OnCreate() {
	  //初期位置などの設定
	  auto ptrTrans = GetComponent<Transform>();
	  ptrTrans->SetScale(1.0f, 1.4f, 1.4f);
	  ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
	  ptrTrans->SetPosition(0.0f,5.0f,0.0f);
	 

	  //CollisionSphere衝突判定を付ける
	  auto Coll = AddComponent<CollisionObb>();

	  Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
	  spanMat.affineTransformation(
		  Vec3(0.35f, 0.2f, 0.4f),//!大きさ
		  Vec3(0.0f, 0.0f, 0.0f),
		  Vec3(0.0f, 0.0f, 0.0f),   //!回転
		  Vec3(0.0f, -0.5f, -0.05f)  //!位置
	  );
	  //重力をつける
	  AddComponent<Gravity>();

	  //影をつける（シャドウマップを描画する）
	  auto ptrShadow = AddComponent<Shadowmap>();

	  //影の形（メッシュ）を設定
	  ptrShadow->SetMeshResource(L"HUNTER_MESH");
	  ptrShadow->SetMeshToTransformMatrix(spanMat);

	  //描画コンポーネントの設定
	  auto ptrDraw = AddComponent<PNTStaticModelDraw>();               //!描画コンポーネント


	  //!メッシュの設定
	  ptrDraw->SetMeshResource(L"HUNTER_MESH");
	  ptrDraw->SetMeshToTransformMatrix(spanMat);
	  Coll->SetDrawActive(true);
  }

}
//!end basecross
