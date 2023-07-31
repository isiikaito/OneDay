/*!
@file DescriptionSpriteFrontState.h
@brief �������̃X�e�[�g
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "DescriptionSpriteFront.h"

namespace basecross
{
	namespace kaito
	{
		//!�y�[�W��
		enum class PageNumber {
			farst,
			second,
			three,
			four
		};

		class DescriptionSpriteFrontState :public State<DescriptionSpriteFront>
		{
		private:
		
			float m_moveTime = 0.0f;				//!�����Ă��鎞��
			float m_stateChangePositionX = -1300.0f;//!�e�N�X�`�������X���C�h������W

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�R���X�g���N�^
			*/
			DescriptionSpriteFrontState() {}

			//!�V���O���g���p�^�[��
			DescriptionSpriteFrontState(const DescriptionSpriteFrontState&) = delete;//!�֐����폜����
			DescriptionSpriteFrontState& operator=(const DescriptionSpriteFrontState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static DescriptionSpriteFrontState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};

		//-------------------------------------------------------------------


		class DescriptionSpriteStandbyFrontState :public State<DescriptionSpriteFront>
		{
		private:
			DescriptionSpriteStandbyFrontState() {}
			Vec3 m_textureResetPosition = Vec3(0.0f, 0.0f, 0.2f);//!�e�N�X�`���̃|�W�V����
			//!�V���O���g���p�^�[��
			DescriptionSpriteStandbyFrontState(const DescriptionSpriteStandbyFrontState&) = delete;//!�֐����폜����
			DescriptionSpriteStandbyFrontState& operator=(const DescriptionSpriteStandbyFrontState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static DescriptionSpriteStandbyFrontState* Instance();


			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};


		class DescriptionPageBackToState :public State<DescriptionSpriteFront>
		{
		private:
			DescriptionPageBackToState() {}
			float m_moveTime = 0.0f;			//!��������
			float m_stateChangePositionX = 0.0f;//!�X�e�[�g��ύX����ʒu

			//!�V���O���g���p�^�[��
			DescriptionPageBackToState(const DescriptionPageBackToState&) = delete;//!�֐����폜����
			DescriptionPageBackToState& operator=(const DescriptionPageBackToState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static DescriptionPageBackToState* Instance();


			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};

		//-------------------------------------------------------------------



	}
}
