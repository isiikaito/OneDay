/**
*@file StageFloor.cpp
*@brief ゲームステージの床の実装が定義されているソースファイル
*@author Ayumu Muroi
*@details ゲームステージの床の実体実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float DrawTime = 31.0f;
	constexpr float m_colLimit = 0.2;

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr,
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
	void StageFloor::OnCreate() {
		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		// モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.04f, 1.0f, 0.04f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(0.0f, 0.5f, -0.003f)  //!位置
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!影をつける（シャドウマップを描画する）
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto Coll = AddComponent<CollisionObb>();         //!キューブ型の当たり判定の追加
		Coll->SetFixed(true);                             //!ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"GROUND_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		ptrDraw->SetOwnShadowActive(true); // 影の映りこみを有効にする

		//!メッシュの設定
		ptrDraw->SetMeshResource(L"GROUND_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
	
	}

	void StageFloor::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - m_colLimit, m_time - m_colLimit, m_time - m_colLimit, 1.0f)); // !夜にする処理
	}

}