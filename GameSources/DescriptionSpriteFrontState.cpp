#include "stdafx.h"
#include "Project.h"
#include "Utility.h"
#include "DescriptionSpriteFrontState.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float FlippingSpeed = 20.0f;//!説明書が動く速度
		

		//!インスタンスの生成(実体の作成)
		DescriptionSpriteFrontState* DescriptionSpriteFrontState::Instance()
		{
			static DescriptionSpriteFrontState instance;
			return &instance;
		}



		void  DescriptionSpriteFrontState::Enter(DescriptionSpriteFront* descriptionSpriteFront)
		{
			
			m_moveTime = 0.0f;
		}

		void DescriptionSpriteFrontState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{

			

			auto& app = App::GetApp();//!アプリの取得
			auto elapsedTime = app->GetElapsedTime();//!時間の取得
			m_moveTime += elapsedTime* FlippingSpeed;
			auto transform = descriptionSpriteFront->GetComponent<Transform>();
			auto descriptionFrontPosition = transform->GetPosition();
			descriptionFrontPosition.x -= m_moveTime;
			transform->SetPosition(descriptionFrontPosition);

			if (descriptionFrontPosition.x <=m_stateChangePositionX)
			{
				descriptionSpriteFront->ChangeState(DescriptionSpriteStandbyFrontState::Instance());//!ステートを変更する

			}

			
		}

		void DescriptionSpriteFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
		
			descriptionSpriteFront->SetDrawActive(false);
			descriptionSpriteFront->SetMoveTexture(false);

		}
		//-------------------------------------------------------------------------



		//!インスタンスの生成(実体の作成)
		DescriptionSpriteStandbyFrontState* DescriptionSpriteStandbyFrontState::Instance()
		{
			static DescriptionSpriteStandbyFrontState instance;
			return &instance;
		}



		void  DescriptionSpriteStandbyFrontState::Enter(DescriptionSpriteFront* descriptionSpriteFront)
		{
			/*auto transform = descriptionSpriteFront->GetComponent<Transform>();
			transform->SetPosition(m_textureResetPosition);*/

			


		}

		void DescriptionSpriteStandbyFrontState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{
			
				if (descriptionSpriteFront->GetMoveTexture())
				{
					descriptionSpriteFront->ChangeState(DescriptionSpriteFrontState::Instance());//!ステートを変更する

				}
				if(descriptionSpriteFront->GetPageBackTo())
				{

					descriptionSpriteFront->ChangeState(DescriptionPageBackToState::Instance());//!ステートを変更する

					
				}


		}

		void DescriptionSpriteStandbyFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
			

		}




		//!インスタンスの生成(実体の作成)
		DescriptionPageBackToState* DescriptionPageBackToState::Instance()
		{
			static DescriptionPageBackToState instance;
			return &instance;
		}



		void  DescriptionPageBackToState::Enter(DescriptionSpriteFront* descriptionSpriteFront)
		{

			m_moveTime = 0.0f;
			descriptionSpriteFront->SetDrawActive(true);

		}

		void DescriptionPageBackToState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{



			auto& app = App::GetApp();//!アプリの取得
			auto elapsedTime = app->GetElapsedTime();//!時間の取得
			m_moveTime += elapsedTime * FlippingSpeed;
			auto transform = descriptionSpriteFront->GetComponent<Transform>();
			auto descriptionFrontPosition = transform->GetPosition();
			descriptionFrontPosition.x += m_moveTime;
			transform->SetPosition(descriptionFrontPosition);

			if (descriptionFrontPosition.x >= m_stateChangePositionX)
			{
				descriptionSpriteFront->ChangeState(DescriptionSpriteStandbyFrontState::Instance());//!ステートを変更する

			}


		}

		void DescriptionPageBackToState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{

			descriptionSpriteFront->SetPageBackTo(false);

		}
		//-------------------------------------------------------------------------


	}
}