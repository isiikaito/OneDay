#include "stdafx.h"
#include "Project.h"
#include "Utility.h"
#include "DescriptionSpriteFrontState.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float FlippingSpeed = 10.0f;
		

		//!�C���X�^���X�̐���(���̂̍쐬)
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

			

			auto& app = App::GetApp();//!�A�v���̎擾
			auto elapsedTime = app->GetElapsedTime();//!���Ԃ̎擾
			m_moveTime += elapsedTime* FlippingSpeed;
			auto transform = descriptionSpriteFront->GetComponent<Transform>();
			auto descriptionFrontPosition = transform->GetPosition();
			descriptionFrontPosition.x -= m_moveTime;
			transform->SetPosition(descriptionFrontPosition);

			if (descriptionFrontPosition.x <=m_stateChangePositionX)
			{
				descriptionSpriteFront->ChangeState(DescriptionSpriteStandbyFrontState::Instance());//!�X�e�[�g��ύX����

			}

			
		}

		void DescriptionSpriteFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
		
			descriptionSpriteFront->SetMoveTexture(false);

		}
		//-------------------------------------------------------------------------



		//!�C���X�^���X�̐���(���̂̍쐬)
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
					descriptionSpriteFront->ChangeState(DescriptionSpriteFrontState::Instance());//!�X�e�[�g��ύX����

				}

		}

		void DescriptionSpriteStandbyFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
			

		}








		

	}
}