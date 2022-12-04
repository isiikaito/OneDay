
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
		wstring strTexture = dataDir +L"Texture\\"+ L"number.png";
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
		//!�r�b�N���}�[�N�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"Surprised.png";
		App::GetApp()->RegisterTexture(L"Surprised_TX", strTexture);
		//!�͂Ăȃ}�[�N�̃X�v���C�g
		strTexture = dataDir + L"Texture\\" + L"LoseSightOf.png";
		App::GetApp()->RegisterTexture(L"LoseSightOf_TX", strTexture);


		//!���̃��f���ǂݍ���
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir,L"MayaModel\\" L"StageFloor.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh1);

		//!�n���^�[�̃��f�����O
		auto staticModelMesh2 = MeshResource::CreateStaticModelMesh(dataDir, L"MayaModel\\" L"Hunter.bmf");
		App::GetApp()->RegisterResource(L"HUNTER_MESH", staticModelMesh2);
		
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


		
		//!BGM
		wstring strMusic = dataDir + L"Sound\\" L"BGM.wav";
		App::GetApp()->RegisterWav(L"bgm", strMusic);
		strMusic = dataDir + L"Sound\\" L"Title.wav";
		App::GetApp()->RegisterWav(L"TitleBGM", strMusic);


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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
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
