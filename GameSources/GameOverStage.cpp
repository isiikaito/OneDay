/*!
@file GameOverStage.cpp
@brief �Q�[���I�[�o�[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight()
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
	void GameOverStage::CreateGameOverSprite() {
		AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));

	}

	//������
	void GameOverStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateGameOverSprite();
	}

	void GameOverStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
	}

	//1A�{�^��
	void GameOverStage::OnPushA() {
		//�T�E���h�Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"decision", 0, 1.0f);
		PostEvent(0.0f, GetThis<GameOverStage>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	}

}
//end basecross
