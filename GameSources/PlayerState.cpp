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
		constexpr float MAXHUMANCHANGETIME = 31.0f;			//!人間の時の時間
		constexpr float MAXWOLFCHANGETIME = 62.0f;			//!狼の時の時間
		constexpr float NOTEALSPEED = 10.0f;					//!何も食べてない状態のスピード
		constexpr float FIRSTEAT = 15.0f;						//!一個食べた状態のスピード
		constexpr float SECONDEAT = 20.0f;					//!二個食べた状態のスピード
		constexpr float THIRDEAT = 23.0f;						//!三個食べた状態のスピード
		constexpr float HUMANSPEED = 24.0f;					//!人間の速度
		constexpr float PLAYERCHANGEDIRECTINHMAXTIME = 2.0f;	//!プレイヤーの変身時間
		constexpr float POSITIONRANGE = 10.0f;				//!位置の幅
		constexpr float CORRECTIONOFPOSITION = 8.6f;			//!位置の修正


		//!人間状態の時----------------------------------------------------------
		//!インスタンスの生成(実体の作成)
		HumanState* HumanState::Instance()
		{
			static HumanState instance;
			return &instance;
		}

		void HumanState::ReadCsv(const wstring& FileNume)
		{
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto scene = App::GetApp()->GetScene<Scene>();

			//!シーンの取得
			m_MeatNumber = scene->GetMeatNamber();

			// フォルダの指定
			auto csvDirectory = DataDir + L"csvFolder\\";
			//!MetaPositonファイルの読み込み
			m_MeatPositon.SetFileName(csvDirectory + FileNume + Util::IntToWStr(m_MeatNumber) + L".csv");
			m_MeatPositon.ReadCsv();

			m_HumanChangeTime = 0.0f;//!時間の更新

		}

		void HumanState::CreateMeat()
		{
			Vec3 scale = Vec3(5.0f);								//!大きさ
			Vec3 rotation = Vec3(0.0f);								//!回転
			ReadCsv(L"MeatPosition");								//!肉のCsvの取得
			auto& app = App::GetApp();								//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();	//!ステージの取得
			auto& Objects = Stage->GetGameObjectVec();				//!ステージの中のオブジェクトを取得
			//CSVの全体の配列
			//CSVからすべての行を抜き出す
			auto& LineVec = m_MeatPositon.GetCsvVec();

			for (size_t i = 0; i < LineVec.size(); i++) {
				//トークン（カラム）の配列
				vector<wstring> Tokens;
				//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
				Util::WStrToTokenVector(Tokens, LineVec[i], L',');
				for (size_t j = 0; j < Tokens.size(); j++) {
					//XとZの位置を計算
					float XPos = (float)((int)j - CORRECTIONOFPOSITION) * POSITIONRANGE;
					float YPos = 4.0f;
					float ZPos = (float)(CORRECTIONOFPOSITION - (int)i) * POSITIONRANGE;
					if (Tokens[j] == L"5")//5の時にゲームステージに追加
					{
						Stage->AddGameObject<Meat>(scale, rotation, Vec3(XPos, YPos, ZPos));//!肉の作成
					}
				}
			}
		}

		void HumanState::CreateWoodBox()
		{
			Vec3 scale = Vec3(9.0f);										//!大きさ
			Vec3 rotation = Vec3(0.0f);										//!回転
			auto& app = App::GetApp();										//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();			//!ステージの取得
			auto& Objects = Stage->GetGameObjectVec();						//!ステージの中のオブジェクトを取得
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);						//!データの取得
			auto scene = App::GetApp()->GetScene<Scene>();					//!シーンの取得
			auto csvDirectory = DataDir + L"csvFolder\\";					//フォルダの指定
			m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");	//!MetaPositonファイルの読み込み
			m_GameStageCsvD.ReadCsv();
			//CSVの全体の配列
		//CSVからすべての行を抜き出す
			auto& LineVec = m_GameStageCsvD.GetCsvVec();
			for (size_t i = 0; i < LineVec.size(); i++) {
				//トークン（カラム）の配列
				vector<wstring> Tokens;
				//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
				Util::WStrToTokenVector(Tokens, LineVec[i], L',');
				for (size_t j = 0; j < Tokens.size(); j++) {
					//XとZの位置を計算
					float XPos = (float)((int)j - CORRECTIONOFPOSITION) * POSITIONRANGE;
					float YPos = 3.0f;
					float ZPos = (float)(CORRECTIONOFPOSITION - (int)i) * POSITIONRANGE;
					if (Tokens[j] == L"3")//3の時にゲームステージに追加
					{
						//!木箱の作成
						Stage->AddGameObject<WoodenBox>(scale, rotation, Vec3(XPos, YPos, ZPos));
					}
				}
			}
		}

		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerChange();														//!プレイヤー状態の取得
			playerChange = PlayerModel::human;												//!状態を狼にする
			Player->SetPlayerChange(playerChange);																//!プレイヤーの状態の設定
			Player->SetMeatCount(0);																			//!肉を食べた数
			Player->SetPlayerTaskDay(true);																		//!プレイヤーのミッションの表示
			CreateWoodBox();																					//!木箱の作成
			CreateMeat();																						//肉の作成
			auto meatPosition = Player->GetMeatPosition();														//!肉のポジションの取得
			Player->SetMeatEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetMeatEfkEffect(), meatPosition));	//!エフェクトの再生
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
			auto gameTime = Player->GetGameTime();								//!ゲームの時間を取得する
			auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
			m_HumanChangeTime = scene->GetPlayerConditionTime();				//!変身時間
			//!ゲーム時間が30秒経過したら
			if (m_HumanChangeTime >= MAXHUMANCHANGETIME)
			{
				Player->ChangeState(HumanChangeDirectingState::Instance());//!狼のステートに変更
			}

		}

		void HumanState::Exit(Player* Player)
		{
			
			//m_HumanChangeTime = 0.0f;//!人間の時の時間を0秒にする
			

			
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

		void WolfState::RemoveWoodBox()
		{
			//!木の箱の削除
			auto& app = App::GetApp();								//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();	//!ステージの取得
			auto& Objects = Stage->GetGameObjectVec();				//!ステージの中のオブジェクトを取得
			for (auto& Obj : Objects)								//!オブジェクトの要素分
			{
				auto stageMeat = dynamic_pointer_cast<WoodenBox>(Obj);//!建物の取得
				if (stageMeat)
				{
					//!木箱の削除
					Stage->RemoveGameObject<WoodenBox>(Obj);
				}
			}
		}

		void WolfState::RemoveMeat()
		{
			//!肉の削除
			auto& app = App::GetApp();								//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();	//!ステージの取得
			auto& Objects = Stage->GetGameObjectVec();				//!ステージの中のオブジェクトを取得
			for (auto& Obj : Objects)//!オブジェクトの要素分
			{
				auto stageMeat = dynamic_pointer_cast<Meat>(Obj);//!建物の取得
				if (stageMeat)
				{
					//!肉の削除
					Stage->RemoveGameObject<Meat>(Obj);
				}
			}
		}

		WolfState* WolfState::Instance()
		{
			static WolfState instance;
			return &instance;
		}

		void WolfState::Enter(Player* Player)
		{

			auto playerChange = Player->GetPlayerChange();						//!プレイヤーの状態の取得
			playerChange = PlayerModel::wolf;					//!状態を狼にする
			Player->SetPlayerChange(playerChange);								//!プレイヤーの状態の設定
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!音量の取得
			//サウンド再生
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"howling", 0, volume);								//!再生
			RemoveMeat();
		}

		void WolfState::Execute(Player* Player)
		{


			auto WolfPlayerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();			//!プレイヤーの描画コンポ―ネントを取得
			auto shadowPtr = Player->GetComponent<Shadowmap>();							//!シャドウマップ
			shadowPtr->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH");				//!メッシュの変更
			WolfPlayerDraw->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");	//!プレイヤーのメッシュの変更
			float elapsedTime = App::GetApp()->GetElapsedTime();						//!エルパソタイムの取得
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();				//アニメーション
			ptrDraw->UpdateAnimation(elapsedTime);										//!アニメーションを更新
            auto scene = App::GetApp()->GetScene<Scene>();								//!シーンの取得
			m_WolfChangeTime = scene->GetPlayerConditionTime();							//!変身時間の取得
			//!オオカミ時間を過ぎたら
			if (m_WolfChangeTime >= MAXWOLFCHANGETIME)
			{
				Player->ChangeState(WolfChangeDirectingState::Instance());
			}
			
			MeatEat(Player);

		}

		void WolfState::Exit(Player* Player)
		{
			auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
			Player->SetMeatCount(0);						//!肉カウントのリセット
			m_Date++;										//!日付の更新
			scene->SetDate(m_Date);							//!日付の設定
			RemoveWoodBox();
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
			Player->SetPlayerTaskNight(true);	//!夜のミッションの表示
			Player->SetSpeed(0.0f);				//!スピードを停止させる
			//エフェクトのプレイ
			auto Ptr = Player->GetComponent<Transform>();//!トランスフォームの取得
			Player->SetTransformEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetTransformEfkEffect(), Ptr->GetPosition()));//!エフェクトの取得
			
			auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
			scene->SetPlayerChangeDirecting(true);			//!プレイヤーの変身を開始する
		
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
			auto Ptr = Player->GetComponent<Transform>();//!トランスフォームの取得
			Player->SetTransformEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetTransformEfkEffect(), Ptr->GetPosition()));//!エフェクトの取得
			auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
			scene->SetPlayerChangeDirecting(true);			//!プレイヤーの変身を開始する

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
		}

		void WolfChangeDirectingState::Exit(Player* Player)
		{
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");
			
			m_wolfChangeDirectingTiem = 0.0f;
		}
		//!----------------------------------------------------------


	}
}