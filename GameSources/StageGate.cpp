/**
*@file StageGate.cpp
*@brief ゲームステージの門の実装が定義されているソースファイル
*@author Ayumu Muroi
*@details ゲームステージの門の実体実装
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	constexpr float COLLIMIT = 0.2;	//!カラーの変更値
	constexpr float TRANCE = 1.0f;		//!透明度
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	StageGate::StageGate(const shared_ptr<Stage>& StagePtr,
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
	void StageGate::OnCreate() {
		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		// モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.3f, 0.1f, 0.09f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(-0.1f, -0.5f, 0.0f)  //!位置
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!影をつける（シャドウマップを描画する）
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネント

		auto scene = App::GetApp()->GetScene<Scene>();
		auto goleGateParameter = scene->GetGoleGateParameter();

		if (!goleGateParameter)
		{
			auto Coll = AddComponent<CollisionObb>();         //!キューブ型の当たり判定の追加
			//Coll->SetDrawActive(true);
			Coll->SetFixed(true);
		}

		if (goleGateParameter)
		{


		}



		////!メッシュの設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBoxの追加
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		ptrShadow->SetMeshResource(L"GateAnimation_MESH");//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"GateAnimation_MESH_WITH_TAN");
		ptrDraw->AddAnimation(L"Open", 0, 60, false, 20.0f);
		ptrDraw->AddAnimation(L"defoult", 0, 1, false, 20.0f);//!開かないアニメーション
	}
	void StageGate::AnimationChange()
	{
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得

		auto goleGateParameter = scene->GetGoleGateParameter();//!門のパラメータの取得
		//!門がゴールステージにある場合
		if (goleGateParameter)
		{
			auto drowComponet = GetComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネントの取得

			auto& AnimationName = drowComponet->GetCurrentAnimation();//!現在のアニメーションの取得
			//!アニメーションがデフォルトの時
			if (AnimationName == L"defoult")
			{
				//!開くアニメーションに変える
				drowComponet->ChangeCurrentAnimation(L"Open");

			}
		}

		else
		{
			auto drowComponet = GetComponent<BcPNTnTBoneModelDraw>();

			auto& AnimationName = drowComponet->GetCurrentAnimation();
			if (AnimationName == L"Open")
			{
				drowComponet->ChangeCurrentAnimation(L"defoult");//!ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）
				;
			}
		}
	}

	void StageGate::OnUpdate() {
		auto AnimaptrDraw = GetComponent<BcPNTnTBoneModelDraw>();	//!アニメーション
		auto scene = App::GetApp()->GetScene<Scene>();				//!シーンの取得
		auto m_time = scene->GetEmissiveChangeTime();

		AnimaptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !夜にする処理

		float elapsedTime = App::GetApp()->GetElapsedTime();

		AnimationChange();

		  AnimaptrDraw->UpdateAnimation(elapsedTime);

	}

}