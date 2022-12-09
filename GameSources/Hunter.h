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
		Vec3  m_Position;//!�ʒu
		Vec3 m_Rotation;//!��]
		Vec3 m_Scale;//!�傫��
		int m_playerChange;//!�v���C���[�̏��
		float m_Speed;//!�X�s�[�h
		int m_patrolindex;
		float m_StateChangeSize;
		bool m_playerDed;//!�v���C���[�̎��S
		bool m_IsGameOver;
		float m_dedTime;

		//bool m_loseSightOfTarget;//!�v���C���[���������Ă���Ƃ�

	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
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
		//--------------------------------------------------------------------------------------
		virtual ~Hunter();
	public:


		//!���l�̃X�s�[�h�̎擾
		int GetSpeed()
		{
			return m_Speed;
		}

		//!���l�̃X�s�[�h�̐ݒ�
		void SetSpeed(int VillagerSpeed)
		{
			m_Speed = VillagerSpeed;
		}

	

		//!�X�e�[�g�`�F���W�T�C�Y
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		//!�v���C���[�̎��S����
		bool GetPlayerDed()
		{
			return m_playerDed;
		}
		void SetPlayerDed(bool playerDed)
		{
			m_playerDed = playerDed;
		}

		void PlayerCatch();//!�v���C���[��߂܂���
		virtual void OnCreate();//������
		virtual void OnUpdate();//!�X�V

	};



}
//!end basecross
