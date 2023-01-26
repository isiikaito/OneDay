/**
*@file WoodenBox.cpp
*@brief 木箱の実装が定義されているソースファイル
*@author kaito isii
*@details 木箱の実体実装
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	constexpr float m_colLimit = 0.2;
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	WoodenBox::WoodenBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	//初期化
	void WoodenBox::OnCreate() {
		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		// モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.08f, 0.08f, 0.08f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(0.0f, -0.5f, 0.0f)  //!位置
		);

		auto ptrShadow = AddComponent<Shadowmap>();       //!影をつける（シャドウマップを描画する）
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto Coll = AddComponent<CollisionObb>();         //!キューブ型の当たり判定の追加
		Coll->SetFixed(true);                             //!ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"BOX_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!メッシュの設定
		ptrDraw->SetMeshResource(L"BOX_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		/*Coll->SetDrawActive(true);*/
		
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<WoodenBox>());

		SetAlphaActive(true);//!SetDiffiuseのカラー変更を適用

	}

	void WoodenBox::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - m_colLimit, m_time - m_colLimit, m_time - m_colLimit, 1.0f)); // !夜にする処理
	}

}