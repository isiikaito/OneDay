#pragma once
/*!
@file Hunter.h
@brief �n���^�[�̍쐬
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "BaseEnemy.h"
namespace basecross
{
	//--------------------------------------------------------
	//!�n���^�[
	//--------------------------------------------------------
	class Hunter :public BaseEnemy
	{
	private:

		std::vector<Vec3> m_patrolPoints;//!����|�C���g
		Vec3  m_Position;				 //!�ʒu
		Vec3 m_Rotation;				 //!��]
		Vec3 m_Scale;					 //!�傫��
		int m_playerChange;				 //!�v���C���[�̏��
		float m_Speed;					 //!�X�s�[�h
		int m_patrolindex;				 //!����|�C���g
		float m_StateChangeSize;		 //!�X�e�[�g��؂�ւ���傫��
		bool m_playerDed;				 //!�v���C���[�̎��S
		bool m_IsGameOver;				 //!�Q�[���I�[�o�[�������ǂ����̔���
		float m_dedTime;				 //!����ł���̎���
		int m_damage;					 //!�_���[�W��^����
									    

	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		Hunter(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const std::vector<Vec3>& patrolPoints
		);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~Hunter(){}
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�n���^�[�̃X�s�[�h�̎擾
		@return �n���^�[�̃X�s�[�h
		*/
		float GetSpeed()
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�n���^�[�̃X�s�[�h�̐ݒ�
		@�����@ �n���^�[�̃X�s�[�h
		*/
		void SetSpeed(float HunterSpeed)
		{
			m_Speed = HunterSpeed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�`�F���W�T�C�Y�̎擾
		@return �X�e�[�g�`�F���W�T�C�Y
		*/
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�̎��S����̎擾
		@return �v���C���[�̎��S����
		*/
		bool GetPlayerDed()
		{
			return m_playerDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�̎��S����̐ݒ�
		@���� �@�v���C���[�̎��S����

		*/
		void SetPlayerDed(bool playerDed)
		{
			m_playerDed = playerDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[��߂܂���
		*/
		void PlayerCatch();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�n���^�[�����񂾂Ƃ�
		*/
		void HunterDed();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate();

	};



}
//!end basecross
