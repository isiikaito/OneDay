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
		constexpr float MAXHUMANCHANGETIME = 31.0f;			//!�l�Ԃ̎��̎���
		constexpr float MAXWOLFCHANGETIME = 62.0f;			//!�T�̎��̎���
		constexpr float NOTEALSPEED = 10.0f;					//!�����H�ׂĂȂ���Ԃ̃X�s�[�h
		constexpr float FIRSTEAT = 15.0f;						//!��H�ׂ���Ԃ̃X�s�[�h
		constexpr float SECONDEAT = 20.0f;					//!��H�ׂ���Ԃ̃X�s�[�h
		constexpr float THIRDEAT = 23.0f;						//!�O�H�ׂ���Ԃ̃X�s�[�h
		constexpr float HUMANSPEED = 24.0f;					//!�l�Ԃ̑��x
		constexpr float PLAYERCHANGEDIRECTINHMAXTIME = 2.0f;	//!�v���C���[�̕ϐg����
		constexpr float POSITIONRANGE = 10.0f;				//!�ʒu�̕�
		constexpr float CORRECTIONOFPOSITION = 8.6f;			//!�ʒu�̏C��


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

			m_HumanChangeTime = 0.0f;//!���Ԃ̍X�V

		}

		void HumanState::CreateMeat()
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

		void HumanState::CreateWoodBox()
		{
			Vec3 scale = Vec3(9.0f);										//!�傫��
			Vec3 rotation = Vec3(0.0f);										//!��]
			auto& app = App::GetApp();										//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();			//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();						//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);						//!�f�[�^�̎擾
			auto scene = App::GetApp()->GetScene<Scene>();					//!�V�[���̎擾
			auto csvDirectory = DataDir + L"csvFolder\\";					//�t�H���_�̎w��
			m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");	//!MetaPositon�t�@�C���̓ǂݍ���
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
					float XPos = (float)((int)j - CORRECTIONOFPOSITION) * POSITIONRANGE;
					float YPos = 3.0f;
					float ZPos = (float)(CORRECTIONOFPOSITION - (int)i) * POSITIONRANGE;
					if (Tokens[j] == L"3")//3�̎��ɃQ�[���X�e�[�W�ɒǉ�
					{
						//!�ؔ��̍쐬
						Stage->AddGameObject<WoodenBox>(scale, rotation, Vec3(XPos, YPos, ZPos));
					}
				}
			}
		}

		void  HumanState::Enter(Player* Player)
		{
			auto playerChange = Player->GetPlayerChange();														//!�v���C���[��Ԃ̎擾
			playerChange = PlayerModel::human;												//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);																//!�v���C���[�̏�Ԃ̐ݒ�
			Player->SetMeatCount(0);																			//!����H�ׂ���
			Player->SetPlayerTaskDay(true);																		//!�v���C���[�̃~�b�V�����̕\��
			CreateWoodBox();																					//!�ؔ��̍쐬
			CreateMeat();																						//���̍쐬
			auto meatPosition = Player->GetMeatPosition();														//!���̃|�W�V�����̎擾
			Player->SetMeatEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetMeatEfkEffect(), meatPosition));	//!�G�t�F�N�g�̍Đ�
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
			auto gameTime = Player->GetGameTime();								//!�Q�[���̎��Ԃ��擾����
			auto scene = App::GetApp()->GetScene<Scene>();						//!�V�[���̎擾
			m_HumanChangeTime = scene->GetPlayerConditionTime();				//!�ϐg����
			//!�Q�[�����Ԃ�30�b�o�߂�����
			if (m_HumanChangeTime >= MAXHUMANCHANGETIME)
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

		void WolfState::RemoveWoodBox()
		{
			//!�؂̔��̍폜
			auto& app = App::GetApp();								//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();	//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();				//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾
			for (auto& Obj : Objects)								//!�I�u�W�F�N�g�̗v�f��
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

		WolfState* WolfState::Instance()
		{
			static WolfState instance;
			return &instance;
		}

		void WolfState::Enter(Player* Player)
		{

			auto playerChange = Player->GetPlayerChange();						//!�v���C���[�̏�Ԃ̎擾
			playerChange = PlayerModel::wolf;					//!��Ԃ�T�ɂ���
			Player->SetPlayerChange(playerChange);								//!�v���C���[�̏�Ԃ̐ݒ�
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!���ʂ̎擾
			//�T�E���h�Đ�
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"howling", 0, volume);								//!�Đ�
			RemoveMeat();
		}

		void WolfState::Execute(Player* Player)
		{


			auto WolfPlayerDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();			//!�v���C���[�̕`��R���|�\�l���g���擾
			auto shadowPtr = Player->GetComponent<Shadowmap>();							//!�V���h�E�}�b�v
			shadowPtr->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH");				//!���b�V���̕ύX
			WolfPlayerDraw->SetMeshResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");	//!�v���C���[�̃��b�V���̕ύX
			float elapsedTime = App::GetApp()->GetElapsedTime();						//!�G���p�\�^�C���̎擾
			auto ptrDraw = Player->GetComponent<BcPNTnTBoneModelDraw>();				//�A�j���[�V����
			ptrDraw->UpdateAnimation(elapsedTime);										//!�A�j���[�V�������X�V
            auto scene = App::GetApp()->GetScene<Scene>();								//!�V�[���̎擾
			m_WolfChangeTime = scene->GetPlayerConditionTime();							//!�ϐg���Ԃ̎擾
			//!�I�I�J�~���Ԃ��߂�����
			if (m_WolfChangeTime >= MAXWOLFCHANGETIME)
			{
				Player->ChangeState(WolfChangeDirectingState::Instance());
			}
			
			MeatEat(Player);

		}

		void WolfState::Exit(Player* Player)
		{
			auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
			Player->SetMeatCount(0);						//!���J�E���g�̃��Z�b�g
			m_Date++;										//!���t�̍X�V
			scene->SetDate(m_Date);							//!���t�̐ݒ�
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
			Player->SetPlayerTaskNight(true);	//!��̃~�b�V�����̕\��
			Player->SetSpeed(0.0f);				//!�X�s�[�h���~������
			//�G�t�F�N�g�̃v���C
			auto Ptr = Player->GetComponent<Transform>();//!�g�����X�t�H�[���̎擾
			Player->SetTransformEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetTransformEfkEffect(), Ptr->GetPosition()));//!�G�t�F�N�g�̎擾
			
			auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
			scene->SetPlayerChangeDirecting(true);			//!�v���C���[�̕ϐg���J�n����
		
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
			auto Ptr = Player->GetComponent<Transform>();//!�g�����X�t�H�[���̎擾
			Player->SetTransformEfkPlay(ObjectFactory::Create<EfkPlay>(Player->GetTransformEfkEffect(), Ptr->GetPosition()));//!�G�t�F�N�g�̎擾
			auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
			scene->SetPlayerChangeDirecting(true);			//!�v���C���[�̕ϐg���J�n����

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
		}

		void WolfChangeDirectingState::Exit(Player* Player)
		{
			Player->GetComponent<BcPNTnTBoneModelDraw>()->ChangeCurrentAnimation(L"Default");
			
			m_wolfChangeDirectingTiem = 0.0f;
		}
		//!----------------------------------------------------------


	}
}