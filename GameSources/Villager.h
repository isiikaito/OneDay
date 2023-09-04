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

		std::vector<Vec3> m_patrolPoints;	//!����|�C���g
		int m_playerChange;					//!�v���C���[�̏��
		float m_Speed;						//!�X�s�[�h
		int m_patrolindex;					//!�p�g���[���|�C���g�̃C���f�b�N�X
		bool m_dedDecision;					//!�����̔���
		int m_damage;						//!�v���C���[�ɗ^����_���[�W��
		BoneModelDeta m_enemyBoneModelDeta;				//!�G�̃��f���f�[�^

		

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
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
		virtual ~Villager(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���l�̃X�s�[�h�̎擾
		@return ���l�̃X�s�[�h
		*/
		float GetSpeed() const
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���l�̃X�s�[�h�̐ݒ�
		@���� ���l�̃X�s�[�h
		*/
		void SetSpeed(float VillagerSpeed)
		{
			m_Speed = VillagerSpeed;
		}

		

		
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

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�ƃG�l�~�[�̏Փ˔���
		*/
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
	};



}
//!end basecross
