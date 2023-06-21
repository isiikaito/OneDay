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

namespace basecross {
	constexpr float m_maxDedTime = 1.0f;			    //!倒れるまでの時間
	constexpr float m_vibrationMaxTime = 1.0f;			//!振動する時間
	constexpr int m_Day = 7;							//!ゲームオーバーまでの日にち
	constexpr int m_soundLoop = 1;						//!音のループ
	constexpr int m_notsoundLoop = 0;					//!サウンドループ無し
	constexpr float m_escapeSphereRadius = 10.0f;		//!プレイヤーを中心とした円の半径
	constexpr float m_villagerkillerSphereRadius = 5.0f;//!村人を倒す時の円の半径
	constexpr float m_breakWoodBoxSphereRadius = 5.0f;	//!木箱を倒す時の円の半径
	constexpr float m_hunterkillerSphereRadius = 5.0f;	//!ハンターを倒す時の円の半径
	constexpr float m_angleEqual = 6.0f;				//!視野の制限
	constexpr float m_rotToHead = 1.0f;					//!正面
	constexpr float m_targetToAtY = 0.25f;				//!カメラの視点位置のy
	constexpr WORD  m_maxVibration = 65535;				//!振動の大きさ
	constexpr int m_movestartSample = 0;				//!動くアニメーションの開始フレーム
	constexpr int m_movesampleLength = 30;				//!動くアニメーションの長さ
	constexpr float m_movesamplesParSecond = 20.0f;		//!動くアニメーションの再生速度
	constexpr int m_defaultstartSample = 31;			//!待機アニメーションの開始フレーム
	constexpr int m_defaultsampleLength = 30;			//!待機アニメーションの長さ
	constexpr float m_defaultsamplesParSecond = 10.0f;	//!待機アニメーションの再生速度
	constexpr int m_dedstartSample = 61;				//!倒れるアニメーションの開始フレーム
	constexpr int m_dedsampleLength = 45;				//!倒れるアニメーションの長さ
	constexpr float m_dedsamplesParSecond = 30.0f;		//!倒れるアニメーションの再生速度
	constexpr int m_changestartSample = 91;				//!変身アニメーションの開始フレーム
	constexpr int m_changesampleLength = 60;			//!変身アニメーションの長さ
	constexpr float m_changesamplesParSecond = 30.0f;	//!変身アニメーションの再生速度
	

	

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
		m_IsPlayerDed(0.0f),
		m_gameOverDrawActive(false),
		m_vibration(0),
		m_gameTime(0.0f),
		m_meatCount(0),
		m_vibrationTime(0.0f),
		m_IsvibrationOn(false),
		m_playerTaskDay(true),
		m_playerTaskNight(false),
		m_IsPlayerChangeEffect(true),
		m_scale(Vec3(3.0f, 3.0f, 3.0f)),
		m_rotation(Vec3(0.0f, 0.0f, 0.0f)),
		m_position(Vec3(0.0f, 4.0f, -90.0f))
	{
		m_StateMachine = new kaito::StateMachine<Player>(this);
		m_StateMachine->SetCurrentState(kaito::HumanState::Instance());	//!現在のステート
	}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//!コントローラの取得
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		//!接続されているコントローラ
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;//!左スティックx座標
			ret.y = cntlVec[0].fThumbLY;//!左スティックy座標
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
			float moveLength = 0;											//!動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();					//!トランスフォームの取得
			auto& ptrCamera = OnGetDrawCamera();							//!カメラの取得
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();	//!進行方向の向きを計算
			front.y = 0;
			front.normalize();												//!進行方向の向きを正規化
			float frontAngle = atan2(front.z, front.x);						//!進行方向向きからの角度を算出
			Vec2 moveVec(moveX, moveZ);										//!コントローラの向き計算
			float moveSize = moveVec.length();								//!動く大きさ
			float cntlAngle = atan2(-moveX, moveZ);							//!コントローラの向きから角度を計算
			float totalAngle = frontAngle + cntlAngle;						//!トータルの角度を算出
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));				//!角度からベクトルを作成
			angle.normalize();												//!正規化する
			angle *= moveSize;												//!移動サイズを設定
			angle.y = 0;													//!Y軸は変化させない
		}
		return angle;
	}

	
	void Player::MovePlayer() {

		
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();			 //アニメーション
		auto& AnimationName = ptrDraw->GetCurrentAnimation();			 //!現在のアニメーション
		float elapsedTime = App::GetApp()->GetElapsedTime();			 //!エルパソタイムの取得
		auto angle = GetMoveVector();									 //!ベクトルの取得
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!効果音量
		//!スティックが傾いていたら
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();		 //!自身のポジションの取得
			pos += angle * elapsedTime * m_Speed;						 //!ポジションの更新
			GetComponent<Transform>()->SetPosition(pos);				 //!ポジションの設定

			//歩くアニメーション
			//!待機モーションか変身モーションの時
			if (AnimationName == L"Default" || AnimationName == L"Change") {
				ptrDraw->ChangeCurrentAnimation(L"Move");				//!アニメーションを変える
				auto& XAptr = App::GetApp()->GetXAudio2Manager();		//!サウンドマネージャーの取得
				m_Wolk = XAptr->Start(L"WalkBGM", m_soundLoop, volume);	//歩く音再生
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
			utilPtr->RotToHead(angle, m_rotToHead);		//!正面を向く
		}
	}

	//!初期化
	void Player::OnCreate() {

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring keyEffectStr = DataDir + L"Effects\\key.efk";										//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
		auto EfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();							//!エフェクトのインターフェースの取得
		m_KeyEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, keyEffectStr);				//!取得したエフェクトで作る

		wstring ScratchEffectStr = DataDir + L"Effects\\kill.efk";									//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
		m_ScratchEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, ScratchEffectStr);		//!取得したエフェクトで作る

		wstring TransformEffectStr = DataDir + L"Effects\\Transform2.efk";							//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
		m_TransformEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, TransformEffectStr);	//!取得したエフェクトで作る

		wstring MeatEffectStr = DataDir + L"Effects\\smoke.efk";									//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
		m_MeatEfkEffect = ObjectFactory::Create<EfkEffect>(EfkInterface, MeatEffectStr);			//!取得したエフェクトで作る


		//!初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_scale);			//!大きさ
		ptr->SetRotation(m_rotation);	//!回転
		ptr->SetPosition(m_position);	//!位置


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),		//!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),		//!回転
			Vec3(0.0f, -1.0f, 0.0f)		//!位置
		);

		auto ptrColl = AddComponent<CollisionCapsule>();																//!CollisionSphere衝突判定を付ける
		auto ptrGra = AddComponent<Gravity>();																			//!重力をつける
		auto shadowPtr = AddComponent<Shadowmap>();																		//!影をつける（シャドウマップを描画する）
		shadowPtr->SetMeshResource(L"Player_WalkAnimation2_MESH");														//!影の形（メッシュ）を設定
		shadowPtr->SetMeshToTransformMatrix(spanMat);																	//!メッシュの大きさ設定
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();															//!描画コンポーネントの設定
		ptrDraw->SetMeshResource(L"Player_WalkAnimation2_MESH_WITH_TAN");												//!描画するメッシュを設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);																		//!メッシュの大きさ設定
		ptrDraw->AddAnimation(L"Move", m_movestartSample, m_movesampleLength, true, m_movesamplesParSecond);			//!歩くアニメーションの登録
		ptrDraw->AddAnimation(L"Default", m_defaultstartSample, m_defaultsampleLength, true, m_defaultsamplesParSecond);//!待機アニメーションの登録
		ptrDraw->AddAnimation(L"Ded", m_dedstartSample, m_dedsampleLength, false, m_dedsamplesParSecond);				//!倒れるアニメーションの登録
		ptrDraw->AddAnimation(L"Change", m_changestartSample, m_changesampleLength, false, m_changesamplesParSecond);	//!変身アニメーションの登録
		ptrDraw->ChangeCurrentAnimation(L"Default");																	//!現在のアニメーションの設定
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");														//!法線マップの設定

		

			//!カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {

			ptrCamera->SetTargetObject(GetThis<GameObject>());	//!MyCameraである
			ptrCamera->SetTargetToAt(Vec3(0, m_targetToAtY, 0));//!MyCameraに注目するオブジェクト（プレイヤー）の設定
		}
	}

	

	void Player::PlayerGameOver()
	{
		auto scene=App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto gameOver = scene->GetGameOver();		//!ゲームオーバー判定の取得
		gameOver = true;							//!ゲームオーバーにする
		scene->SetGameOver(gameOver);				//!ゲームオーバーにする

		
		float Time = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		m_dedTime += Time;							 //!倒れる時間に加算
		//!倒れる時間になったら
		if (m_dedTime >= m_maxDedTime)
		{
			m_gameOverDrawActive = true;			//!ゲームオーバー画面を表示
		}

	}

	void Player::PlayerDed()
	{
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();	//!描画コンポーネントの取得
		auto& AnimationName = ptrDraw->GetCurrentAnimation();	//!現在のアニメーションの取得
		float elapsedTime = App::GetApp()->GetElapsedTime();	//!エルパソタイムの取得

		//立ち止まるアニメーション
		if (AnimationName == L"Move" || AnimationName == L"Default")
		{
			ptrDraw->ChangeCurrentAnimation(L"Ded");			//!アニメーションをDedに変更
			auto& XAptr = App::GetApp()->GetXAudio2Manager();	//!サウンドマネージャーの取得
			XAptr->Stop(m_Wolk);								//!歩くサウンドを止める

		}
		PlayerGameOver();
	}

	

	void Player::EnemyDedSound()
	{
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!効果音量の取得
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();				 //!サウンドマネージャーの取得
		ptrXA->Start(L"kill", m_notsoundLoop, volume);					 //!倒したときのサウンドの開始
		ptrXA->Start(L"scream", m_notsoundLoop, volume);				 //!攻撃のサウンドの開始
	}

	void Player::Hunterkiller()
	{
		auto transComp = GetComponent<Transform>();						  //!トランスフォームを取得
		auto position = transComp->GetPosition();						  //!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, m_hunterkillerSphereRadius);			  //!プレイヤーの座標を中心に半径5センチの円の作成
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
			auto HunterTrans = GetComponent<Transform>();				 //!ハンターのトランスフォームの取得
			auto HunterPosition = HunterTrans->GetPosition();            //!ハンターのポジションの取得
			Vec3 PEvector = position - HunterPosition;					 //!プレイヤーと敵のベクトルを取得
			PEvector.normalize();										 //!プレイヤーと敵のベクトルを正規化
			auto Enemyfront = HunterTrans->GetForword();				 //!敵の正面を取得
			auto angle = angleBetweenNormals(-Enemyfront, PEvector);     //!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
			auto chk = XM_PI / m_angleEqual;							 //!360を6で割って角度を出す。
		

			//!プレイヤーの範囲に敵がはいったら
			if (ptrHunter)
			{
				auto HunterCapsrul = ptrHunter->GetComponent<CollisionCapsule>()->GetCapsule();//!ハンタ-のObbオブジェクトを取得
                
				//!プレイヤーの周りを囲んでいるスフィアに当たったら
				if (HitTest::SPHERE_CAPSULE(playerSp, HunterCapsrul, ret))
				{
					
						auto HunterSpeed = ptrHunter->GetSpeed();//!村人のスピードを取得
						//!ハンターの速度が0ではないとき
						if (HunterSpeed != m_Ded)
						{
							HunterSpeed = m_Ded;						//!村人のスピードを０にする
							ptrHunter->SetSpeed(HunterSpeed);			//!村人のスピードを設定
							alertlevelCount++;							//!危険度を上げる
							scene->SetAlertlevelCount(alertlevelCount); //!危険度を更新
							EnemyDedSound();
						}
					
				}
			}

		}
	}

	void Player::OneWeek()
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
		auto Date = scene->GetDate();					//!日付の取得
		//!ゲームオーバーの日付になったら
		if (Date == m_Day)
		{
			PlayerGameOver();//!ゲームオーバー
		}

	}

	void Player::BreakWoodBox()
	{
		auto transComp = GetComponent<Transform>();							//!トランスフォームを取得
		auto position = transComp->GetPosition();							//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, m_breakWoodBoxSphereRadius);				//!プレイヤーの座標を中心に半径2センチの円の作成
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
				auto WoodBoxOBB = ptrWoodBox->GetComponent<CollisionObb>()->GetObb();//!ハンタ-のObbオブジェクトを取得
				//!プレイヤーの周りを囲んでいるスフィアに当たったら
				if (HitTest::SPHERE_OBB(playerSp, WoodBoxOBB, ret))					 
				{
					auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!効果音量の取得
					GetStage()->RemoveGameObject<WoodenBox>(ptrWoodBox);			 //!木箱を消す
					
					auto& ptrXA = App::GetApp()->GetXAudio2Manager();				 //サウンド再生
					ptrXA->Start(L"WoodBoxBreak", m_notsoundLoop, volume);
					
				}
			}
		}
	}

	//!村人を倒す処理
	void Player::Villagerkiller()
	{
		auto transComp = GetComponent<Transform>();							//!トランスフォームを取得
		auto position = transComp->GetPosition();							//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, m_villagerkillerSphereRadius);			//!プレイヤーの座標を中心に半径2センチの円の作成
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
					
					auto VillagerSpeed = ptrVillager->GetSpeed();									//!村人のスピードを取得
					//!村人の速度が停止していなかったら
					if (VillagerSpeed != m_Ded)
					{
						VillagerSpeed = m_Ded;						//!村人のスピードを０にする
						ptrVillager->SetSpeed(VillagerSpeed);		//!村人のスピードを設定
						alertlevelCount++;							//!危険度を上げる
						scene->SetAlertlevelCount(alertlevelCount); //!危険度を設定

						EnemyDedSound();
					}
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
		auto transComp = GetComponent<Transform>();						//!トランスフォームを取得
		auto position = transComp->GetPosition();						//!現在のプレイヤーの位置の取得
		SPHERE playerSp(position, m_escapeSphereRadius);				//!プレイヤーの座標を中心に半径2センチの円の作成

		auto gate = GetStage()->GetSharedGameObject<StageGate>(L"Gate");//!門を取得
		Vec3 ret;														//!最近接点の代入
		auto gateObb = gate->GetComponent<CollisionObb>()->GetObb();	//!コリジョンの衝突判定
		if (HitTest::SPHERE_OBB(playerSp, gateObb, ret))				//!プレイヤーの周りを囲んでいるスフィアに当たったら
		{
			auto& XAptr = App::GetApp()->GetXAudio2Manager();			//!サウンドマネージャーの取得
			XAptr->Stop(m_Wolk);										//!歩く音の停止
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//!ゲームクリアステージに遷移
		}
	}

	

	void Player::ChangeState(kaito::State<Player>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!ステートを変更する
	}

	
	void Player::Controllervibration()
	{
		

		//!振動がオンになっているとき
		if (m_IsvibrationOn == true)
		{
			auto Time = App::GetApp()->GetElapsedTime();//!時間の取得
			m_vibrationTime += Time;					//!振動させる時間
             m_vibration = m_maxVibration;				//!現在の振動の大きさ
			//!振動する時間経ったら
			if (m_vibrationTime >= m_vibrationMaxTime)
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

	//更新
	void Player::OnUpdate() {
		if (m_playerChange == static_cast<int>(PlayerModel::human))
		{
			//!プレイヤーが鍵を持っていたら
			if (m_KeyCount == m_MaxKeyCount)
			{
				Escape();
			}
		}

		m_StateMachine->Update();							//!ステートマシンの更新
		OneWeek();
		Controllervibration();
		auto scene = App::GetApp()->GetScene<Scene>();		//!シーンの取得
		auto gameOver = scene->GetGameOver();				//!ゲームオーバーかどうかの取得
		auto gameTime = scene->GetGameTime();				//!ゲーム時間の取得
		m_gameTime += gameTime;								//!時間の加算

		
		float elapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//アニメーション
		ptrDraw->UpdateAnimation(elapsedTime);				//!アニメーションの更新

		
		
		auto playerChange = scene->GetPlayerChangeDirecting();//!プレイヤーの変身を開始する
		auto gameStrat = scene->GetGameStrat();				  //!オープニングカメラの時かどうか
	
		//!ゲームオーバーになってない時に
		if (!gameOver)
		{
			GetPlayerPositionBrett();
			//!プレイヤーが変身していない時
			if (!playerChange)
			{
				//!オープニングカメラではない時
				if (!gameStrat)
				{
					MovePlayer();
				}

			}
			//!変身しているかオープニングカメラの時
			if(playerChange|| gameStrat)
			{
				auto& XAptr = App::GetApp()->GetXAudio2Manager();//!サウンドマネージャーの取得
				XAptr->Stop(m_Wolk);							 //!歩く音を止める
			}
				
		}
		
		//!プレイヤーが倒れた時
		if (m_IsPlayerDed == true)
		{
			PlayerDed();
		}

		//!HPが無くなったとき
		if (m_PlayerHp == m_Ded)
		{
			PlayerGameOver();
		}
            m_InputHandlerB.PushHandleB(GetThis<Player>());//!Bボタンのインプットハンドラの追加
	    }



	//!プレイヤーが相手に当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		
		auto ptrKey = dynamic_pointer_cast<Key>(Other);//!鍵の取得

		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!効果音量の取得
		if (m_playerChange == static_cast<int>(PlayerModel::wolf))
		{
			//!プレイヤーが鍵に当たったら
			if (ptrKey)
			{

				m_KeyCount++;																		//!鍵のカウント
				GetStage()->RemoveGameObject<Key>(Other);											//!鍵オブジェクトの削除
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!サウンドマネージャーの取得
				ptrXA->Start(L"acquisition", m_notsoundLoop, volume);								//!サウンドの再生
				auto Ptr = ptrKey->GetComponent<Transform>();										//!エフェクトのプレイ
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					//!エフェクトインターフェースの取得
				m_KeyEfkPlay = ObjectFactory::Create<EfkPlay>(m_KeyEfkEffect, Ptr->GetPosition());	//!エフェクトのポジション

			}


		}

		auto ptrMeat = dynamic_pointer_cast<Meat>(Other);//!肉の取得

		if (m_playerChange == static_cast<int>(PlayerModel::human))
		{
			//!プレイヤーが肉に当たったら
			if (ptrMeat)
			{
				m_meatCount++;
				GetStage()->RemoveGameObject<Meat>(Other);											//!鍵オブジェクトの削除
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();									//!サウンドマネージャーの取得
				ptrXA->Start(L"MeatEat", m_notsoundLoop, volume);									//!肉を食べるサウンドの再生
				auto Ptr = GetComponent<Transform>();												//!トランスフォームの取得
				auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					//!エフェクトインターフェースの取得
				m_MeatEfkPlay = ObjectFactory::Create<EfkPlay>(m_MeatEfkEffect, Ptr->GetPosition());//!エフェクトの作成
				auto manager=ShEfkInterface->GetManager();											//!マネージャーの取得
				
			}


		}

	}

	void Player::AttackEffect()
	{
		//エフェクトのプレイ
		auto Ptr = GetComponent<Transform>();                                                 //!トランスフォームの取得
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();					  //!エフェクトインターフェースの取得 
		auto playerPosition = Ptr->GetPosition();											  //!プレイヤーのポジションの取得 
		m_ScratchEfkPlay = ObjectFactory::Create<EfkPlay>(m_ScratchEfkEffect, playerPosition);//!エフェクトの作成
	}																						  
																							   
	void Player::OnPushB()																	   
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
		auto gameOver = scene->GetGameOver();			//!ゲームオーバーの取得
		//!ゲームオーバーになってない時に
		if (gameOver == false)
		{
			//!オオカミの姿になったとき
			if (m_playerChange == static_cast<int>(PlayerModel::wolf))
			{
				Villagerkiller();
				Hunterkiller();
				BreakWoodBox();
				AttackEffect();
			}

		}
	}
}
//end basecross

