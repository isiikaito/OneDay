/**
*@file GameClear.cpp
*@brief �Q�[���N���A��ʂ̃\�[�X�t�@�C��
*@author Kanazawa yuma
*@details �Q�[���N���A��ʂ̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//--------------------------------------------------------------------------------------
//	�Q�[���I�[�o�[�X�e�[�W�N���X
//--------------------------------------------------------------------------------------
	void GameClearStage::CreateViewLight()
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
	void GameClearStage::CreateGameClearSprite() {
		AddGameObject<GameClearSprite>(L"GAMECLEAR_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 0.0f));

	}

	//������
	void GameClearStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateGameClearSprite();
	}

	void GameClearStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameClearStage>());
	}

	//A�{�^��
	void GameClearStage::OnPushA() {
		PostEvent(0.0f, GetThis<GameClearStage>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
	}
}
//end basecros