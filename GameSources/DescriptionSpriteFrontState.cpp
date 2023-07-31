/*!
@file DescriptionSpriteFrontState.cpp
@brief �������̃X�e�[�g
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
		constexpr float FlippingSpeed = 20.0f;//!���������������x
		

		//!�C���X�^���X�̐���(���̂̍쐬)
		DescriptionSpriteFrontState* DescriptionSpriteFrontState::Instance()
		{
			static DescriptionSpriteFrontState instance;
			return &instance;
		}



		void  DescriptionSpriteFrontState::Enter(DescriptionSpriteFront* descriptionSpriteFront)
		{
			
			m_moveTime = 0.0f;//!���Ԃ̃��Z�b�g
		}

		void DescriptionSpriteFrontState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{

			

			auto& app = App::GetApp();											//!�A�v���̎擾
			auto elapsedTime = app->GetElapsedTime();							//!���Ԃ̎擾
			m_moveTime += elapsedTime* FlippingSpeed;							//!���Ԃ̍X�V
			auto transform = descriptionSpriteFront->GetComponent<Transform>();	//!�������̃g�����X�t�H�[���̎擾
			auto descriptionFrontPosition = transform->GetPosition();			//!�������̈ʒu
			descriptionFrontPosition.x -= m_moveTime;							//!�������̈ʒu���ړ�������
			transform->SetPosition(descriptionFrontPosition);					//!�������̈ʒu��ݒ�
			//!���̈ʒu�𒴂�����
			if (descriptionFrontPosition.x <=m_stateChangePositionX)
			{
				descriptionSpriteFront->ChangeState(DescriptionSpriteStandbyFrontState::Instance());//!�X�e�[�g��ύX����

			}

			
		}

		void DescriptionSpriteFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
		
			descriptionSpriteFront->SetDrawActive(false);	//!��\��
			descriptionSpriteFront->SetMoveTexture(false);	//!�e�N�X�`�����~�߂�

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
		}

		void DescriptionSpriteStandbyFrontState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{
			
				if (descriptionSpriteFront->GetMoveTexture())//!�e�N�X�`���𓮂�����
				{
					descriptionSpriteFront->ChangeState(DescriptionSpriteFrontState::Instance());//!�X�e�[�g��ύX����

				}
				if(descriptionSpriteFront->GetPageBackTo())//!�y�[�W�����ɂ���
				{

					descriptionSpriteFront->ChangeState(DescriptionPageBackToState::Instance());//!�X�e�[�g��ύX����

					
				}


		}
		void DescriptionSpriteStandbyFrontState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{
		}

		//!�C���X�^���X�̐���(���̂̍쐬)
		DescriptionPageBackToState* DescriptionPageBackToState::Instance()
		{
			static DescriptionPageBackToState instance;
			return &instance;
		}

		void  DescriptionPageBackToState::Enter(DescriptionSpriteFront* descriptionSpriteFront)
		{

			m_moveTime = 0.0f;							//!���Ԃ̍X�V
			descriptionSpriteFront->SetDrawActive(true);//!��\��

		}

		void DescriptionPageBackToState::Execute(DescriptionSpriteFront* descriptionSpriteFront)
		{
			auto& app = App::GetApp();											//!�A�v���̎擾
			auto elapsedTime = app->GetElapsedTime();							//!���Ԃ̎擾
			m_moveTime += elapsedTime * FlippingSpeed;							//!���Ԃ̍X�V
			auto transform = descriptionSpriteFront->GetComponent<Transform>();	//!�������̃g�����X�t�H�[���̎擾
			auto descriptionFrontPosition = transform->GetPosition();			//!�������̈ʒu�̎擾
			descriptionFrontPosition.x += m_moveTime;							//!�������̈ʒu���ړ�������
			transform->SetPosition(descriptionFrontPosition);					//!�������̈ʒu��ݒ�

			if (descriptionFrontPosition.x >= m_stateChangePositionX)
			{
				descriptionSpriteFront->ChangeState(DescriptionSpriteStandbyFrontState::Instance());//!�X�e�[�g��ύX����

			}


		}

		void DescriptionPageBackToState::Exit(DescriptionSpriteFront* descriptionSpriteFront)
		{

			descriptionSpriteFront->SetPageBackTo(false);

		}
		//-------------------------------------------------------------------------


	}
}