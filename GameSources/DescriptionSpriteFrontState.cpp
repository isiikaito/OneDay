/*!
@file DescriptionSpriteFrontState.cpp
@brief 説明書のステート
@author Kaito Isii
*/

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
			
			m_moveTime = 0.0f;//!時間のリセット
		}

		void DescriptionSpriteFrontState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{

			

			auto& app = App::GetApp();											//!アプリの取得
			auto elapsedTime = app->GetElapsedTime();							//!時間の取得
			m_moveTime += elapsedTime* FlippingSpeed;							//!時間の更新
			auto transform = descriptionSpriteFront->GetComponent<Transform>();	//!説明書のトランスフォームの取得
			auto descriptionFrontPosition = transform->GetPosition();			//!説明書の位置
			descriptionFrontPosition.x -= m_moveTime;							//!説明書の位置を移動させる
			transform->SetPosition(descriptionFrontPosition);					//!説明書の位置を設定
			//!一定の位置を超えたら
			if (descriptionFrontPosition.x <=m_stateChangePositionX)
			{
				descriptionSpriteFront->ChangeState(DescriptionSpriteStandbyFrontState::Instance());//!ステートを変更する

			}

			
		}

		void DescriptionSpriteFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
		
			descriptionSpriteFront->SetDrawActive(false);	//!非表示
			descriptionSpriteFront->SetMoveTexture(false);	//!テクスチャを止める

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
		}

		void DescriptionSpriteStandbyFrontState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{
			
				if (descriptionSpriteFront->GetMoveTexture())//!テクスチャを動かす時
				{
					descriptionSpriteFront->ChangeState(DescriptionSpriteFrontState::Instance());//!ステートを変更する

				}
				if(descriptionSpriteFront->GetPageBackTo())//!ページを後ろにする
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

			m_moveTime = 0.0f;							//!時間の更新
			descriptionSpriteFront->SetDrawActive(true);//!非表示

		}

		void DescriptionPageBackToState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{
			auto& app = App::GetApp();											//!アプリの取得
			auto elapsedTime = app->GetElapsedTime();							//!時間の取得
			m_moveTime += elapsedTime * FlippingSpeed;							//!時間の更新
			auto transform = descriptionSpriteFront->GetComponent<Transform>();	//!説明書のトランスフォームの取得
			auto descriptionFrontPosition = transform->GetPosition();			//!説明書の位置の取得
			descriptionFrontPosition.x += m_moveTime;							//!説明書の位置を移動させる
			transform->SetPosition(descriptionFrontPosition);					//!説明書の位置を設定

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