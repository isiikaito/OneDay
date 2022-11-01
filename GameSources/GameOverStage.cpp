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
			Vec2(256.0f, 64.0f), Vec2(0.0f, 0.0f));

	}

	//������
	void GameOverStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateGameOverSprite();
	}


}
//end basecross
