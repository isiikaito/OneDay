/*!
@file Villager.cpp
@brief 村人の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross
{
	constexpr float EYERANGE = 20.0f;				//!視野の長さ
	
	Villager::Villager(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const std::vector<Vec3>& patrolPoints
	) :

		BaseEnemy(StagePtr),
		m_patrolPoints(patrolPoints),
		m_playerChange(0),
		m_Speed(22.0f),
		m_patrolindex(0),
		m_dedDecision(false),
		m_damage(1),
		m_enemyBoneModelDeta(
			{
			Scale ,
			Rotation,
			Position,
			Vec3(0.4f, 0.4f, 0.4f),			
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),			
			Vec3(0.0f, -1.0f, 0.0f),		
			L"EnemyVillager_WalkAnimation_MESH",
			L"EnemyVillager_WalkAnimation_MESH_WITH_TAN",
			L"OBJECT_NORMAL_TX"
			})
	{
	}

		void Villager::OnCreate()
	{
		AddComponent<BoneModelComponent>(m_enemyBoneModelDeta);
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");	//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Villager>());									//!グループに自分自身を追加
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();					//!描画コンポーネントの設定
		AddComponent<AnimationComponent>(L"Villager", L"Move");									//!アニメーションの読み込み

		//!巡回ポイントの取得
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);										//!巡回ポイントの情報を末尾に追加する
		}

		SetpatorolPoints(patrolPoints);		
		SetEyeRang(EYERANGE);

	}
	


	
	void Villager::OnUpdate()
	{
		SetMaxSpeed(m_Speed);
		SetEyeRang(EYERANGE);
		BaseEnemy::OnUpdate();
	}

	//!村人がプレイヤーを捕まえたら
	void Villager::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		//!自分が生きているかどうかの取得
		auto villagerDed = GetIsEnemyDed();
		//!生きていたら
		if (villagerDed == false)
		{
			auto ptrPlayer = dynamic_pointer_cast<Player>(Other);//!プレイヤーの取得
			auto seekCondition = GetseekCondition();			 //!追いかけているかどう
			//!プレイヤーに当たっている
			if (ptrPlayer)
			{
				//!追いかけているとき
				if (seekCondition == true)
				{
					auto playerDed = ptrPlayer->GetIsplayerDed();//!プレイヤーが倒れているかどうか
					playerDed = true;							 //!プレイヤーを倒す
					ptrPlayer->SetIsplayerDed(playerDed);		 //!プレイヤーを倒した状態に設定する

				}
			}
		}
	}
}
//!end basecross
