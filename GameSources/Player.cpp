/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//!構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Speed(50.0f),
		m_idleTime(0.0f),
		m_playerChange(0),
		m_humanTime(30.0f),
		m_wolfTime(60.0f),
		m_reset(0)
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
		ptr->SetScale(2.0f, 2.0f, 2.0f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 10.0f, -30));

		
		auto ptrColl = AddComponent<CollisionCapsule>();//!CollisionSphere衝突判定を付ける

		//!各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		
		auto ptrGra = AddComponent<Gravity>();//!重力をつける

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//!文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		
		auto shadowPtr = AddComponent<Shadowmap>();//!影をつける（シャドウマップを描画する）
		
		shadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");//!影の形（メッシュ）を設定

		
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();//!描画コンポーネントの設定
	
		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		/*ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);*/

		//!カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			
			
			ptrCamera->SetTargetObject(GetThis<GameObject>());//!MyCameraである
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));//!MyCameraに注目するオブジェクト（プレイヤー）の設定
		}
	}
	//更新
	void Player::OnUpdate() {
		
		m_InputHandler.PushHandle(GetThis<Player>());//!コントローラチェックして入力があればコマンド呼び出し
		MovePlayer();

		
		float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTimeを取得することにより時間を使える
		m_idleTime += elapsedTime;//時間を変数に足す
		if (m_idleTime >= m_humanTime)
		{
			m_playerChange = static_cast<int>(PlayerModel::wolf);
			auto transComp = AddComponent<Transform>();
			auto ptrDraw = AddComponent<BcPNTStaticDraw>();
			ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
			if (m_idleTime >= m_wolfTime)
			{
				m_playerChange = static_cast<int>(PlayerModel::human);//!プレイヤーの状態は人間
				
				ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
				m_idleTime = 0;
		    }
			return;
			
		}

		

	}
	void Player::OnPushA()
	{
		
	}
}
//end basecross

