#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross
{
	namespace kaito
	{


		//!プレイヤーを発見したときの始めの追いかける処理-------------
		
		
	    //!インスタンスの生成(実体の作成)
		SurprisedState* SurprisedState::Instance()
		{
			static SurprisedState instance;
			return &instance;
		}


		void SurprisedState::Enter(BaseEnemy* Enemy)
		{
			//!ハンターの頭上にビックリマークのテクスチャを出す
			auto Player = Enemy->GetTarget();
			auto PlayerFound = Player->GetPlayerFound();
			PlayerFound = true;
			Player->SetPlayerFound(PlayerFound);


		}

		void SurprisedState::Execute(BaseEnemy* Enemy)
		{

			//!追いかける処理を書く
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得
			auto maxSpeed = Enemy->GetMaxSpeed();

			auto distance = PlayerPosition - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * maxSpeed;//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)
			Enemy->SetForce(Force);//!力を設定


			Vec3 PEvector = PlayerPosition - EnemyPosition;//!プレイヤーと敵のベクトルを取得
			auto Enemyfront = ptrEnemyTrans->GetForword();//!敵の正面を取得
			PEvector.normalize();//!プレイヤーと敵のベクトルを正規化
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
			auto chk = XM_PI / 6.0f;//!360を6で割って角度を出す。

			float f = bsm::length(PlayerPosition - EnemyPosition);//!プレイヤーと敵の距離

			
			if (f > BrettGramRange)//!プレイヤーと敵の距離より長くなったら
			{
				Enemy->ChangeState(BrettGramState::Instance());//!ステートを変更する
			}

			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!ステートを変更する
			}
		}
		void SurprisedState::Exit(BaseEnemy* Enemy)
		{
			//!首を振る動作をする
		}
		//!-----------------------------------------------------------
		
		//!追いかけるステート-----------------------------------------

		//!インスタンスの生成(実体の作成)
		SeekState* SeekState::Instance()
		{
			static SeekState instance;
			return &instance;
		}


		void SeekState::Enter(BaseEnemy* Enemy)
		{
			

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


			Vec3 PEvector = PlayerPosition - EnemyPosition;//!プレイヤーと敵のベクトルを取得
			auto Enemyfront = ptrEnemyTrans->GetForword();//!敵の正面を取得
			PEvector.normalize();//!プレイヤーと敵のベクトルを正規化
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!敵の正面とプレイヤーと敵のベクトルを取得し角度に変換
			auto chk = XM_PI / 6.0f;//!360を6で割って角度を出す。

			float f = bsm::length(PlayerPosition - EnemyPosition);//!プレイヤーと敵の距離

			if (f > SeekArriveRange)//!プレイヤーと敵の距離より長くなったら
			{
				if (angle <= chk && angle >= -chk)//!敵から見て+60度か-60度にプレイヤーが入ったら
				{
					Enemy->ChangeState(PatrolState::Instance());//!ステートを変更する
				}
			}
			if (f > BrettGramRange)//!プレイヤーと敵の距離より長くなったら
			{
				Enemy->ChangeState(BrettGramState::Instance());//!ステートを変更する
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
			//!ハンターの頭上にビックリマークのテクスチャを出す
			auto loseSightOfTarget=Enemy->GetloseSightOfTarget();
			loseSightOfTarget = true;
			Enemy->SetloseSightOfTarget(loseSightOfTarget);


		}


		void PatrolState::Execute(BaseEnemy* Enemy)
		{

			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得
			auto m_patrolPoints = Enemy->GetEnemyPatorolPoints();//!パトロールポイント
			auto maxSpeed = Enemy->GetMaxSpeed();

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!ターゲット(プレイヤー)のトランスフォームの取得
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!ターゲット(プレイヤー)の座標の取得

			//!パトロールポイントを配列に入れる
			std::vector<Vec3> patrol;
			for (auto& a : m_patrolPoints)
			{
				patrol.push_back(a);
			}

			auto& app = App::GetApp();//!アプリの取得
			float delta = app->GetElapsedTime();//!時間の取得
			auto patrolPoint = Enemy->GetEnemyPatorolindex();//!パトロールポイントのインデックスの取得
			Vec3 start = patrol[patrolPoint];//!スタートの位置にパトロールポイントを設定
			const int movePointsCount = patrol.size();//!パトロールポイントの配列の長さ
			Vec3 end = patrol[(patrolPoint + 1) % movePointsCount];//!敵が次に向かうポイントの設定

			auto distance = end - EnemyPosition;//!プレイヤーの座標から敵の座標を引きベクトルの計算
			distance.normalize();//!ベクトルをノーマライズ化
			auto Requiredspeed = distance * maxSpeed;//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)

			float pointdistance = bsm::length(end - EnemyPosition);//!敵が向かうポイントから敵までの距離



			if (pointdistance <= PatrolArriveRange)//!敵が向かうポイントから敵までの距離が一定の距離近づいたら
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
						Enemy->ChangeState(SurprisedState::Instance());//!ステートを変更する
					}
				}
			}

			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!ステートを変更する
			}
		}

		void PatrolState::Exit(BaseEnemy* Enemy)
		{}

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
		}

		void BrettGramState::Execute(BaseEnemy* Enemy)
		{
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!敵のトランスフォームの取得
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!敵のポジションの取得
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			Vec3 Force = Enemy->GetForce();//!敵の力の取得

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
			auto Requiredspeed = distance * Enemy->GetMaxSpeed();//!速度の取得
			Force += Requiredspeed - EnemyVelocity;//!最高速度を現在の速度で引く(旋回の速さなどの力が求まる)

			float Brettpointdistance = bsm::length(end - EnemyPosition);//!次に向かうブレットポイントと敵の位置の距離

			if (Brettpointdistance <= BrettGramArriveRange)//!二つの距離が５以下になった時
			{

				BrettGramindex++;//!次のポイントに移行する

				if (BrettGramindex == 49)//!インデックスが19だからそれを越えた時。
				{
					BrettGramindex = 0;//!配列の一番最初をさす。
				}
			}

			Enemy->SetForce(Force);//!力を設定
			float PEdistance = bsm::length(PlayerPosition - EnemyPosition);//!プレイヤーと敵の距離

			if (PEdistance <= 10.0f)//!5より近づいたら
			{
				Enemy->ChangeState(SeekState::Instance());//!ステートの変更
			}
			if (PEdistance >= 60)//!プレイヤーと敵の距離より長くなったら
			{
				Enemy->ChangeState(PatrolState::Instance());//!ステートを変更する
			}
		}
		void BrettGramState::Exit(BaseEnemy* Enemy)
		{}
		//!-------------------------------------------------------------
		
			//!殺されたときのステート-----------------------------------------

		//!インスタンスの生成(実体の作成)
		DedState* DedState::Instance()
		{
			static DedState instance;
			return &instance;

		}

		void DedState::Enter(BaseEnemy* Enemy)
		{
			auto maxSpeed = Enemy->GetMaxSpeed();
			maxSpeed = 0;

		}

		void DedState::Execute(BaseEnemy* Enemy)
		{
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!敵の速度の取得
			EnemyVelocity = Vec3(0);
			Enemy->SetVelocity(EnemyVelocity);
			Vec3 Force = Enemy->GetForce();//!敵の力の取得
			
			
		}
		void DedState::Exit(BaseEnemy* Enemy)
		{
			//!首を振る動作をする

		}

	
	}
}