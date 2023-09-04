#include "stdafx.h"
#include "Project.h"
#include "GameManagerState.h"
#include "Meat.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float MAXDEDTIME = 1.0f;					//!倒れるまでの時間
		constexpr float MAXHUMANCHANGETIME = 31.0f;			//!人間の時の時間
		constexpr float MAXWOLFCHANGETIME = 62.0f;			//!狼の時の時間
		constexpr float PLAYERCHANGEDIRECTINHMAXTIME = 2.0f;//!プレイヤーの変身時間
		constexpr float POSITIONRANGE = 10.0f;				//!位置の幅
		constexpr float CORRECTIONOFPOSITION = 8.6f;		//!位置の修正

		//!オープニングカメラの時
		OpeningCameraPlayState* OpeningCameraPlayState::Instance()
		{
			static OpeningCameraPlayState instance;
			return &instance;
		}

		void OpeningCameraPlayState::Enter(GameManager* gameManager)
		{
			
		}

		void OpeningCameraPlayState::Execute(GameManager* gameManager)
		{
			auto player = gameManager->GetPlayer();
			player->SetUpdateActive(false);
			auto& app = App::GetApp();					//!アプリの取得
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!ステージの取得
			app->GetScene<Scene>()->GetGameOver();
			auto gameStrat = app->GetScene<Scene>()->GetGameStrat();				  //!オープニングカメラの時かどうか
			if (gameStrat == false)
			{
				gameManager->ChangeState(MiddayState::Instance());//!ステートを変更する

			}
			
		}

		void OpeningCameraPlayState::Exit(GameManager* gameManager)
		{
			auto player = gameManager->GetPlayer();
			player->SetUpdateActive(true);

		}



		//!昼間の時
		MiddayState* MiddayState::Instance()
		{
			static MiddayState instance;
			return &instance;
		}

		void MiddayState::Enter(GameManager* gameManager)
		{
			
			CreateMeat();
		}

		void MiddayState::Execute(GameManager* gameManager)
		{

			auto scene = App::GetApp()->GetScene<Scene>();						//!シーンの取得
			m_middayTime = scene->GetPlayerConditionTime();				//!変身時間
			//!ゲーム時間が30秒経過したら
			if (m_middayTime >= MAXHUMANCHANGETIME)
			{
				gameManager->ChangeState(NightState::Instance());//!狼のステートに変更
			}

			auto playerHp = gameManager->GetPlayer()->GetPlayerHp();
			if (playerHp <= 0)
			{
				gameManager->ChangeState(GameOverState::Instance());//!ステートを変更する

			}

		}

		void MiddayState::Exit(GameManager* gameManager)
		{

		}


		void MiddayState::ReadCsv(const wstring& FileNume)
		{
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto scene = App::GetApp()->GetScene<Scene>();

			//!シーンの取得
			m_MeatNumber = scene->GetMeatNamber();

			// フォルダの指定
			auto csvDirectory = DataDir + L"csvFolder\\"+L"MeatPosition\\";
			//!MetaPositonファイルの読み込み
			m_MeatPositon.SetFileName(csvDirectory + FileNume + Util::IntToWStr(m_MeatNumber) + L".csv");
			m_MeatPositon.ReadCsv();

			m_middayTime = 0.0f;//!時間の更新

		}

		void MiddayState::CreateMeat()
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



		//!夜の時
		NightState* NightState::Instance()
		{
			static NightState instance;
			return &instance;
		}

		void NightState::Enter(GameManager* gameManager)
		{
			RemoveMeat();
		}

		void NightState::Execute(GameManager* gameManager)
		{

			auto scene = App::GetApp()->GetScene<Scene>();								//!シーンの取得
			m_nightTime = scene->GetPlayerConditionTime();								//!変身時間の取得
			//!オオカミ時間を過ぎたら
			if (m_nightTime >= MAXWOLFCHANGETIME)
			{
				gameManager->ChangeState(MiddayState::Instance());
			}

			auto playerHp = gameManager->GetPlayer()->GetPlayerHp();
			if (playerHp <= 0)
			{
				gameManager->ChangeState(GameOverState::Instance());//!ステートを変更する

			}

		}

		void NightState::Exit(GameManager* gameManager)
		{
			auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
			m_Date++;										//!日付の更新
			scene->SetDate(m_Date);							//!日付の設定

		}

		
		void NightState::RemoveMeat()
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

		//!ゲームオーバーの時
		GameOverState* GameOverState::Instance()
		{
			static GameOverState instance;
			return &instance;
		}

		void GameOverState::Enter(GameManager* gameManager)
		{
			auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
			auto gameOverSprite = scene->GetGameOverSprite();		//!ゲームオーバー判定の取得
			gameOverSprite = true;							//!ゲームオーバーにする
			scene->SetGameOverSprite(gameOverSprite);
			
		}

		void GameOverState::Execute(GameManager* gameManager)
		{

			float Time = App::GetApp()->GetElapsedTime();//!経過時間の取得
			m_dedTime += Time;							 //!プレイヤーが倒れる時間に加算

			//!倒れる時間になったら
			if (m_dedTime >= MAXDEDTIME)
			{
				auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
				auto gameOver = scene->GetGameOver();		//!ゲームオーバー判定の取得
				gameOver = true;							//!ゲームオーバーにする
				scene->SetGameOver(gameOver);
				auto player = gameManager->GetPlayer();
				player->SetUpdateActive(false);
			}

		}

		void GameOverState::Exit(GameManager* gameManager)
		{

		}


	}
}
