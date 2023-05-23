/*!
@file LoseSightOf.cpp
@author Kaito Isii
@brief 敵のプレイヤーを見失ったときのはてなマークの表示
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float helfSize = 0.5f;//!ポリゴンサイズ
	constexpr float MaxLosefSeghtOfTime = 2.0f;//!テクスチャを表示する時間
	void LoseSightOf::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		// 頂点データ
		float HelfSize = helfSize;

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
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"LoseSightOf_TX");			//!テクスチャの設定
		drawComp->SetDepthStencilState(DepthStencilState::None);	// 重ね合わせの問題を解消する
		SetAlphaActive(true);
		SetDrawActive(false);
		auto transComp = GetComponent<Transform>();					// トランスフォーム：変換行列(Transform Matrix)		
		transComp->SetScale(m_scale);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
	}

	void LoseSightOf::Billboard()
	{
		
		auto ptrTransform = GetComponent<Transform>();				//!自身のトランスフォームの取得
		auto& PtrCamera = GetStage()->GetView()->GetTargetCamera();	//!カメラの取得

		Quat Qt;
		//向きをビルボードにする
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		ptrTransform->SetQuaternion(Qt);							//!ビルボード下向きを設定する
		auto EnemyTransform = parent->GetComponent<Transform>();	//!敵のトランスフォームの取得
		auto EnemyPosition=EnemyTransform->GetPosition();			//!敵のポジションの取得
		//!ビルボード処理はオブジェクトの回転まで反映してしまうためポジションを変更する
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);

	}

	
	void LoseSightOf::LoseSight()
	{
		auto GetHunter = std::dynamic_pointer_cast<BaseEnemy>(parent);


		auto loseSightOfTarget = GetHunter->GetloseSightOfTarget();

		//!プレイヤーが見つかったら
		if (loseSightOfTarget == true)
		{
			float Time = App::GetApp()->GetElapsedTime();//!時間の取得
			m_LoseSeghtOfTime += Time;

			SetDrawActive(true);
			//!2秒たったら
			if (m_LoseSeghtOfTime >= MaxLosefSeghtOfTime)
			{
				loseSightOfTarget = false;
				GetHunter->SetloseSightOfTarget(loseSightOfTarget);
			}

		}
		//!巡回に戻る
		if (loseSightOfTarget == false)
		{
			m_LoseSeghtOfTime = 0.0f;	//!見失った時間を0秒にする
			SetDrawActive(false);		//!描画をやめる

		}
	}

	void LoseSightOf::OnUpdate()
	{
		Billboard();
		
		LoseSight();
	}
}