/**
*@file GameClear.h
*@brief �Q�[���N���A��ʂ̃w�b�_�[�t�@�C��
*@author Kanazawa yuma
*@details �Q�[���N���A��ʂ̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���N���A�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameClearStage : public Stage {
	private:
		InputHandler<GameClearStage> m_InputHandler;//!���̓n���h���[

	public:
		
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateGameClearSprite();

		//�\�z�Ɣj��
		GameClearStage() :Stage() {}
		virtual ~GameClearStage() {}
		//������
		virtual void OnCreate()override;

		void OnPushA();//!A�{�^��

		//�X�V
		virtual void OnUpdate()override;
	 };
}
//end basecross
