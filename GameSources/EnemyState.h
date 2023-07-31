
/*!
@file EnemyState.h
@brief �G�̃X�e�[�g
@author Kaito Isii
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	namespace kaito
	{

	
		//!�ǂ�������X�e�[�g----------------------------------------------------------------------
		class SeekState :public State<BaseEnemy>
		{

		private:
			SeekState() {}
			float m_surprisedTime = 0.0f;

			//!�V���O���g���p�^�[��
			SeekState(const SeekState&) = delete;			//!�֐����폜����
			SeekState& operator=(const SeekState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
			float SeekArriveRange = 30.0f;					//!�ǂ�������X�e�[�g�̃X�e�[�g�ύX�̒���

		public:
			static SeekState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(BaseEnemy* Enemy)override;
			

		};
		//!----------------------------------------------------------------------------------------

		//!����X�e�[�g----------------------------------------------------------------------------
		class PatrolState :public State<BaseEnemy>
		{
		private:
			PatrolState() {}
			PatrolState(const PatrolState&) = delete;
			PatrolState& operator=(const PatrolState&) = delete;

			std::vector<Vec3>m_patrol;//!����|�C���g
			const float PatrolArriveRange = 30.0f;//!�X�e�[�g��ύX��������̒���
		public:
			static PatrolState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(BaseEnemy* Enemy)override;

		};

		//!----------------------------------------------------------------------------------------
		
		//!�u���b�g�O�����o�H�T���X�e�[�g----------------------------------------------------------
		class BrettGramState :public State<BaseEnemy>
		{
		private:
			BrettGramState(){}
			BrettGramState(const BrettGramState&) = delete;
			BrettGramState& operator=(const BrettGramState&) = delete;

			
			const float BrettGramArriveRange = 10.0f;	//!�|�C���g�܂ł̋���
			int BrettGramindex = 0;						//!�u���b�g�N�����̔z��̗v�f��
			int maxBrettGramindex = 40;					//!�擾�C���f�b�N�X�̍ő�
			std::vector<Vec3>m_BrettGramPoint;			//!�u���b�g�N�����̔z��
			float Neardistance = FLT_MAX;				//!��ԋ߂�����
			Vec3 start = Vec3(0);						//!�u���b�g�N�����̎n�܂�̃|�C���g
			float m_lostTime = 0.0f;					//!������������

		public:
			static BrettGramState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(BaseEnemy* Enemy) override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(BaseEnemy* Enemy)override;
			void HitStageBuildingObb(BaseEnemy* Enemy);
		};

		//!�E���ꂽ�Ƃ��̃X�e�[�g-------------------------------------------------------------------
		class DedState :public State<BaseEnemy>
		{

		private:
			DedState() {}

			//!�V���O���g���p�^�[��
			DedState(const DedState&) = delete;//!�֐����폜����
			DedState& operator=(const DedState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
		
		public:
			static DedState* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(BaseEnemy* Enemy)override;

		};
		//!-----------------------------------------------------------------------------------------

		//!����������̃X�e�[�g---------------------------------------------------------------------
		class LostStata :public State<BaseEnemy>
		{
		private:
			LostStata(){}
			//!�V���O���g���p�^�[��
			LostStata(const LostStata&) = delete;//!�֐����폜����
			LostStata& operator=(const LostStata&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
			float m_lostTime = 0.0f;			//!������������
			const float m_MaxlostTime = 2.0f;	//!����������
		public:
			static LostStata* Instance();

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��ɏ�ɌĂ΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(BaseEnemy* Enemy)override;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(BaseEnemy* Enemy)override;
		};
		//!----------------------------------------------------------------------------------------

	}
}