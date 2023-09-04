#include "stdafx.h"
#include "Project.h"
#include "WoodenBoxState.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float MAXHUMANCHANGETIME = 31.0f;			//!�l�Ԃ̎��̎���
		constexpr float MAXWOLFCHANGETIME = 62.0f;			//!�T�̎��̎���

		//!���Ԃ̎�
		WoodenBoxMiddayState* WoodenBoxMiddayState::Instance()
		{
			static WoodenBoxMiddayState instance;
			return &instance;
		}

		void WoodenBoxMiddayState::Enter(WoodenBox* woodenBox)
		{
			woodenBox->GetComponent<CollisionObb>()->SetUpdateActive(true);	//!�����蔻��𖳂���
			woodenBox->SetDrawActive(true);									//!���f���̕\��������

		}

		void WoodenBoxMiddayState::Execute(WoodenBox* woodenBox)
		{

			auto scene = App::GetApp()->GetScene<Scene>();					//!�V�[���̎擾
			m_middayTime = scene->GetPlayerConditionTime();					//!�ϐg�܂ł̎���
			//!�Q�[�����Ԃ�30�b�o�߂�����
			if (m_middayTime >= MAXHUMANCHANGETIME)
			{
				woodenBox->ChangeState(WoodenBoxNightState::Instance());//!�T�̃X�e�[�g�ɕύX
			}


		}
		void WoodenBoxMiddayState::Exit(WoodenBox* woodenBox)
		{
		}

		//!��̎�
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

			auto scene = App::GetApp()->GetScene<Scene>();								//!�V�[���̎擾
			m_nightTime = scene->GetPlayerConditionTime();								//!�ϐg�܂ł̎��Ԃ̎擾
			//!�Q�[�����Ԃ�61�b�o�߂�����
			if (m_nightTime >= MAXWOLFCHANGETIME)
			{
				woodenBox->ChangeState(WoodenBoxMiddayState::Instance());
			}

			

		}

		void WoodenBoxNightState::Exit(WoodenBox* woodenBox)
		{

		}




		//!�j�󂳂ꂽ��
		WoodenBoxBreakState* WoodenBoxBreakState::Instance()
		{
			static WoodenBoxBreakState instance;
			return &instance;
		}

		void WoodenBoxBreakState::Enter(WoodenBox* woodenBox)
		{
			woodenBox->GetComponent<CollisionObb>()->SetUpdateActive(false);	//!�����蔻��𖳂���
			woodenBox->SetDrawActive(false);									//!���f���̕\��������

		}

		void WoodenBoxBreakState::Execute(WoodenBox* woodenBox)
		{



			auto scene = App::GetApp()->GetScene<Scene>();								//!�V�[���̎擾
			m_nightTime = scene->GetPlayerConditionTime();								//!�ϐg�܂ł̎��Ԃ̎擾
			//!�Q�[�����Ԃ�61�b�o�߂�����
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