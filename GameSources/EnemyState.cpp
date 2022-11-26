#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross
{
	namespace kaito
	{
		//!�ǂ�������X�e�[�g-----------------------------------------

		//!�C���X�^���X�̐���(���̂̍쐬)
		SeekState* SeekState::Instance()
		{
			static SeekState instance;
			return &instance;
		}


		void SeekState::Enter(BaseEnemy* Enemy)
		{
			//!�n���^�[�̓���Ƀr�b�N���}�[�N�̃e�N�X�`�����o��

		}

		void SeekState::Execute(BaseEnemy* Enemy)
		{

			//!�ǂ������鏈��������
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();//!�G�̗͂̎擾

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾


			auto distance = PlayerPosition - EnemyPosition;//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * Enemy->GetMaxSpeed();//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)
			Enemy->SetForce(Force);//!�͂�ݒ�


			float f = bsm::length(ptrPlayerTrans->GetPosition() - ptrEnemyTrans->GetPosition());

			if (f > SeekArriveRange)
			{
				Enemy->ChangeState(PatrolState::Instance());
			}


		}
		void SeekState::Exit(BaseEnemy* Enemy)
		{
			//!���U�铮�������
		}

		//!����X�e�[�g-------------------------------------------------
		PatrolState* PatrolState::Instance()
		{
			static PatrolState instance;
			return &instance;
		}

		void PatrolState::Enter(BaseEnemy* Enemy)
		{

		}


		void PatrolState::Execute(BaseEnemy* Enemy)
		{
			//!����o�H
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();//!�G�̗͂̎擾
			auto m_patrolPoints = Enemy->GetEnemyPatorolPoints();
			
			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾

			std::vector<Vec3> patrol;
			for (auto a : m_patrolPoints)
			{
				patrol.push_back(a);
			}

			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();
			auto patrolPoint = Enemy->GetEnemyPatorolindex();

			Vec3 start = patrol[patrolPoint];

		
			const int movePointsCount = patrol.size();
			Vec3 end = patrol[(patrolPoint + 1) % movePointsCount];
			

			auto distance = end - EnemyPosition;//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * Enemy->GetMaxSpeed();//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)

			float pointdistance = bsm::length(end - EnemyPosition);

			if (pointdistance <= PatrolArriveRange)
			{

				patrolPoint++;
			
				if (patrolPoint >= movePointsCount)
				{
					patrolPoint = 0;
				}
				Enemy->SetEnemyPatorolindex(patrolPoint);

			}
			Enemy->SetForce(Force);//!�͂�ݒ�

			float f = bsm::length(PlayerPosition - EnemyPosition);

			if (f < PatrolArriveRange)
			{
				Enemy->ChangeState(SeekState::Instance());
			}
		}

		void PatrolState::Exit(BaseEnemy* Enemy)
		{

		}

		//!-------------------------------------------------------------

	}
}