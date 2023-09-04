/*!
@file PlayerMoveComponent.h
@author Kaito Isii
@brief  �v���C���[�̓�������
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross 
{

	class PlayerMoveComponent :public Component
	{
		float m_Speed;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�̈ړ�
		*/
		void MovePlayer();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���g���[���[�̏��
		@return ���X�e�B�b�N��xy���W
		*/
		Vec2 GetControlerInformation() const;

		

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g
		*/
		explicit PlayerMoveComponent(
			const shared_ptr<GameObject>& GameObjectPtr):
			Component(GameObjectPtr),
			m_Speed(20.0f) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~PlayerMoveComponent(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���g���[����������x�N�g���𓾂�
		@return �R���g���[����������x�N�g��
		*/
		Vec3 GetMoveVector() const;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�s�[�h�̎擾
		@retrun �v���C���[�̃X�s�[�h
		*/
		float GetSpeed() const
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�s�[�h�̐ݒ�
		@�����@�v���C���[�̃X�s�[�h
		*/
		void SetSpeed(float speed)
		{
			m_Speed = speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V����
		*/
		virtual void OnUpdate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�`�揈���B�f�t�H���g�͉����s��Ȃ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}
