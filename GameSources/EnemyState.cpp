#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross
{
	namespace kaito
	{
		//!追いかけるステート-----------------------------------------

		//!インスタンスの生成(実体の作成)
		SeekState* SeekState::Instance()
		{
			static SeekState instance;
			return &instance;
		}


		void SeekState::Enter(BaseEnemy* Enemy)
		{
			//!ハンターの頭上にビックリマークのテクスチャを出す

		}

		void SeekState::Execute(BaseEnemy* Enemy)
		{

			//!追いかける処理を書く
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得


			auto distance = PlayerPosition - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * Enemy->GetMaxSpeed();//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)
			Enemy->SetForce(Force);//!力を設定


			float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrEnemyTrans->GetPosition());

			if (f > SeekArriveRange)
			{
				Enemy->ChangeState(PatrolState::Instance());
			}


		}
		void SeekState::Exit(BaseEnemy* Enemy)
		{
			//!首を振る動作をする
		}

		//!巡回ステート-------------------------------------------------
		PatrolState* PatrolState::Instance()
		{
			static PatrolState instance;
			return &instance;
		}

		void PatrolState::Enter(BaseEnemy* Enemy)
		{

		}


		void PatrolState::Execute(BaseEnemy* Enemy)
		{
			//!巡回経路
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得
			auto m_patrolPoints = Enemy->GetEnemyPatorolPoints();
			
			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得

			std::vector<Vec3> patrol;
			for (auto a : m_patrolPoints)
			{
				patrol.push_back(a);
			}

			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();
			auto patrolPoint = Enemy->GetEnemyPatorolindex();

			Vec3 start = patrol[patrolPoint];

		
			const int movePointsCount = patrol.size();
			Vec3 end = patrol[(patrolPoint + 1) % movePointsCount];
			

			auto distance = end - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * Enemy->GetMaxSpeed();//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)

			float pointdistance = bsm::length(end - EnemyPosition);

			if (pointdistance <= PatrolArriveRange)
			{

				patrolPoint++;
			
				if (patrolPoint >= movePointsCount)
				{
					patrolPoint = 0;
				}
				Enemy->SetEnemyPatorolindex(patrolPoint);

			}
			Enemy->SetForce(Force);//!力を設定

			float f = bsm::length(PlayerPosition - EnemyPosition);

			if (f < PatrolArriveRange)
			{
				Enemy->ChangeState(SeekState::Instance());
			}
		}

		void PatrolState::Exit(BaseEnemy* Enemy)
		{

		}

		//!-------------------------------------------------------------

	}
}