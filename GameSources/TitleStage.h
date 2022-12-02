/*!
@file TitleStage.h
@brief 
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
	private:
		//���̓n���h���[
		InputHandler<TitleStage> m_InputHandler;

	public:
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();

		shared_ptr<SoundItem>m_BGM;
		void CreatePlayBGM();//!BGM�쐬

		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;

		virtual void OnDestroy() override;

		//A�{�^��
		void OnPushA();
	};


}
//end basecross
