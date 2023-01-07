#include "stdafx.h"
#include "Project.h"
#include "Utility.h"
#include "PlayerState.h"
#include "Meat.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float m_maxHumanChangeTime = 31.0f;
		constexpr float m_maxWolfChangeTime = 61.0f;
		constexpr int randomNumber = 2;
		constexpr float m_MeatTimeSpeed = 22.0f;
		

		//!�l�ԏ�Ԃ̎�----------------------------------------------------------
		//!�C���X�^���X�̐���(���̂̍쐬)
		HumanState* HumanState::Instance()
		{
			static HumanState instance;
			return &instance;
		}

		void HumanState::ReadCsv(const wstring& FileNume)
		{
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto scene = App::GetApp()->GetScene<Scene>();

			//!�V�[���̎擾
			m_MeatNumber = scene->GetMeatNamber();

			// �t�H���_�̎w��
			auto csvDirectory = DataDir + L"csvFolder\\";
			//!MetaPositon�t�@�C���̓ǂݍ���
			m_MeatPositon.SetFileName(csvDirectory + FileNume + Util::IntToWStr(m_MeatNumber) + L".csv");
			m_MeatPositon.ReadCsv();
		}
		
		void HumanState:: CreateMeat()
		{
			
			ReadCsv(L"MeatPosition");

			//!���̍폜
			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

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
						float XPos = (float)((int)j - 8.6f) * 10.0f;
						float ZPos = (float)(8.6f - (int)i) * 10.0f;
						if (Tokens[j] == L"5")//5�̎��ɃQ�[���X�e�[�W�ɒǉ�
						{
							Stage->AddGameObject<Meat>(Vec3(5.0f, 5.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 4.0f, ZPos));
						}
					}
				}
		}

		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerCange();
			playerChange = static_cast<int>(PlayerModel::human);//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);
			CreateMeat();
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

			//!���̍폜
			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

			for (auto& Obj : Objects)//!�I�u�W�F�N�g�̗v�f��
			{
				auto stageMeat = dynamic_pointer_cast<Meat>(Obj);//!�����̎擾
				if (stageMeat)
				{
					Stage->RemoveGameObject<Meat>(Obj);
				}
			}

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