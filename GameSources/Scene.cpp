
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses()
	{
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!�e�N�X�`��
		wstring strTexture = dataDir +L"Texture\\"+ L"Nomber_3.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		//!�^�C�g�����
		strTexture = dataDir + L"Texture\\"+L"Title.jpg";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		//!�Q�[���I�[�o�[���
		strTexture = dataDir + L"Texture\\" + L"GameOver.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		//!�Q�[���N���A���
		strTexture = dataDir + L"Texture\\"+ L"GameClear.png";
		App::GetApp()->RegisterTexture(L"GAMECLEAR_TX", strTexture);
		//!�L�[�X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"key.png";
		App::GetApp()->RegisterTexture(L"KEY_TX", strTexture);
		//!�v���C���[��HP�X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"PlayerHp.png";
		App::GetApp()->RegisterTexture(L"PlayerHp_TX", strTexture);
		//!���v�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"testTime.png";
		App::GetApp()->RegisterTexture(L"testTime_TX", strTexture);
		//!�r�b�N���}�[�N�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"Surprised.png";
		App::GetApp()->RegisterTexture(L"Surprised_TX", strTexture);
		//!�͂Ăȃ}�[�N�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"LoseSightOf.png";
		App::GetApp()->RegisterTexture(L"LoseSightOf_TX", strTexture);
		//!�댯�x�̃Q�[�W�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"testGauge.png";
		App::GetApp()->RegisterTexture(L"AlertlevelGaugeGauge_TX", strTexture);
		//!�댯�x�̃Q�[�W�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"Arrow.png";
		App::GetApp()->RegisterTexture(L"Arrow_TX", strTexture);


		//!���̃��f���ǂݍ���
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir,L"MayaModel\\" L"StageFloor.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh1);

	
		//!�ǂ̃��f���ǂݍ���
		auto staticModelMesh3 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageWall.bmf");
		App::GetApp()->RegisterResource(L"STAGEWALL_MESH", staticModelMesh3);
	
		//!�����̃��f���ǂݍ���
		auto staticModelMesh4 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"House.bmf");
		App::GetApp()->RegisterResource(L"STAGEBUILDING_MESH", staticModelMesh4);

		//!���̃��f���ǂݍ���
		auto staticModelMesh5 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"Key.bmf");
		App::GetApp()->RegisterResource(L"KEY_MESH", staticModelMesh5);

		//!��̃��f���̓ǂݍ���
		auto staticModelMesh6 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageGate.bmf");
		App::GetApp()->RegisterResource(L"STAGEGATE_MESH", staticModelMesh6);

		//!�n�ʂ̃��f���̓ǂݍ���
		auto staticModelMesh7 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"Ground.bmf");
		App::GetApp()->RegisterResource(L"GROUND_MESH", staticModelMesh7);

		//!�v���C���[�̃��f���̓ǂݍ���
		auto staticModelMesh8 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"PlayerWolf.bmf");
		App::GetApp()->RegisterResource(L"PLAYER_Wolf", staticModelMesh8);

		//!�v���C���[�̃��f���̓ǂݍ���
		auto staticModelMesh10 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"MainCharacter.bmf");
		App::GetApp()->RegisterResource(L"PLAYER_HUMAN", staticModelMesh10);


		//!��̃��f���̓ǂݍ���
		auto staticModelMesh9 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"StageFence.bmf");
		App::GetApp()->RegisterResource(L"STAGE_FENCE", staticModelMesh9);

		//���f��
		//�{�[�����f���̒ʏ탊�\�[�X
		auto humanMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"Enemy_Animation.bmf");
		App::GetApp()->RegisterResource(L"Player_WalkAnimation_MESH", humanMultiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		humanMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"Enemy_Animation.bmf");
		App::GetApp()->RegisterResource(L"Player_WalkAnimation_MESH_WITH_TAN", humanMultiModelMesh);

		//���f��
		//�{�[�����f���̒ʏ탊�\�[�X
		auto playrWolfMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"Wolf_Animation.bmf");
		App::GetApp()->RegisterResource(L"PlayerWolf_WalkAnimation_MESH", playrWolfMultiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		playrWolfMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"Wolf_Animation.bmf");
		App::GetApp()->RegisterResource(L"PlayerWolf_WalkAnimation_MESH_WITH_TAN", playrWolfMultiModelMesh);

		//���f��
		//�{�[�����f���̒ʏ탊�\�[�X
		auto EnemyHunterMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"EnemyHunter_Animation.bmf");
		App::GetApp()->RegisterResource(L"Enemy_WalkAnimation_MESH", EnemyHunterMultiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		EnemyHunterMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"EnemyHunter_Animation.bmf");
		App::GetApp()->RegisterResource(L"Enemy_WalkAnimation_MESH_WITH_TAN", EnemyHunterMultiModelMesh);


		//���f��
	//�{�[�����f���̒ʏ탊�\�[�X
		auto EnemyVillagerMultiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" L"EnemyVillager_Animation.bmf");
		App::GetApp()->RegisterResource(L"EnemyVillager_WalkAnimation_MESH", EnemyVillagerMultiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		EnemyVillagerMultiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" L"EnemyVillager_Animation.bmf");
		App::GetApp()->RegisterResource(L"EnemyVillager_WalkAnimation_MESH_WITH_TAN", EnemyVillagerMultiModelMesh);

		//�@���}�b�v
		strTexture = dataDir + L"PlalyerBanpMap.png";
		App::GetApp()->RegisterTexture(L"OBJECT_NORMAL_TX", strTexture);

		//!BGM
		wstring strMusic = dataDir + L"Sound\\" L"BGM.wav";//�Q�[������BGM
		App::GetApp()->RegisterWav(L"bgm", strMusic);

		strMusic = dataDir + L"Sound\\" L"Title.wav";//�^�C�g����ʂ�BGM
		App::GetApp()->RegisterWav(L"TitleBGM", strMusic);

		strMusic = dataDir + L"Sound\\" L"walk.wav";//�^�C�g����ʂ�BGM
		App::GetApp()->RegisterWav(L"WalkBGM", strMusic);

		wstring decisionWav = dataDir + "Sound\\" L"decision.wav";//�{�^�����������Ƃ��̉�
		App::GetApp()->RegisterWav(L"decision", decisionWav);

		wstring killWav = dataDir + "Sound\\" L"kill.wav";//�G���E�������̉�
		App::GetApp()->RegisterWav(L"kill", killWav);

		


	}

	//!�삯�t�����G�̍쐬

	//!�G(�X�P�[���A���[�e�C�V�����A�|�W�V����)�̍\����
	struct TransformCreate {
		//!�\���̃e���v���[�g
		Vec3 scale = Vec3(0.0f);//!�傫��
		Vec3 rotation = Vec3(0.0f);//!��]
		Vec3 position = Vec3(0.0f);//!�ʒu
		wstring EnemykeyName = L"";//!���l�̏��񃋁[�g�̃L�[�t���[�����擾

		TransformCreate() :
			TransformCreate(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), wstring(L""))
		{}
		//!�\���̂̏�����
		TransformCreate(
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
	std::vector<TransformCreate>TransformDate(const wstring& folderName, const wstring& fileName, const wstring& keyName) {
		std::vector<TransformCreate>result;//!�ϐ���
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
			result.push_back(TransformCreate(Scale, Rot, Pos, EnemykeyName));

		}

		return result;
	}



	//!�p�g���[���|�C���g�̍\����
	struct PointCreate {
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0.0f);

		PointCreate() :
			PointCreate(vector<Vec3>(0.0f)) {}
		PointCreate(const std::vector<Vec3>& patrolPoints) :
			m_patorlPositions(patrolPoints)
		{}
	};

	//!�p�g���[���|�C���g
	PointCreate PointDate(const wstring& folderName, const wstring& fileName, const wstring& keyName)
	{
		PointCreate PatorlPoint;

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


	void Scene::CreateEnemy()
	{
		
		auto datasHunter = TransformDate(L"csvFolder\\", L"RushedEnemy.csv", L"Hunter");//!�n���^�[��Excel�̃f�[�^
		for (auto dataHunter : datasHunter)
		{
			auto pointData = PointDate(L"csvFolder\\", L"Point.csv", dataHunter.EnemykeyName);//!�G�̏���|�C���g�̖��O�����o��
			auto HunterPtr = GetActiveStage()->AddGameObject<Hunter>(dataHunter.scale, dataHunter.rotation, dataHunter.position, pointData.m_patorlPositions);//!���������n���^�[�̍쐬
			GetActiveStage()->AddGameObject<LoseSightOf>(HunterPtr);
			GetActiveStage()->AddGameObject<SurprisedSprite>(HunterPtr);

		}
		
	}

	void Scene::SetAlertlevelCount(int AlertlevelCount)
	{
		//m_alertLevelCount�ƈႤ�Ȃ�
		if (m_AlertlevelCount != AlertlevelCount) {

			//�A���[�g���x����1�Ȃ�
			if (AlertlevelCount == 1) {

				//�G�̐���
				CreateEnemy();
			}

		}


	}
	void Scene::OnCreate(){
		try {
			CreateResourses();//!���\�[�X�쐬
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}

	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage")//!�^�C�g���X�e�[�W
		{
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToGameOverStage")//!�Q�[���I�[�o�[�X�e�[�W
		{
			ResetActiveStage<GameOverStage>();
		}
		else if (event->m_MsgStr == L"ToGameClearStage")//!�Q�[���N���A�X�e�[�W
		{
			ResetActiveStage<GameClearStage>();
		}
	}

}
//end basecross
