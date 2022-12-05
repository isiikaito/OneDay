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
		m_Speed(25),
		m_patrolindex(0),
	    m_dedDecision(false)

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

		ptrShadow->SetMeshResource(L"Player_WalkAnimation_MESH");//!影の形（メッシュ）を設定
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネントの設定
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Player_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 40.0f);
		ptrDraw->ChangeCurrentAnimation(L"Move");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		Coll->SetDrawActive(false);

		m_patrolPoints[m_patrolindex];
		SetEnemyPatorolindex(m_patrolindex);

		auto patrolPoints = GetEnemyPatorolPoints();
		for (auto& v : m_patrolPoints)
		{
			patrolPoints.emplace_back(v);
		}

		SetpatorolPoints(patrolPoints);
	
	}

	//!更新
	void Villager::OnUpdate()
	{
		
		auto MaxSpeed = GetMaxSpeed();
		MaxSpeed = m_Speed;
		SetMaxSpeed(MaxSpeed);

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
			if (seekCondition ==true)
			{
              PostEvent(0.0f, GetThis<Villager>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
	}
}
//!end basecross
