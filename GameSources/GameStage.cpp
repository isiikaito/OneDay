/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "HeadManComment.h"
#include "Meat.h"
#include "HungerGage.h"
#include "DateChangeCommentDay.h"
#include "DateChangeCommentNight.h"
#include "GameManager.h"
#include "OpeningCamera.h"
#include "OpeningCameraMan.h"
#include "GameUI.h"
#include "PlayerHurteSprite.h"

namespace basecross {

	constexpr int alertlevelFirst = 1;
	constexpr int randomNumber = 4;
	constexpr float m_MeatTimeSpeed = 22.0f;
	constexpr float m_playerChangeMaxTime = 2.0f;
	constexpr float m_gameStartMaxTime = 6.0f;
	constexpr float m_circleClockSpeed = 10.0f;
	constexpr float m_opningCameraTime = 6.0f;
	constexpr float m_playerConditionMaxTime = 62.0f;
	constexpr float m_emissiveChangeTimeSpeed = 32.0f;
	constexpr float m_emissiveReset = 1.0f;
	constexpr float m_emissiveChangeMaxTime = 1.0f;
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {

		//OpeningCameraView�p�̃r���[
		m_openingCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_openingCameraView->SetCamera(ptrOpeningCamera);

		//�r���[�̃J�����̐ݒ�
		//MyCamera�p�̃r���[
		m_myCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_myCameraView->SetCamera(ptrMyCamera);

		SetView(m_openingCameraView);
		m_CameraSelect = CameraSelect::openingCamera;

		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();


	}

	//!�J�����}���̍쐬 
	void GameStage::CreateCameraman()
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraMan>();
		//�V�F�A�z���OpeningCameraman��ǉ�
		SetSharedGameObject(L"OpeningCameraMan", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_openingCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_openingCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	//!�J�������v���C���[�̈ʒu�ɖ߂�����
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_myCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_myCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}


	// !�X�e�[�W�̏�
	void GameStage::CreateStageFloor()
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

	// !�X�e�[�W�̕�
	void GameStage::CreateStageWall()
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

	// !�X�e�[�W�̌���
	void GameStage::CreateStageBuilding()
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


	//!�J�M
	void GameStage::CreateKey()
	{
		//CSV�̑S�̂̔z��
		//CSV���炷�ׂĂ̍s�𔲂��o��
		auto group = CreateSharedObjectGroup(L"key_ObjGroup");
		auto& LineVec = m_KeyPositon.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size(); j++) {
				//X��Z�̈ʒu���v�Z
				float XPos = (float)((int)j - 8.6f) * 10.0f;
				float ZPos = (float)(8.6f - (int)i) * 10.0f;
				if (Tokens[j] == L"2")//2�̎��ɃQ�[���X�e�[�W�ɒǉ�
				{
					AddGameObject<Key>(Vec3(2.0f, 4.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
				}
			}
		}
	}

	//!�ؔ��̍쐬
	void GameStage::CreateWoodenBox()
	{
		//CSV�̑S�̂̔z��
		//CSV���炷�ׂĂ̍s�𔲂��o��
		auto group = CreateSharedObjectGroup(L"WoodBox_ObjGroup");
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
					AddGameObject<WoodenBox>(Vec3(9.0f, 9.0f, 9.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
					
				}
			}
		}
	}

	//!�؂̍쐬
	void GameStage::CreateWood()
	{
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
				if (Tokens[j] == L"4")//4�̎��ɃQ�[���X�e�[�W�ɒǉ�
				{
					AddGameObject<Wood>(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
				}
			}
		}
	}

	void GameStage::CreateMeat()
	{
		//CSV�̑S�̂̔z��
		//CSV���炷�ׂĂ̍s�𔲂��o��
		auto& LineVec = m_MeatPositon.GetCsvVec();
		auto group = CreateSharedObjectGroup(L"Meat_ObjGroup");

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
					AddGameObject<Meat>(Vec3(5.0f, 5.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 4.0f, ZPos));
				}
			}
		}

	}


	// !�X�e�[�W�̖�̍쐬
	void GameStage::CreateStageGate()
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
			auto ptrGate=AddGameObject<StageGate>(Scale, Rot, Pos);
			SetSharedGameObject(L"Gate", ptrGate);
		}

	}

	void GameStage::CreateDateChangeCommentDay()
	{
		AddGameObject<DateChangeCommentDay>(
			L"CommentDay_TX",//!�e�N�X�`��
			true,
			Vec2(700.0f, 300.0f),//�傫��
			Vec2(0.0f, 240.0f)//���W
			);
	}

	void GameStage::CreateDateChangeCommentNight()
	{
		AddGameObject<DateChangeCommentNight>(
			L"CommentNignt_TX",//!�e�N�X�`��
			true,
			Vec2(700.0f, 300.0f),//�傫��
			Vec2(0.0f, 240.0f)//���W
			);

	
	}


	void GameStage:: CreateGameOver()
	{
		AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f,0.0f));
		
	}

	//�X�R�A�X�v���C�g�쐬
	void GameStage::CreateTimerSprite() {
		AddGameObject<Timer>(2,
			L"NUMBER_TX",
			true,
			Vec2(50.0f, 40.0f),
			Vec3(-400.0f, 265.0f, 10.0f));

	}


	//!�v���C���[�̍쐬
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();//!�v���C���[�̍쐬
		SetSharedGameObject(L"Player", ptrPlayer);
	}

	//!�G(�X�P�[���A���[�e�C�V�����A�|�W�V����)�̍\����
	struct TransformCreateDate {
		//!�\���̃e���v���[�g
		Vec3 scale = Vec3(0.0f);//!�傫��
		Vec3 rotation = Vec3(0.0f);//!��]
		Vec3 position = Vec3(0.0f);//!�ʒu
		wstring EnemykeyName = L"";//!���l�̏��񃋁[�g�̃L�[�t���[�����擾

		TransformCreateDate() :
			TransformCreateDate(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), wstring(L""))
		{}
		//!�\���̂̏�����
		TransformCreateDate(
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& EnemykeyName
		) :
			scale(scale),
			rotation(rotation),
			position(position),
			EnemykeyName(EnemykeyName)
		{}
	};

	//!�G(�X�P�[���A���[�e�C�V�����A�|�W�V����)�̊֐�
	std::vector<TransformCreateDate>TransformDate(const wstring& folderName, const wstring& fileName, const wstring& keyName) {
		std::vector<TransformCreateDate>result;//!�ϐ���
		vector<wstring>LineVec;//!CSV�̍s�P�ʂ̔z��

		auto& app = App::GetApp();//!�A�v���̎擾
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto fullPass = DataDir + folderName + fileName;

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);//!0�Ԗڂ̃J������L"Villager"�ł���s�𔲂��o��

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')
			//!�g�[�N��(�J����)���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//!��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			//!���l�̈ʒu
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			wstring	EnemykeyName = Tokens[10];
			result.push_back(TransformCreateDate(Scale, Rot, Pos, EnemykeyName));

		}

		return result;
	}


	
	//!�p�g���[���|�C���g�̍\����
	struct PointCreateDate {
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0);

		PointCreateDate() :
			PointCreateDate(vector<Vec3>(0)) {}
		PointCreateDate(const std::vector<Vec3>& patrolPoints) :
			m_patorlPositions(patrolPoints)
		{}
	};

	//!�p�g���[���|�C���g
	PointCreateDate PointDate(const wstring& folderName, const wstring& fileName, const wstring& keyName)
	{
		PointCreateDate PatorlPoint;

		vector<wstring>LineVec;
		auto& app = App::GetApp();//!�A�v���̎擾
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto fullPass = DataDir + folderName + fileName;//!

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);//!0�Ԗڂ̃J������keyName�ł���s�𔲂��o��
		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')

			auto& routePositions = PatorlPoint.m_patorlPositions;

			routePositions.push_back(
				Vec3((float)_wtof(Tokens[1].c_str()),
					(float)_wtof(Tokens[2].c_str()),
					(float)_wtof(Tokens[3].c_str())));
		}

		return PatorlPoint;
	}
	void GameStage::CreateMeatGageFrame()
	{
		auto meatGageFrameSprite = AddGameObject<GameUI>(
			L"Frame_TX",//!�e�N�X�`��
			true,
			Vec2(200.0f, 50.0f),//�傫��
			Vec3(420.0f, -320.0f,0.2f)//���W
			);
		

		


	}

	void GameStage::CreateHungerGage()
	{
		AddGameObject<HungerGage>(
			L"Full_TX",//!�e�N�X�`��
			true,
			Vec2(400.0f, 100.0f),//�傫��
			Vec2(420.0f, -320.0f)//���W
			);
	}

	void GameStage::CreateMeatGageBackGround()
	{
		AddGameObject<GameUI>
			(
			L"Background_TX",//!�e�N�X�`��
			true,
			Vec2(200.0f, 50.0f),//�傫��
			Vec3(420.0f, -320.0f,1.0f)//���W
			);
		

	}

	void GameStage::CreateKeyFrame()
	{
		AddGameObject<GameUI>(
			L"ItemField_TX",//!�e�N�X�`��
			true,
			Vec2(200.0f, 150.0f), //!�傫��
			Vec3(-450.0f, -280.0f,0.2f)//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
			);
		

	}

	void GameStage::CreateHeartSprite()
	{
		

		//!�����̃n�[�g
		AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),        //!�傫��
				Vec3(370.0f, -250.0f,0.2f),//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				2,//!���݂̃��C�t
				true//!�\������Ă��邩�ǂ���
				);

		//!�������̃n�[�g
		AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!�傫��
				Vec3(460.0f, -250.0f, 0.2f),//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				1,//!���݂̃��C�t
				true//!�\������Ă��邩�ǂ���
				);

		//!�E���̃n�[�g
	AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!�傫��
				Vec3(550.0f, -250.0f, 0.2f),//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				0,//!���݂̃��C�t
				true//!�\������Ă��邩�ǂ���
				);
		
	}

	void GameStage::CreateAlertlevelGauge()
	{

		auto alertlevelGaugeSprite = AddGameObject<GameUI>
			(
				L"AlertlevelGaugeGauge_TX",
				true,
				Vec2(150.0f, 50.0f),       //!�傫��
				Vec3(460.0f, 350.0f, 1.0f) //!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);
		

	}
	void GameStage::CreateClockArrow()
	{
		auto clockArrowSprite=AddGameObject<GameUI>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),//!�傫��
				Vec3(0.0f,0.0f,90.0f),//!��]
				Vec3(-500.0f, 300.0f,0.2f)//!�ʒu
				);
		

	}

	void GameStage::CreateArrow()
	{
		//!���̍쐬
		AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),       //!�傫��
				Vec3(390.0f, 330.0f, 0.8f)//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);

		

	}

	// !���v�̃X�v���C�g�̍쐬
	void GameStage::CreateClockSprite()
	{
		auto clockSprite=AddGameObject<GameUI>
			(
				L"Clock_TX",
				true,
				Vec2(170.0f, 128.0f),
				Vec3(-460.0f, 290.0f,0.3f)
				);
		


	}

	// !���v�̉~�Ղ̃X�v���C�g�̍쐬
	void GameStage::CreateCircleClockSprite()
	{
		auto circleClockSprite = AddGameObject<CircleClockSprite>
			(
				L"Circle_TX",
				true,
				Vec2(65.0f, 70.0f),
				Vec3(-550.0f, 263.0f,1.0f)
				);

	}

	

	void GameStage::UIDrawActive(bool t)
	{
		

	
		

		
		

		

		

		//!���Ԃ̃X�v���C�g�̕\��
		auto timer = GetSharedGameObject<Timer>(L"Time");
		timer->SetDrawActive(t);

		
		
	

	}
	//!���l�̍쐬
	void GameStage::CerateVillager()
	{
		auto group = CreateSharedObjectGroup(L"Villager_ObjGroup");//!�O���[�v���擾

		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"Villager");//!Excel�̃f�[�^�w��
		
		for (auto& data : datas) {

		
			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", data.EnemykeyName);//!���l�̑傫�����������Ă�CSV����L�[�l�[�������o����������s����I��
			

			auto VillagerPtr=AddGameObject<Villager>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);
		
			
			
			AddGameObject<LoseSightOf>(VillagerPtr);
			AddGameObject<SurprisedSprite>(VillagerPtr);
			
		}
		
	}

	//!�n���^�[�̍쐬
	void GameStage::CerateHunter()
	{
		auto group = CreateSharedObjectGroup(L"Hunter_ObjGroup");//!�O���[�v���擾

		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"Hunter");//!Excel�̃f�[�^�w��
		
		for (auto& data : datas) {

			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", data.EnemykeyName);//!���l�̑傫�����������Ă�CSV����L�[�l�[�������o����������s����I��

			auto HunterPtr = AddGameObject<Hunter>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);

			AddGameObject<LoseSightOf>(HunterPtr);
			AddGameObject<SurprisedSprite>(HunterPtr);
		}

	}

	void GameStage::CreateHeadMan()
	{
		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"HeadMan");//!Excel�̃f�[�^�w��

		for (auto& data : datas) 
		{
			auto HeadManPtr = AddGameObject<HeadMan>(data.scale, data.rotation,data.position );
			SetSharedGameObject(L"HeadMan", HeadManPtr);

			AddGameObject<HeadManComment>(HeadManPtr);

		}
	}

	void GameStage::OpeningCameraBooting(float time)
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		m_gameStartTime += elapsedTime;//!�G���p�\�^�C���𑫂��Ď��Ԃ̐���
		//!�I�[�v�j���O�J�����̎��Ԃ��߂�����
		if (m_gameStartTime >= time)
		{
			UIDrawActive(true);
			auto gameStrat = scene->GetGameStrat();//!�I�[�v�j���O�J�����̏�Ԃ��擾
			gameStrat = false;			//!�I�[�v�j���O�J�����̏�Ԃ��I�t
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);//!�I�[�v�j���O�J�����̏�Ԃ�ݒ�

			//m_gameStrat = false;
			if (m_heartSpriteDraw == false)
			{
				
				m_heartSpriteDraw = true;
			}
		}
		else
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			auto m_emissiveChangeTime = scene->GetEmissiveChangeTime();
			m_emissiveChangeTime = m_emissiveReset;
			scene->SetEmissiveChangeTime(m_emissiveChangeTime);
			auto gameStrat = scene->GetGameStrat();
			gameStrat = true;
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);

			//m_gameStrat = true;
			UIDrawActive(false);
			
		}
	    //App::GetApp()->GetScene<Scene>()->SetGameStrat(m_gameStrat);

	}


	void GameStage::GameTime()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾

		OpeningCameraBooting(m_opningCameraTime);//!�I�[�v�j���O�J�����̎��Ԓ��̏���
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStrat = scene->GetGameStrat();


		//!�I�[�v�j���O�J�������I������Ƃ�
		if (!gameStrat)
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			auto m_playerConditionTime = scene->GetPlayerConditionTime();
			//!�v���C���[�̕ϐg���J�n���ꂽ
			if (scene->GetPlayerChangeDirecting())
			{
				if (m_playerConditionTime >= m_playerConditionMaxTime)
				{
					
					m_playerConditionTime = 0.0f;
					scene->SetPlayerConditionTime(m_playerConditionTime);

				}
				float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
				m_playerChangeTime += elapsedTime;//!���Ԃ��~�߂Ă��鎞��
				//!�v���C���[�̕ϐg���Ԃ��߂����玞�Ԃ𓮂���
				if (m_playerChangeTime >= m_playerChangeMaxTime)
				{
					
					m_playerChangeTime = 0.0f;
					scene->SetPlayerChangeDirecting(false);

				}
			}
			//!�ϐg���J�n����Ă��Ȃ��Ƃ�
			else
			{

				float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
				m_dayTime += elapsedTime / m_circleClockSpeed;
				m_playerConditionTime += elapsedTime;
				m_totalTime -= elapsedTime;//!�Q�[�����Ԃ̎擾
				auto m_emissiveChangeTime = App::GetApp()->GetScene<Scene>()->GetEmissiveChangeTime();

				if (m_oneday == static_cast<int>(Oneday::midday))
				{
					m_emissiveChangeTime -= elapsedTime / m_emissiveChangeTimeSpeed;//!�G�~�b�V�u���ς�鎞��
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);

					if (m_emissiveChangeTime <= 0.0f)
					{
						m_oneday = static_cast<int>(Oneday::night);

					}
				}
				

				if (m_oneday == static_cast<int>(Oneday::night))
				{
					m_emissiveChangeTime += elapsedTime / m_emissiveChangeTimeSpeed;//!�G�~�b�V�u���ς�鎞��
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);

					if (m_emissiveChangeTime >= m_emissiveChangeMaxTime)
					{
						m_oneday = static_cast<int>(Oneday::midday);
					}
				}
				

				
				//!30�b�o������܂�30�b�ɖ߂�
				if (m_totalTime <= 0.0f)
				{
					m_totalTime = m_GameTime;

				}

				auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
				scene->SetGameTime(elapsedTime);//!�Q�[���̎��Ԃ�ݒ肷��
				scene->SetDayTime(m_dayTime);//!���v�̎���
				scene->SetPlayerConditionTime(m_playerConditionTime);

			}
			

		}

		////�X�R�A���X�V����
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_totalTime);

	}
	

	void GameStage::CreateLightingCol()
	{
		////�X�e�[�W�ɒu���ꍇ
		//auto ptrMulti = dynamic_pointer_cast<MultiLight>(GetLight());
		//auto light0 = ptrMulti->GetLight(0);
		//auto light1 = ptrMulti->GetLight(1);
		//auto light2 = ptrMulti->GetLight(2);
		////���̌�light0�Ȃǂ�ύX
		//light2.m_DiffuseColor = Col4(1, 1, 1, 1);
		//light2.m_SpecularColor = Col4(1, 1, 1, 1);
		//ptrMulti->SetLight(1, light2);

	}

	void GameStage::OnCreate() {
		
		try {
			auto scene = App::GetApp()->GetScene<Scene>();

			//auto GameMneager =AddGameObject<GameManager>();
			auto m_playerConditionTime = scene->GetPlayerConditionTime();
			m_playerConditionTime = 0.0f;
			scene->SetPlayerConditionTime(m_playerConditionTime);

			scene->SetGoleGateParameter(false);//!��̃p�����[�^�[�̓K��

			//!�G�t�F�N�g�쐬
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			SetPhysicsActive(true);//�����v�Z�L��
			//! �u�A�v���v�I�u�W�F�N�g�̃C���X�^���X���擾����i�C���X�^���X�F�N���X�̎��ԁA�I�u�W�F�N�g�w���̃I�u�W�F�N�g�̂��Ɓj
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//!�V�[���̎擾
			auto m_keyNamber = scene->GetKeyNamber();

			// �t�H���_�̎w��
			auto csvDirectory = DataDir + L"csvFolder\\";

			//!�X�e�[�W�t�@�C���̓ǂݍ���
			m_StageCsv.SetFileName(csvDirectory + L"stage1.csv");
			m_StageCsv.ReadCsv();

			//!Building�t�@�C���̓ǂݍ���
			m_GameStageCsvA.SetFileName(csvDirectory + L"GameStageA.csv");
			m_GameStageCsvA.ReadCsv();
		
			//!Building�t�@�C���̓ǂݍ���2
			m_GameStageCsvB.SetFileName(csvDirectory + L"GameStageB.csv");
			m_GameStageCsvB.ReadCsv();

			//!Building�t�@�C���̓ǂݍ���3
			m_GameStageCsvC.SetFileName(csvDirectory + L"GameStageC.csv");
			m_GameStageCsvC.ReadCsv();

			//!Building�t�@�C���̓ǂݍ���4
			m_GameStageCsvD.SetFileName(csvDirectory + L"GameStageD.csv");
			m_GameStageCsvD.ReadCsv();

			//!KeyPositon�t�@�C���̓ǂݍ���4-1
			m_KeyPositon.SetFileName(csvDirectory + L"KeyPosition" + Util::IntToWStr(m_keyNamber) + L".csv");
			m_KeyPositon.ReadCsv();

			//!MetaPositon�t�@�C���̓ǂݍ���
			m_MeatPositon.SetFileName(csvDirectory + L"MeatPosition" + Util::IntToWStr(m_MeatNumber) + L".csv");
			m_MeatPositon.ReadCsv();

            CreateTimerSprite();//!���Ԃ̃X�v���C�g�̍쐬
			CreateViewLight();//�r���[�ƃ��C�g�̍쐬
			CreateStageFloor();//!�X�e�[�W�̏��̍쐬
			CreateStageWall(); //!�X�e�[�W�̕ǂ̍쐬
			CreateStageBuilding(); //!�X�e�[�W�̌����̍쐬
			CreateKey();//!�J�M�̍쐬
			CreateStageGate(); //!�X�e�[�W�̖�̍쐬
			CreatePlayer();//!�v���[���[�̍쐬
			CerateVillager();//!���l�̍쐬
			CreatePlayBGM();//!BGM�̍쐬
			CreateHeartSprite();//!�v���C���[��HP�̍쐬
			CerateHunter();//!�n���^�[�̍쐬
			CreateAlertlevelGauge();//!�x���x�̃Q�[�W�̍쐬
			CreateArrow();//!���̍쐬
			CreateClockSprite(); //!���v�̃X�v���C�g�̍쐬
			CreateCircleClockSprite(); //!���v�̉~�Ղ̃X�v���C�g�̍쐬
			CreateWoodenBox();//!���̍쐬
			CreateWood();//!�؂̍쐬
			CreateHeadMan();//!�����̍쐬
			CreateMeat();//!���̍쐬
			CreateGameOver();//!�Q�[���I�[�o�[
			CreateMeatGageBackGround();//!�󕠃Q�[�W�̔w�i
			CreateMeatGageFrame();//!�󕠃Q�[�W�̘g
			CreateHungerGage();//!�󕠃Q�[�W
			CreateClockArrow();//!���v�̐j
			CreateDateChangeCommentDay();//!�邩�璋�ɂł�e�N�X�`��
			CreateDateChangeCommentNight();//!�������ɂł�e�N�X�`��
			CreateKeyFrame();//!�J�M�̘g�̍쐬
			CreateCameraman(); //!�J�����}���̍쐬

			auto gameOver = scene->GetGameOver();
			if (gameOver == true)
			{
				CreateGameOverBGM();

			}
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {

		

		m_EfkInterface->OnUpdate();

		auto scene = App::GetApp()->GetScene<Scene>();

		auto& app = App::GetApp();
		auto deltaTime = app->GetElapsedTime();
		m_MeatTime += deltaTime* m_MeatTimeSpeed;
		srand(std::time(0));
		m_MeatNumber = rand() % randomNumber;//!�����_���̏���̐����Ŋ��邱�Ƃł���ȏ�ɂȂ�Ȃ�
		
		scene->SetMeatNamber(m_MeatNumber);//!���̈ʒu�̐������ݒ肳���

		GameTime();
		CreateLightingCol();
		
		//auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto gameOver = scene->GetGameOver();
		if (gameOver == true)
		{

			OnDestroy();//!BGM������

		}
		
		//else { DestroyGameOverBGM(); }

		m_InputHandler.PushHandle(GetThis<GameStage>());

	}

	//!�Q�[���I�[�o�[�̓X�e�[�W��ς��Ȃ��B
	//! �|��郂�[�V�����������ăt�F�[�h�A�E�g���Ĉꖇ�G�ɂȂ�B
	void GameStage::OnDraw()
	{
		auto& camera = GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}
	

	// !BGM�̍Đ�
	void GameStage::CreatePlayBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"bgm", XAUDIO2_LOOP_INFINITE, 0.2f);
	}

	// !�Q�[���I�[�o�[��BGM�̍Đ�
	void GameStage::CreateGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_GameOverBGM = XAPtr->Start(L"GameOver", XAUDIO2_LOOP_INFINITE, 0.1f);

	}

	// !BGM�̃X�g�b�v
	void GameStage::OnDestroy()
	{
        auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);	
	}

	// !�Q�[���I�[�o�[BGM�̍폜
	void GameStage::DestroyGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_GameOverBGM);
	}

	void GameStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto gameOver = scene->GetGameOverSprite();
		if (gameOver == true)
		{
			auto gameOver = scene->GetGameOver();
			gameOver = false;
			scene->SetGameOver(gameOver);

			//�T�E���h�Đ�
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"decision", 0, 1.0f);
			PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			gameOver = false;
			scene->SetGameOverSprite(gameOver);
		}
	}
}
//end basecross
