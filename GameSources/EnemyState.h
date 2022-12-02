#pragma once
#include "stdafx.h"

namespace basecross
{
	namespace kaito
	{

		//!�v���C���[�𔭌������Ƃ��̎n�߂̒ǂ������鏈��-------------
		class SurprisedState :public State<BaseEnemy>
		{
		private:
			SurprisedState() {}

			//!�V���O���g���p�^�[��
			SurprisedState(const SurprisedState&) = delete;//!�֐����폜����
			SurprisedState& operator=(const SurprisedState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
			float SeekArriveRange = 30.0f;//!�ǂ�������X�e�[�g�̃X�e�[�g�ύX�̒���
			float BrettGramRange = 5.0f;

		public:
			static SurprisedState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};
		//!-------------------------------------------------------------
		
		//!�ǂ�������X�e�[�g-------------------------------------------
		class SeekState :public State<BaseEnemy>
		{

		private:
			SeekState() {}

			//!�V���O���g���p�^�[��
			SeekState(const SeekState&) = delete;//!�֐����폜����
			SeekState& operator=(const SeekState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
			float SeekArriveRange = 60.0f;//!�ǂ�������X�e�[�g�̃X�e�[�g�ύX�̒���
			float BrettGramRange = 10.0f;

		public:
			static SeekState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};
		//!-------------------------------------------------------------

		//!����X�e�[�g-------------------------------------------------
		class PatrolState :public State<BaseEnemy>
		{
		private:
			PatrolState() {}
			PatrolState(const PatrolState&) = delete;
			PatrolState& operator=(const PatrolState&) = delete;

			std::vector<Vec3>m_patrol;//!����|�C���g
			const float PatrolArriveRange = 20.0f;//!�X�e�[�g��ύX��������̒���

		public:
			static PatrolState* Instance();
			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};

		//!-------------------------------------------------------------
		
		class BrettGramState :public State<BaseEnemy>
		{
		private:
			BrettGramState(){}
			BrettGramState(const BrettGramState&) = delete;
			BrettGramState& operator=(const BrettGramState&) = delete;

			
			const float BrettGramArriveRange = 10.0f;//!�|�C���g�܂ł̋���
			int BrettGramindex = 0;//!�u���b�g�N�����̔z��̗v�f��
			std::vector<Vec3>m_BrettGramPoint;//!�u���b�g�N�����̔z��
			float Neardistance = FLT_MAX;//!��ԋ߂�����
			Vec3 start = Vec3(0);//!�u���b�g�N�����̎n�܂�̃|�C���g

		public:
			static BrettGramState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy) override;
			virtual void Exit(BaseEnemy* Enemy)override;
		};

		//!�E���ꂽ�Ƃ��̃X�e�[�g-------------------------------------------
		class DedState :public State<BaseEnemy>
		{

		private:
			DedState() {}

			//!�V���O���g���p�^�[��
			DedState(const DedState&) = delete;//!�֐����폜����
			DedState& operator=(const DedState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
		

		public:
			static DedState* Instance();

			virtual void Enter(BaseEnemy* Enemy)override;
			virtual void Execute(BaseEnemy* Enemy)override;
			virtual void Exit(BaseEnemy* Enemy)override;

		};
		//!-------------------------------------------------------------


	}
}