/*!
@file BaseEnemy.cpp
@brief 敵の親の実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float m_maxRotationTime = 4.0f;//!見渡す時間
	constexpr int m_randomRange = 6;//!乱数の上限
	constexpr int m_randomNumber = 4;//!特定の乱数
	constexpr float m_rotToHead = 1.0f;//!正面を向く値
	//!-------------------------------------
	//! 敵のオブジェクトの親
	//! ------------------------------------

	//!構造と破棄
	BaseEnemy::BaseEnemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Force(0),
		m_Velocity(0),
		m_MaxSpeed(20),
		m_StateChangeSize(20.0f),
		m_Enemypatorolindex(0),
		m_loseSightOfTarget(false),
		m_IsEnemyDed(false),
		m_eyeRange(0),
		m_IspositionLiset(false),
		m_SurprisedSprite(false),
		m_seekCondition(false),
		m_surprisedTime(0.0f),
		m_patrolRotation(false),
		m_rotationTime(0.0f),
		m_randomTime(0.0f),
		m_randomCount(0),
		m_dedAnimationEnd(false)
	{
		m_StateMachine = new kaito::StateMachine<BaseEnemy>(this);
		m_StateMachine->SetCurrentState(kaito::PatrolState::Instance());
	}

	
	void BaseEnemy::ApplyForce()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force * elapsedTime;
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += m_Velocity * elapsedTime;
		ptrTrans->SetPosition(pos);
	}

	void BaseEnemy::ChangeState(kaito::State<BaseEnemy>* NewState)
	{

		m_StateMachine->ChangeState(NewState);
	}

	shared_ptr<Player>BaseEnemy::GetTarget()const {
		return std::dynamic_pointer_cast<Player>(GetStage()->GetSharedObject(L"Player"));
	}


	void BaseEnemy::HunterDisappear()
	{

		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!村人のオブジェクトグループの取得
		auto& vecHunter = group->GetGroupVector();//!ゲームオブジェクトの配列の取得
		//!村人配列オブジェクトの配列分回す
		for (auto& v : vecHunter)
		{
			auto hunterPtr = v.lock();//!村人のグループから1つロックする
			Vec3 ret;//!最近接点の代入
			auto ptrHunter = dynamic_pointer_cast<Hunter>(hunterPtr);//!ロックした物を取り出す
			if (ptrHunter)
			{
				auto hunterSpeed = ptrHunter->GetSpeed();//!村人のスピードを取得
				if (hunterSpeed == 0.0f)
				{

					GetStage()->RemoveGameObject<Hunter>(ptrHunter);
					m_dedAnimationEnd = false;

				}
			}

		}


	}

	void BaseEnemy::VillagerDisappear()
	{


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

				auto VillagerSpeed = ptrVillager->GetSpeed();//!村人のスピードを取得
				if (VillagerSpeed == 0.0f)
				{

					GetStage()->RemoveGameObject<Villager>(VillagerPtr);
					m_dedAnimationEnd = false;

				}
			}
		}

	}

	void BaseEnemy::AnimationUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//アニメーション
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void BaseEnemy::ObstacleAvoidance()
	{
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!障害物を避ける行動
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());
	}

	void BaseEnemy::Facade()
	{
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(m_rotToHead);
	}

	void BaseEnemy::EnemyRandomRotation()
	{
		auto& app = App::GetApp();//!アプリの取得
		auto time = app->GetElapsedTime();//!時間の取得
		m_randomTime += time;//!ランダムタイムに時間を足す

		srand(0);//!乱数の初期化
		m_randomCount = rand() % m_randomRange;

		//!ランダムに変わる変数が特定の数字に変わったとき
		if (m_randomCount == m_randomNumber)
		{
			m_patrolRotation = true;//!敵の見渡す処理をtrueにする
		}

		if (m_patrolRotation == true)
		{
			auto EnemyTransform = GetComponent<Transform>();//!敵のトランスコンフォームコンポーネントを取得
			auto elapsdTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
			m_rotationTime += elapsdTime;//!変数に毎フレームエルパソタイムを足す
			EnemyTransform->SetRotation(0, m_rotationTime, 0);//!Y軸の回転を変更

			//!周り終わったら回転の処理を実行しない
			if (m_rotationTime >= m_maxRotationTime)
			{
				m_patrolRotation = false;
			}

			//!追いかけているときは回転の処理を実行しない
			if (m_seekCondition == true)
			{
				m_patrolRotation = false;
			}

		}

	}

	void BaseEnemy::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto playerChange = scene->GetPlayerChangeDirecting();//!プレイヤーの変身を開始する
		auto gameOver = scene->GetGameOver();
		//!ゲームオーバーになっていないとき
		if (!gameOver)
		{
			//!プレイヤーが返信していないとき
			if (!playerChange)
			{
				//!倒れたアニメーション終了後
				if (m_dedAnimationEnd)
				{
					VillagerDisappear();//!村人を消す
					HunterDisappear();//!ハンターを消す
				}


				AnimationUpdate();//!アニメーションの更新

				m_StateMachine->Update();//!ステートマシンの更新

				ObstacleAvoidance();//!障害物回避

				EnemyRandomRotation();//!周りを見渡す
				//!見渡していないとき
				if (m_patrolRotation == false)
				{
					m_rotationTime = 0.0f;
					ApplyForce();//!適応力
				}

				m_Force = Vec3(0);

				Facade();//!進行方向を向く

			}
		}
	}

}