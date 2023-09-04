/*!
@file TitleStage.cpp
@brief 
*@author isii kaito
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "TitleStageCanvas.h"

namespace basecross {
	
	constexpr int RANDOMSPEED = 22;			//�����̎���
	constexpr int RANDOMNUMBER = 3;			//�����_���ɑI�Ԑ���
	constexpr float BUTTONVOLUME = 1.0f;	//����
	constexpr float TITLEVOLUME = 0.5f;		//�^�C�g��BGM
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(m_startEye);
		PtrCamera->SetAt(m_startAt);
		auto PtrMultiLight = CreateLight<MultiLight>();//�}���`���C�g�̍쐬
		PtrMultiLight->SetDefaultLighting();//�f�t�H���g�̃��C�e�B���O���w��
	}

	

	//!������
	void TitleStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleStageCanvas>();
		CreatePlayBGM();//!BGM�̍쐬
		auto scene = App::GetApp()->GetScene<Scene>();
		scene->SetGameOver(false);
	    scene->SetGameStrat(true);
		scene->SetGameOverSprite(false);

	}

	//!�X�V
	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();//!�A�v���̎擾
		auto scene = app->GetScene<Scene>();//!�V�[���̎擾
		
		auto deltaTime = app->GetElapsedTime();//!�f���^�^�C���̎擾
		m_keyTime += deltaTime * RANDOMSPEED;
		srand((unsigned)std::time(0));
		m_keyNumber = rand() % RANDOMNUMBER;
		scene->SetKeyNamber(m_keyNumber);


		//!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}

	//!BGM�̍Đ�
	void TitleStage::CreatePlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, TITLEVOLUME);
	}

	//! BGM�̃X�g�b�v
	void TitleStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//!A�{�^��
	void TitleStage::OnPushA() {
		//!�T�E���h�Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"decision", 0, BUTTONVOLUME);
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToDescriptionStage");
	}


}
//end basecross
