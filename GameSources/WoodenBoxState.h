#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "WoodenBox.h"
namespace basecross
{
	namespace kaito
	{
		class WoodenBoxMiddayState :public State<WoodenBox>
		{
		private:

			float m_middayTime = 0.0f;		//!�ύX���鎞��


			WoodenBoxMiddayState() {}
			WoodenBoxMiddayState(const WoodenBoxMiddayState&) = delete;
			WoodenBoxMiddayState& operator=(const WoodenBoxMiddayState&) = delete;

			
		public:
			static WoodenBoxMiddayState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(WoodenBox* woodenBox) override;

		};



		class WoodenBoxNightState :public State<WoodenBox>
		{
		private:

			float m_nightTime = 0.0f;//!��̎���
			int m_Date = 0;//!���t
			WoodenBoxNightState() {}
			WoodenBoxNightState(const WoodenBoxNightState&) = delete;
			WoodenBoxNightState& operator=(const WoodenBoxNightState&) = delete;

			

		public:
			static WoodenBoxNightState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(WoodenBox* woodenBox) override;

		};

		class WoodenBoxBreakState :public State<WoodenBox>
		{
		private:

			float m_nightTime = 0.0f;//!��̎���
			WoodenBoxBreakState() {}
			WoodenBoxBreakState(const WoodenBoxBreakState&) = delete;
			WoodenBoxBreakState& operator=(const WoodenBoxBreakState&) = delete;



		public:
			static WoodenBoxBreakState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(WoodenBox* woodenBox) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(WoodenBox* woodenBox) override;

		};
	
	}
}