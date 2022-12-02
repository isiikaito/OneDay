/*!
@file LoseSightOf.cpp
@author Kaito Isii
@brief 敵のプレイヤーを見失ったときのはてなマークの表示
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void LoseSightOf::OnCreate()
	{

		auto PtrTransform = GetComponent<Transform>();
		// 頂点データ
		float HelfSize = 0.5f;

		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		// 頂点インデックス（頂点をつなぐ順番）
		std::vector<uint16_t> indices = {
			// つなげる順番が「右回り(時計回り)」だと表面になる
			0, 1, 2, // 左上の三角ポリゴン
			2, 1, 3  // 右下の三角ポリゴン
		};

		// Position : 頂点座標
		// Normal : 法線ベクトル（頂点の向き、ポリゴンの向き → 光の反射の計算に使う）
		// Color : 頂点色
		// Texture : テクスチャ座標(UV座標)
		auto drawComp = AddComponent<PCTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_SQUARE");
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"LoseSightOf_TX");
		/*drawComp->SetDiffuse(Col4(1, 1, 1, 0.5f));*/ // 拡散反射（アルファ成分は透過処理に使われる）
		//drawComp->SetEmissive(color); // 自己発光
		drawComp->SetDepthStencilState(DepthStencilState::None); // 重ね合わせの問題を解消する
		SetAlphaActive(true);
		SetDrawActive(false);
		auto transComp = GetComponent<Transform>();  // トランスフォーム：変換行列(Transform Matrix)
		transComp->SetParent(parent); // 親オブジェクトを指定する
		transComp->SetPosition(0.0f, 5.0f, 0.0f);
		transComp->SetScale(10, 10, 10);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
	}

	void LoseSightOf::Billboard()
	{
		auto ptrTransform = GetComponent<Transform>();
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

		Quat Qt;
		//向きをビルボードにする
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		ptrTransform->SetQuaternion(Qt);

	}

	void LoseSightOf::LoseSight()
	{
		
	}

	void LoseSightOf::OnUpdate()
	{
		Billboard();
		//std::dynamic_pointer_cast<BaseEnemy>();
		//auto group =GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		//auto vecEnemy = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		////!ハンター配列オブジェクトの配列分回す
		//for (auto& v : vecEnemy) {
		//	auto HunterPtr = v.lock();//!ハンターのグループから1つロックする
		//	auto loseSightOfTarget = dynamic_pointer_cast<Hunter>(HunterPtr);

		//	auto loseSightOfTarget=loseSightOfTarget->GetloseSightOfTarget();

		//	//!プレイヤーが見つかったら
		//	if (loseSightOfTarget == true)
		//	{
		//		float Time = App::GetApp()->GetElapsedTime();//!時間の取得
		//		m_LoseSeghtOfTime += Time;

		//		auto PtrDraw = GetComponent<PCTSpriteDraw>();//!描画コンポーネント
		//		SetDrawActive(true);
		//		//!2秒たったら
		//		if (loseSightOfTarget >= 2)
		//		{

		//			loseSightOfTarget = false;//!発見をやめる
		//			SetloseSightOfTarget(loseSightOfTarget);
		//		}

		//	}
		//}
		//////!見つけることをやめたら
		////if (loseSightOfTarget == false)
		////{
		////	m_LoseSeghtOfTime = 0.0f;//!驚く時間を0秒にする
		////	SetDrawActive(false);//!描画をやめる

		////}
		///*LoseSight();*/
	}
}