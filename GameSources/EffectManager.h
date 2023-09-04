/*!
@file GameManager.h
@brief �Q�[���X�e�[�W���ԃ}�l�[�W���[
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "EfkInterfece.h"

namespace basecross
{

	class EffectManager
	{

	private:
		EffectManager() {}
		//!�V���O���g���p�^�[��
		EffectManager(const EffectManager&) = delete;//!�֐����폜����
		EffectManager& operator=(const EffectManager&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_KeyEfkEffect;				//������������̃G�t�F�N�g
		shared_ptr<EfkEffect> m_ScratchEfkEffect;			//�U���������̃G�t�F�N�g
		shared_ptr<EfkEffect> m_TransformEfkEffect;			//�T�ɕϐg�������̃G�t�F�N�g
		shared_ptr<EfkEffect> m_MeatEfkEffect;				//�T�ɕϐg�������̃G�t�F�N�g
		//�G�t�F�N�g���s�I�u�W�F�N�g
		shared_ptr<EfkPlay> m_KeyEfkPlay;
		shared_ptr<EfkPlay> m_ScratchEfkPlay;
		shared_ptr<EfkPlay> m_TransformEfkPlay;
		shared_ptr<EfkPlay> m_MeatEfkPlay;

		shared_ptr<EfkInterface> m_EfkInterface;			//!�G�t�F�N�g�C���^�[�t�F�[�X



	public:
		static EffectManager* Instance();

		void OnCreate();
		//----------------------------------------------------------------------------------
		/*!
		@brief	�U���G�t�F�N�g
		@param[in]	position	�G�t�F�N�g�ʒu
		*/
		void ScratchEfkPlay(Vec3 position)
		{
			m_ScratchEfkPlay = ObjectFactory::Create<EfkPlay>(m_ScratchEfkEffect, position);//!�G�t�F�N�g�̍쐬
		}

		//----------------------------------------------------------------------------------
		/*!
		@brief	�J�M�̃G�t�F�N�g
		@param[in]	position	�G�t�F�N�g�ʒu
		*/
		void KeyEfkPlay(Vec3 position)
		{
			m_KeyEfkPlay = ObjectFactory::Create<EfkPlay>(m_KeyEfkEffect, position);//!�G�t�F�N�g�̍쐬
		}


		//----------------------------------------------------------------------------------
		/*!
		@brief	�G�t�F�N�g�C���^�[�t�F�[�X�̎擾
		*/
		shared_ptr<EfkInterface> GetEfkInterface()
		{
			return m_EfkInterface;
		}

		//----------------------------------------------------------------------------------
		/*!
		@brief	���̃G�t�F�N�g
		@param[in]	position	�G�t�F�N�g�ʒu
		*/
		void MeatEfkPlay(Vec3 position)
		{
			m_MeatEfkPlay = ObjectFactory::Create<EfkPlay>(m_MeatEfkEffect, position);//!�G�t�F�N�g�̍쐬

		}

		//----------------------------------------------------------------------------------
		/*!
		@brief	�ϐg�̃G�t�F�N�g
		@param[in]	position	�G�t�F�N�g�ʒu
		*/
		void PlayerChangeEfkPlay(Vec3 position)
		{
			m_TransformEfkPlay = ObjectFactory::Create<EfkPlay>(m_TransformEfkEffect, position);//!�G�t�F�N�g�̍쐬
		}

	};
}
//end basecross


