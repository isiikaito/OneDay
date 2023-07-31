/**
*@file GameClear.cpp
*@brief �Q�[���N���A��ʂ̃\�[�X�t�@�C��
*@author  Ayumiu Muroi
*@details �Q�[���N���A��ʂ̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "GoalPlayer.h"
#include "ClearStageCanvas.h"

namespace basecross {
//--------------------------------------------------------------------------------------
//	�Q�[���N���A�X�e�[�W�N���X
//--------------------------------------------------------------------------------------
	void GameClearStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(10.0f, 20.0f, 130.0f));
		PtrCamera->SetAt(Vec3(10.0f, 10.0f, 100.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	

	// !�X�e�[�W�̏�
	void GameClearStage::CreateStageFloor()
	{
		
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;

		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_StageCsv.GetSelect(LineVec, 0, L"StageFloor");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<StageFloor>(Scale, Rot, Pos);
		}

	}

	
	//!�S�[�����̃v���C���[�̍쐬
	void GameClearStage::CerateGoalPlayer()
	{
	AddGameObject<GoalPlayer>(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f, 50.0f, 80.0f)); //!�S�[���v���C���[�̍쐬
	}

	// !�X�e�[�W�̌���
	void GameClearStage::CreateStageBuilding()
	{
		auto group = CreateSharedObjectGroup(L"StageBuilding_Group");

		
		//CSV�̑S�̂̔z��
		//CSV���炷�ׂĂ̍s�𔲂��o��
		auto& LineVec = m_GameStageCsvD.GetCsvVec(); // csv�t�@�C�����Z�b�g����
		for (size_t i = 0; i < LineVec.size(); i++) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//X��Z�̈ʒu���v�Z
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"1")
				{
					AddGameObject<StageBuilding>(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 5.0f, ZPos));
				}
			}
		}

	}

	// !�X�e�[�W�̕�
	void GameClearStage::CreateStageWall()
	{
		auto group = CreateSharedObjectGroup(L"StageWall_Group");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_StageCsv.GetSelect(LineVec, 0, L"StageWall");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<StageWall>(Scale, Rot, Pos);
		}

	}

	// !�X�e�[�W�̖�̍쐬
	void GameClearStage::CreateStageGate()
	{

		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_StageCsv.GetSelect(LineVec, 0, L"StageGate");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			auto ptrGate = AddGameObject<StageGate>(Scale, Rot, Pos);
			SetSharedGameObject(L"Gate", ptrGate);
			
		}

	}

	//������
	void GameClearStage::OnCreate() {
		CreateViewLight();
		
		SetPhysicsActive(true);//�����v�Z�L��
		auto scene = App::GetApp()->GetScene<Scene>();

		scene->SetGoleGateParameter(true);//!��̃p�����[�^�[�̓K��

		//!BGM
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GameClear", XAUDIO2_LOOP_INFINITE, 0.2f);
		
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		// �t�H���_�̎w��
		auto csvDirectory = DataDir + L"csvFolder\\";

		m_StageCsv.SetFileName(csvDirectory + L"ClearStage.csv");
		m_StageCsv.ReadCsv();
		//!Building�t�@�C���̓ǂݍ���4
		m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");
		m_GameStageCsvD.ReadCsv();

		CerateGoalPlayer(); //! �v���C���[�̒ǉ�
		CreateStageFloor();	//!�X�e�[�W�̒ǉ�
		CreateStageBuilding(); //!�����̒ǉ�
		CreateStageWall(); //!�ǂ̒ǉ�
		CreateStageGate(); //!��̒ǉ�
		AddGameObject<ClearStageCanvas>();
	}

	void GameClearStage::OnUpdate() {
		
		//!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameClearStage>());
	}
	// !BGM�̃X�g�b�v
	void GameClearStage::OnDestroy()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//A�{�^��
	void GameClearStage::OnPushA() {
		PostEvent(0.0f, GetThis<GameClearStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		OnDestroy();
	}

	
}
//end basecros