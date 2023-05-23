/*!
@file DescriptionStage.cpp
@brief �������̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionStage.h"
#include "DescriptionSpriteFront.h"
#include "DescriptionStageCanvas.h"

namespace basecross {

	constexpr int m_page = 1;//!�ő�y�[�W��(0���܂�ł���)

	//!�r���[�̍쐬
	void DescriptionStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();			//!�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();	//!�J�����̎擾
		PtrView->SetCamera(PtrCamera);						//!�J�����̐ݒ�
		PtrCamera->SetEye(m_startEye);						//!�J�����̈ʒu�̐ݒ�
		PtrCamera->SetAt(m_startAt);						//!�J�����̎��_�̐ݒ�
		auto PtrMultiLight = CreateLight<MultiLight>();		//!�}���`���C�g�̍쐬
		PtrMultiLight->SetDefaultLighting();				//!�f�t�H���g�̃��C�e�B���O���w��
	}

	//!������
	void DescriptionStage::OnCreate() {
		CreateViewLight();
		auto m_descriptionStageCanvas = AddGameObject<DescriptionStageCanvas>();//!�������̃L�����o�X�̍쐬
		DescriptionSprites= m_descriptionStageCanvas->GetDescriptionSprites();	//!�y�[�W���Ƃ̏���z��ɓ����
		CreatePlayBGM();
	}
	//!�X�V
	void DescriptionStage::OnUpdate() {
		auto& app = App::GetApp();												//!�A�v���̎擾
		auto scene = app->GetScene<Scene>();									//!�V�[���̎擾	
		m_InputHandler.PushHandle(GetThis<DescriptionStage>());					//!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��	
		m_InputHandlerCrossKey.PushHandleCrossKey(GetThis<DescriptionStage>()); //!�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�̌Ăяo��
		auto DescriptionNumber = scene->GetDescriptionStageNumber();			//!�������̔ԍ����󂯎��

	}
	//!BGM�쐬
	void DescriptionStage::CreatePlayBGM()
	{
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!���ʂ̎擾
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();					//!�T�E���h�}�l�[�W���[�̎擾
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, volume);	//!BGM�̍Đ�
	}
	//!�����~�߂�
	void DescriptionStage::OnDestroy()
	{
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();	//!�T�E���h�}�l�[�W���[�̎擾
		XAPtr->Stop(m_BGM);									//!BGM�̃X�g�b�v
	}

	//!A�{�^��������
	void DescriptionStage::OnPushA() {
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();	//!���ʂ̎擾
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();					//!�T�E���h�}�l�[�W���[�̎擾
		ptrXA->Start(L"decision", 0, volume);								//!���ʉ��̊J�n
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//!�X�e�[�W�ڍs

	}
	//!�\���L�[�E
	void DescriptionStage::PushHandleCrossRight()
	{
		
		auto scene = App::GetApp()->GetScene<Scene>();				//!�V�[���̎擾
		auto volume = scene->GetSoundvolume();						//!���ʂ̎擾
		auto DescriptionNumber = scene->GetDescriptionStageNumber();//!�������̔ԍ��̎擾
		//!�y�[�W��1�ȉ��̎�
		if (DescriptionNumber < m_page)
		{
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʂ̎擾
			DescriptionNumber++;								//!���̃y�[�W��
			scene->SetDescriptionStageNumber(DescriptionNumber);//!���݂̃y�[�W�����X�V
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();	//!�T�E���h�}�l�[�W���[�̎擾
			ptrXA->Start(L"FlipPage", 0, volume);				//!�T�E���h�Đ�

		}
		//!��������2�y�[�W�̎�
		if (DescriptionNumber == static_cast<int>(PageNumber::second))
		{
			DescriptionSprites[static_cast<int>(PageNumber::farst)]->SetMoveTexture(true);//!�e�N�X�`���𓮂���
		}
		
		
	}

	//!�\���L�[��
	void DescriptionStage::PushHandleCrossLeft()
	{

	
		auto scene = App::GetApp()->GetScene<Scene>();              //!�V�[���̎擾
		auto DescriptionNumber = scene->GetDescriptionStageNumber();//!�������̔ԍ��̎擾
		//!�y�[�W��1�ȏ�̎�
		if (DescriptionNumber >= m_page)							
		{
			auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʂ̎擾
			DescriptionNumber--;											 //!�O�̃y�[�W��
			scene->SetDescriptionStageNumber(DescriptionNumber);			 //!���݂̃y�[�W�����X�V
			auto& ptrXA = App::GetApp()->GetXAudio2Manager();//!�T�E���h�}�l�[�W���[�̎擾
			ptrXA->Start(L"FlipPage", 0, volume);				 //!�T�E���h�Đ�
		}

		//!��������1�y�[�W�̎�
		if (DescriptionNumber == static_cast<int>(PageNumber::farst))
		{
			DescriptionSprites[static_cast<int>(PageNumber::farst)]->SetPageBackTo(true);//!�e�N�X�`���𓮂���
		}		
		
	}


}
//end basecross
