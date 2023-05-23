/*!
@file Meat.cpp
@brief 肉の実体
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "Meat.h"


namespace basecross {
	Meat::Meat(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Time(0.0f)

	{
	}

	void Meat::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.15f),	//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),		//!回転
			Vec3(0.0f, -0.5f, 0.0f)		//!位置
		);


		auto ptrShadow = AddComponent<Shadowmap>();						//!影をつける（シャドウマップを描画する）
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();				//!描画コンポーネント
		auto Coll = AddComponent<CollisionObb>();						//!キューブ型の当たり判定の追加
		ptrShadow->SetMeshResource(L"MEAT_MESH");						//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);					//!メッシュの大きさ設定
		ptrDraw->SetMeshResource(L"MEAT_MESH");							//!メッシュの設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);						//!メッシュの大きさ設定
		auto group = GetStage()->GetSharedObjectGroup(L"Meat_ObjGroup");//!自身のグループを作成
		group->IntoGroup(GetThis<Meat>());								//グループに自分自身を追加

	}
	void Meat::OnUpdate()
	{
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();	//!描画コンポーネント
		auto ptrTrans = GetComponent<Transform>();			//!自身のトランスフォームの取得
		auto& app = App::GetApp();							//!アプリの取得
		auto time = app->GetElapsedTime();					//!エルパソタイムの取得
		m_Time += time;										//!y軸回転にエルパソタイムを加算する
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.15f),						//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, m_Time, 0.0f),						//!回転
			Vec3(0.0f, -0.5f, 0.0f)							//!位置
		);
		ptrDraw->SetMeshToTransformMatrix(spanMat);			//!メッシュの大きさ設定


	}
}
//end basecross