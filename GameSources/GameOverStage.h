/*!
@file GameOverStage.h
@brief �Q�[���I�[�o�[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		
	private:
		InputHandler<GameOverStage> m_InputHandler;//!���̓n���h���[

	public:
		
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateGameOverSprite();
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;

		//void OnPushA();//!A�{�^��

		////�X�V
		//virtual void OnUpdate()override;

	};




}
//end basecross

