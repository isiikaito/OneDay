/*!
@file GameStageCanvas.h
@author Kaito Isii
@brief �Q�[���X�e�[�W�Ŏg��UI�̐����Ǘ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class GameStageCanvas : public GameObject {
	private:
		

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		GameStageCanvas(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���v�̃X�v���C�g�̍쐬
		*/
		void CreateClockSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���v�̉~�Ղ̃X�v���C�g
		*/
		void CreateCircleClockSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�x���x�Q�[�W�̍쐬
		*/
		void CreateAlertlevelGauge();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�^�C�}�[�X�v���C�g�쐬
		*/
		void CreateTimerSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�n���^�[�̃��C�t�̍쐬
		*/
		void CreateHeartSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���̍쐬
		*/
		void CreateArrow();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�J�M�̃t���[��
		*/
		void CreateKeyFrame();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�����̃Q�[�W�̔w�i
		*/
		void CreateMeatGageBackGround();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�󕠃Q�[�W�̍쐬
		*/
		void CreateHungerGage();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�󕠃Q�[�W�̘g�̍쐬
		*/
		void CreateMeatGageFrame();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���v�̐j
		*/
		void CreateClockArrow();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�邩�璋�ɕς��Ƃ��̃R�����g
		*/
		void CreateDateChangeCommentDay();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�������ɕς��Ƃ��̃R�����g
		*/
		void CreateDateChangeCommentNight();
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�Q�[���I�[�o�[�X�v���C�g
		*/
		void CreateGameOver();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���̃X�v���C�g�̍쐬
		*/
		void CreateKeySprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�t�F�[�h�A�E�g�̍쐬
		*/
		void CreateFadeOut();
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~GameStageCanvas(){}

		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		void OnCreate();

	};



}
//end basecross