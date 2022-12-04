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
			auto seekCondition=Enemy->GetseekCondition();
			seekCondition = true;
			Enemy->SetseekCondition(seekCondition);

		}

		void SeekState::Execute(BaseEnemy* Enemy)
		{

			//!追いかける処理を書く
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得
			auto maxSpeed = Enemy->GetMaxSpeed();//!敵の最大速度

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得

			auto distance = PlayerPosition - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * maxSpeed;//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)
			Enemy->SetForce(Force);//!力を設定

			float f = bsm::length(PlayerPosition - EnemyPosition);//!プレイヤーと敵の距離

			//!障害物の取得
			auto& app = App::GetApp();//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!ステージの取得
			auto Objects = Stage->GetGameObjectVec();//!ステージの中のオブジェクトを取得

			for (auto& Obj : Objects)//!オブジェクトの要素分
			{
				auto stageBuilding = dynamic_pointer_cast<StageBuilding>(Obj);//!建物の取得
				if (stageBuilding)
				{
					auto StageBuildingObb = stageBuilding->GetComponent<CollisionObb>()->GetObb();//!ステージの壁のObbの取得

					if (HitTest::SEGMENT_OBB(PlayerPosition, EnemyPosition, StageBuildingObb))//!カメラと視点の間に壁が入ったら
					{
						Enemy->ChangeState(BrettGramState::Instance());//!プレイヤーと敵の間に障害物が入ったときステートを変更する
					}
				}
			}

			//!敵が殺されたとき死亡のステートに切り替わる
			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!ステートを変更する
			}
		}
		void SeekState::Exit(BaseEnemy* Enemy)
		{
			auto seekCondition = Enemy->GetseekCondition();
			seekCondition = false;
			Enemy->SetseekCondition(seekCondition);
		}

		//!巡回ステート-------------------------------------------------
		PatrolState* PatrolState::Instance()
		{
			static PatrolState instance;
			return &instance;
		}

		void PatrolState::Enter(BaseEnemy* Enemy)
		{
			//!村人の頭上にビックリマークのテクスチャを出す
			auto loseSightOfTarget = Enemy->GetloseSightOfTarget();
			loseSightOfTarget = true;
			Enemy->SetloseSightOfTarget(loseSightOfTarget);

		}

		void PatrolState::Execute(BaseEnemy* Enemy)
		{
			
			//!敵のパラメーターの取得
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得
			auto m_patrolPoints = Enemy->GetEnemyPatorolPoints();//!パトロールポイント
			auto maxSpeed = Enemy->GetMaxSpeed();//!敵の最大速度の取得
			auto patrolPoint = Enemy->GetEnemyPatorolindex();//!パトロールポイントのインデックスの取得
			//1プレイヤーのパラメーターの取得
			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得

			//!巡回する処理
			const int movePointsCount = m_patrolPoints.size();//!パトロールポイントの配列の長さ
			Vec3 end = m_patrolPoints[(patrolPoint + 1) % movePointsCount];//!敵が次に向かうポイントの設定
			auto distance = end - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * maxSpeed;//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)

			float pointdistance = bsm::length(end - EnemyPosition);//!敵が向かうポイントから敵までの距離

			if (pointdistance <= 5)//!敵が向かうポイントから敵までの距離が一定の距離近づいたら
			{

				patrolPoint++;//!次のポイントに移動

				if (patrolPoint >= movePointsCount)//!パトロール配列の最後の要素になったら。
				{
					patrolPoint = 0;//!パトロール配列の最初の要素に戻す
				}
				Enemy->SetEnemyPatorolindex(patrolPoint);//!パトロールポイントのインデックスを設定する

			}
			Enemy->SetForce(Force);//!力を設定


			Vec3 PEvector = PlayerPosition - EnemyPosition;//!プレイヤーと敵のベクトルを取得
			auto Enemyfront = ptrEnemyTrans->GetForword();//!敵の正面を取得
			PEvector.normalize();//!プレイヤーと敵のベクトルを正規化
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
			auto chk = XM_PI / 6.0f;//!360を6で割って角度を出す。
			float f = bsm::length(PlayerPosition - EnemyPosition);//!敵とプレイヤーの距離

			auto playerChange = Enemy->GetTarget()->GetPlayerCange();

			if (playerChange == static_cast<int>(PlayerModel::wolf))
			{
				if (angle <= chk && angle >= -chk)//!敵から見て+60度か-60度にプレイヤーが入ったら
				{
					if (f < PatrolArriveRange)//!敵とプレイヤーの距離が一定距離近づいたら
					{
						Enemy->ChangeState(SeekState::Instance());//!ステートを変更する
					}
				}
			}
			//!敵が殺されたとき
			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!ステートを変更する
			}
		}

		void PatrolState::Exit(BaseEnemy* Enemy)
		{
			//!村人の頭上にビックリマークのテクスチャを出す
			auto Player = Enemy->GetTarget();
			auto PlayerFound = Player->GetPlayerFound();
			PlayerFound = true;
			Player->SetPlayerFound(PlayerFound);
		
			m_lostTime = 0.0f;
			m_IspositionLiset = false;
			Enemy->SetIspositionLiset(m_IspositionLiset);
		}

		//!-------------------------------------------------------------

	   //!ブレットグラムステート---------------------------------------
		BrettGramState* BrettGramState::Instance()
		{
			static BrettGramState instance;
			return &instance;
		}

		void BrettGramState::Enter(BaseEnemy* Enemy)
		{
			BrettGramindex = 0;

			auto m_BrettGramPoints = Enemy->GetTarget()->GetPlayerPositionOnSecond();//!プレイヤーの毎秒取得している位置の取得
			for (int i = 0; i < m_BrettGramPoints.size(); i++)
			{
				auto EnemyPosition = Enemy->GetComponent<Transform>()->GetPosition();//!敵の位置の取得
				auto pointdistance = bsm::length(m_BrettGramPoints[i] - EnemyPosition);//!ブレットブラムのポイントと敵の位置から近さを取得
				if (Neardistance > pointdistance)//!他の近いポイントより今のポイントが近かったら
				{
					Vec3 NearPoint = m_BrettGramPoints[i];//!今のポイントが一番近い
					start = NearPoint;//!ブレットクラムのスタートをそこに決定
				}
			}

			auto seekCondition = Enemy->GetseekCondition();
			seekCondition = true;
			Enemy->SetseekCondition(seekCondition);
			m_lostTime = 0l;
		}

		void BrettGramState::Execute(BaseEnemy* Enemy)
		{
			BrettGramindex = 0;
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得
			auto maxSpeed = Enemy->GetMaxSpeed();

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得

			auto m_BrettGramPoints = Enemy->GetTarget()->GetPlayerPositionOnSecond();//!プレイヤーの毎秒ごとの位置の取得

			if (m_BrettGramPoints.size() == 0) //!配列の中身がない時
			{
				return;
			}

			start = m_BrettGramPoints[BrettGramindex];//!最初のブレットクラムポイントの設定
			const int movePointsCount = m_BrettGramPoints.size();//!ブレットクラムの配列の大きさ
			Vec3 end = m_BrettGramPoints[(BrettGramindex + 1) % movePointsCount];//!敵が向かうポイントの設定

			auto distance = end - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * maxSpeed;//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)

			float Brettpointdistance = bsm::length(end - EnemyPosition);//!次に向かうブレットポイントと敵の位置の距離

			if (Brettpointdistance <= BrettGramArriveRange)//!二つの距離が５以下になった時
			{
				BrettGramindex++;//!次のポイントに移行する

				if (BrettGramindex == maxBrettGramindex)//!インデックスが19だからそれを越えた時。
				{
					BrettGramindex = 0;//!配列の一番最初をさす。
				}
			}

			Enemy->SetForce(Force);//!力を設定
			float PEdistance = bsm::length(PlayerPosition - EnemyPosition);//!プレイヤーと敵の距離

			//!敵の視野
			Vec3 PEvector = PlayerPosition - EnemyPosition;//!プレイヤーと敵のベクトルを取得
			auto Enemyfront = ptrEnemyTrans->GetForword();//!敵の正面を取得
			PEvector.normalize();//!プレイヤーと敵のベクトルを正規化
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
			auto chk = XM_PI / 9.0f;//!360を6で割って角度を出す。
			if (angle <= chk && angle >= -chk)//!敵から見て+60度か-60度にプレイヤーが入ったら
			{
				if (PEdistance >= 100)
				{
					Enemy->ChangeState(SeekState::Instance());//!ステートを変更する
				}
			}

			//!障害物の取得
			auto& app = App::GetApp();//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!ステージの取得
			auto Objects = Stage->GetGameObjectVec();//!ステージの中のオブジェクトを取得

			for (auto& Obj : Objects)//!オブジェクトの要素分
			{
				auto stageBuilding = dynamic_pointer_cast<StageBuilding>(Obj);//!建物の取得
				if (stageBuilding)
				{
					auto StageBuildingObb = stageBuilding->GetComponent<CollisionObb>()->GetObb();//!ステージの壁のObbの取得

					if (HitTest::SEGMENT_OBB(PlayerPosition, EnemyPosition, StageBuildingObb))//!カメラと視点の間に壁が入ったら
					{
						auto time=app->GetElapsedTime();
						m_lostTime += time;
						if ( PEdistance>=37&&m_lostTime >= 3)
						{
                               Enemy->ChangeState(PatrolState::Instance());//!ステートの変更
						}
						if ( PEdistance <= 37&&m_lostTime >= 3)
						{
							m_lostTime = 0.0f;
						}
						
					}
				}
			}


			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!ステートを変更する
			}

		}
		void BrettGramState::Exit(BaseEnemy* Enemy)
		{
			auto seekCondition = Enemy->GetseekCondition();
			seekCondition = false;
			Enemy->SetseekCondition(seekCondition);
		}
		//!-------------------------------------------------------------

		//!殺されたときのステート-----------------------------------------

		//!インスタンスの生成(実体の作成)
		DedState* DedState::Instance()
		{
			static DedState instance;
			return &instance;

		}

		void DedState::Enter(BaseEnemy* Enemy)
		{}

		void DedState::Execute(BaseEnemy* Enemy)
		{
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			EnemyVelocity = Vec3(0);
			Enemy->SetVelocity(EnemyVelocity);
			


		}
		void DedState::Exit(BaseEnemy* Enemy)
		{
			//!首を振る動作をする

		}


	}
}
//!見失うときは範囲外に行ってから数秒追いかけてから見失う処理をした方がいい
