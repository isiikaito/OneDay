/*!
@file TitleStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionStage.h"
#include "DescriptionSpriteFront.h"
#include "DescriptionStageCanvas.h"

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

	
	//������
	void DescriptionStage::OnCreate() {
		CreateViewLight();
		//!�������̃f�[�^�̎擾
		auto m_descriptionStageCanvas = AddGameObject<DescriptionStageCanvas>();
		//!�y�[�W���Ƃ̏���z��ɓ����
		DescriptionSprites= m_descriptionStageCanvas->GetDescriptionSprites();
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

	


	


	//!����[�����[�E
	void DescriptionStage::PushHandleCrossRight()
	{
		
		auto scene = App::GetApp()->GetScene<Scene>();
		auto DescriptionNumber = scene->GetDescriptionStageNumber();
		if (DescriptionNumber < 1)
		{
			DescriptionNumber++;
			
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
		
		}
		
		
	}


}
//end basecross
