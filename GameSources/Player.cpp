/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerState.h"
#include "Meat.h"

namespace basecross {
	constexpr float m_maxDisappearTime = 2.0f;
	constexpr float m_MaxwolfHowlingTime = 0.1f;
	constexpr float m_maxDedTime = 1.0f;
	constexpr float m_vibrationMaxTime = 1.0f;

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
		m_Ded(0.0f),
		m_GetPlayerPositionTime(0.8f),
		m_PlayerPositionTime(0.0f),
		m_PlayerPositionOnSecondMax(39),
		m_PlayerHp(3),
		m_IsPlayerFound(false),
		m_wolfPlayerSpeed(21.0f),
		m_humanPlayerSpeed(20.0f),
		m_AlertleveCount(0),
		m_IsFastHowling(false),
		m_wolfHowlingTime(0),
		m_dedTime(0.0f),
		m_disappearTime(0.0f),
		m_IsPlayerDed(0.0f),
		m_gameOverDrawActive(false),
		m_vibration(0.0f),
		m_gameTime(0.0f),
		m_meatCount(0),
		m_vibrationTime(0.0f),
		m_IsvibrationOn(false)
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());
	}

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
			auto& ptrCamera = OnGetDrawCamera();

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
		//アニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);

			//歩くアニメーション
			if (AnimationName == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//歩く音再生
				auto& XAptr = App::GetApp()->GetXAudio2Manager();
				m_Wolk = XAptr->Start(L"WalkBGM", 1, 1.0f);
			}
		}

		else {
			//立ち止まるアニメーション
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto& XAptr = App::GetApp()->GetXAudio2Manager();
				XAptr->Stop(m_Wolk);


			}
		}


		//!回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}


	}

	//!初期化
	void Player::OnCreate() {

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\key.efk";//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();//!エフェクトのインターフェースの取得
		m_keyEfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);//!取得したエフェクトで作る

		
		wstring scratchEffectStr = DataDir + L"Effects\\scratch.efk";//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
		auto scratchEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();//!エフェクトのインターフェースの取得
		m_scratchEfkEffect = ObjectFactory::Create<EfkEffect>(scratchEfkInterface, scratchEffectStr);//!取得したエフェクトで作る

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

		shadowPtr->SetMeshResource(L"Player_WalkAnimation_MESH");//!影の形（メッシュ）を設定
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネントの設定

		//!描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Player_WalkAnimation_MESH_WITH_TAN");

		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 20.0f);
		ptrDraw->AddAnimation(L"Default", 31, 30, true, 10.0f);
		ptrDraw->AddAnimation(L"Ded", 61, 30, false, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");

			//!カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());//!MyCameraである
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));//!MyCameraに注目するオブジェクト（プレイヤー）の設定
		}
	}

	

	void Player::PlayerGameOver()
	{
		auto scene=App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		gameOver = true;
		scene->SetGameOver(gameOver);
		GetStage()->AddGameObject<FadeOut>(true,
			Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.1f));
		float Time = App::GetApp()->GetElapsedTime();
		m_dedTime += Time;
		if (m_dedTime >= m_maxDedTime)
		{
			m_gameOverDrawActive = true;
			
		}

	}

	void Player::PlayerDed()
	{
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//立ち止まるアニメーション
		if (AnimationName == L"Move" || AnimationName == L"Default")
		{
			ptrDraw->ChangeCurrentAnimation(L"Ded");
			auto& XAptr = App::GetApp()->GetXAudio2Manager();
			XAptr->Stop(m_Wolk);

		}

		PlayerGameOver();
	}

	void Player::VillagerDisappear()
	{
		auto position = GetComponent<Transform>()->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 100);//!プレイヤーの座標を中心に半径2センチの円の作成
		//!村人を殺す
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");
		auto& vecVillager = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		//!村人配列オブジェクトの配列分回す
		for (auto& v : vecVillager)
		{

			auto VillagerPtr = v.lock();//!村人のグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったら
			if (ptrVillager)
			{
				auto VillagerCapsrul = ptrVillager->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
				if (HitTest::SPHERE_CAPSULE(playerSp, VillagerCapsrul, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら
				{
					
					auto VillagerSpeed = ptrVillager->GetSpeed();//!村人のスピードを取得
					if (VillagerSpeed == m_Ded)
					{
						float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTimeを取得することにより時間を使える
						m_disappearTime += elapsedTime;//時間を変数に足す
						if (m_disappearTime >= m_maxDisappearTime)
						{
							GetStage()->RemoveGameObject<Villager>(VillagerPtr);
							m_disappearTime = 0;
						}
					}


				}
			}
		}
	}

	void Player::HunterDisappear()
	{
		auto position = GetComponent<Transform>()->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 100);//!プレイヤーの座標を中心に半径2センチの円の作成
		//!村人を殺す
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		auto& vecHunter = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		//!村人配列オブジェクトの配列分回す
		for (auto& v : vecHunter)
		{

			auto hunterPtr = v.lock();//!村人のグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrHunter = dynamic_pointer_cast<Hunter>(hunterPtr);//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったら
			if (ptrHunter)
			{
				auto hunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
				if (HitTest::SPHERE_CAPSULE(playerSp, hunterCapsrul, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら
				{

					auto hunterSpeed = ptrHunter->GetSpeed();//!村人のスピードを取得
					if (hunterSpeed == m_Ded)
					{
						float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTimeを取得することにより時間を使える
						m_disappearTime += elapsedTime;//時間を変数に足す
						if (m_disappearTime >= m_maxDisappearTime)
						{
							GetStage()->RemoveGameObject<Hunter>(ptrHunter);
							m_disappearTime = 0;
						}
					}


				}
			}
		}
	}

	void Player::EnemyDedSound()
	{
		//サウンド再生
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"kill", 0, 9.0f);
		ptrXA->Start(L"scream", 0, 9.0f);
	}

	void Player::Hunterkiller()
	{
		auto transComp = GetComponent<Transform>();//!トランスフォームを取得
		auto position = transComp->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 5.0f);//!プレイヤーの座標を中心に半径5センチの円の作成
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		int alertlevelCount = scene->GetAlertlevelCount();//!警戒度の取得
		//!ハンターを殺す
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		auto& vecHunter = group->GetGroupVector();
		//!ハンターの配列オブジェクトの配列分for分で回す
		for (auto& v : vecHunter)
		{
			auto HunterPtr = v.lock();//!ハンターのグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);//!ロックした物を取り出す

			auto HunterTrans = GetComponent<Transform>();//!ハンターのトランスフォームの取得
			auto HunterPosition = HunterTrans->GetPosition();//!ハンターのポジションの取得
			Vec3 PEvector = position - HunterPosition;//!プレイヤーと敵のベクトルを取得
			PEvector.normalize();//!プレイヤーと敵のベクトルを正規化
			auto Enemyfront = HunterTrans->GetForword();//!敵の正面を取得
			auto angle = angleBetweenNormals(-Enemyfront, PEvector);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
			auto chk = XM_PI / 6.0f;//!360を6で割って角度を出す。

			//!プレイヤーの範囲に敵がはいったら
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
                
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら)
				{
					
						auto HunterSpeed = ptrHunter->GetSpeed();//!村人のスピードを取得
						if (HunterSpeed != m_Ded)
						{
							HunterSpeed = m_Ded;//!村人のスピードを０にする
							ptrHunter->SetSpeed(HunterSpeed);//!村人のスピードを設定
							alertlevelCount++;
							scene->SetAlertlevelCount(alertlevelCount);

							//サウンド再生
							EnemyDedSound();
						}
					
				}
			}

		}
	}

	void Player::BreakWoodBox()
	{
		auto transComp = GetComponent<Transform>();//!トランスフォームを取得
		auto position = transComp->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 5.0f);//!プレイヤーの座標を中心に半径2センチの円の作成
		auto scene = App::GetApp()->GetScene<Scene>();
		//!村人を殺す
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup");
		auto& vecWoodBox = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		//!村人配列オブジェクトの配列分回す
		for (auto& v : vecWoodBox)
		{
			auto WoodBox = v.lock();//!村人のグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrWoodBox = dynamic_pointer_cast<WoodenBox>(WoodBox);//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったら
			if (ptrWoodBox)
			{
				auto WoodBoxOBB = ptrWoodBox->GetComponent<CollisionObb>()->GetObb();//!ハンタ-のObbオブジェクトを取得
				if (HitTest::SPHERE_OBB(playerSp, WoodBoxOBB, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら
				{
					GetStage()->RemoveGameObject<WoodenBox>(ptrWoodBox);
					//サウンド再生
					auto& ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"WoodBoxBreak", 0, 1.0f);
					
				}
			}
		}
	}

	//!村人を倒す処理
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();//!トランスフォームを取得
		auto position = transComp->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 5.0f);//!プレイヤーの座標を中心に半径2センチの円の作成
		auto scene = App::GetApp()->GetScene<Scene>();
		int alertlevelCount = scene->GetAlertlevelCount();
		//!村人を殺す
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");
		auto& vecVillager = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		//!村人配列オブジェクトの配列分回す
		for (auto& v : vecVillager)
		{
			auto VillagerPtr = v.lock();//!村人のグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったら
			if (ptrVillager)
			{
				auto VillagerCapsrul = ptrVillager->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
				if (HitTest::SPHERE_CAPSULE(playerSp, VillagerCapsrul, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら
				{
					
					auto VillagerSpeed = ptrVillager->GetSpeed();//!村人のスピードを取得
					if (VillagerSpeed != m_Ded)
					{
						VillagerSpeed = m_Ded;//!村人のスピードを０にする
						ptrVillager->SetSpeed(VillagerSpeed);//!村人のスピードを設定
						alertlevelCount++;
						scene->SetAlertlevelCount(alertlevelCount);

						//サウンド再生
						EnemyDedSound();
					}
				}
			}
		}
	}

	void Player::GetPlayerPositionBrett()
	{
		

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
	}

	void Player::Escape()
	{
		auto transComp = GetComponent<Transform>();//!トランスフォームを取得
		auto position = transComp->GetPosition();//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, 10.0f);//!プレイヤーの座標を中心に半径2センチの円の作成

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");
		Vec3 ret;
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))//!プレイヤーの周りを囲んでいるスフィアに当たったら
		{
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!ゲームクリアステージに遷移
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

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);
	}

	//!コントローラの振動処理
	void Player::Controllervibration()
	{
		
		

		//!振動がオンになっているとき
		if (m_IsvibrationOn == true)
		{
			auto Time = App::GetApp()->GetElapsedTime();//!時間の取得
			m_vibrationTime += Time;
             m_vibration = 65535.0f;
			
			if (m_vibrationTime >= m_vibrationMaxTime)
			{
				
				m_IsvibrationOn = false;
			}
		}
		if (m_IsvibrationOn == false)
		{
			m_vibrationTime = 0.0f;
			m_vibration = 0.0f;
		}

		//コントローラーの振動
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = m_vibration; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = m_vibration; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}

	//更新
	void Player::OnUpdate() {

		m_StateMachine->Update();


		Controllervibration();

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		auto gameTime = scene->GetGameTime();
		m_gameTime += gameTime;

		//!敵の親クラスを取得できる
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//アニメーション
		ptrDraw->UpdateAnimation(elapsedTime);

		
		//!ゲームオーバーになってない時に
		if (gameOver == false)
		{
        GetPlayerPositionBrett();
		VillagerDisappear();
		HunterDisappear();
		 MovePlayer();
		
		}
		

		if (m_IsPlayerDed == true)
		{
			PlayerDed();
		}

		

		if (m_PlayerHp == m_Ded)
		{
			PlayerGameOver();
		}
m_InputHandlerB.PushHandleB(GetThis<Player>());//!Bボタンのインプットハンドラの追加
	}

	//!プレイヤーが相手に当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{

		auto ptrKey = dynamic_pointer_cast<Key>(Other);

		if (m_playerChange == static_cast<int>(PlayerModel::wolf))
		{
			//!プレイヤーが鍵に当たったら
			if (ptrKey)
			{
				m_KeyCount++;
				GetStage()->RemoveGameObject<Key>(Other);//!鍵オブジェクトの削除
				CreateKeySprite();
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"acquisition", 0, 9.0f);

				//エフェクトのプレイ
				auto Ptr = ptrKey->GetComponent<Transform>();
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
				m_keyEfkPlay = ObjectFactory::Create<EfkPlay>(m_keyEfkEffect, Ptr->GetPosition());

			}


		}

		auto ptrMeat = dynamic_pointer_cast<Meat>(Other);

		if (m_playerChange == static_cast<int>(PlayerModel::human))
		{
			//!プレイヤーが肉に当たったら
			if (ptrMeat)
			{
				m_meatCount++;
				GetStage()->RemoveGameObject<Meat>(Other);//!鍵オブジェクトの削除
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"MeatEat", 0, 9.0f);
			}


		}


	}
	void Player::OnPushB()
	{
		//エフェクトのプレイ
		auto Ptr = GetComponent<Transform>();
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		m_scratchEfkPlay = ObjectFactory::Create<EfkPlay>(m_scratchEfkEffect, Ptr->GetPosition());
		

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		//!ゲームオーバーになってない時に
		if (gameOver == false)
		{
			if (m_playerChange == static_cast<int>(PlayerModel::wolf))
			{
				Villagerkiller();//!村人を倒す処理
				Hunterkiller();//!ハンターを倒す処理
				BreakWoodBox();//!ボックスを壊す
			}

			if (m_playerChange == static_cast<int>(PlayerModel::human))
			{
				//!プレイヤーが鍵を持っていたら
				if (m_KeyCount == m_MaxKeyCount)
				{
					Escape();
				}
			}

		}
	}
}
//end basecross

