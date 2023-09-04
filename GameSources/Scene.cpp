
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionStage.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::RoadTexture(const wstring& TextureName, const wstring& UseTextureName)
	{
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!�e�N�X�`��
		wstring strTexture = dataDir + L"Texture\\" + TextureName;
		App::GetApp()->RegisterTexture(UseTextureName, strTexture);
	}

	void Scene::RoadSound(const wstring& soundDataName, const wstring& soundName)
	{
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);//!�T���v���̂��߃��f�B�A�f�B���N�g�����擾
		wstring strMusic = dataDir + L"Sound\\" + soundDataName;
		App::GetApp()->RegisterWav(soundName, strMusic);
	}

	//!�X�^�e�B�b�N���f���̓ǂݍ���
	void Scene::RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName)
	{
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);

		App::GetApp()->RegisterResource(
			staticModelMeshName,
			MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" + staticModelbmfName + L".bmf")
		);

	}

	//!�{�[���t�����f���̓ǂݍ���
	void Scene::RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName)
	{
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);

		//!�{�[�����f���̒ʏ탊�\�[�X
		App::GetApp()->RegisterResource(BoneModelMeshName,
			MeshResource::CreateBoneModelMesh(dataDir, L"MayaModel\\" + BoneModelbmfName + L".bmf"));

		//! �{�[�����f���̃^���W�F���g�t�����\�[�X
		App::GetApp()->RegisterResource(BomeModelMeshTangentName,
			MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"MayaModel\\" + BoneModelbmfName + L".bmf")
		);

	}

	void Scene::CreateResourses()
	{
		//!�e�N�X�`��

		//!���v�̉~�Ղ̃X�v���C�g
		RoadTexture(L"Circle.png", L"Circle_TX");
		//!�Q�[�W�̔w�i
		RoadTexture(L"Background.png", L"Background_TX");
		//!�Q�[�W�̃t���[��
		RoadTexture(L"Frame.png", L"Frame_TX");
		//!�Q�[�W
		RoadTexture(L"FullGage.png", L"Full_TX");
		//!�����̃R�����g
		RoadTexture(L"HeadManCommet1.png", L"HeadManCommet1_TX");
		RoadTexture(L"HeadManCommet2.png", L"HeadManCommet2_TX");
		RoadTexture(L"HeadManCommet3.png", L"HeadManCommet3_TX");
		//!�邩�璋�ɂȂ����Ƃ��ɏo��e�N�X�`��
		RoadTexture(L"QuestMessage_Noon.png", L"CommentDay_TX");
		//!�������ɂȂ�����ł�e�N�X�`��
		RoadTexture(L"QuestMessage_Night.png", L"CommentNignt_TX"); 
		//!�����̎擾
		RoadTexture(L"Nomber_3.png", L"NUMBER_TX");
		//!�댯�x�̃Q�[�W�̃X�v���C�g
		RoadTexture(L"Arrow.png", L"Arrow_TX");
		//!�x���x�Q�[�W
		RoadTexture(L"testGauge.png", L"AlertlevelGaugeGauge_TX");
		//!�͂Ăȃ}�[�N�̃X�v���C�g
		RoadTexture(L"LoseSightOf.png", L"LoseSightOf_TX");
		//!�r�b�N���}�[�N�̃X�v���C�g
		RoadTexture(L"Surprised.png", L"Surprised_TX");
		//!���v�̃X�v���C�g
		RoadTexture(L"Clock.png", L"Clock_TX");
		//!�v���C���[��HP�X�v���C�g
		RoadTexture(L"PlayerHp.png", L"PlayerHp_TX");
		//!�L�[�X�v���C�g
		RoadTexture(L"key.png", L"KEY_TX");
		//!�Q�[���N���A���
		RoadTexture(L"GameClear.png", L"GAMECLEAR_TX");
		//!�Q�[���I�[�o�[���
		RoadTexture(L"GameOver.png", L"GAMEOVER_TX");

		RoadTexture(L"Title.jpg", L"MESSAGE_TX");
		//!�J�M�̘g
		RoadTexture(L"ItemField.png", L"ItemField_TX");
		//!������1�̃e�N�X�`��
		RoadTexture(L"Explanation_01.png", L"DescriptionSprite1_TX");
		//!������2�̃e�N�X�`��
		RoadTexture(L"Explanation_02.png", L"DescriptionSprite2_TX");
		//!�@���}�b�v�̃e�N�X�`��
		RoadTexture(L"PlalyerBanpMap.png", L"OBJECT_NORMAL_TX");
	    //!���̃��f��
		RoadStaticModelMesh(L"StageFloor", L"STAGEFLOOR_MESH");
		//!�{�b�N�X�̒ǉ�
		RoadStaticModelMesh(L"Box", L"BOX_MESH");
		
		//!�ǂ̃��f���ǂݍ���
		RoadStaticModelMesh(L"StageWall", L"STAGEWALL_MESH");
		//!�����̃��f���ǂݍ���
		RoadStaticModelMesh(L"House", L"STAGEBUILDING_MESH");
		//!���̃��f���ǂݍ���
		RoadStaticModelMesh(L"Key", L"KEY_MESH");
		//!�n�ʂ̃��f���̓ǂݍ���
		RoadStaticModelMesh(L"Ground", L"GROUND_MESH");
		//!��̃��f���̓ǂݍ���
		RoadStaticModelMesh(L"StageFence", L"STAGE_FENCE");
		//!��̃��f���̓ǂݍ���
		RoadStaticModelMesh(L"Wood", L"STAGE_WOOD");
		//!���̃��f���̓ǂݍ���
		RoadStaticModelMesh(L"Meat", L"MEAT_MESH");
		
		//�{�[�����f���̒ʏ탊�\�[�X
		// �v���C���[�i�T�j�̃A�j���[�V����
		RoadBoneModel(L"Wolf_Animation", L"PlayerWolf_WalkAnimation_MESH", L"PlayerWolf_WalkAnimation_MESH_WITH_TAN");
		// �n���^�[�̃A�j���[�V����
		RoadBoneModel(L"Hunter_Animation", L"EnemyHunter_Animation_MESH", L"EnemyHunter_Animation_MESH_WITH_TAN");

		// ���l�̃A�j���[�V����
		RoadBoneModel(L"EnemyVillager_Animation", L"EnemyVillager_WalkAnimation_MESH", L"EnemyVillager_WalkAnimation_MESH_WITH_TAN");

		// �v���C���[�i�l�ԁj�̃A�j���[�V����
		RoadBoneModel(L"Player_Animation", L"Player_WalkAnimation2_MESH", L"Player_WalkAnimation2_MESH_WITH_TAN");

		// ���̃A�j���[�V����
		RoadBoneModel(L"Gate_Animation", L"GateAnimation_MESH", L"GateAnimation_MESH_WITH_TAN");
		
		

		//!�Q�[������BGM
		RoadSound(L"BGM.wav", L"bgm");
		//����H�ׂ鉹
		RoadSound(L"MeatEat.wav", L"MeatEat");
		//�ؔ��j��
		RoadSound(L"WoodBoxBreak.wav", L"WoodBoxBreak");
		//�^�C�g����ʂ�BGM
		RoadSound(L"Title.wav", L"TitleBGM");
		//������
		RoadSound(L"walk.wav", L"WalkBGM");
		//�{�^�����������Ƃ��̉�
		RoadSound(L"decision.wav", L"decision");
		//�G���E�������̉�
		RoadSound(L"kill.wav", L"kill");
		//�T�ɕϐg�������̉��i��
		RoadSound(L"howling.wav", L"howling");
		//���l�̋��ѐ�
		RoadSound(L"scream.wav", L"scream");
		//�J�M���E����
		RoadSound(L"acquisition.wav", L"acquisition");
		//�U����
		RoadSound(L"firing.wav", L"firing");
		//�Q�[���N���A��
		RoadSound(L"GameClear.wav", L"GameClear");
		//�Q�[���I�[�o�[��
		RoadSound(L"GameOver.wav", L"GameOver");
		//!�y�[�W�߂��鉹
		RoadSound(L"FlipPage.wav", L"FlipPage");

		

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

		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);		//!�f�[�^�̎擾
		auto fullPass = DataDir + folderName + fileName;//!�t�@�C���̈ʒu�̓���
		CsvFile csvFile;
		csvFile.SetFileName(fullPass);					//!�t�@�C���̈ʒu�̐ݒ�
		csvFile.ReadCsv();								//!csv�̓ǂݍ���

		csvFile.GetSelect(LineVec, 0, keyName);			//!0�Ԗڂ̃J������L"Villager"�ł���s�𔲂��o��

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
		std::vector<Vec3>m_patorlPositions = vector<Vec3>(0);

		PointCreate() :
			PointCreate(vector<Vec3>(0)) {}
		PointCreate(const std::vector<Vec3>& patrolPoints) :
			m_patorlPositions(patrolPoints)
		{}
	};

	//!�p�g���[���|�C���g
	PointCreate PointDate(const wstring& folderName, const wstring& fileName, const wstring& keyName)
	{
		PointCreate PatorlPoint;

		vector<wstring>LineVec;
		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);		//!�f�[�^�̎擾
		auto fullPass = DataDir + folderName + fileName;//!�t�@�C���̈ʒu�̓���

		CsvFile csvFile;								//!�t�@�C���̈ʒu�̐ݒ�
		csvFile.SetFileName(fullPass);					//!csv�̓ǂݍ���
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
		
		auto datasHunter = TransformDate(L"csvFolder\\" L"EnemyData\\", L"RushedEnemy.csv", L"Hunter");															//!�n���^�[��Excel�̃f�[�^
		for (auto& dataHunter : datasHunter)
		{
			auto pointData = PointDate(L"csvFolder\\" L"EnemyData\\", L"Point.csv", dataHunter.EnemykeyName);													//!�G�̏���|�C���g�̖��O�����o��
			auto HunterPtr = GetActiveStage()->AddGameObject<Hunter>(dataHunter.scale, dataHunter.rotation, dataHunter.position, pointData.m_patorlPositions);	//!���������n���^�[�̍쐬
			GetActiveStage()->AddGameObject<LoseSightOf>(HunterPtr);																							//!�͂Ăȃ}�[�N�̔|���������Ƀn���^�[�ƃy�A�����g������
			GetActiveStage()->AddGameObject<SurprisedSprite>(HunterPtr);																						//!�r�b�N���}�[�N�̔|���������Ƀn���^�[�ƃy�A�����g������

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
		
			CreateResourses();//!���\�[�X�쐬
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		

	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage")				//!�Q�[���X�e�[�W
		{
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage")		//!�^�C�g���X�e�[�W
		{
			ResetActiveStage<TitleStage>();
		}
		
		else if (event->m_MsgStr == L"ToGameClearStage")	//!�Q�[���N���A�X�e�[�W
		{
			ResetActiveStage<GameClearStage>();
		}
		else if (event->m_MsgStr == L"ToDescriptionStage")	//!�������X�e�[�W
		{
			ResetActiveStage<DescriptionStage>();
		}
	}

}
//end basecross
