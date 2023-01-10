/*!
@file Villager.cpp
@brief 村人の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float eyeRang = 50.0f;
	constexpr float maxPlayerCatch = 10.0f;
	constexpr float m_maxdedTime = 1.0f;
	constexpr float dividedNumber = 9.0f;
	Hunter::Hunter(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const std::vector<Vec3>& patrolPoints
	) :

		BaseEnemy(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_patrolPoints(patrolPoints),
		m_StateChangeSize(30.0f),
		m_playerChange(0),
		m_Speed(22.0f),
		m_patrolindex(0),
		m_IsGameOver(false),
		m_dedTime(0),
		m_playerDed(false),
		m_damage(1)

	{
	}

	//!デストラクタ
	Hunter::~Hunter() {}



	//!初期化
	void Hunter::OnCreate()
	{
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);//!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 59.7f, 0.0f),   //!回転
			Vec3(0.0f, -1.0f, 0.0f)  //!位置
		);


		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Hunter>());//!グループに自分自身を追加
		SetAlphaActive(true);//!SetDiffiuseのカラー変更を適用

		AddComponent<Gravity>(); //!重力をつける
		auto Coll = AddComponent<CollisionCapsule>();//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();  //!影をつける（シャドウマップを描画する）

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"EnemyHunter_Animation_MESH");//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネントの設定
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"EnemyHunter_Animation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->AddAnimation(L"Ded", 60, 30, false, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Move");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");

	
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);
		}

		SetpatorolPoints(patrolPoints);
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));

		SetEyeRang(eyeRang);


	}

	void Hunter::PlayerCatch()
	{

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
		auto playerPosition = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto hunterPosition = GetComponent<Transform>()->GetPosition();
		auto phdistans = playerPosition - hunterPosition;
		auto playerCatch = bsm::length(phdistans);
		auto Enemyfront = GetComponent<Transform>()->GetForword();//!敵の正面を取得
		auto angle = angleBetweenNormals(Enemyfront, phdistans);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
		auto chk = XM_PI / dividedNumber;//!360を6で割って角度を出す。

		if (m_seekCondition == true)
		{

			if (angle <= chk && angle >= -chk)//!敵から見て+40度か-40度にプレイヤーが入ったら
			{
				if (playerCatch <= maxPlayerCatch)
				{

					auto playerDed = ptrPlayer->GetIsplayerDed();
					playerDed = true;
					ptrPlayer->SetIsplayerDed(playerDed);


				}

			}
		}

	}

	void Hunter::HunterDed()
	{
		auto hunterDed = GetIsEnemyDed();
		if (hunterDed == true)
		{
			//アニメーション
			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
			auto& AnimationName = ptrDraw->GetCurrentAnimation();
			//立ち止まるアニメーション
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Ded");
				auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
				auto playerHp = ptrPlayer->GetPlayerHp();
				playerHp += m_damage;
				ptrPlayer->SetPlayerHp(playerHp);
			}
		}
	}
	//!更新
	void Hunter::OnUpdate()
	{
		HunterDed();
		PlayerCatch();

		auto MaxSpeed = GetMaxSpeed();
		MaxSpeed = m_Speed;
		SetMaxSpeed(MaxSpeed);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
		BaseEnemy::OnUpdate();

	
		
	}

	
}
//!end basecross
