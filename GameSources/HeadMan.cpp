/*!
@file HeadMan.cpp
@brief 村長の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "AnimationComponent.h"

namespace basecross
{
	constexpr float HEADMANSP = 30.0f;			//!当たり判定を作るスフィアの半径
	
		

	HeadMan::HeadMan(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :

		GameObject(StagePtr),
		m_IsheadManCommentOn(false),
		m_headManBoneModelDeta(
			{
				Scale,
				Rotation,
				Position,
				Vec3(0.4f, 0.4f, 0.4f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -1.0f, 0.0f),
				L"EnemyVillager_WalkAnimation_MESH",
				L"EnemyVillager_WalkAnimation_MESH_WITH_TAN",
				L"OBJECT_NORMAL_TX"
			}
		)
	{
	}

	void HeadMan::OnCreate()
	{

		AddComponent<BoneModelComponent>(m_headManBoneModelDeta);										//!プレイヤーのモデル作成
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();				                       //!描画コンポーネントの設定
		AddComponent<AnimationComponent>(L"HeadMan", L"Default");									//!アニメーションの読み込み

	}

	void HeadMan::HeadManComment()
	{
		auto position = GetComponent<Transform>()->GetPosition();				  //!現在のプレイヤーの位置の取得
		SPHERE headManSp(position, HEADMANSP);									  //!プレイヤーの座標を中心に半径30センチの円の作成
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