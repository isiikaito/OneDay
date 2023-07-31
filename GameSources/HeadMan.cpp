/*!
@file HeadMan.cpp
@brief 村長の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
namespace basecross
{
	constexpr float SAMPLESPARSECOND = 10.0f;//!アニメーションの再生速度
	constexpr int STARTSAMPLE = 31;		   //!アニメーションの開始フレーム
	constexpr int SAMPLELENGTH = 30;		   //!アニメーションの長さ
	constexpr float HEADMANSP = 30.0f;       //!当たり判定を作るスフィアの半径
	
		

	HeadMan::HeadMan(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :

		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_IsheadManCommentOn(false)
	{
	}

	void HeadMan::OnCreate()
	{
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);	  //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		Mat4x4 spanMat;                // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),    //!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),    //!回転
			Vec3(0.0f, -1.0f, 0.0f)    //!位置
		);

		AddComponent<Gravity>();											                       //!重力をつける
		auto Coll = AddComponent<CollisionCapsule>();						                       //!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();							                       //!影をつける（シャドウマップを描画する）
		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");	                       //!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);						                       //!メッシュを当たり判定と合わせる
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();				                       //!描画コンポーネントの設定
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");                    //!描画するメッシュを設定
		ptrDraw->AddAnimation(L"Default", STARTSAMPLE, SAMPLELENGTH, true, SAMPLESPARSECOND);//!アニメーションの取得
		ptrDraw->ChangeCurrentAnimation(L"Default");						                       //!現在のアニメーションの設定
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");			                       //!法線マップの設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);												   //!メッシュの大きさの設定
	}

	void HeadMan::HeadManComment()
	{
		auto position = GetComponent<Transform>()->GetPosition();				  //!現在のプレイヤーの位置の取得
		SPHERE headManSp(position, HEADMANSP);								  //!プレイヤーの座標を中心に半径30センチの円の作成
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");		  //!プレイヤーの取得
		Vec3 ret;																  //!最近接点
		auto playerCapsrul=player->GetComponent<CollisionCapsule>()->GetCapsule();//!プレイヤーのカプセルオブジェクトを取得
				if (HitTest::SPHERE_CAPSULE(headManSp, playerCapsrul, ret))		  //!プレイヤーの周りを囲んでいるスフィアに当たったら
				{
					m_IsheadManCommentOn = true;								  //!村長が話している
				}
				else
				{
					m_IsheadManCommentOn = false;								  //!村長が話してない
				}
	}

	void HeadMan::HeadManAnimation()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//アニメーション
		ptrDraw->UpdateAnimation(elapsedTime);				//!アニメーションの更新
	}

	void HeadMan::OnUpdate()
	{
		HeadManAnimation();
		HeadManComment();
	}
}