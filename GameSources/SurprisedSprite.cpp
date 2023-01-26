/*!
@file SurprisedSprite.cpp
@author Kaito Isii
@brief ビックリマークの表示
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	ビックリマークスプライト
	//--------------------------------------------------------------------------------------

	constexpr float MaxSurprisedTime = 2.0f;
	constexpr float m_maxSurprisedTime = 2.0f;
	constexpr float helfSize = 0.5f;

	void SurprisedSprite::OnCreate()
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
		//drawComp->SetMeshResource(L"DEFAULT_SQUARE");
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"Surprised_TX");
		drawComp->SetDepthStencilState(DepthStencilState::None); // 重ね合わせの問題を解消する
		SetAlphaActive(true);
		SetDrawActive(false);
		auto transComp = GetComponent<Transform>();  // トランスフォーム：変換行列(Transform Matrix)		
		transComp->SetScale(m_scale);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
	}

	void SurprisedSprite::Billboard()
	{

		auto ptrTransform = GetComponent<Transform>();
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

		Quat Qt;
		//向きをビルボードにする
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		ptrTransform->SetQuaternion(Qt);
		auto EnemyTransform = parent->GetComponent<Transform>();
		auto EnemyPosition = EnemyTransform->GetPosition();
		//!ビルボード処理はオブジェクトの回転まで反映してしまうためポジションを変更する
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);

	}


	void SurprisedSprite::Surprised()
	{
		auto GetEnemy = std::dynamic_pointer_cast<BaseEnemy>(parent);


		auto SurprisedTarget = GetEnemy->GetSurprisedSprite();

		//!プレイヤーが見つかったら
		if (SurprisedTarget == true)
		{
			auto Time = App::GetApp()->GetElapsedTime();
			m_surprisedTime += Time;
			if (m_surprisedTime >= m_maxSurprisedTime)
			{
				GetEnemy->SetSurprisedSprite(false);
			}
		
			SetDrawActive(true);
		}

		else
		{
			m_surprisedTime = 0.0f;
			SetDrawActive(false);
		}
		

		

	}

	void SurprisedSprite::OnUpdate()
	{
		Billboard();
		Surprised();
	}
}
