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
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateGameOverSprite();

	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		////�X�V
		//virtual void OnUpdate()override;

	};




}
//end basecross

