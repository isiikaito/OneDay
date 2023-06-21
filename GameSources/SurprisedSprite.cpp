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

	constexpr float m_maxSurprisedTime = 2.0f;//!テクスチャを表示している時間
	constexpr float helfSize = 0.5f;//!ポリゴンサイズ

	void SurprisedSprite::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		// 頂点データ
		float HelfSize = helfSize;

		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0),m_TextureColor, m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), m_TextureColor,m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),m_TextureColor,m_RightLowerSummit) },
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
		auto drawComp = AddComponent<PCTStaticDraw>();				//!描画コンポーネントの取得
		drawComp->CreateOriginalMesh(vertices, indices);			//!メッシュの生成
		drawComp->SetOriginalMeshUse(true);							//!オリジナルメッシュを使う
		drawComp->SetTextureResource(L"Surprised_TX");				//!テクスチャの設定
		drawComp->SetDepthStencilState(DepthStencilState::None);	//!重ね合わせの問題を解消する
		SetAlphaActive(true);										//!透明処理
		SetDrawActive(false);										//!非表示
		auto transComp = GetComponent<Transform>();					//!トランスフォーム：変換行列(Transform Matrix)		
		transComp->SetScale(m_scale);								//!大きさの設定
		auto EnemyTransform = parent->GetComponent<Transform>();	//!敵のトランスフォームの取得
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());	//!自分の回転に敵の回転を取得
	}

	void SurprisedSprite::Billboard()
	{

		auto ptrTransform = GetComponent<Transform>();				//!トランスフォームの取得
		auto& PtrCamera = GetStage()->GetView()->GetTargetCamera();	//!カメラの取得
		Quat Qt;
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());	//向きをビルボードにする
		ptrTransform->SetQuaternion(Qt);							//!自分の回転を設定
		auto EnemyTransform = parent->GetComponent<Transform>();	//!敵のトランスフォームの取得
		auto EnemyPosition = EnemyTransform->GetPosition();			//!敵の位置の取得
		//!ビルボード処理はオブジェクトの回転まで反映してしまうためポジションを変更する
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);
	}


	void SurprisedSprite::Surprised()
	{
		auto GetEnemy = std::dynamic_pointer_cast<BaseEnemy>(parent);	//!ペアレントの敵の取得
		auto SurprisedTarget = GetEnemy->GetSurprisedSprite();			//!スプライトの取得
		//!プレイヤーが見つかったら
		if (SurprisedTarget == true)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();			//!エルパソタイムの取得
			m_surprisedTime += elapsedTime;								//!時間の更新
			//!表示時間を過ぎたら
			if (m_surprisedTime >= m_maxSurprisedTime)
			{
				GetEnemy->SetSurprisedSprite(false);					//!非表示を消す
			}
		
			SetDrawActive(true);//!表示する
		}

		else
		{
			m_surprisedTime = 0.0f;	//!時間のリセット
			SetDrawActive(false);	//!表示しない
		}
	}

	void SurprisedSprite::OnUpdate()
	{
		Billboard();
		Surprised();
	}
}
