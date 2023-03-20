/*!
@file TitleStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionStage.h"
#include "DescriptionSpriteFront.h"

namespace basecross {

	constexpr int randomspeed = 22;
	constexpr int randomNumber = 3;
	constexpr int m_maxPage = 3;
	constexpr float m_timeToTurnThePage = 1.0f;
	//--------------------------------------------------------------------------------------
	//	�����X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void DescriptionStage::CreateViewLight()
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

	//�\�̐������̃X�v���C�g�̍쐬
	void DescriptionStage::CreateDescriptionSpriteFront() {

		DescriptionSprites.push_back(
			AddGameObject<DescriptionSpriteFront>(L"DescriptionSprite1_TX", false,
				Vec3(1300.0f, 800.0f, 0.0f), Vec3(0.0f, 0.0f, 0.1f))
		);
		DescriptionSprites.push_back(
			AddGameObject<DescriptionSpriteFront>(L"DescriptionSprite2_TX", false,
				Vec3(1300.0f, 800.0f, 0.0f), Vec3(0.0f, 0.0f, 0.2f))
		);
		

		

	}
	//������
	void DescriptionStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateDescriptionSpriteFront();
		CreatePlayBGM();//!BGM�̍쐬
	}



	//�X�V
	void DescriptionStage::OnUpdate() {
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		//!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<DescriptionStage>());
		//!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�̌Ăяo��
		m_InputHandlerCrossKey.PushHandleCrossKey(GetThis<DescriptionStage>());

		auto DescriptionNumber = scene->GetDescriptionStageNumber();

		
		

		
	}

	////BGM�̍Đ�
	void DescriptionStage::CreatePlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
	}

	/// BGM�̃X�g�b�v
	void DescriptionStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//A�{�^��
	void DescriptionStage::OnPushA() {
		//�T�E���h�Đ�
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(L"decision", 0, 1.0f);
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

	}

	


	void DescriptionStage::MoveForwardInaPage()
	{
		

	}

	void DescriptionStage::PageBackTo()
	{

	
		
	}



	//!����[�����[�E
	void DescriptionStage::PushHandleCrossRight()
	{
		
		auto scene = App::GetApp()->GetScene<Scene>();
		auto DescriptionNumber = scene->GetDescriptionStageNumber();
		if (DescriptionNumber < 1)
		{
			DescriptionNumber++;
			/*std::wstringstream ms;
			ms << DescriptionNumber;
			MessageBox(NULL, ms.str().c_str(), L"", MB_OK);*/
			scene->SetDescriptionStageNumber(DescriptionNumber);

			//�T�E���h�Đ�
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"FlipPage", 0, 1.0f);

		}
		switch (DescriptionNumber)
		{
		case(static_cast<int>(PageNumber::second)):
			DescriptionSprites[static_cast<int>(PageNumber::farst)]->SetMoveTexture(true);
			break;
		/*case(static_cast<int>(PageNumber::three)):
			DescriptionSprites[static_cast<int>(PageNumber::second)]->SetMoveTexture(true);
			break;

		case(static_cast<int>(PageNumber::four)):
			DescriptionSprites[static_cast<int>(PageNumber::three)]->SetMoveTexture(true);
			break;*/

		}
		

		
	}


	//!��
	void DescriptionStage::PushHandleCrossLeft()
	{

	
		auto scene = App::GetApp()->GetScene<Scene>();
		auto DescriptionNumber = scene->GetDescriptionStageNumber();
		if (DescriptionNumber >=1)
		{
			DescriptionNumber--;
			/*std::wstringstream ms;
			ms << DescriptionNumber;
			MessageBox(NULL, ms.str().c_str(), L"", MB_OK);*/
			scene->SetDescriptionStageNumber(DescriptionNumber);

			//�T�E���h�Đ�
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"FlipPage", 0, 1.0f);
		}
		switch (DescriptionNumber)
		{
		case(static_cast<int>(PageNumber::farst)):
			DescriptionSprites[static_cast<int>(PageNumber::farst)]->SetPageBackTo(true);
			break;
		/*case(static_cast<int>(PageNumber::second)):
			DescriptionSprites[static_cast<int>(PageNumber::second)]->SetPageBackTo(true);
			break;

		case(static_cast<int>(PageNumber::three)):
			DescriptionSprites[static_cast<int>(PageNumber::three)]->SetPageBackTo(true);
			break;*/

		}
		
		
	}


}
//end basecross
