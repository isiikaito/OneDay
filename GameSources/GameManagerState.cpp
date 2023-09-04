#include "stdafx.h"
#include "Project.h"
#include "GameManagerState.h"
#include "Meat.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float MAXDEDTIME = 1.0f;					//!�|���܂ł̎���
		constexpr float MAXHUMANCHANGETIME = 31.0f;			//!�l�Ԃ̎��̎���
		constexpr float MAXWOLFCHANGETIME = 62.0f;			//!�T�̎��̎���
		constexpr float PLAYERCHANGEDIRECTINHMAXTIME = 2.0f;//!�v���C���[�̕ϐg����
		constexpr float POSITIONRANGE = 10.0f;				//!�ʒu�̕�
		constexpr float CORRECTIONOFPOSITION = 8.6f;		//!�ʒu�̏C��

		//!�I�[�v�j���O�J�����̎�
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
			auto& app = App::GetApp();					//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			app->GetScene<Scene>()->GetGameOver();
			auto gameStrat = app->GetScene<Scene>()->GetGameStrat();				  //!�I�[�v�j���O�J�����̎����ǂ���
			if (gameStrat == false)
			{
				gameManager->ChangeState(MiddayState::Instance());//!�X�e�[�g��ύX����

			}
			
		}

		void OpeningCameraPlayState::Exit(GameManager* gameManager)
		{
			auto player = gameManager->GetPlayer();
			player->SetUpdateActive(true);

		}



		//!���Ԃ̎�
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

			auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
			m_middayTime = scene->GetPlayerConditionTime();				//!�ϐg����
			//!�Q�[�����Ԃ�30�b�o�߂�����
			if (m_middayTime >= MAXHUMANCHANGETIME)
			{
				gameManager->ChangeState(NightState::Instance());//!�T�̃X�e�[�g�ɕύX
			}

			auto playerHp = gameManager->GetPlayer()->GetPlayerHp();
			if (playerHp <= 0)
			{
				gameManager->ChangeState(GameOverState::Instance());//!�X�e�[�g��ύX����

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

			//!�V�[���̎擾
			m_MeatNumber = scene->GetMeatNamber();

			// �t�H���_�̎w��
			auto csvDirectory = DataDir + L"csvFolder\\"+L"MeatPosition\\";
			//!MetaPositon�t�@�C���̓ǂݍ���
			m_MeatPositon.SetFileName(csvDirectory + FileNume + Util::IntToWStr(m_MeatNumber) + L".csv");
			m_MeatPositon.ReadCsv();

			m_middayTime = 0.0f;//!���Ԃ̍X�V

		}

		void MiddayState::CreateMeat()
		{
			Vec3 scale = Vec3(5.0f);								//!�傫��
			Vec3 rotation = Vec3(0.0f);								//!��]
			ReadCsv(L"MeatPosition");								//!����Csv�̎擾
			auto& app = App::GetApp();								//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();	//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();				//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾
			//CSV�̑S�̂̔z��
			//CSV���炷�ׂĂ̍s�𔲂��o��
			auto& LineVec = m_MeatPositon.GetCsvVec();

			for (size_t i = 0; i < LineVec.size(); i++) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;
				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, LineVec[i], L',');
				for (size_t j = 0; j < Tokens.size(); j++) {
					//X��Z�̈ʒu���v�Z
					float XPos = (float)((int)j - CORRECTIONOFPOSITION) * POSITIONRANGE;
					float YPos = 4.0f;
					float ZPos = (float)(CORRECTIONOFPOSITION - (int)i) * POSITIONRANGE;
					if (Tokens[j] == L"5")//5�̎��ɃQ�[���X�e�[�W�ɒǉ�
					{
						Stage->AddGameObject<Meat>(scale, rotation, Vec3(XPos, YPos, ZPos));//!���̍쐬
					}
				}
			}
		}



		//!��̎�
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

			auto scene = App::GetApp()->GetScene<Scene>();								//!�V�[���̎擾
			m_nightTime = scene->GetPlayerConditionTime();								//!�ϐg���Ԃ̎擾
			//!�I�I�J�~���Ԃ��߂�����
			if (m_nightTime >= MAXWOLFCHANGETIME)
			{
				gameManager->ChangeState(MiddayState::Instance());
			}

			auto playerHp = gameManager->GetPlayer()->GetPlayerHp();
			if (playerHp <= 0)
			{
				gameManager->ChangeState(GameOverState::Instance());//!�X�e�[�g��ύX����

			}

		}

		void NightState::Exit(GameManager* gameManager)
		{
			auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
			m_Date++;										//!���t�̍X�V
			scene->SetDate(m_Date);							//!���t�̐ݒ�

		}

		
		void NightState::RemoveMeat()
		{
			//!���̍폜
			auto& app = App::GetApp();								//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();	//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();				//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾
			for (auto& Obj : Objects)//!�I�u�W�F�N�g�̗v�f��
			{
				auto stageMeat = dynamic_pointer_cast<Meat>(Obj);//!�����̎擾
				if (stageMeat)
				{
					//!���̍폜
					Stage->RemoveGameObject<Meat>(Obj);
				}
			}
		}

		//!�Q�[���I�[�o�[�̎�
		GameOverState* GameOverState::Instance()
		{
			static GameOverState instance;
			return &instance;
		}

		void GameOverState::Enter(GameManager* gameManager)
		{
			auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
			auto gameOverSprite = scene->GetGameOverSprite();		//!�Q�[���I�[�o�[����̎擾
			gameOverSprite = true;							//!�Q�[���I�[�o�[�ɂ���
			scene->SetGameOverSprite(gameOverSprite);
			
		}

		void GameOverState::Execute(GameManager* gameManager)
		{

			float Time = App::GetApp()->GetElapsedTime();//!�o�ߎ��Ԃ̎擾
			m_dedTime += Time;							 //!�v���C���[���|��鎞�Ԃɉ��Z

			//!�|��鎞�ԂɂȂ�����
			if (m_dedTime >= MAXDEDTIME)
			{
				auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
				auto gameOver = scene->GetGameOver();		//!�Q�[���I�[�o�[����̎擾
				gameOver = true;							//!�Q�[���I�[�o�[�ɂ���
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
