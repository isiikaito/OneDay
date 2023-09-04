/*!
@file Player.cpp
@brief プレイヤーなど実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "PlayerState.h"
#include "Meat.h"
#include "GameUI.h"
#include "WoodenBoxState.h"
#include "AnimationComponent.h"



namespace basecross {
	constexpr float VIbRATIONMAXTIME = 1.0f;			//!振動する時間
	constexpr int DAY = 7;								//!ゲームオーバーまでの日にち
	constexpr int SOUNDLOOP = 1;						//!音のループ
	constexpr int NOTSOUNDLOOP = 0;						//!サウンドループ無し
	constexpr float ESCAPESPHERERAKIUS = 10.0f;			//!プレイヤーを中心とした円の半径
	constexpr float VILLAGERKILLERSPHERERADIUS = 5.0f;	//!村人を倒す時の円の半径
	constexpr float BREAKWOODBOXSPHERERADIUS = 5.0f;	//!木箱を倒す時の円の半径
	constexpr float HUNTERKILLERSPHERERADIUS = 5.0f;	//!ハンターを倒す時の円の半径
	constexpr float ANGLEEQUAL = 6.0f;					//!視野の制限
	constexpr float ROTTOHEAD = 1.0f;					//!正面
	constexpr float TARGETTOATY = 0.25f;				//!カメラの視点位置のy
	constexpr WORD  MAXVIBRATION = 65535;				//!振動の大きさ
	
	//!構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_playerBoneModelDeta({ 
		Vec3(3.0f, 3.0f, 3.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 4.0f, -90.0f),
		Vec3(0.4f, 0.4f, 0.4f) ,
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, -1.0f, 0.0f),
		L"Player_WalkAnimation2_MESH" ,
		L"Player_WalkAnimation2_MESH_WITH_TAN",
		L"OBJECT_NORMAL_TX" }),
		m_playerChange(PlayerModel::human),
		m_reset(0),
		m_KeyCount(0),
		m_Ded(0.0f),
		m_GetPlayerPositionTime(0.8f),
		m_PlayerPositionTime(0.0f),
		m_PlayerPositionOnSecondMax(39),
		m_PlayerHp(3),
		m_IsPlayerDed(0.0f),
		m_vibration(0),
		m_meatCount(0),
		m_vibrationTime(0.0f),
		m_IsvibrationOn(false),
		m_playerTaskDay(true),
		m_playerTaskNight(false),
		m_effectManager(NULL)
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());	//!現在のステート
	}

	//プレイヤーを動かす
	void Player::MovePlayer() {

		
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();				//アニメーション
		auto& AnimationName = ptrDraw->GetCurrentAnimation();				//!現在のアニメーション
		float elapsedTime = App::GetApp()->GetElapsedTime();				//!経過時間の取得
		auto angle = m_playermove.lock()->GetMoveVector();					//!ベクトルの取得
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!効果音量
		//!スティックが傾いていたら
		if (angle.length() > 0.0f) {
			
			//歩くアニメーション
			//!待機モーションか変身モーションの時
			if (AnimationName == L"Default" || AnimationName == L"Change") {
				ptrDraw->ChangeCurrentAnimation(L"Move");						//!アニメーションを変える
				auto& XAptr = App::GetApp()->GetXAudio2Manager();				//!サウンドマネージャーの取得
				m_Wolk = XAptr->Start(L"WalkBGM", SOUNDLOOP, volume);			//歩く音再生
			}
		}

		else {
			//立ち止まるアニメーション
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");		//!アニメーションを変える
				auto& XAptr = App::GetApp()->GetXAudio2Manager();	//!サウンドマネージャーの取得
				XAptr->Stop(m_Wolk);								//歩く音を止める
			}
		}

		//!回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, ROTTOHEAD);		//!正面を向く
		}
	}

	void Player::OnCreate() {

		m_effectManager = EffectManager::Instance();

		AddComponent<PlayerMoveComponent>();														//!プレイヤーの動く処理
		m_playermove = GetComponent<PlayerMoveComponent>();
		AddComponent<BoneModelComponent>(m_playerBoneModelDeta);									//!プレイヤーのモデル作成
		AddComponent<BcPNTnTBoneModelDraw>();														//!モデルの描画コンポーネントの追加
		m_draw = GetComponent<BcPNTnTBoneModelDraw>();												//!描画処理
		AddComponent<AnimationComponent>(L"Player", L"Default");									//!アニメーションの読み込み

			//!カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());	//!MyCameraである
			ptrCamera->SetTargetToAt(Vec3(0, TARGETTOATY, 0));//!MyCameraに注目するオブジェクト（プレイヤー）の設定
		}
	}

	
	

	void Player::EnemyDedSound()
	{
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!効果音量の取得
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();					//!サウンドマネージャーの取得
		ptrXA->Start(L"kill", NOTSOUNDLOOP, volume);						//!倒したときのサウンドの開始
		ptrXA->Start(L"scream", NOTSOUNDLOOP, volume);						//!攻撃のサウンドの開始
	}

	void Player::Hunterkiller()
	{
		auto transComp = GetComponent<Transform>();						  //!トランスフォームを取得
		auto position = transComp->GetPosition();						  //!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, HUNTERKILLERSPHERERADIUS);			  //!プレイヤーの座標を中心に半径5センチの円の作成
		auto scene = App::GetApp()->GetScene<Scene>();					  //!シーンの取得
		int alertlevelCount = scene->GetAlertlevelCount();				  //!警戒度の取得
		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!ハンターグループの取得
		auto& vecHunter = group->GetGroupVector();						  //!グループの取得
		//!ハンターの配列オブジェクトの配列分for分で回す
		for (auto& v : vecHunter)
		{
			auto HunterPtr = v.lock();									 //!ハンターのグループから1つロックする
			Vec3 ret;													 //!最近接点の代入
			auto ptrHunter = dynamic_pointer_cast<Hunter>(HunterPtr);    //!ロックした物を取り出す

			//!プレイヤーの範囲に敵がはいったら
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
                
				//!プレイヤーの周りを囲んでいるスフィアに当たったら
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))
				{
					
					ptrHunter->SetIsEnemyDed(true);				//!敵を死んだステートに変更する
					alertlevelCount++;							//!危険度を上げる
					scene->SetAlertlevelCount(alertlevelCount); //!危険度を更新
					EnemyDedSound();
						
				}
			}

		}
	}

	void Player::OneWeek()
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
		auto Date = scene->GetDate();					//!日付の取得
		//!ゲームオーバーの日付になったら
		if (Date == DAY)
		{
			m_PlayerHp = 0;//!ゲームオーバー
		}

	}
	//!木箱を破壊する
	void Player::BreakWoodBox()
	{
		auto transComp = GetComponent<Transform>();							//!トランスフォームを取得
		auto position = transComp->GetPosition();							//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, BREAKWOODBOXSPHERERADIUS);				//!プレイヤーの座標を中心に半径2センチの円の作成
		auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup"); //!グループの取得
		auto& vecWoodBox = group->GetGroupVector();							//!ゲームオブジェクトの配列の取得
		//!木箱配列オブジェクトの配列分回す
		for (auto& v : vecWoodBox)
		{
			auto WoodBox = v.lock();										//!村人のグループから1つロックする
			Vec3 ret;														//!最近接点の代入
			auto ptrWoodBox = dynamic_pointer_cast<WoodenBox>(WoodBox);		//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったら
			if (ptrWoodBox)
			{
				auto woodBoxCollision = ptrWoodBox->GetComponent<CollisionObb>();
				auto WoodenBoxOBB = woodBoxCollision->GetObb();//!ハンタ-のObbオブジェクトを取得

				//!プレイヤーの周りを囲んでいるスフィアに当たったら
				if (HitTest::SPHERE_OBB(playerSp, WoodenBoxOBB, ret))
				{
					ptrWoodBox->ChangeState(basecross::kaito::WoodenBoxBreakState::Instance());	//!木箱を破壊するステートに変更
					auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();			//!効果音量の取得					
					auto& ptrXA = App::GetApp()->GetXAudio2Manager();							//サウンド再生
					ptrXA->Start(L"WoodBoxBreak", NOTSOUNDLOOP, volume);
					
				}
			}
		}
	}

	//!村人を倒す処理
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();							//!トランスフォームを取得
		auto position = transComp->GetPosition();							//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, VILLAGERKILLERSPHERERADIUS);				//!プレイヤーの座標を中心に半径2センチの円の作成
		auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
		int alertlevelCount = scene->GetAlertlevelCount();					//!危険度の取得
		//!村人を殺す
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");//!村人のグループを取得
		auto& vecVillager = group->GetGroupVector();						//!ゲームオブジェクトの配列の取得
		//!村人配列オブジェクトの配列分回す
		for (auto& v : vecVillager)
		{
			auto VillagerPtr = v.lock();									//!村人のグループから1つロックする
			Vec3 ret;														//!最近接点の代入
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);	//!ロックした物を取り出す

			//!プレイヤーの範囲に敵が入ったらv

			if (ptrVillager)
			{
				auto VillagerCapsrul = ptrVillager->GetComponent<CollisionCapsule>()->GetCapsule();	//!ハンタ-のObbオブジェクトを取得
				//!プレイヤーの周りを囲んでいるスフィアに当たったら
				if (HitTest::SPHERE_CAPSULE(playerSp, VillagerCapsrul, ret))						
				{
						ptrVillager->SetIsEnemyDed(true);			//!敵を死んだステートに変更する
						alertlevelCount++;							//!危険度を上げる
						scene->SetAlertlevelCount(alertlevelCount); //!危険度を設定
						EnemyDedSound();
					
				}
			}
		}
	}
	
	
	void Player::GetPlayerPositionBrett()
	{
		
		
		auto PlayerTrans = GetComponent<Transform>();		//!プレイヤーのトランスフォームを取得
		auto PlayerPosition = PlayerTrans->GetPosition();	//!プレイヤーのポジションを取得
		auto Time = App::GetApp()->GetElapsedTime();		//!エルパソタイムを取得
		m_PlayerPositionTime += Time;						//!時間の作成

		//!プレイヤーがポジションを保存する時間
		if (m_PlayerPositionTime >= m_GetPlayerPositionTime)
		{
			m_PlayerPositionOnSecond.push_back(PlayerPosition);//!ポジションを保存

			//!一定数保存したら
			if (m_PlayerPositionOnSecond.size() >= m_PlayerPositionOnSecondMax)
			{
				
				m_PlayerPositionOnSecond.erase(m_PlayerPositionOnSecond.begin());//!古い情報を削除する
			}
		}
	}

	void Player::Escape()
	{
		auto transComp = GetComponent<Transform>();														//!トランスフォームを取得
		auto position = transComp->GetPosition();														//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, ESCAPESPHERERAKIUS);													//!プレイヤーの座標を中心に半径2センチの円の作成

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");								//!門を取得
		Vec3 ret;																						//!最近接点の代入
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();									//!コリジョンの衝突判定
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))												//!プレイヤーの周りを囲んでいるスフィアに当たったら
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();											//!サウンドマネージャーの取得
			XAptr->Stop(m_Wolk);																		//!歩く音の停止
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");	//!ゲームクリアステージに遷移
		}
	}
		
	

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!ステートを変更する
	}

	
	void Player::Controllervibration()
	{
		auto scene = App::GetApp()->GetScene<Scene>();			//!シーンの取得
		auto gameOverSprite = scene->GetGameOverSprite();		//!ゲームオーバー判定の取得
		if (gameOverSprite == false)
		{
			//!振動がオンになっているとき
			if (m_IsvibrationOn == true)
			{
				auto Time = App::GetApp()->GetElapsedTime();//!時間の取得
				m_vibrationTime += Time;					//!振動させる時間
				m_vibration = MAXVIBRATION;					//!現在の振動の大きさ
				//!振動する時間経ったら
				if (m_vibrationTime >= VIbRATIONMAXTIME)
				{
					m_IsvibrationOn = false;//!振動をやめる
				}
			}
			if (m_IsvibrationOn == false)
			{
				m_vibrationTime = 0.0f;	//!時間をリセット
				m_vibration = 0;		//!振動を無くす
			}


			XINPUT_VIBRATION vibration;							//!コントローラーの振動
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = m_vibration;			// use any value between 0-65535 here
			vibration.wRightMotorSpeed = m_vibration;			// use any value between 0-65535 here
			XInputSetState(0, &vibration);						//!コントローラーの振動の設定
		}

		else
		{
			
				m_vibrationTime = 0.0f;	//!時間をリセット
				m_vibration = 0;		//!振動を無くす
		
			XINPUT_VIBRATION vibration;							//!コントローラーの振動
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = m_vibration;			// use any value between 0-65535 here
			vibration.wRightMotorSpeed = m_vibration;			// use any value between 0-65535 here
			XInputSetState(0, &vibration);						//!コントローラーの振動の設定
		}
		
	}

	//更新
	void Player::OnUpdate() {
		

		m_StateMachine->Update();								//!ステートマシンの更新
		OneWeek();
		Controllervibration();
		auto scene = App::GetApp()->GetScene<Scene>();			//!シーンの取得
		float elapsedTime = App::GetApp()->GetElapsedTime();	//!経過時間の取得
		auto ptrDraw = m_draw.lock();							//アニメーション
		ptrDraw->UpdateAnimation(elapsedTime);					//!アニメーションの更新
		auto playerChange = scene->GetPlayerChangeDirecting();	//!プレイヤーの変身を開始する
		auto gameStrat = scene->GetGameStrat();					//!オープニングカメラの時かどうか
	
		GetPlayerPositionBrett();
		//!プレイヤーが変身していない時
		if (!playerChange)
		{
				MovePlayer();
		}
		//!変身しているかオープニングカメラの時
		if(playerChange|| gameStrat)
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();//!サウンドマネージャーの取得
			XAptr->Stop(m_Wolk);							 //!歩く音を止める
		}

	 }



	//!プレイヤーが相手に当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		
		auto ptrKey = dynamic_pointer_cast<Key>(Other);//!鍵の取得

		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!効果音量の取得
		if (m_playerChange == PlayerModel::wolf)
		{
			//!プレイヤーが鍵に当たったら
			if (ptrKey)
			{

				m_KeyCount++;																		//!鍵のカウント
				GetStage()->RemoveGameObject<Key>(Other);											//!鍵オブジェクトの削除
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!サウンドマネージャーの取得
				ptrXA->Start(L"acquisition", NOTSOUNDLOOP, volume);									//!サウンドの再生
				auto position = ptrKey->GetComponent<Transform>()->GetPosition();					//!エフェクトのプレイ
				m_effectManager->KeyEfkPlay(position);												//!エフェクトの再生

			
			}


		}

		auto ptrMeat = dynamic_pointer_cast<Meat>(Other);//!肉の取得

		if (m_playerChange == PlayerModel::human)
		{
			//!プレイヤーが肉に当たったら
			if (ptrMeat)
			{
				m_meatCount++;
				GetStage()->RemoveGameObject<Meat>(Other);											//!鍵オブジェクトの削除
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!サウンドマネージャーの取得
				ptrXA->Start(L"MeatEat", NOTSOUNDLOOP, volume);										//!肉を食べるサウンドの再生
				auto Ptr = GetComponent<Transform>();												//!トランスフォームの取得
				m_effectManager->MeatEfkPlay(Ptr->GetPosition());									//!エフェクトの再生

			}


		}

	}

	void Player::AttackEffect()
	{
		//エフェクトのプレイ
		auto Ptr = GetComponent<Transform>();                                               //!トランスフォームの取得
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					//!エフェクトインターフェースの取得 
		auto playerPosition = Ptr->GetPosition();											//!プレイヤーのポジションの取得 
		m_effectManager->ScratchEfkPlay(playerPosition);									//!エフェクトの再生

	}																						  
																							   
	void Player::OnPushB()																	   
	{
		
			Villagerkiller();
			Hunterkiller();
			BreakWoodBox();
			AttackEffect();
		
	}
}
//end basecross

