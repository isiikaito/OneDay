#include "stdafx.h"
#include "Project.h"
#include "WoodenBoxState.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float MAXHUMANCHANGETIME = 31.0f;			//!人間の時の時間
		constexpr float MAXWOLFCHANGETIME = 62.0f;			//!狼の時の時間

		//!昼間の時
		WoodenBoxMiddayState* WoodenBoxMiddayState::Instance()
		{
			static WoodenBoxMiddayState instance;
			return &instance;
		}

		void WoodenBoxMiddayState::Enter(WoodenBox* woodenBox)
		{
			woodenBox->GetComponent<CollisionObb>()->SetUpdateActive(true);	//!当たり判定を無くす
			woodenBox->SetDrawActive(true);									//!モデルの表示をする

		}

		void WoodenBoxMiddayState::Execute(WoodenBox* woodenBox)
		{

			auto scene = App::GetApp()->GetScene<Scene>();					//!シーンの取得
			m_middayTime = scene->GetPlayerConditionTime();					//!変身までの時間
			//!ゲーム時間が30秒経過したら
			if (m_middayTime >= MAXHUMANCHANGETIME)
			{
				woodenBox->ChangeState(WoodenBoxNightState::Instance());//!狼のステートに変更
			}


		}
		void WoodenBoxMiddayState::Exit(WoodenBox* woodenBox)
		{
		}

		//!夜の時
		WoodenBoxNightState* WoodenBoxNightState::Instance()
		{
			static WoodenBoxNightState instance;
			return &instance;
		}

		void WoodenBoxNightState::Enter(WoodenBox* woodenBox)
		{
		}

		void WoodenBoxNightState::Execute(WoodenBox* woodenBox)
		{

			auto scene = App::GetApp()->GetScene<Scene>();								//!シーンの取得
			m_nightTime = scene->GetPlayerConditionTime();								//!変身までの時間の取得
			//!ゲーム時間が61秒経過したら
			if (m_nightTime >= MAXWOLFCHANGETIME)
			{
				woodenBox->ChangeState(WoodenBoxMiddayState::Instance());
			}

			

		}

		void WoodenBoxNightState::Exit(WoodenBox* woodenBox)
		{

		}




		//!破壊された時
		WoodenBoxBreakState* WoodenBoxBreakState::Instance()
		{
			static WoodenBoxBreakState instance;
			return &instance;
		}

		void WoodenBoxBreakState::Enter(WoodenBox* woodenBox)
		{
			woodenBox->GetComponent<CollisionObb>()->SetUpdateActive(false);	//!当たり判定を無くす
			woodenBox->SetDrawActive(false);									//!モデルの表示をする

		}

		void WoodenBoxBreakState::Execute(WoodenBox* woodenBox)
		{



			auto scene = App::GetApp()->GetScene<Scene>();								//!シーンの取得
			m_nightTime = scene->GetPlayerConditionTime();								//!変身までの時間の取得
			//!ゲーム時間が61秒経過したら
			if (m_nightTime >= MAXWOLFCHANGETIME)
			{
				woodenBox->ChangeState(WoodenBoxMiddayState::Instance());
			}



		}

		void WoodenBoxBreakState::Exit(WoodenBox* woodenBox)
		{

		}
		
	}
}