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
		float m_keyTime;
		int m_keyNumber;
	public:
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();

		shared_ptr<SoundItem>m_BGM;
		void CreatePlayBGM();//!BGM�쐬

		//�\�z�Ɣj��
		TitleStage() :Stage(),m_keyTime(0.0f),m_keyNumber(0) {}
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
