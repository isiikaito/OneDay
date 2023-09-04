/*!
@file PlayerState.cpp
@brief プレイヤーのステート
@author Kaito Isii
*/
#include "stdafx.h"
#include "Project.h"
#include "Utility.h"
#include "PlayerState.h"
#include "Meat.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float MAXHUMANCHANGETIME = 31.0f;				//!人間の時の時間
		constexpr float MAXWOLFCHANGETIME = 62.0f;				//!狼の時の時間
		constexpr float NOTEALSPEED = 10.0f;					//!何も食べてない状態のスピード
		constexpr float FIRSTEAT = 15.0f;						//!一個食べた状態のスピード
		constexpr float SECONDEAT = 20.0f;						//!二個食べた状態のスピード
		constexpr float THIRDEAT = 23.0f;						//!三個食べた状態のスピード
		constexpr float HUMANSPEED = 24.0f;						//!人間の速度
		constexpr float PLAYERCHANGEDIRECTINHMAXTIME = 2.0f;	//!プレイヤーの変身時間
		constexpr int MaxKeyCount = 3;							//!カギの最大個数

		//!人間状態の時----------------------------------------------------------
		//!インスタンスの生成(実体の作成)
		HumanState* HumanState::Instance()
		{
			static HumanState instance;
			return &instance;
		}

		
		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerChange();														//!プレイヤー状態の取得
			playerChange = PlayerModel::human;												//!状態を狼にする
			Player->SetPlayerChange(playerChange);																//!プレイヤーの状態の設定
			Player->SetPlayerTaskDay(true);																		//!プレイヤーのミッションの表示
			Player->SetSpeed(HUMANSPEED);																		//!プレイヤーの時のスピード

		}

		void HumanState::Execute(Player* Player)
		{	
			float elapsedTime = App::GetApp()->GetElapsedTime();				//!エルパソタイムの取得
			auto playerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();		//!描画コンポーネントの取得
			auto shadowPtr = Player->GetComponent<Shadowmap>();					//!シャドウコンポーネントの取得
			shadowPtr->SetMeshResource(L"Player_WalkAnimation2_MESH");			//!プレイヤーのメッシュの変更
			playerDraw->SetMeshResource(L"Player_WalkAnimation2_MESH_WITH_TAN");//!プレイヤーのメッシュの変更
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();		//アニメーション
			ptrDraw->UpdateAnimation(elapsedTime);								//!アニメーションの更新
			auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
			m_HumanChangeTime = scene->GetPlayerConditionTime();				//!変身時間

			//!プレイヤーが鍵を持っていたら
			if (Player->GetKeyCount() == MaxKeyCount)
			{
				Player->Escape();
			}

			//!ゲーム時間が30秒経過したら
			if (m_HumanChangeTime >= MAXHUMANCHANGETIME)
			{
				Player->ChangeState(HumanChangeDirectingState::Instance());//!狼のステートに変更
			}

			if (Player->GetPlayerHp() == 0 || Player->GetIsplayerDed() == true)
			{
				Player->ChangeState(PlayerDedState::Instance());//!死亡のステートに変更
			}

		}

		void HumanState::Exit(Player* Player)
		{
			
		}
		//-------------------------------------------------------------------------

		//!狼男の状態の時----------------------------------------------------------

		void WolfState::MeatEat(Player* Player)
		{

			
			auto meatCount = Player->GetMeatCount();//!プレイヤーが食べた肉の数

			switch (meatCount)
			{
			case(static_cast<int>(EatCondition::notEat)):
				Player->SetSpeed(NOTEALSPEED);
				break;
			case(static_cast<int>(EatCondition::firstEat)):
				Player->SetSpeed(FIRSTEAT);
				break;
			case(static_cast<int>(EatCondition::secondEat)):
				Player->SetSpeed(SECONDEAT);
				break;
			case(static_cast<int>(EatCondition::thirdEat)):
				Player->SetSpeed(THIRDEAT);
				break;
			}
		}

		
		WolfState* WolfState::Instance()
		{
			static WolfState instance;
			return &instance;
		}

		void WolfState::Enter(Player* player)
		{

			auto playerChange = player->GetPlayerChange();						//!プレイヤーの状態の取得
			playerChange = PlayerModel::wolf;									//!状態を狼にする
			player->SetPlayerChange(playerChange);								//!プレイヤーの状態の設定
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!音量の取得
			//サウンド再生
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"howling", 0, volume);								//!再生
			auto& app = App::GetApp();//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!ステージの取得
			m_player = Stage->GetSharedGameObject<Player>(L"Player");
		}

		void WolfState::Execute(Player* player)
		{
			

			m_InputHandlerB.PushHandleB(m_player.lock());//!Bボタンのインプットハンドラの追加
			auto WolfPlayerDraw = player->GetComponent<BcPNTnTBoneModelDraw>();			//!プレイヤーの描画コンポ―ネントを取得
			auto shadowPtr = player->GetComponent<Shadowmap>();							//!シャドウマップ
			shadowPtr->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH");				//!メッシュの変更
			WolfPlayerDraw->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");	//!プレイヤーのメッシュの変更
			float elapsedTime = App::GetApp()->GetElapsedTime();						//!エルパソタイムの取得
			auto ptrDraw = player->GetComponent<BcPNTnTBoneModelDraw>();				//アニメーション
			ptrDraw->UpdateAnimation(elapsedTime);										//!アニメーションを更新
            auto scene = App::GetApp()->GetScene<Scene>();								//!シーンの取得
			m_WolfChangeTime = scene->GetPlayerConditionTime();							//!変身時間の取得
			//!オオカミ時間を過ぎたら
			if (m_WolfChangeTime >= MAXWOLFCHANGETIME)
			{
				player->ChangeState(WolfChangeDirectingState::Instance());
			}

			if (player->GetPlayerHp() == 0|| player->GetIsplayerDed()==true)
			{
				player->ChangeState(PlayerDedState::Instance());//!死亡のステートに変更
			}
			
			

			MeatEat(player);

		}

		void WolfState::Exit(Player* Player)
		{
			Player->SetMeatCount(0);						//!肉カウントのリセット
			
		}

		//!	-------------------------------------------------------------------------------------

		//!人間から狼に変身するときの演出ステート-------------------------------------------------
		HumanChangeDirectingState* HumanChangeDirectingState::Instance()
		{
			static HumanChangeDirectingState instance;
			return &instance;
		}

		void HumanChangeDirectingState::Enter(Player* Player)
		{
			Player->SetPlayerTaskNight(true);									//!夜のミッションの表示
			Player->SetSpeed(0.0f);												//!スピードを停止させる
			auto position = Player->GetComponent<Transform>()->GetPosition();	//!トランスフォームの取得
			Player->GetEffectManager()->PlayerChangeEfkPlay(position);			//!変身エフェクト			
			auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
			scene->SetPlayerChangeDirecting(true);								//!プレイヤーの変身を開始する
		
		}

		void HumanChangeDirectingState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();			//!アプリの取得
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//!描画コンポーネントの取得
			auto& AnimationName = ptrDraw->GetCurrentAnimation();		//!現在のアニメーション
			//!人から狼になるときのアニメーションモデル
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Change");
			}

			auto scene = App::GetApp()->GetScene<Scene>();
			m_humanChangeDirectingTiem += elapsedTime;//!ゲームの時間を変数に足す
			if (m_humanChangeDirectingTiem>= PLAYERCHANGEDIRECTINHMAXTIME)
			{
				Player->ChangeState(WolfState::Instance());//!狼のステートに変更
			}

			if (Player->GetPlayerHp() == 0)
			{
				Player->ChangeState(PlayerDedState::Instance());//!死亡のステートに変更
			}
		}

		void HumanChangeDirectingState::Exit(Player* Player)
		{
			m_humanChangeDirectingTiem = 0.0f;
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");

		}
		//!----------------------------------------------------------
		
		//!狼から人間に変身するときの演出ステート-------------------------------------------------
		WolfChangeDirectingState* WolfChangeDirectingState::Instance()
		{
			static WolfChangeDirectingState instance;
			return &instance;
		}

		void WolfChangeDirectingState::Enter(Player* Player)
		{

			Player->SetSpeed(0.0f);
			//エフェクトのプレイ
			auto position = Player->GetComponent<Transform>()->GetPosition();	//!トランスフォームの取得
			Player->GetEffectManager()->PlayerChangeEfkPlay(position);			//!変身エフェクト
			auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
			scene->SetPlayerChangeDirecting(true);								//!プレイヤーの変身を開始する

		}

		void WolfChangeDirectingState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();//!アプリの取得
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();
			auto& AnimationName = ptrDraw->GetCurrentAnimation();

			//!狼から人になるときのアニメーションモデル
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Change");
			}

			//!狼から人間に変身する時のアニメーションモデル 
			auto scene = App::GetApp()->GetScene<Scene>();
			m_wolfChangeDirectingTiem += elapsedTime;//!ゲームの時間を変数に足す
			if (m_wolfChangeDirectingTiem>= PLAYERCHANGEDIRECTINHMAXTIME)
			{
				Player->ChangeState(HumanState::Instance());//!狼のステートに変更
			}

			if (Player->GetPlayerHp() == 0)
			{
				Player->ChangeState(PlayerDedState::Instance());//!死亡のステートに変更
			}

		}

		void WolfChangeDirectingState::Exit(Player* Player)
		{
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");
			
			m_wolfChangeDirectingTiem = 0.0f;
		}
		//!----------------------------------------------------------


		
			//!プレイヤーが死んだときのステート-------------------------------------------------
		PlayerDedState* PlayerDedState::Instance()
		{
			static PlayerDedState instance;
			return &instance;
		}

		void PlayerDedState::Enter(Player* Player)
		{
			Player->SetPlayerHp(0);//!プレイヤーのHpを0にする
			Player->SetSpeed(0.0f);//!プレイヤーの速度を0にする
		}

		void PlayerDedState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();			//!アプリの取得
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//!描画処理
			auto& AnimationName = ptrDraw->GetCurrentAnimation();		//!アニメーションの取得

			//!狼から人になるときのアニメーションモデル
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				ptrDraw->ChangeCurrentAnimation(L"Ded");			//!アニメーションをDedに変更
				auto& XAptr = App::GetApp()->GetXAudio2Manager();	//!サウンドマネージャーの取得
				XAptr->Stop(Player->GetWolkSound());								//!歩くサウンドを止める
			}

			
		}

		void PlayerDedState::Exit(Player* Player)
		{

		}
		//!----------------------------------------------------------
	}
}