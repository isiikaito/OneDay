/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadMan.h"
#include "HeadManComment.h"
#include "Meat.h"
#include "KeyFrame.h"
#include "MeatGageBackground.h"
#include "MeatGageFrame.h"
#include "HungerGage.h"


namespace basecross {

	constexpr int alertlevelFirst = 1;
	constexpr int randomNumber = 4;
	constexpr float m_MeatTimeSpeed = 22.0f;
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();


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
					AddGameObject<WoodenBox>(Vec3(5.0f, 5.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(XPos, 3.0f, ZPos));
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

	void GameStage:: CreateGameOver()
	{

		auto GameOver=AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
		SetSharedGameObject(L"GameOverSprite", GameOver);
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
		AddGameObject<MeatGageFrame>(
			L"Frame_TX",//!�e�N�X�`��
			true,
			Vec2(350.0f, 150.0f),//�傫��
			Vec2(-440.0f, -300.0f)//���W
			);
	}

	void GameStage::CreateHungerGage()
	{
		AddGameObject<HungerGage>(
			L"Full_TX",//!�e�N�X�`��
			true,
			Vec2(300.0f, 120.0f),//�傫��
			Vec2(-440.0f, -300.0f)//���W
			);
	}

	void GameStage::CreateMeatGageBackGround()
	{
		AddGameObject<MeatGageBackGround>
			(
			L"Background_TX",//!�e�N�X�`��
			true,
			Vec2(350.0f, 150.0f),//�傫��
			Vec2(-440.0f, -300.0f)//���W
			);
	}

	void GameStage::CreateKeyFrame()
	{
		AddGameObject<KeyFrame>(
			L"KEY_TX",//!�e�N�X�`��
			true,
			Vec2(150.0f, 150.0f),//�傫��
			Vec2(300.0f , -320.0f)//���W
			);
	}

	void GameStage::CreateHeartSprite()
	{
		AddGameObject<PlayerHeartSpriteRight>
			(
			L"PlayerHp_TX",
			true,
			Vec2(70.0f, 70.0f),
			Vec2(550.0f, 270.0f)
			);

		AddGameObject<PlayerHeartSpriteMiddle>
			(
				L"PlayerHp_TX",
				true,
				Vec2(70.0f, 70.0f),
				Vec2(460.0f, 270.0f)
				);

		AddGameObject<PlayerHeartSpriteLeft>
			(
				L"PlayerHp_TX",
				true,
				Vec2(70.0f, 70.0f),
				Vec2(370.0f, 270.0f)
				);


	}

	void GameStage::CreateAlertlevelGauge()
	{

		AddGameObject<AlertlevelGauge>
			(
				L"AlertlevelGaugeGauge_TX",
				true,
				Vec2(300.0f, 100.0f),
				Vec2(460.0f, 350.0f)
				);
	}

	void GameStage::CreateArrow()
	{
		//!���̍쐬
		AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(50.0f, 70.0f),
				Vec2(390.0f, 330.0f)
				);

		AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(50.0f, 70.0f),
				Vec2(-550.0f, 200.0f)
				);

	}

	// !���v�̃X�v���C�g�̍쐬
	void GameStage::CreateClockSprite()
	{
		AddGameObject<ClockSprite>
			(
				L"Clock_TX",
				true,
				Vec2(350.0f, 250.0f),
				Vec2(-460.0f, 290.0f)
				);

	}

	// !���v�̉~�Ղ̃X�v���C�g�̍쐬
	void GameStage::CreateCircleClockSprite()
	{
		AddGameObject<CircleClockSprite>
			(
				L"Circle_TX",
				true,
				Vec2(130.0f, 130.0f),
				Vec2(-553.0f, 263.0f)
				);

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
		
		for (auto data : datas) {


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

	void GameStage::GameTime()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime;
		if (m_TotalTime <= 0.0f) {
			m_TotalTime = m_GameTime;
		}
		////�X�R�A���X�V����
		auto ptrScor = GetSharedGameObject<Timer>(L"Time");
		ptrScor->SetScore(m_TotalTime);

		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		scene->SetGameTime(elapsedTime);

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

			//!�G�t�F�N�g�쐬
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();

			SetPhysicsActive(true);//�����v�Z�L��
			//! �u�A�v���v�I�u�W�F�N�g�̃C���X�^���X���擾����i�C���X�^���X�F�N���X�̎��ԁA�I�u�W�F�N�g�w���̃I�u�W�F�N�g�̂��Ɓj
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto scene = App::GetApp()->GetScene<Scene>();
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
			//CreatePlayBGM();//!BGM�̍쐬
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
		auto time = app->GetElapsedTime();
		m_MeatTime += time* m_MeatTimeSpeed;
		srand(m_MeatTime);
		m_MeatNumber = rand() % randomNumber;
		
		scene->SetMeatNamber(m_MeatNumber);

		GameTime();
		CreateLightingCol();
		
		//auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto gameOver = scene->GetGameOver();
		if (gameOver == true)
		{
			OnDestroy();

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
		m_BGM = XAPtr->Start(L"bgm", XAUDIO2_LOOP_INFINITE, 0.3f);
	}

	// !�Q�[���I�[�o�[��BGM�̍Đ�
	void GameStage::CreateGameOverBGM()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		m_GameOverBGM = XAPtr->Start(L"GameOver", XAUDIO2_LOOP_INFINITE, 0.3f);

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
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"decision", 0, 1.0f);
			PostEvent(0.0f, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			gameOver = false;
			scene->SetGameOverSprite(gameOver);
		}
	}
}
//end basecross
