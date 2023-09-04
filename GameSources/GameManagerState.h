#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "GameManager.h"
namespace basecross
{
	namespace kaito
	{
		//!�I�[�v�j���O�J����-----------------------
		class OpeningCameraPlayState :public State<GameManager>
		{
		private:
			OpeningCameraPlayState() {}

			OpeningCameraPlayState(const OpeningCameraPlayState&) = delete;
			OpeningCameraPlayState& operator=(const OpeningCameraPlayState&) = delete;
		public:
			static OpeningCameraPlayState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(GameManager* gamaManager) override;

		};

		class MiddayState :public State<GameManager>
		{
		private:

			float m_middayTime = 0.0f;		//!�ύX���鎞��
			CsvFile m_MeatPositon;			//!���̃|�W�V������CSV�t�@�C��
			int m_MeatNumber = 0;			//!���̈ʒu���ۑ����ꂽCSV�t�@�C���̔ԍ�
			CsvFile m_GameStageCsvD;		// !�����̔z�u4
			float m_meatTime = 0.0f;		//!���̎���



			MiddayState() {}
			MiddayState(const MiddayState&) = delete;
			MiddayState& operator=(const MiddayState&) = delete;

			//!���̐���
			void CreateMeat();
			//!�ؔ��̐���
			void CreateWoodBox();
			//!csv�̎擾
			void ReadCsv(const wstring& FileNume);
		public:
			static MiddayState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(GameManager* gamaManager) override;

		};

		

		class NightState :public State<GameManager>
		{
		private:

			float m_nightTime = 0.0f;//!��̎���
			int m_Date = 0;//!���t
			NightState() {}
			NightState(const NightState&) = delete;
			NightState& operator=(const NightState&) = delete;

			//!���̈ʒu���Z�b�g
			void RemoveMeat();
			//!�ؔ��̃��Z�b�g
			void RemoveWoodBox();

		public:
			static NightState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(GameManager* gamaManager) override;

		};

		

		//!�Q�[���I�[�o�[-----------------------
		class GameOverState :public State<GameManager>
		{
		private:
			GameOverState() {}
			float m_dedTime = 0.0f;								//!�v���C���[������ł���̎���

			GameOverState(const GameOverState&) = delete;
			GameOverState& operator=(const GameOverState&) = delete;

		public:
			static GameOverState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(GameManager* gamaManager) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(GameManager* gamaManager) override;
		};
	}

	
}


