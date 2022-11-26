#pragma once
#include "stdafx.h"

namespace basecross
{
	namespace kaito
	{
		//!�ǂ�������X�e�[�g-------------------------------------------
		class SeekState :public State<BaseEnemy>
		{

		private:
			SeekState() {}

			//!�V���O���g���p�^�[��
			SeekState(const SeekState&) = delete;//!�֐����폜����
			SeekState& operator=(const SeekState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj
			float pointdistance = 0.0f;
			float SeekArriveRange = 30.0f;

		public:
			static SeekState* Instance();

			virtual void Enter(BaseEnemy* Enemy);
			virtual void Execute(BaseEnemy* Enemy);
			virtual void Exit(BaseEnemy* Enemy);

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
			const float PatrolArriveRange = 10.0f;//!�X�e�[�g��ύX��������̒���

		public:
			static PatrolState* Instance();
			virtual void Enter(BaseEnemy* Enemy);
			virtual void Execute(BaseEnemy* Enemy);
			virtual void Exit(BaseEnemy* Enemy);

		};

		//!-------------------------------------------------------------

	}
}