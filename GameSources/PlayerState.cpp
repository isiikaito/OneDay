#include "stdafx.h"
#include "Project.h"
#include "Utility.h"
#include "PlayerState.h"
#include "Meat.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float m_maxHumanChangeTime = 31.0f;//!�l�Ԃ̎��̎���
		constexpr float m_maxWolfChangeTime = 62.0f;//!�T�̎��̎���
		constexpr int randomNumber = 2;//!�����_���Ȑ����͈̔�
		constexpr float m_MeatTimeSpeed = 22.0f;//!�����_���ɂ���X�s�[�h
		constexpr float m_notEatSpeed = 10.0f;//!�����H�ׂĂȂ���Ԃ̃X�s�[�h
		constexpr float m_firstEat = 15.0f;//!��H�ׂ���Ԃ̃X�s�[�h
		constexpr float m_secondEat = 20.0f;//!��H�ׂ���Ԃ̃X�s�[�h
		constexpr float m_thirdEat = 23.0f;//!�O�H�ׂ���Ԃ̃X�s�[�h
		constexpr float m_humanSpeed = 24.0f;//!�l�Ԃ̑��x
		constexpr float m_playerChangeDirectingMaxTiem = 2.0f;//!�v���C���[�̕ϐg����



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

			m_HumanChangeTime = 0.0f;

		}

		void HumanState::CreateMeat()
		{

			ReadCsv(L"MeatPosition");//!����Csv�̎擾

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

		void HumanState::CreateWoodBox()
		{

			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾


			// �t�H���_�̎w��
			auto csvDirectory = DataDir + L"csvFolder\\";
			//!MetaPositon�t�@�C���̓ǂݍ���
			m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");
			m_GameStageCsvD.ReadCsv();



			//CSV�̑S�̂̔z��
		//CSV���炷�ׂĂ̍s�𔲂��o��
			auto& LineVec = m_GameStageCsvD.GetCsvVec();
			for (size_t i = 0; i < LineVec.size(); i++) {
				//�g�[�N���i�J�����j�̔z��
				vector<wstring> Tokens;
				//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
				Util::WStrToTokenVector(Tokens, LineVec[i], L',');
				for (size_t j = 0; j < Tokens.size(); j++) {
					//X��Z�̈ʒu���v�Z
					float XPos = (float)((int)j - 8.6f) * 10.0f;
					float ZPos = (float)(8.6f - (int)i) * 10.0f;
					if (Tokens[j] == L"3")//3�̎��ɃQ�[���X�e�[�W�ɒǉ�
					{
						//!�ؔ��̍쐬
						Stage->AddGameObject<WoodenBox>(Vec3(9.0f, 9.0f, 9.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
					}
				}
			}
		}

		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerCange();//!�v���C���[��Ԃ̎擾
			playerChange = static_cast<int>(PlayerModel::human);//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);//!�v���C���[�̏�Ԃ̐ݒ�
			Player->SetMeatCount(0);//!����H�ׂ���
			Player->SetPlayerTaskDay(true);//!�v���C���[�̃~�b�V�����̕\��

			CreateWoodBox();//!�ؔ��̍쐬

			CreateMeat();//���̍쐬

			
			auto meatPosition = Player->GetMeatPosition();//!���̃|�W�V�����̎擾
			Player->SetMeatEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetMeatEfkEffect(), meatPosition));//!�G�t�F�N�g�̍Đ�

			Player->SetSpeed(m_humanSpeed);//!�v���C���[�̎��̃X�s�[�h


		}

		void HumanState::Execute(Player* Player)
		{	
			float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾


			auto playerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̎擾
			auto shadowPtr = Player->GetComponent<Shadowmap>();//!�V���h�E�R���|�[�l���g�̎擾

			shadowPtr->SetMeshResource(L"Player_WalkAnimation2_MESH");
			playerDraw->SetMeshResource(L"Player_WalkAnimation2_MESH_WITH_TAN");//!�v���C���[�̃��b�V���̕ύX

			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
			ptrDraw->UpdateAnimation(elapsedTime);//!�A�j���[�V�����̍X�V

			auto gameTime = Player->GetGameTime();//!�Q�[���̎��Ԃ��擾����

			auto scene = App::GetApp()->GetScene<Scene>();
			m_HumanChangeTime = scene->GetPlayerConditionTime();
			//!�Q�[�����Ԃ�30�b�o�߂�����
			if (m_HumanChangeTime >= m_maxHumanChangeTime)
			{
				Player->ChangeState(HumanChangeDirectingState::Instance());//!�T�̃X�e�[�g�ɕύX
			}

		}

		void HumanState::Exit(Player* Player)
		{
			
			//m_HumanChangeTime = 0.0f;//!�l�Ԃ̎��̎��Ԃ�0�b�ɂ���
			

			
		}
		//-------------------------------------------------------------------------







		//!�T�j�̏�Ԃ̎�----------------------------------------------------------

		void WolfState::MeatEat(Player* Player)
		{

			
			auto meatCount = Player->GetMeatCount();//!�v���C���[���H�ׂ����̐�

			switch (meatCount)
			{
			case(static_cast<int>(EatCondition::notEat)):
				Player->SetSpeed(m_notEatSpeed);
				break;
			case(static_cast<int>(EatCondition::firstEat)):
				Player->SetSpeed(m_firstEat);
				break;
			case(static_cast<int>(EatCondition::secondEat)):
				Player->SetSpeed(m_secondEat);
				break;
			case(static_cast<int>(EatCondition::thirdEat)):
				Player->SetSpeed(m_thirdEat);
				break;
			}
		}

		void WolfState::RemoveWoodBox()
		{
			//!�؂̔��̍폜
			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

			for (auto& Obj : Objects)//!�I�u�W�F�N�g�̗v�f��
			{
				auto stageMeat = dynamic_pointer_cast<WoodenBox>(Obj);//!�����̎擾
				if (stageMeat)
				{
					//!�ؔ��̍폜
					Stage->RemoveGameObject<WoodenBox>(Obj);
				}
			}
		}

		void WolfState::RemoveMeat()
		{
			//!���̍폜
			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

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

		WolfState* WolfState::Instance()
		{
			static WolfState instance;
			return &instance;
		}

		void WolfState::Enter(Player* Player)
		{

			auto playerChange = Player->GetPlayerCange();//!�v���C���[�̏�Ԃ̎擾
			playerChange = static_cast<int>(PlayerModel::wolf);//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);//!�v���C���[�̏�Ԃ̐ݒ�

			
			//�T�E���h�Đ�
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"howling", 0, 1.0f);

			RemoveMeat();

			

			
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
			m_WolfChangeTime = scene->GetPlayerConditionTime();

			
			//m_WolfChangeTime += scene->GetGameTime();
			if (m_WolfChangeTime >= m_maxWolfChangeTime)
			{
				Player->ChangeState(WolfChangeDirectingState::Instance());
			}
			
			MeatEat(Player);

		}

		void WolfState::Exit(Player* Player)
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			//m_WolfChangeTime = 0.0f;
			Player->SetMeatCount(0);
			m_Date++;
			scene->SetDate(m_Date);
			RemoveWoodBox();
			
			
		
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
			Player->SetPlayerTaskNight(true);//!��̃~�b�V�����̕\��

			Player->SetSpeed(0.0f);
			//�G�t�F�N�g�̃v���C
			auto Ptr = Player->GetComponent<Transform>();
			Player->SetTransformEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetTransformEfkEffect(), Ptr->GetPosition()));
			
			auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
			scene->SetPlayerChangeDirecting(true);//!�v���C���[�̕ϐg���J�n����
		
		}

		void HumanChangeDirectingState::Execute(Player* Player)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();//!�A�v���̎擾
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();
			auto& AnimationName = ptrDraw->GetCurrentAnimation();

			//!�l����T�ɂȂ�Ƃ��̃A�j���[�V�������f��
			if (AnimationName == L"Move" || AnimationName == L"Default")
			{
				Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Change");
			}

			auto scene = App::GetApp()->GetScene<Scene>();
			m_humanChangeDirectingTiem += elapsedTime;//!�Q�[���̎��Ԃ�ϐ��ɑ���
			if (m_humanChangeDirectingTiem>= m_playerChangeDirectingMaxTiem)
			{
				Player->ChangeState(WolfState::Instance());//!�T�̃X�e�[�g�ɕύX
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
			auto Ptr = Player->GetComponent<Transform>();
			Player->SetTransformEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetTransformEfkEffect(), Ptr->GetPosition()));

			auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
			scene->SetPlayerChangeDirecting(true);//!�v���C���[�̕ϐg���J�n����

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
			if (m_wolfChangeDirectingTiem>= m_playerChangeDirectingMaxTiem)
			{
				Player->ChangeState(HumanState::Instance());//!�T�̃X�e�[�g�ɕύX
			}
		}

		void WolfChangeDirectingState::Exit(Player* Player)
		{
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");
			
			m_wolfChangeDirectingTiem = 0.0f;
		}
		//!----------------------------------------------------------


	}
}