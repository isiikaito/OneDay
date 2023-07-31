/*!
@file HeadManComment.cpp
@author Kaito Isii
@brief 村長のコメントの表示
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadManComment.h"
#include "HeadMan.h"

namespace basecross
{
	constexpr float HELFSIZE = 0.5f;//!ポリゴンサイズ


	void HeadManComment::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		// 頂点データ
		

		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HELFSIZE, HELFSIZE, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HELFSIZE, HELFSIZE, 0), m_TextureColor,m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HELFSIZE, -HELFSIZE, 0), m_TextureColor, m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HELFSIZE, -HELFSIZE, 0), m_TextureColor, m_RightLowerSummit) },
		};

		// 頂点インデックス（頂点をつなぐ順番）
		std::vector<uint16_t> indices = {
			// つなげる順番が「右回り(時計回り)」だと表面になる
			0, 1, 2, // 左上の三角ポリゴン
			2, 1, 3  // 右下の三角ポリゴン
		};

		
		auto drawComp = AddComponent<PCTStaticDraw>();					//!描画コンポーネントの取得
		drawComp->CreateOriginalMesh(vertices, indices);				//!メッシュの生成
		drawComp->SetOriginalMeshUse(true);								//!メッシュの適用
		drawComp->SetTextureResource(L"HeadManCommet1_TX");				//!使うテクスチャの読み込み
		drawComp->SetDepthStencilState(DepthStencilState::None);		//!重ね合わせの問題を解消する
		SetAlphaActive(true);											//!透明処理をする
		auto transComp = GetComponent<Transform>();						//!トランスフォーム：変換行列(Transform Matrix)		
		transComp->SetScale(m_scale);									//!大きさの設定
		auto EnemyTransform = parent->GetComponent<Transform>();		//!トランスフォームの取得
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());		//!敵の開店に合わせる
		SetDrawActive(false);											//!表示しない

	}

	void HeadManComment::Billboard()
	{

		auto ptrTransform = GetComponent<Transform>();					//!トランスフォームの取得
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();		//!カメラの取得
		Quat Qt;
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());		//!向きをビルボードにする
		ptrTransform->SetQuaternion(Qt);								//!回転の設定
		auto EnemyTransform = parent->GetComponent<Transform>();		//!トランスフォームの取得
		auto EnemyPosition = EnemyTransform->GetPosition();				//!敵の位置の取得
		//!ビルボード処理はオブジェクトの回転まで反映してしまうためポジションを変更する
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);

	}


	void HeadManComment::Comment()
	{
		auto headMan=GetStage()->GetSharedGameObject<HeadMan>(L"HeadMan");	//!村長の取得
		auto CommentOn=headMan->GetHeadManComment();						//!コメントを出すかどうか

		//!コメントを出す時
		if (CommentOn == true)
		{
			SetDrawActive(true);//!表示する
		}
		else
		{
			SetDrawActive(false);//!表示しない

		}

		
		auto drawComp = AddComponent<PCTStaticDraw>();	//!描画コンポーネント
		auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
		auto date = scene->GetDate();					//!日付の取得

		//!日にちごとのコメント
		switch (date)
		{
		case(static_cast<int>(Day::FirstDay)):
			drawComp->SetTextureResource(L"HeadManCommet1_TX");
				break;
		case(static_cast<int>(Day::SecondDay)):
			drawComp->SetTextureResource(L"HeadManCommet1_TX");
			break;
		case(static_cast<int>(Day::ThirdDay)):
			drawComp->SetTextureResource(L"HeadManCommet1_TX");
			break;
		case(static_cast<int>(Day::ForceDay)):
			drawComp->SetTextureResource(L"HeadManCommet2_TX");
			break;
		case(static_cast<int>(Day::FiveDay)):
			drawComp->SetTextureResource(L"HeadManCommet2_TX");
			break;
		case(static_cast<int>(Day::SixDay)):
			drawComp->SetTextureResource(L"HeadManCommet3_TX");
			break;
		}
	}

	void HeadManComment::OnUpdate()
	{
		Billboard();
		Comment();
	}
}