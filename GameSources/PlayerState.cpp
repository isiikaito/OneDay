#include "stdafx.h"
#include "Project.h"
#include "Utility.h"
#include "PlayerState.h"
namespace basecross
{
	namespace kaito
	{
		constexpr float m_maxHumanChangeTime = 31.0f;
		constexpr float m_maxWolfChangeTime = 61.0f;

		//!�l�ԏ�Ԃ̎�----------------------------------------------------------
		//!�C���X�^���X�̐���(���̂̍쐬)
		HumanState* HumanState::Instance()
		{
			static HumanState instance;
			return &instance;
		}

		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerCange();
			playerChange = static_cast<int>(PlayerModel::human);//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);
		}

		void HumanState::Execute(Player* Player)
		{
			auto playerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();
			auto shadowPtr = Player->GetComponent<Shadowmap>();

			shadowPtr->SetMeshResource(L"Player_WalkAnimation_MESH");
			playerDraw->SetMeshResource(L"Player_WalkAnimation_MESH_WITH_TAN");//!�v���C���[�̃��b�V���̕ύX

			float elapsedTime = App::GetApp()->GetElapsedTime();
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
			ptrDraw->UpdateAnimation(elapsedTime);

			auto gameTime=Player->GetGameTime();

			auto scene = App::GetApp()->GetScene<Scene>();
			m_HumanChangeTime+=scene->GetGameTime();
			if (m_HumanChangeTime >= m_maxHumanChangeTime)
			{
				Player->ChangeState(WolfState::Instance());
			}

		}

		void HumanState::Exit(Player* Player)
		{
			m_HumanChangeTime = 0.0f;
		}
		//-------------------------------------------------------------------------


		//!�T�j�̏�Ԃ̎�----------------------------------------------------------
		WolfState* WolfState::Instance()
		{
			static WolfState instance;
			return &instance;
		}

		void WolfState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerCange();
			playerChange = static_cast<int>(PlayerModel::wolf);//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);

			//�T�E���h�Đ�
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"howling", 0, 1.0f);

		}

		void WolfState::Execute(Player* Player)
		{
			auto WolfPlayerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//!�v���C���[�̕`��R���|�\�l���g���擾
			auto shadowPtr = Player->GetComponent<Shadowmap>();
			shadowPtr->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH");
			WolfPlayerDraw->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");//!�v���C���[�̃��b�V���̕ύX

			float elapsedTime = App::GetApp()->GetElapsedTime();
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
			ptrDraw->UpdateAnimation(elapsedTime);



			

			auto scene = App::GetApp()->GetScene<Scene>();
			m_WolfChangeTime += scene->GetGameTime();
			if (m_WolfChangeTime >= m_maxHumanChangeTime)
			{
				Player->ChangeState(HumanState::Instance());
			}


		}

		void WolfState::Exit(Player* Player)
		{
			m_WolfChangeTime = 0.0f;
		}
        //-------------------------------------------------------------------------
	}
}