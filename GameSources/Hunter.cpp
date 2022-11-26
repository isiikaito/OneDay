/*!
@file Hunter.cpp
@brief ハンターの実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
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
		m_Speed(1),
		m_patrolindex(0),
	    m_DedDecision(false)


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
			Vec3(0.35f, 0.2f, 0.4f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(0.0f, -0.5f, -0.05f)  //!位置
		);

		AddTag(L"Hunter_ObjGroup");//!オブジェクトタグの作成
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Hunter>());//!グループに自分自身を追加
		SetAlphaActive(true);//!SetDiffiuseのカラー変更を適用
		
		AddComponent<Gravity>(); //!重力をつける
		auto Coll = AddComponent<CollisionObb>();//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();  //!影をつける（シャドウマップを描画する）

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"HUNTER_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();    //!描画コンポーネントの設定 

		//!メッシュの設定
		ptrDraw->SetMeshResource(L"HUNTER_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		Coll->SetDrawActive(true);

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
	void Hunter::OnUpdate()
	{
	

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");             //!プレイヤーの取得
		m_playerChange = ptrPlayer->GetPlayerCange();//!プレイヤーの状態の取得
		ptrPlayer->SetPlayerChange(m_playerChange);//!プレイヤーの取得した状態の設定
		BaseEnemy::OnUpdate();
	}
	
	//!ハンターがプレイヤーを捕まえたら
	void Hunter::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrPlayer = dynamic_pointer_cast<Player>(Other);
		if (ptrPlayer)
		{
			if (m_playerChange == static_cast<int>(PlayerModel::wolf)&&m_DedDecision ==false)
			{
              PostEvent(0.0f, GetThis<Hunter>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
	}
}
//!end basecross
