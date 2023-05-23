/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "HeadManComment.h"
#include "Meat.h"
#include "OpeningCamera.h"
#include "OpeningCameraMan.h"
#include "GameUI.h"
#include "GameStageCanvas.h"

namespace basecross {

	constexpr int alertlevelFirst = 1;				  //!�댯�x���x��1
	constexpr int randomNumber = 4;					  //!�����_���̍ő�l
	constexpr float m_MeatTimeSpeed = 22.0f;		  //!���������_���ɂ���l�̕ω�����X�s�[�h
	constexpr float m_playerChangeMaxTime = 2.0f;	  //!�v���C���[��ϐg���鎞��
	constexpr float m_circleClockSpeed = 10.0f;		  //!���v����]������X�s�[�h
	constexpr float m_opningCameraTime = 6.0f;		  //!�I�[�v�j���O�J�����̎���
	constexpr float m_playerConditionMaxTime = 62.0f; //!�v���C���[�̏�Ԃ̍ő厞��
	constexpr float m_emissiveChangeTimeSpeed = 32.0f;//!���邳��ς��鎞��
	constexpr float m_emissiveReset = 1.0f;			  //!���邳�̃��Z�b�g
	constexpr float m_emissiveChangeMaxTime = 1.0f;   //!����̕ύX
	constexpr float m_celladjustment = 8.6f;		  //!�Z���̕�����
	constexpr float m_cellPosadjustment = 10.0f;	  //!�Z���̃|�W�V�����𒲐�
	constexpr float m_bgmVolume=0.2f;				  //!BGM�̉���
	
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {

		//OpeningCameraView�p�̃r���[
		m_openingCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_openingCameraView->SetCamera(ptrOpeningCamera);//!�I�[�v�j���O�J�����̐ݒ�

		//�r���[�̃J�����̐ݒ�
		//MyCamera�p�̃r���[
		m_myCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(m_startEye);				//!�J�����̏����ʒu
		ptrMyCamera->SetAt(m_startAt);					//!�J�����̎��_
		m_myCameraView->SetCamera(ptrMyCamera);			//!�}�C�J�����̐ݒ�
		SetView(m_openingCameraView);					//!�I�[�v�j���O�J�����̃r���[�ɐݒ肷��
		m_CameraSelect = CameraSelect::openingCamera;	//!���݂̃J�����̏��

		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();


	}

	//!�J�����}���̍쐬 
	void GameStage::CreateCameraman()
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraMan>();//!�J�����}���̍쐬
		//�V�F�A�z���OpeningCameraman��ǉ�
		SetSharedGameObject(L"OpeningCameraMan", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_openingCameraView->GetCamera());//!�I�[�v�j���O�J�����̎擾
		//!�I�[�v�j���O�J���������鎞
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);	//!�I�[�v�j���O�J�����ɐݒ�
			SetView(m_openingCameraView);							//!�I�[�v�j���O�J�������r���[�ɐݒ�
			m_CameraSelect = CameraSelect::openingCamera;			//!���݂̃J�����̏��
		}


	}
	//!�J�������v���C���[�̈ʒu�ɖ߂�����
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_myCameraView->GetCamera());//!�}�C�J�����̎擾
		//!�}�C�J���������鎞
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);//!�^�[�Q�b�g�I�u�W�F�N�g�̐ݒ�
			SetView(m_myCameraView);				//!m_MyCameraView���g��
			m_CameraSelect = CameraSelect::myCamera;//!�J�����̏��
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
				float XPos = (float)((int)j - m_celladjustment) * m_cellPosadjustment;
				float Ypos = 5.0f;
				float ZPos = (float)(m_celladjustment - (int)i) * m_cellPosadjustment;
				if (Tokens[j] == L"1")
				{
					AddGameObject<StageBuilding>(m_BuildingScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
				}
			}
		}
	}


	//!���̍쐬
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
				float XPos = (float)((int)j - m_celladjustment) * m_cellPosadjustment;
				float Ypos = 3.0f;
				float ZPos = (float)(m_celladjustment - (int)i) * m_cellPosadjustment;
				if (Tokens[j] == L"2")//2�̎��ɃQ�[���X�e�[�W�ɒǉ�
				{
					AddGameObject<Key>(Vec3(2.0f, 4.0f, 1.0f), Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
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
				float XPos = (float)((int)j - m_celladjustment) * m_cellPosadjustment;
				float Ypos = 3.0f;
				float ZPos = (float)(m_celladjustment - (int)i) * m_cellPosadjustment;
				if (Tokens[j] == L"3")//3�̎��ɃQ�[���X�e�[�W�ɒǉ�
				{
					AddGameObject<WoodenBox>(m_woodenBoxScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
					
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
				float XPos = (float)((int)j - m_celladjustment) * m_cellPosadjustment;
				float Ypos = 3.0f;
				float ZPos = (float)(m_celladjustment - (int)i) * m_cellPosadjustment;
				if (Tokens[j] == L"4")//4�̎��ɃQ�[���X�e�[�W�ɒǉ�
				{
					AddGameObject<Wood>(m_woodScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
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
				float XPos = (float)((int)j - m_celladjustment) * m_cellPosadjustment;
				float Ypos = 4.0f;
				float ZPos = (float)(m_celladjustment - (int)i) * m_cellPosadjustment;
				if (Tokens[j] == L"5")//5�̎��ɃQ�[���X�e�[�W�ɒǉ�
				{
					AddGameObject<Meat>(m_meteScale, Vec3(0.0f), Vec3(XPos, Ypos, ZPos));
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

		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DataDir;								//!�f�[�^
		App::GetApp()->GetDataDirectory(DataDir);		//!�f�[�^���擾
		auto fullPass = DataDir + folderName + fileName;//!�t�@�C���̓���

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);					//!���肵��csv�t�@�C����ǂݍ���
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);			//!0�Ԗڂ̃J������L"Villager"�ł���s�𔲂��o��
		//!�擾�����s�̏��
		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;						//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');	//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')
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
		PointCreateDate PatorlPoint;//!����|�C���g��ۑ�����

		vector<wstring>LineVec;
		auto& app = App::GetApp();//!�A�v���̎擾
		wstring DataDir;								//!�A�v���̎擾
		App::GetApp()->GetDataDirectory(DataDir);		//!�f�[�^
		auto fullPass = DataDir + folderName + fileName;//!�t�@�C���̓���
		//!�f�[�^���擾								 
		CsvFile csvFile;								
		csvFile.SetFileName(fullPass);					//!���肵��csv�t�@�C����ǂݍ���
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);			//!0�Ԗڂ̃J������keyName�ł���s�𔲂��o��
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


	void GameStage::UIDrawActive(bool t)
	{
		//!���Ԃ̃X�v���C�g�̕\��
		auto timer = GetSharedGameObject<Timer>(L"Time");
		timer->SetDrawActive(t);


	}
	//!���l�̍쐬
	void GameStage::CerateVillager()
	{
		auto group = CreateSharedObjectGroup(L"Villager_ObjGroup");				//!�O���[�v���擾

		auto datas = TransformDate(L"csvFolder\\", L"Enemy.csv", L"Villager");	//!Excel�̃f�[�^�w��
		
		for (auto& data : datas) {

		
			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", data.EnemykeyName);//!���l�̑傫�����������Ă�CSV����L�[�l�[�������o����������s����I��
			

			auto VillagerPtr=AddGameObject<Villager>(data.scale, data.rotation, data.position, pointData.m_patorlPositions);
		
		
			AddGameObject<LoseSightOf>(VillagerPtr);	//!���������Ƃ��̔|���̍쐬
			AddGameObject<SurprisedSprite>(VillagerPtr);//!�������Ƃ��̔|���̍쐬
			
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

			AddGameObject<LoseSightOf>(HunterPtr);		//!���������Ƃ��̔|���̍쐬
			AddGameObject<SurprisedSprite>(HunterPtr);	//!�������Ƃ��̔|���̍쐬
		}

	}
	//!�����̍쐬
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

	//!�I�[�v�j���O�J�����̐ݒ�
	void GameStage::OpeningCameraBooting(float time)
	{
		auto scene = App::GetApp()->GetScene<Scene>();		//!�V�[���̎擾
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		m_gameStartTime += elapsedTime;						//!�G���p�\�^�C���𑫂��Ď��Ԃ̐���
		//!�I�[�v�j���O�J�����̎��Ԃ��߂�����
		if (m_gameStartTime >= time)
		{
			UIDrawActive(true);						//!�e�N�X�`���̕\�������Ȃ�
			auto gameStrat = scene->GetGameStrat();	//!�I�[�v�j���O�J�����̏�Ԃ��擾
			gameStrat = false;						//!�I�[�v�j���O�J�����̏�Ԃ��I�t
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);//!�I�[�v�j���O�J�����̏�Ԃ�ݒ�

			
		}
		else
		{
			auto scene = App::GetApp()->GetScene<Scene>();				//!�V�[���̎擾
			auto m_emissiveChangeTime = scene->GetEmissiveChangeTime();	//!���邳��ύX���鎞�Ԃ̎擾
			m_emissiveChangeTime = m_emissiveReset;						//!���邳��ύX���鎞�Ԃ̃��Z�b�g
			scene->SetEmissiveChangeTime(m_emissiveChangeTime);			//!���邳��ύX���鎞�Ԃ̐ݒ�
			auto gameStrat = scene->GetGameStrat();						//!�Q�[���X�^�[�g���Ă��邩�̎擾
			gameStrat = true;											//!�Q�[���X�^�[�g����				
			App::GetApp()->GetScene<Scene>()->SetGameStrat(gameStrat);	//!�Q�[���X�^�[�g���Ă��邩�̐ݒ�
			UIDrawActive(false);										//!�e�N�X�`���̕\��������
			
		}

	}


	void GameStage::GameTime()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		OpeningCameraBooting(m_opningCameraTime);			//!�I�[�v�j���O�J�����̎��Ԓ��̏���
		auto scene = App::GetApp()->GetScene<Scene>();		//!�V�[���̎擾
		auto gameStrat = scene->GetGameStrat();				//!�X�^�[�g���Ă��邩�ǂ����̎擾


		//!�I�[�v�j���O�J�������I������Ƃ�
		if (!gameStrat)
		{
			auto scene = App::GetApp()->GetScene<Scene>();				 //!�V�[���̎擾
			auto m_playerConditionTime = scene->GetPlayerConditionTime();//!�v���C���[�̕ϐg���Ԃ̎擾
			//!�v���C���[�̕ϐg���J�n���ꂽ
			if (scene->GetPlayerChangeDirecting())
			{
				//!�v���C���[�̕ϐg���I�������
				if (m_playerConditionTime >= m_playerConditionMaxTime)
				{
					m_playerConditionTime = 0.0f;						 //!�ϐg���Ԃ̃��Z�b�g
					scene->SetPlayerConditionTime(m_playerConditionTime);//!�ϐg���Ԃ̃��Z�b�g�ݒ�
				}
				float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
				m_playerChangeTime += elapsedTime;					//!���Ԃ��~�߂Ă��鎞��

				//!�v���C���[�̕ϐg���Ԃ��߂����玞�Ԃ𓮂���
				if (m_playerChangeTime >= m_playerChangeMaxTime)
				{
					
					m_playerChangeTime = 0.0f;				//!���Ԃ��~�߂Ă��鎞�Ԃ̃��Z�b�g
					scene->SetPlayerChangeDirecting(false);//!���Ԃ��~�߂Ă��鎞�Ԃ̐ݒ�

				}
			}

			//!�ϐg���J�n����Ă��Ȃ��Ƃ�
			else
			{
				float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
				m_dayTime += elapsedTime / m_circleClockSpeed;		//!���Ԃ���]������X�s�[�h�Ŋ���
				m_playerConditionTime += elapsedTime;				//!�ϐg�̎��Ԃɉ��Z
				m_totalTime -= elapsedTime;							//!�Q�[�����Ԃ̎擾
				auto m_emissiveChangeTime = App::GetApp()->GetScene<Scene>()->GetEmissiveChangeTime();//!���邳�̕ύX

				//!���̎�
				if (m_oneday == static_cast<int>(Oneday::midday))
				{
					m_emissiveChangeTime -= elapsedTime / m_emissiveChangeTimeSpeed;//!�G�~�b�V�u���ς�鎞��
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);				//!�G�~�b�V�u���ς�鎞�Ԃ̐ݒ�
					
					//!��̎��ԂɂȂ�����
					if (m_emissiveChangeTime <= 0.0f)
					{
						m_oneday = static_cast<int>(Oneday::night);//!��ɕω�

					}
				}
				
				//!��̎�
				if (m_oneday == static_cast<int>(Oneday::night))
				{
					m_emissiveChangeTime += elapsedTime / m_emissiveChangeTimeSpeed;//!�G�~�b�V�u���ς�鎞��
					scene->SetEmissiveChangeTime(m_emissiveChangeTime);				//!�G�~�b�V�u���ς�鎞�Ԃ̐ݒ�

					//!���̎��ԂɂȂ�����
					if (m_emissiveChangeTime >= m_emissiveChangeMaxTime)
					{
						m_oneday = static_cast<int>(Oneday::midday);//!���ɕω�
					}
				}
				

				
				//!30�b�o������܂�30�b�ɖ߂�
				if (m_totalTime <= 0.0f)
				{
					m_totalTime = m_GameTime;//!�Q�[�����ԃ��Z�b�g

				}

				auto scene = App::GetApp()->GetScene<Scene>();		  //!�V�[���̎擾
				scene->SetGameTime(elapsedTime);					  //!�Q�[���̎��Ԃ�ݒ肷��
				scene->SetDayTime(m_dayTime);						  //!���v�̎���
				scene->SetPlayerConditionTime(m_playerConditionTime); //!�v���C���[�̏�Ԏ��Ԃ�ݒ�

			}
			

		}

		////�X�R�A���X�V����
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_totalTime);

	}
	

	

	void GameStage::OnCreate() {
		
		try {
			auto scene = App::GetApp()->GetScene<Scene>();					//!�V�[���̎擾
			auto m_playerConditionTime = scene->GetPlayerConditionTime();	//!�v���C���[�̏�Ԃ̎���
			m_playerConditionTime = 0.0f;									//!�v���C���[�̏�Ԃ̎��Ԃ̏�����
			scene->SetPlayerConditionTime(m_playerConditionTime);			//!�v���C���[�̏�Ԃ̎��Ԃ̐ݒ�
			scene->SetGoleGateParameter(false);								//!��̃p�����[�^�[�̓K��
			//!�G�t�F�N�g�쐬
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();
			SetPhysicsActive(true);											//�����v�Z�L��
			//! �u�A�v���v�I�u�W�F�N�g�̃C���X�^���X���擾����i�C���X�^���X�F�N���X�̎��ԁA�I�u�W�F�N�g�w���̃I�u�W�F�N�g�̂��Ɓj
			auto& app = App::GetApp();										//!�A�v���̎擾
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

			CreateViewLight();//�r���[�ƃ��C�g�̍쐬
			CreateStageFloor();//!�X�e�[�W�̏��̍쐬
			CreateStageWall(); //!�X�e�[�W�̕ǂ̍쐬
			CreateStageBuilding(); //!�X�e�[�W�̌����̍쐬
			CreateKey();//!�J�M�̍쐬
			CreateStageGate(); //!�X�e�[�W�̖�̍쐬
			CreatePlayer();//!�v���[���[�̍쐬
			CerateVillager();//!���l�̍쐬
			CreatePlayBGM();//!BGM�̍쐬
			CerateHunter();//!�n���^�[�̍쐬
			CreateWoodenBox();//!���̍쐬
			CreateWood();//!�؂̍쐬
			CreateHeadMan();//!�����̍쐬
			CreateMeat();//!���̍쐬
			CreateCameraman(); //!�J�����}���̍쐬

			//!�Q�[���X�e�[�W��UI�L�����o�X�̍쐬
			AddGameObject<GameStageCanvas>();

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

		m_EfkInterface->OnUpdate();						//!�G�t�F�N�g�̍X�V
		auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
		auto& app = App::GetApp();						//!�A�v���̎擾
		auto deltaTime = app->GetElapsedTime();			//!�G���p�\�^�C���̎擾
		m_MeatTime += deltaTime* m_MeatTimeSpeed;		//!���̎��Ԃɉ��Z
		srand(std::time(0));
		m_MeatNumber = rand() % randomNumber;			//!�����_���̏���̐����Ŋ��邱�Ƃł���ȏ�ɂȂ�Ȃ�
		scene->SetMeatNamber(m_MeatNumber);				//!���̈ʒu�̐������ݒ肳���
		GameTime();
		auto gameOver = scene->GetGameOver();			//!�Q�[���I�[�o�[���Ă��邩�ǂ���
		//!�Q�[���I�[�o�[�̎�
		if (gameOver == true)
		{

			OnDestroy();//!BGM������

		}
		
		m_InputHandler.PushHandle(GetThis<GameStage>());//!�R���g���[���̃C���v�b�g�n���h���̎擾
		m_InputHandlerReset.PushHandleReset(GetThis<GameStage>());

	}
	//!�G�t�F�N�g
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
		m_BGM = XAPtr->Start(L"bgm", XAUDIO2_LOOP_INFINITE, m_bgmVolume);
	}

	// !�Q�[���I�[�o�[��BGM�̍Đ�
	void GameStage::CreateGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_GameOverBGM = XAPtr->Start(L"GameOver", XAUDIO2_LOOP_INFINITE, m_bgmVolume);

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
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʂ̎擾
		auto scene = App::GetApp()->GetScene<Scene>();					 //!�V�[���̎擾
		auto gameOver = scene->GetGameOverSprite();						 //!�Q�[���I�[�o�[�X�v���C�g�̎擾
		//!�Q�[���I�[�o�[�̎�
		if (gameOver == true)
		{
			auto gameOver = scene->GetGameOver();//!�Q�[���I�[�o�[���ǂ����̎擾
			gameOver = false;					 //!�Q�[���I�[�o�[���ǂ����̎擾
			scene->SetGameOver(gameOver);		 //!�Q�[���I�[�o�[���ǂ����̐ݒ�

			//�T�E���h�Đ�
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"decision", 0, volume);
			PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");//!�^�C�g���X�e�[�W�ɑJ��
			gameOver = false;//!�Q�[���I�[�o�[����߂�
			scene->SetGameOverSprite(gameOver);//!�Q�[���I�[�o�[���ǂ����̐ݒ�
		}
	}

	//!���Z�b�g�{�^��
	void GameStage::OnPushReset()
	{
		//!�^�C�g����ʂ̑J��
		PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	}
}
//end basecross
