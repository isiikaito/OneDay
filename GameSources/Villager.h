/*!
@file Villager.h
@brief ���l�̍쐬
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "BaseEnemy.h"
namespace basecross
{
	//--------------------------------------------------------
	//!���l
	//--------------------------------------------------------
	class Villager :public BaseEnemy
	{
	private:

		std::vector<Vec3> m_patrolPoints;//!����|�C���g
		Vec3  m_Position;//!�ʒu
		Vec3 m_Rotation;//!��]
		Vec3 m_Scale;//!�傫��
	    int m_playerChange;//!�v���C���[�̏��
		int m_Speed;//!�X�s�[�h
		int m_patrolindex;
		float m_StateChangeSize;	
		bool m_dedDecision;//!�����̔���
		
		//bool m_loseSightOfTarget;//!�v���C���[���������Ă���Ƃ�

	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Villager(const shared_ptr<Stage>& StagePtr,
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
		virtual ~Villager();
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

		//!���l�̐����̔���̎擾
		bool GetDedDecision()const
		{
			return m_dedDecision;
		}
		//!���l�̐����̐ݒ�
		void SetDedDecision(bool DedDecision)
		{
			m_dedDecision = DedDecision;
		}

		//!�X�e�[�g�`�F���W�T�C�Y
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}
	
		
		
		virtual void OnCreate();//������
		virtual void OnUpdate();//!�X�V
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//�v���C���[�ƃG�l�~�[�̏Փ˔���

	};

	

}
//!end basecross
