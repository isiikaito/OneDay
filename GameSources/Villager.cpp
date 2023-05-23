/*!
@file Villager.cpp
@brief 村人の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float eyeRang = 20.0f;			   //!視野の長さ
	constexpr int m_movestartSample = 0;		   //!動くアニメーションの開始フレーム
	constexpr int m_movesampleLength = 30;		   //!動くアニメーションの長さ
	constexpr float m_movesamplesParSecond = 40.0f;//!動くアニメーションの再生速度
	constexpr int m_dedstartSample = 60;		   //!倒れるアニメーションの開始フレーム
	constexpr int m_dedsampleLength = 30;		   //!倒れるアニメーションの長さ
	constexpr float m_dedsamplesParSecond = 15.0f; //!倒れるアニメーションの再生速度
	
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
		m_Speed(22.0f),
		m_patrolindex(0),
		m_dedDecision(false),
		m_damage(1)
	{
	}

		void Villager::OnCreate()
	{

		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);		//!大きさ
		ptrTrans->SetRotation(m_Rotation);	//!回転
		ptrTrans->SetPosition(m_Position);	//!位置

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),			//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),			//!回転
			Vec3(0.0f, -1.0f, 0.0f)			//!位置
		);

		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");	//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Villager>());									//!グループに自分自身を追加
		AddComponent<Gravity>();												//!重力をつける
		auto Coll = AddComponent<CollisionCapsule>();							//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();								//!影をつける（シャドウマップを描画する）
		ptrShadow->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH");		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);							//!メッシュの大きさを設定する
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();					//!描画コンポーネントの設定
		ptrDraw->SetMeshResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");	//!描画するメッシュを設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);								//!メッシュの大きさを設定する
		ptrDraw->AddAnimation(L"Move", m_movestartSample, m_movesampleLength, true, m_movesamplesParSecond);//!歩くアニメーションの読み込み
		ptrDraw->AddAnimation(L"Ded", m_dedstartSample, m_dedsampleLength, false, m_dedsamplesParSecond);	//!倒れるアニメーションの追加
		ptrDraw->ChangeCurrentAnimation(L"Move");								//!現在のアニメーションの設定
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");				//!法線マップの設定

		//!巡回ポイントの取得
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);										//!巡回ポイントの情報を末尾に追加する
		}

		SetpatorolPoints(patrolPoints);		
		SetEyeRang(eyeRang);

	}
	

	void Villager::VillagerDed()
	{
		auto elapasedime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		auto villagerDed = GetIsEnemyDed();				   //!自分が生きているかどうかの取得
		
		//!倒れたら
		if (villagerDed == true)
		{
			
			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();		//アニメーションの取得
			auto& AnimationName = ptrDraw->GetCurrentAnimation();		//!現在のアニメーションを取得
			auto AnimationEnd = ptrDraw->UpdateAnimation(elapasedime);	//!アニメーションの更新
			//歩くアニメーションの時
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Ded");							//!倒れるアニメーションに変更
				auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
				auto playerHp = ptrPlayer->GetPlayerHp();							//!プレイヤーのHPを取得
				playerHp -= m_damage;												//!プレイヤーのHPを1削る
				ptrPlayer->SetPlayerHp(playerHp);									//!プレイヤーのHPを更新する
			}

			else
			{
				//!アニメーションが終わったら
				if (AnimationEnd)
				{
					SetDedAnimationEnd(true);										//!死体を消す処理
				}
			}
		}
	}

	
	void Villager::OnUpdate()
	{
		VillagerDed();
		SetMaxSpeed(m_Speed);
		SetEyeRang(eyeRang);
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
