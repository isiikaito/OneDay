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
		int m_playerChange;				 //!�v���C���[�̏��
		float m_Speed;					 //!�X�s�[�h
		int m_patrolindex;				 //!����|�C���g
		BoneModelDeta m_enemyBoneModelDeta;				//!�G�̃��f���f�[�^

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



		//--------------------------------------------------------------------------------------
		/*!
		@brief	�n���^�[�̃X�s�[�h�̎擾
		@return �n���^�[�̃X�s�[�h
		*/
		float GetSpeed() const
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�n���^�[�̃X�s�[�h�̐ݒ�
		@param	�n���^�[�̃X�s�[�h
		*/
		void SetSpeed(float HunterSpeed)
		{
			m_Speed = HunterSpeed;
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

	};



}
//!end basecross
