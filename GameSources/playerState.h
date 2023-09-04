/*!
@file PlayerState.h
@brief �v���C���[�̃X�e�[�g
@author Kaito Isii
*/
#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "Player.h"

namespace basecross
{
	namespace kaito
	{
		enum class EatCondition {
			notEat,
			firstEat,
			secondEat,
			thirdEat
		};
		//!�v���C���[���l�ԏ�Ԃ̎��̃X�e�[�g---------------------------
		class HumanState :public State<Player>
		{
		private:
			HumanState() {}
			float m_HumanChangeTime = 0.0f;	//!�ύX���鎞��
			

			
			//!�V���O���g���p�^�[��
			HumanState(const HumanState&) = delete;//!�֐����폜����
			HumanState& operator=(const HumanState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static HumanState* Instance();

			
			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------


		//!�v���C���[���T�j��Ԃ̎��̃X�e�[�g---------------------------
		class WolfState :public State<Player>
		{
		private:
			WolfState() {}
			WolfState(const WolfState&) = delete;//!�֐����폜����
			WolfState& operator=(const WolfState&) = delete;//!operator�̒��ɂ���=���폜(�R�s�[����Ȃ��悤��)
			float m_WolfChangeTime = 0.0f;						//!�ϐg����܂ł̎���
			InputHandlerB<Player> m_InputHandlerB;				//!�R���g���[���[�̃{�^���̎擾B

			weak_ptr<Player> m_player;
		public:
			static WolfState* Instance();
			
			void MeatEat(Player* Player);

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------

		//!�v���C���[���l�Ԃ���T�ɕϐg����Ƃ��̃X�e�[�g--------------------

		class HumanChangeDirectingState :public State<Player>
		{
		private:

			float m_humanChangeDirectingTiem = 0.0f;//!�ϐg����
			HumanChangeDirectingState(){}

			HumanChangeDirectingState(const HumanChangeDirectingState&) = delete;//!�֐����폜����
			HumanChangeDirectingState& operator=(const HumanChangeDirectingState&) = delete;//!operator�̒��ɂ���=���폜(�R�s�[����Ȃ��悤��)
		
		public:
			static HumanChangeDirectingState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------

		//!�v���C���[���T����l�Ԃɕϐg����Ƃ��̃X�e�[�g--------------------
		class WolfChangeDirectingState :public State<Player>
		{
		private:

			float m_wolfChangeDirectingTiem = 0.0f;//!�ϐg����
			WolfChangeDirectingState() {}

			WolfChangeDirectingState(const WolfChangeDirectingState&) = delete;//!�֐����폜����
			WolfChangeDirectingState& operator=(const WolfChangeDirectingState&) = delete;//!operator�̒��ɂ���=���폜(�R�s�[����Ȃ��悤��)

		public:
			static WolfChangeDirectingState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(Player* Player)override;
		};
		//-------------------------------------------------------------------


		//�v���C���[�����񂾂Ƃ��̃X�e�[�g
		class PlayerDedState :public State<Player>
		{
		private:

			PlayerDedState() {}

			PlayerDedState(const PlayerDedState&) = delete;//!�֐����폜����
			PlayerDedState& operator=(const PlayerDedState&) = delete;//!operator�̒��ɂ���=���폜(�R�s�[����Ȃ��悤��)

		public:
			static PlayerDedState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(Player* Player)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(Player* Player)override;
		};
		//-------------------------------------------------------------------


	}
}