/*!
@file PlayerState.cpp
@brief �v���C���[�̃X�e�[�g
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
		constexpr float MAXHUMANCHANGETIME = 31.0f;				//!�l�Ԃ̎��̎���
		constexpr float MAXWOLFCHANGETIME = 62.0f;				//!�T�̎��̎���
		constexpr float NOTEALSPEED = 10.0f;					//!�����H�ׂĂȂ���Ԃ̃X�s�[�h
		constexpr float FIRSTEAT = 15.0f;						//!��H�ׂ���Ԃ̃X�s�[�h
		constexpr float SECONDEAT = 20.0f;						//!��H�ׂ���Ԃ̃X�s�[�h
		constexpr float THIRDEAT = 23.0f;						//!�O�H�ׂ���Ԃ̃X�s�[�h
		constexpr float HUMANSPEED = 24.0f;						//!�l�Ԃ̑��x
		constexpr float PLAYERCHANGEDIRECTINHMAXTIME = 2.0f;	//!�v���C���[�̕ϐg����
		constexpr int MaxKeyCount = 3;							//!�J�M�̍ő��

		//!�l�ԏ�Ԃ̎�----------------------------------------------------------
		//!�C���X�^���X�̐���(���̂̍쐬)
		HumanState* HumanState::Instance()
		{
			static HumanState instance;
			return &instance;
		}

		
		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerChange();														//!�v���C���[��Ԃ̎擾
			playerChange = PlayerModel::human;												//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);																//!�v���C���[�̏�Ԃ̐ݒ�
			Player->SetPlayerTaskDay(true);																		//!�v���C���[�̃~�b�V�����̕\��
			Player->SetSpeed(HUMANSPEED);																		//!�v���C���[�̎��̃X�s�[�h

		}

		void HumanState::Execute(Player* Player)
		{	
			float elapsedTime = App::GetApp()->GetElapsedTime();				//!�G���p�\�^�C���̎擾
			auto playerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();		//!�`��R���|�[�l���g�̎擾
			auto shadowPtr = Player->GetComponent<Shadowmap>();					//!�V���h�E�R���|�[�l���g�̎擾
			shadowPtr->SetMeshResource(L"Player_WalkAnimation2_MESH");			//!�v���C���[�̃��b�V���̕ύX
			playerDraw->SetMeshResource(L"Player_WalkAnimation2_MESH_WITH_TAN");//!�v���C���[�̃��b�V���̕ύX
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();		//�A�j���[�V����
			ptrDraw->UpdateAnimation(elapsedTime);								//!�A�j���[�V�����̍X�V
			auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
			m_HumanChangeTime = scene->GetPlayerConditionTime();				//!�ϐg����

			//!�v���C���[�����������Ă�����
			if (Player->GetKeyCount() == MaxKeyCount)
			{
				Player->Escape();
			}

			//!�Q�[�����Ԃ�30�b�o�߂�����
			if (m_HumanChangeTime >= MAXHUMANCHANGETIME)
			{
				Player->ChangeState(HumanChangeDirectingState::Instance());//!�T�̃X�e�[�g�ɕύX
			}

			if (Player->GetPlayerHp() == 0 || Player->GetIsplayerDed() == true)
			{
				Player->ChangeState(PlayerDedState::Instance());//!���S�̃X�e�[�g�ɕύX
			}

		}

		void HumanState::Exit(Player* Player)
		{
			
		}
		//-------------------------------------------------------------------------

		//!�T�j�̏�Ԃ̎�----------------------------------------------------------

		void WolfState::MeatEat(Player* Player)
		{

			
			auto meatCount = Player->GetMeatCount();//!�v���C���[���H�ׂ����̐�

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

			auto playerChange = player->GetPlayerChange();						//!�v���C���[�̏�Ԃ̎擾
			playerChange = PlayerModel::wolf;									//!��Ԃ�T�ɂ���
			player->SetPlayerChange(playerChange);								//!�v���C���[�̏�Ԃ̐ݒ�
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!���ʂ̎擾
			//�T�E���h�Đ�
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"howling", 0, volume);								//!�Đ�
			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			m_player = Stage->GetSharedGameObject<Player>(L"Player");
		}

		void WolfState::Execute(Player* player)
		{
			

			m_InputHandlerB.PushHandleB(m_player.lock());//!B�{�^���̃C���v�b�g�n���h���̒ǉ�
			auto WolfPlayerDraw = player->GetComponent<BcPNTnTBoneModelDraw>();			//!�v���C���[�̕`��R���|�\�l���g���擾
			auto shadowPtr = player->GetComponent<Shadowmap>();							//!�V���h�E�}�b�v
			shadowPtr->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH");				//!���b�V���̕ύX
			WolfPlayerDraw->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");	//!�v���C���[�̃��b�V���̕ύX
			float elapsedTime = App::GetApp()->GetElapsedTime();						//!�G���p�\�^�C���̎擾
			auto ptrDraw = player->GetComponent<BcPNTnTBoneModelDraw>();				//�A�j���[�V����
			ptrDraw->UpdateAnimation(elapsedTime);										//!�A�j���[�V�������X�V
            auto scene = App::GetApp()->GetScene<Scene>();								//!�V�[���̎擾
			m_WolfChangeTime = scene->GetPlayerConditionTime();							//!�ϐg���Ԃ̎擾
			//!�I�I�J�~���Ԃ��߂�����
			if (m_WolfChangeTime >= MAXWOLFCHANGETIME)
			{
				player->ChangeState(WolfChangeDirectingState::Instance());
			}

			if (player->GetPlayerHp() == 0|| player->GetIsplayerDed()==true)
			{
				player->ChangeState(PlayerDedState::Instance());//!���S�̃X�e�[�g�ɕύX
			}
			
			

			MeatEat(player);

		}

		void WolfState::Exit(Player* Player)
		{
			Player->SetMeatCount(0);						//!���J�E���g�̃��Z�b�g
			
		}

		//!	-------------------------------------------------------------------------------------

		//!�l�Ԃ���T�ɕϐg����Ƃ��̉��o�X�e�[�g-------------------------------------------------
		HumanChangeDirectingState* HumanChangeDirectingState::Instance()
		{
			static HumanChangeDirectingState instance;
			return &instance;
		}

		void HumanChangeDirectingState::Enter(Player* Player)
		{
			Player->SetPlayerTaskNight(true);									//!��̃~�b�V�����̕\��
			Player->SetSpeed(0.0f);												//!�X�s�[�h���~������
			auto position = Player->GetComponent<Transform>()->GetPosition();	//!�g�����X�t�H�[���̎擾
			Player->GetEffectManager()->PlayerChangeEfkPlay(position);			//!�ϐg�G�t�F�N�g			
			auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
			scene->SetPlayerChangeDirecting(true);								//!�v���C���[�̕ϐg���J�n����
		
		}

		void HumanChangeDirectingState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();			//!�A�v���̎擾
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̎擾
			auto& AnimationName = ptrDraw->GetCurrentAnimation();		//!���݂̃A�j���[�V����
			//!�l����T�ɂȂ�Ƃ��̃A�j���[�V�������f��
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Change");
			}

			auto scene = App::GetApp()->GetScene<Scene>();
			m_humanChangeDirectingTiem += elapsedTime;//!�Q�[���̎��Ԃ�ϐ��ɑ���
			if (m_humanChangeDirectingTiem>= PLAYERCHANGEDIRECTINHMAXTIME)
			{
				Player->ChangeState(WolfState::Instance());//!�T�̃X�e�[�g�ɕύX
			}

			if (Player->GetPlayerHp() == 0)
			{
				Player->ChangeState(PlayerDedState::Instance());//!���S�̃X�e�[�g�ɕύX
			}
		}

		void HumanChangeDirectingState::Exit(Player* Player)
		{
			m_humanChangeDirectingTiem = 0.0f;
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");

		}
		//!----------------------------------------------------------
		
		//!�T����l�Ԃɕϐg����Ƃ��̉��o�X�e�[�g-------------------------------------------------
		WolfChangeDirectingState* WolfChangeDirectingState::Instance()
		{
			static WolfChangeDirectingState instance;
			return &instance;
		}

		void WolfChangeDirectingState::Enter(Player* Player)
		{

			Player->SetSpeed(0.0f);
			//�G�t�F�N�g�̃v���C
			auto position = Player->GetComponent<Transform>()->GetPosition();	//!�g�����X�t�H�[���̎擾
			Player->GetEffectManager()->PlayerChangeEfkPlay(position);			//!�ϐg�G�t�F�N�g
			auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
			scene->SetPlayerChangeDirecting(true);								//!�v���C���[�̕ϐg���J�n����

		}

		void WolfChangeDirectingState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();//!�A�v���̎擾
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();
			auto& AnimationName = ptrDraw->GetCurrentAnimation();

			//!�T����l�ɂȂ�Ƃ��̃A�j���[�V�������f��
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Change");
			}

			//!�T����l�Ԃɕϐg���鎞�̃A�j���[�V�������f�� 
			auto scene = App::GetApp()->GetScene<Scene>();
			m_wolfChangeDirectingTiem += elapsedTime;//!�Q�[���̎��Ԃ�ϐ��ɑ���
			if (m_wolfChangeDirectingTiem>= PLAYERCHANGEDIRECTINHMAXTIME)
			{
				Player->ChangeState(HumanState::Instance());//!�T�̃X�e�[�g�ɕύX
			}

			if (Player->GetPlayerHp() == 0)
			{
				Player->ChangeState(PlayerDedState::Instance());//!���S�̃X�e�[�g�ɕύX
			}

		}

		void WolfChangeDirectingState::Exit(Player* Player)
		{
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");
			
			m_wolfChangeDirectingTiem = 0.0f;
		}
		//!----------------------------------------------------------


		
			//!�v���C���[�����񂾂Ƃ��̃X�e�[�g-------------------------------------------------
		PlayerDedState* PlayerDedState::Instance()
		{
			static PlayerDedState instance;
			return &instance;
		}

		void PlayerDedState::Enter(Player* Player)
		{
			Player->SetPlayerHp(0);//!�v���C���[��Hp��0�ɂ���
			Player->SetSpeed(0.0f);//!�v���C���[�̑��x��0�ɂ���
		}

		void PlayerDedState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();			//!�A�v���̎擾
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//!�`�揈��
			auto& AnimationName = ptrDraw->GetCurrentAnimation();		//!�A�j���[�V�����̎擾

			//!�T����l�ɂȂ�Ƃ��̃A�j���[�V�������f��
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				ptrDraw->ChangeCurrentAnimation(L"Ded");			//!�A�j���[�V������Ded�ɕύX
				auto& XAptr = App::GetApp()->GetXAudio2Manager();	//!�T�E���h�}�l�[�W���[�̎擾
				XAptr->Stop(Player->GetWolkSound());								//!�����T�E���h���~�߂�
			}

			
		}

		void PlayerDedState::Exit(Player* Player)
		{

		}
		//!----------------------------------------------------------
	}
}