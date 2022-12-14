/*!
@file TitleStage.cpp
@brief 
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	//--------------------------------------------------------------------------------------
//	�^�C�g���X�e�[�W�N���X
//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	//�X�v���C�g�̍쐬
	void TitleStage::CreateTitleSprite() {
		AddGameObject<TitleSprite>(L"MESSAGE_TX", false,
			Vec2(1300.0f, 800.0f), Vec2(0.0f, 0.0f));

	}

	//������
	void TitleStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
		CreatePlayBGM();//!BGM�̍쐬
	}

	//�X�V
	void TitleStage::OnUpdate() {
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		
		auto time = app->GetElapsedTime();
		m_keyTime += time*22;
		srand(m_keyTime);
		m_keyNumber = rand() % 3;
		scene->SetKeyNamber(m_keyNumber);


		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}

	////BGM�̍Đ�
	void TitleStage::CreatePlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
	}

	/// BGM�̃X�g�b�v
	void TitleStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//A�{�^��
	void TitleStage::OnPushA() {
		//�T�E���h�Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"decision", 0, 1.0f);
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}


}
//end basecross
