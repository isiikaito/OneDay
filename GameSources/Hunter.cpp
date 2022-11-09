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

		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_patrolPoints(patrolPoints),
		m_StateChangeSize(30.0f),
		m_Force(0),
		m_Velocity(0),
		m_PEvector(0),
		m_playerChange(0)

	{
	}

	//!デストラクタ
	Hunter::~Hunter() {}
	//!適応力
	void Hunter::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();//!時間の取得
		m_Velocity += m_Force * elapsedTime;//!行動の力に時間をかけて速度を求めている
		auto ptrTrans = GetComponent<Transform>();//!敵のTransformを取得している
		auto pos = ptrTrans->GetPosition();//!敵のポジションを取得している
		pos += m_Velocity * elapsedTime * 2;//!敵のポジションに速度と時間を掛けたものを足す
		ptrTrans->SetPosition(pos);//!敵のポジションの設定
	}

	//!ターゲット(プレイヤー)の取得
	shared_ptr<GameObject>  Hunter::GetTarget()const
	{
		return GetStage()->GetSharedObject(L"Player");
	}

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

		//経路巡回を付ける
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		list<Vec3> pathList = {};//!巡回ポイントのリスト

		for (auto v : m_patrolPoints)//!vector配列の要素分ループを回す
		{
			pathList.push_back(v);//!巡回経路のリストに巡回ポイントを入れる
		}

		ptrFollowPath->SetPathList(pathList);//!リストを設定する
		ptrFollowPath->SetLooped(true);//!巡回のループを回す

		AddComponent<Gravity>(); //!重力をつける
		auto Coll = AddComponent<CollisionObb>();//!CollisionObb衝突判定を付ける
		auto ptrShadow = AddComponent<Shadowmap>();  //!影をつける（シャドウマップを描画する）

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"HUNTER_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();    //!描画コンポーネントの設定            //!描画コンポーネント

		//!メッシュの設定
		ptrDraw->SetMeshResource(L"HUNTER_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		Coll->SetDrawActive(true);

		//!障害物回避行動
		vector<shared_ptr<GameObject>>obObjVec;
		GetStage()->GetUsedTagObjectVec(L"StageBuilding", obObjVec);
		vector<SPHERE>obVec;
		for (auto& v : obObjVec)
		{
			auto TransPtr = v->GetComponent<Transform>();

			SPHERE sp;
			sp.m_Center = TransPtr->GetPosition();
			sp.m_Radius = TransPtr->GetScale().x * 1.414f * 0.5f;
			obVec.push_back(sp);
		}
		auto ptrAvoidandce = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidandce->SetObstacleSphereVec(obVec);
		m_StateMachine.reset(new StateMachine<Hunter>(GetThis<Hunter>()));
		m_StateMachine->ChangeState(FarState::Instance());
	}
	//!更新
	void Hunter::OnUpdate()
	{
		m_Force = Vec3(0);//!行動の力をゼロにする

		m_StateMachine->Update();//!この中でステートの切り替えが行われる

		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!障害物を避ける行動
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");             //!プレイヤーの取得
		m_playerChange = ptrPlayer->GetPlayerCange();//!プレイヤーの状態の取得
		ptrPlayer->SetPlayerChange(m_playerChange);//!プレイヤーの取得した状態の設定
	}
	//!動作
	//!ステートが近い時の処理
	void Hunter::NearBehavior()
	{


		auto ptrArrive = GetBehavior<ArriveSteering>();                                  //!到着ステアリング
		auto ptrTrans = GetComponent<Transform>();                                       //!敵のコンポーネントの取得
		auto ptrPlayerTrans = GetTarget()->GetComponent<Transform>();                    //!プレイヤーのコンポーネントの取得
		auto force = GetForce();                                                         //!行動の力の取得
		force += ptrArrive->Execute(force, GetVelocity(), ptrPlayerTrans->GetPosition());//!現在の力、速度、位置を代入している。
		SetForce(force);                                                                 //!力を設定する
		float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition());  //!プレイヤーの位置ー敵の位置
		//!一定の距離離れたら
		if (f > GetStateChangeSize() || m_playerChange == static_cast<int>(PlayerModel::human)) //!ステートの大きさ分離れたらまたはプレイヤーが人間状態になったら
		{
			GetStateMachine()->ChangeState(FarState::Instance());                        //!ステートをチェンジする
		}
	}

	//!ステートが遠い時の処理
	void Hunter::FarBehavior() {

		auto ptrFollowPath = GetBehavior<FollowPathSteering>();//!巡回行動のステアリング
			auto ptrTrans = GetComponent<Transform>();//!敵のコンポーネントの取得
			auto ptrPlayerTrans = GetTarget()->GetComponent<Transform>();//!プレイヤーのコンポーネントの取得
			auto force = GetForce();//!行動の力の取得
		force += ptrFollowPath->Execute(force, GetVelocity());//!現在の力、速度、位置を代入している。
		SetForce(force);//!力を設定する
		float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition());//!プレイヤーの位置ー敵の位置


		Vec3 PEvector = ptrPlayerTrans->GetPosition() - ptrTrans->GetPosition();//!プレイヤーと敵のベクトルを取得
		auto Enemyfront = ptrTrans->GetForword();//!敵の正面を取得
		PEvector.normalize();//!プレイヤーと敵のベクトルを正規化
		auto angle = angleBetweenNormals(Enemyfront, PEvector);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
		auto chk = XM_PI / 6.0f;//!360を6で割って角度を出す。

		if (m_playerChange == static_cast<int>(PlayerModel::wolf))//!プレイヤーが狼の状態の時
		{
			if (angle <= chk && angle >= -chk)//!敵から見て+60度か-60度にプレイヤーが入ったら
			{
				//!一定の近づいたら
				if (f <= GetStateChangeSize())
				{
					GetStateMachine()->ChangeState(NearState::Instance());//!ステートをチェンジする

				}
			}
		}





	}

	//--------------------------------------------------------------------------------------
	  //	プレイヤーから遠いときの移動
	  //--------------------------------------------------------------------------------------
	shared_ptr<FarState> FarState::Instance() {
		static shared_ptr<FarState> instance(new FarState);
		return instance;
	}
	void FarState::Enter(const shared_ptr<Hunter>& Obj) {
	}
	void FarState::Execute(const shared_ptr<Hunter>& Obj) {
		Obj->FarBehavior();
	}

	void FarState::Exit(const shared_ptr<Hunter>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	shared_ptr<NearState> NearState::Instance() {
		static shared_ptr<NearState> instance(new NearState);
		return instance;
	}
	void NearState::Enter(const shared_ptr<Hunter>& Obj) {
	}
	void NearState::Execute(const shared_ptr<Hunter>& Obj) {
		Obj->NearBehavior();
	}
	void NearState::Exit(const shared_ptr<Hunter>& Obj) {
	}


	void Hunter::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrHunter = dynamic_pointer_cast<Player>(Other);
		if (ptrHunter) 
		{
			GetStage()->RemoveGameObject<Hunter>(GetThis<Hunter>());
			PostEvent(0.0f, GetThis<Hunter>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
		}
	}
}
//!end basecross
