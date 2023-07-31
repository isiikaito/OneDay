/*!
@file Hunter.cpp
@brief ハンターの実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float EYERANGE = 50.0f;				//!視界の長さ
	constexpr float MAXPLAYERCATCH = 10.0f;			//!プレイヤーを捕まえる距離
	constexpr float dividedNumber = 9.0f;			//!視野の広さを決める
	constexpr int MOVESTARTSAMPLE = 0;				//!動くアニメーションの開始フレーム
	constexpr int MOVESAMPLELENGTH = 30;			//!動くアニメーションの長さ
	constexpr float MOVESAMPLESPARSECOND = 40.0f;	//!動くアニメーションの再生速度
	constexpr int DEDSTARTSAMPLE = 60;				//!倒れるアニメーションの開始フレーム
	constexpr int DEDSAMPLELENGTH = 30;				//!倒れるアニメーションの長さ
	constexpr float DEDSAMPLESPARSECOND = 15.0f;	//!倒れるアニメーションの再生速度



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



	void Hunter::OnCreate()
	{
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);	  //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),	//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 59.7f, 0.0f),//!回転
			Vec3(0.0f, -1.0f, 0.0f) //!位置
		);


		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");								//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Hunter>());															//!グループに自分自身を追加
		SetAlphaActive(true);																			//!SetDiffiuseのカラー変更を適用

		AddComponent<Gravity>();																		//!重力をつける
		auto Coll = AddComponent<CollisionCapsule>();													//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();														//!影をつける（シャドウマップを描画する）
		ptrShadow->SetMeshResource(L"EnemyHunter_Animation_MESH");										//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);													//!見た目と当たり判定
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();											//!描画コンポーネントの設定
		ptrDraw->SetMeshResource(L"EnemyHunter_Animation_MESH_WITH_TAN");								//!描画するメッシュを設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);														//!メッシュの大きさ設定
		ptrDraw->AddAnimation(L"Move", MOVESTARTSAMPLE, MOVESAMPLELENGTH, true, MOVESAMPLESPARSECOND);	//!歩くアニメーションの読み込み
		ptrDraw->AddAnimation(L"Ded", DEDSTARTSAMPLE, DEDSAMPLELENGTH, false, DEDSAMPLESPARSECOND);		//!倒れるアニメーションの追加
		ptrDraw->ChangeCurrentAnimation(L"Move");														//!現在のアニメーションの設定
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");										//!法線マップの設定

		//!巡回ポイントの取得
		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);									//!巡回ポイントの情報を末尾に追加する
		}

		SetpatorolPoints(patrolPoints);
		SetEyeRang(EYERANGE);


	}

	void Hunter::PlayerCatch()
	{

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");		//!プレイヤーの取得
		auto playerPosition = ptrPlayer->GetComponent<Transform>()->GetPosition();	//!プレイヤーのポジションの取得
		auto hunterPosition = GetComponent<Transform>()->GetPosition();				//!ハンターのポジションの取得
		auto phdistans = playerPosition - hunterPosition;							//!ハンターとプレイヤーのベクトルを計算
		auto playerCatch = bsm::length(phdistans);									//!計算したベクトルを距離に変換
		auto Enemyfront = GetComponent<Transform>()->GetForword();					//!敵の正面を取得
		auto angle = angleBetweenNormals(Enemyfront, phdistans);					//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
		auto chk = XM_PI / dividedNumber;											//!360を9で割って角度を出す。

		//!プレイヤーを追っている状態の時
		if (m_seekCondition == true)
		{
			//!敵から見て+40度か-40度にプレイヤーが入ったら
			if (angle <= chk && angle >= -chk)
			{
				//!プレイヤーを捕まえる範囲の中にプレイヤーがいたら
				if (playerCatch <= MAXPLAYERCATCH)
				{
					ptrPlayer->SetIsplayerDed(true);								//!プレイヤーを倒す
				}

			}
		}

	}

	void Hunter::HunterDed()
	{
		auto elapasedime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		auto hunterDed = GetIsEnemyDed();				   //!自分が生きているかどうかの取得

		//!倒れたら
		if (hunterDed == true)
		{

			auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();					//アニメーションの取得
			auto& AnimationName = ptrDraw->GetCurrentAnimation();					//!現在のアニメーションを取得
			auto AnimationEnd = ptrDraw->UpdateAnimation(elapasedime);				//!アニメーションの更新
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
	//!更新
	void Hunter::OnUpdate()
	{
		HunterDed();
		PlayerCatch();
		SetMaxSpeed(m_Speed);
		BaseEnemy::OnUpdate();//!親クラスの情報を利用する		
	}

}
//!end basecross
