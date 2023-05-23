/*!
@file DescriptionStage.h
@brief�������X�e�[�W
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class PageNumber {
		farst,
		second,
		three,
		four
	};


	class DescriptionSpriteFront;
	
	
	class DescriptionStage : public Stage {
	private:
		
		InputHandler<DescriptionStage> m_InputHandler;
		InputHandlerCrossKey<DescriptionStage> m_InputHandlerCrossKey;//���̓n���h���[


		Vec3 m_startEye;					//!�J�����̈ʒu
		Vec3 m_startAt;						//!�J�����̎��_
		shared_ptr<SoundItem>m_BGM;			//!��
		float m_keyTime;					//!�J�M�������_���ɔz�u���鎞��
		int m_descriptionStageNumber;		//!�������̃y�[�W��
		int m_keyNumber;					//!�J�M�̔z�u���ǂݍ���ł���CSV�̐���
		float m_timeItTakesToTurnThePage;	//!�y�[�W���߂����Ă��鎞��
		bool m_IsmoveForwardInaPage;		//!�y�[�W��i�߂Ă��邩�ǂ���
		bool m_IspageBackTo;				//!�y�[�W��߂��Ă��邩�ǂ���
		std::vector<shared_ptr<DescriptionSpriteFront>> DescriptionSprites;//!��������ۊǂ���z��
	    public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���[�̍쐬
		*/
		void CreateViewLight();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@BGM�쐬
		*/
		void CreatePlayBGM();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		DescriptionStage() :Stage(), m_IsmoveForwardInaPage(false),m_IspageBackTo(false), m_timeItTakesToTurnThePage(0.0f), m_descriptionStageNumber(0), m_keyTime(0.0f), m_keyNumber(0), m_startEye(Vec3(0.0f, 2.0f, -3.0f)), m_startAt(Vec3(0.0f, 0.0f, 0.0f)) {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~DescriptionStage() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�X�V
		*/
		virtual void OnUpdate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �폜
		*/
		virtual void OnDestroy() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@A�{�^���̏���
		*/
		void OnPushA();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�\���L�[�̉E�{�^���̏���
		*/
		void PushHandleCrossRight();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�\���L�[�̍��{�^���̏���
		*/
		void PushHandleCrossLeft();

		
		
	};


}
//end basecross

