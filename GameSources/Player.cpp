/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//!構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Speed(20.0f),
		m_ChangeTime(0.0f),
		m_playerChange(static_cast<int>(PlayerModel::human)),
		m_humanTime(31.0f),
		m_wolfTime(61.0f),
		m_reset(0),
		m_KeyCount(0),
		m_MaxKeyCount(3),
		m_Ded(0),
		m_GetPlayerPositionTime(0.8f),
		m_PlayerPositionTime(0.0f),
		m_PlayerPositionOnSecondMax(39),
		m_PlayerHp(3),
		m_IsPlayerFound(false)

	{}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//!コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}

		return ret;
	}

	//!プレイヤーのベクトルの取得
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);

		//!入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;

		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//!動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			//!進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();

			float frontAngle = atan2(front.z, front.x);//!進行方向向きからの角度を算出

			//!コントローラの向き計算
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();

			float cntlAngle = atan2(-moveX, moveZ);//!コントローラの向きから角度を計算

			float totalAngle = frontAngle + cntlAngle;//!トータルの角度を算出

			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));//!角度からベクトルを作成

			angle.normalize();//!正規化する

			angle *= moveSize;//!移動サイズを設定。

			angle.y = 0;//!Y軸は変化させない
		}
		return angle;
	}

	//!プレイヤーを動かす処理
	void Player::MovePlayer() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//!回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}

	//!初期化
	void Player::OnCreate() {

		//!初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(3.0f, 3.0f, 3.0f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0.0f, 4.0f, -90.0f));


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!回転
			Vec3(0.0f, -1.0f, 0.0f)  //!位置
		);

		auto ptrColl = AddComponent<CollisionCapsule>();//!CollisionSphere衝突判定を付ける

		ptrColl->SetDrawActive(false);
		auto ptrGra = AddComponent<Gravity>();//!重力をつける

	
		auto shadowPtr = AddComponent<Shadowmap>();//!影をつける（シャドウマップを描画する）

		shadowPtr->SetMeshResource(L"PLAYER_HUMAN");//!影の形（メッシュ）を設定
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネントの設定

		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"PLAYER_HUMAN");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		/*ptrDraw->SetFogEnabled(true);*/
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		
		//!カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());//!MyCameraである
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));//!MyCameraに注目するオブジェクト（プレイヤー）の設定
		}
	}

	void Player::AppearanceChange()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTimeを取得することにより時間を使える
		m_ChangeTime += elapsedTime;//時間を変数に足す
		if (m_ChangeTime >= m_humanTime)//!人間の時間が終わったら
		{

			m_playerChange = static_cast<int>(PlayerModel::wolf);//!状態を狼にする

			auto ptrDraw = GetComponent<PNTStaticModelDraw>();//!プレイヤーの描画コンポ―ネントを取得
			auto shadowPtr = GetComponent<Shadowmap>();
			ptrDraw->SetMeshResource(L"PLAYER_Wolf");//!プレイヤーのメッシュの変更
			shadowPtr->SetMeshResource(L"PLAYER_Wolf");
			ptrDraw->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));
			if (m_ChangeTime >= m_wolfTime)//!狼の時間になったら
			{
				ptrDraw->SetMeshResource(L"PLAYER_HUMAN");//!プレイヤーのメッシュの変更
				shadowPtr->SetMeshResource(L"PLAYER_HUMAN");
				m_playerChange = static_cast<int>(PlayerModel::human);//!プレイヤーの状態は人間
				ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
				/*ptrDraw->SetMeshResource(L"PLAYER_HUMAN");*///!プレイヤーのメッシュの変更
				m_ChangeTime = (float)m_reset;//!状態タイムをリセットする
			}
			return;

		}
	}


	//!村人を倒す処理
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();//!トランスフォームを取得
		auto position = transComp->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 10.0f);//!プレイヤーの座標を中心に半径2センチの円の作成

		//!村人を殺す
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		auto vecHnter = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		//!ハンター配列オブジェクトの配列分回す
		for (auto& v : vecHnter)
		{
			auto HunterPtr = v.lock();//!ハンターのグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったら
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら
				{
					
					auto HunterDedDecision = ptrHunter->GetDedDecision();//!ハンターの生死の判定の取得
					HunterDedDecision = true;//!ハンターの生死を死にする
					ptrHunter->SetDedDecision(HunterDedDecision);//!ハンターの生死の設定
					auto HunterSpeed = ptrHunter->GetSpeed();//!ハンターのスピードを取得
					if (!HunterSpeed == m_Ded)
					{
                    HunterSpeed = m_Ded;//!ハンターのスピードを０にする
					ptrHunter->SetSpeed(HunterSpeed);//!ハンターのスピードを設定
					auto HunterDraw = ptrHunter->GetComponent<PNTStaticModelDraw>();//!ハンターの描画コンポーネントを取得
					HunterDraw->SetDiffuse(Col4(1, 0, 0, 1));//!ハンターの色の設定
					m_PlayerHp--;
					}
					

				}
			}
		}
	}

	//!鍵のスプライトの作成
	void Player::CreateKeySprite()
	{
		GetStage()->AddGameObject<KeySprite>(
			L"KEY_TX",//!テクスチャ
			true,
			Vec2(150.0f, 150.0f),//大きさ
			Vec2(300.0f + (100.0f * (m_KeyCount - 1)), -320.0f)//座標
			);
	}

	

	//更新
	void Player::OnUpdate() {
		//!敵の親クラスを取得できる
		
		auto PlayerTrans = GetComponent<Transform>();
		auto PlayerPosition = PlayerTrans->GetPosition();
		auto Time = App::GetApp()->GetElapsedTime();
		m_PlayerPositionTime += Time;

		if (m_PlayerPositionTime >= m_GetPlayerPositionTime)
		{	
			m_PlayerPositionOnSecond.push_back(PlayerPosition);

			if (m_PlayerPositionOnSecond.size() >= m_PlayerPositionOnSecondMax)
			{
				m_PlayerPositionOnSecond.erase(m_PlayerPositionOnSecond.begin());
			}
		}
		

		MovePlayer();
		AppearanceChange();//!プレイヤーの姿変化
		m_InputHandlerB.PushHandleB(GetThis<Player>());//!Bボタンのインプットハンドラの追加

	}

	//!プレイヤーが相手に当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto ptrKey = dynamic_pointer_cast<Key>(Other);
		//!プレイヤーが鍵に当たったら
		if (ptrKey)
		{
			m_KeyCount++;
			GetStage()->RemoveGameObject<Key>(Other);//!鍵オブジェクトの削除
			CreateKeySprite();
		}
		
		//!プレイヤーが鍵を持っていたら
			if (m_KeyCount == m_MaxKeyCount)
			{
				auto ptrGate = dynamic_pointer_cast<StageGate>(Other);//!門のオブジェクト取得
				if (ptrGate)//!プレイヤーが門に当たったら
				{
					PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!ゲームクリアステージに遷移
				}
			}
	}
	void Player::OnPushB()
	{
		if (m_playerChange == static_cast<int>(PlayerModel::wolf))
		{
          Villagerkiller();//!村人を倒す処理
		}
		
	}
}
//end basecross

