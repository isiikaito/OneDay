/*!
@file Villager.cpp
@brief 村人の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	
	Villager::Villager(const shared_ptr<Stage>& StagePtr,
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
		m_Speed(22),
		m_patrolindex(0),
		m_dedDecision(false),
		m_IsGameOver(false),
		m_lostTime(0.0f),
		m_damage(-1)

	{
	}

	//!デストラクタ
	Villager::~Villager() {}



	//!初期化
	void Villager::OnCreate()
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
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(0.0f, -1.0f, 0.0f)  //!位置
		);

		AddTag(L"Villager_ObjGroup");//!オブジェクトタグの作成
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Villager>());//!グループに自分自身を追加
		SetAlphaActive(true);//!SetDiffiuseのカラー変更を適用

		AddComponent<Gravity>(); //!重力をつける
		auto Coll = AddComponent<CollisionCapsule>();//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();  //!影をつける（シャドウマップを描画する）

		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネントの設定
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->AddAnimation(L"Ded", 60, 30, false, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Move");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		Coll->SetDrawActive(false);

		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);
		}

		SetpatorolPoints(patrolPoints);
		/*for (int i = 0; i < m_patrolPoints.size(); i++)
		{
			GetStage()->AddGameObject<StageBuilding>(Vec3(1, 10, 1), Vec3(0, 0, 0), m_patrolPoints[i]);
		}*/
		SetEyeRang(50.0f);

	}
	

	void Villager::VillagerDed()
	{
		auto villagerDed = GetIsEnemyDed();
		if (villagerDed == true)
		{
			//アニメーション
			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
			auto AnimationName = ptrDraw->GetCurrentAnimation();
			//立ち止まるアニメーション
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Ded");
				auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
				auto playerHp = ptrPlayer->GetPlayerHp();
				playerHp+= m_damage;
				ptrPlayer->SetPlayerHp(playerHp);
			}
		}
	}

	//!更新
	void Villager::OnUpdate()
	{
		

		if (m_IsGameOver == true)
		{
			auto& app = App::GetApp();//!アプリの取得
			auto time = app->GetElapsedTime();
			m_lostTime += time;
			if (m_lostTime >= 1.0f)
			{
				PostEvent(0.0f, GetThis<Villager>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
		
		VillagerDed();

		auto MaxSpeed = GetMaxSpeed();
		MaxSpeed = m_Speed;
		SetMaxSpeed(MaxSpeed);
		SetEyeRang(20.0f);
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
		m_playerChange = ptrPlayer->GetPlayerCange();//!プレイヤーの状態の取得
		ptrPlayer->SetPlayerChange(m_playerChange);//!プレイヤーの取得した状態の設定
		BaseEnemy::OnUpdate();
	}

	//!村人がプレイヤーを捕まえたら
	void Villager::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		auto seekCondition = GetseekCondition();
		if (ptrPlayer)
		{
			if (seekCondition == true)
			{
				
					auto playerDed = ptrPlayer->GetIsplayerDed();

					playerDed = true;
					ptrPlayer->SetIsplayerDed(playerDed);

					ptrPlayer->SetSpeed(0.0f);

					
					ptrPlayer->SetSpeed(0.0f);
					GetStage()->AddGameObject<FadeOut>(true,
						Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
					
					
					m_IsGameOver = true;
					

				
			}
		}
	}
}
//!end basecross
