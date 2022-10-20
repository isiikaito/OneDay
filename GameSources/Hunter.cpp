/*!
@file Hunter.cpp
@brief ハンターの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		PEvector(0)

	{
	}

	//!デストラクタ
	Enemy::~Enemy() {}
	//!適応力
	void Enemy::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();//!時間の取得
		m_Velocity += m_Force * elapsedTime;//!行動の力に時間をかけて速度を求めている
		auto ptrTrans = GetComponent<Transform>();//!敵のTransformを取得している
		auto pos = ptrTrans->GetPosition();//!敵のポジションを取得している
		pos += m_Velocity * elapsedTime;//!敵のポジションに速度と時間を掛けたものを足す
		ptrTrans->SetPosition(pos);//!敵のポジションの設定
	}

	//!ターゲット(プレイヤー)の取得
	shared_ptr<GameObject>  Enemy::GetTarget()const
	{
		return GetStage()->GetSharedObject(L"Player");
	}

	//!初期化
	void Enemy::OnCreate()
	{
		auto group = GetStage()->GetSharedObjectGroup(L"ObjGroup");//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Enemy>());//!グループに自分自身を追加

		//!分離行動をつける
		auto ptrSep = GetBehavior<SeparationSteering>();
		ptrSep->SetGameObjectGroup(group);

		//!分かんないから聞く
		//壁回避行動を付ける(ゲーム盤の外に出ないようにする)
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();
		vector<PLANE> planeVec = {
			{
				Vec3(20,0,0),
				Vec3(20,1.0,0),
				Vec3(20,0,-1.0),
			},
			{
				Vec3(0,0,-20),
				Vec3(0,1.0,-20),
				Vec3(-1.0,0,-20),
			},
			{
				Vec3(-20,0,0),
				Vec3(-20,1.0,0),
				Vec3(-20,0,1.0),
			},
			{
				Vec3(0,0,20),
				Vec3(0,1.0,20),
				Vec3(1.0,0,20),
			},
		};
		ptrWall->SetPlaneVec(planeVec);

		//!障害物回避行動を付ける
		vector<shared_ptr<GameObject>>spObjVec;
		GetStage()->GetUsedTagObjectVec(L"StageWall", spObjVec);//!障害物の取得
		vector<SPHERE> spVec;//!球体のベクトルの取得
		for (auto& v : spObjVec) {
			auto TransPtr = v->GetComponent<Transform>();//!グループ内のコンポーネントを取得
			SPHERE sp;//!聞く
			sp.m_Center = TransPtr->GetPosition();
			sp.m_Radius = TransPtr->GetScale().x * 0.5f;
			spVec.push_back(sp);
		}
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();
		ptrAvoidance->SetObstacleSphereVec(spVec);
		m_StateMachine.reset(new StateMachine<Enemy>(GetThis<Enemy>()));//!ステートマシンの構築
		m_StateMachine->ChangeState(NearState::Instance());
	}
	//!更新
	void Enemy::OnUpdate()
	{
		m_Force = Vec3(0);//!行動の力をゼロにする
		//!共通のステアリング1
		auto ptrWall = GetBehavior<WallAvoidanceSteering>();//!ステージの外に出ないようにする処理
		m_Force += ptrWall->Execute(m_Force, GetVelocity());//!実行する力と速度を代入
		m_StateMachine->Update();//!この中でステートの切り替えが行われる
		//!共通のステアリング2
		auto ptrSep = GetBehavior<SeparationSteering>();//!分離行動を実行する
		m_Force += ptrSep->Execute(m_Force);//!分離行動の力を代入する
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!障害物を避ける行動
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
		ApplyForce();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);



	}

	//--------------------------------------------------------------------------------------
	  //	プレイヤーから遠いときの移動
	  //--------------------------------------------------------------------------------------
	shared_ptr<FarState> FarState::Instance() {
		static shared_ptr<FarState> instance(new FarState);
		return instance;
	}
	void FarState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void FarState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->FarBehavior();
	}

	void FarState::Exit(const shared_ptr<Enemy>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	shared_ptr<NearState> NearState::Instance() {
		static shared_ptr<NearState> instance(new NearState);
		return instance;
	}
	void NearState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void NearState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->NearBehavior();
	}
	void NearState::Exit(const shared_ptr<Enemy>& Obj) {
	}


	//--------------------------------------------------------------------------------------
	   //	パスを巡回する配置オブジェクト
	   //--------------------------------------------------------------------------------------
	   //構築と破棄
	Hunter::Hunter(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		Enemy(StagePtr, StartPos)
	{
	}
	Hunter::~Hunter() {}

	//初期化
	void Hunter::OnCreate()
	{
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1.0f, 1.4f, 1.4f);//!大きさ
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);//!回転
		ptrTrans->SetPosition(0.0f, 5.0f, 0.0f);//!位置

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.35f, 0.2f, 0.4f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(0.0f, -0.5f, -0.05f)  //!位置
		);

		AddTag(L"ObjGroup");//!オブジェクトタグの作成
		auto group = GetStage()->GetSharedObjectGroup(L"ObjGroup");//!オブジェクトのグループを得る
		group->IntoGroup(GetThis<Enemy>());//!グループに自分自身を追加

		//経路巡回を付ける
		auto ptrFollowPath = GetBehavior<FollowPathSteering>();
		list<Vec3> pathList = {
			Vec3(-10,0.125,10),
			Vec3(10,0.125,10),
			Vec3(-10,0.125,-10),
			Vec3(10,0.125,-10),
		};
		ptrFollowPath->SetPathList(pathList);
		ptrFollowPath->SetLooped(true);

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
		//!親クラスのOnCreateを呼ぶ
		Enemy::OnCreate();
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
		if (f > GetStateChangeSize()) {
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
//!end basecross
