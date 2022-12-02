#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross
{
	namespace kaito
	{


		//!�v���C���[�𔭌������Ƃ��̎n�߂̒ǂ������鏈��-------------
		
		
	    //!�C���X�^���X�̐���(���̂̍쐬)
		SurprisedState* SurprisedState::Instance()
		{
			static SurprisedState instance;
			return &instance;
		}


		void SurprisedState::Enter(BaseEnemy* Enemy)
		{
			//!�n���^�[�̓���Ƀr�b�N���}�[�N�̃e�N�X�`�����o��
			auto Player = Enemy->GetTarget();
			auto PlayerFound = Player->GetPlayerFound();
			PlayerFound = true;
			Player->SetPlayerFound(PlayerFound);


		}

		void SurprisedState::Execute(BaseEnemy* Enemy)
		{

			//!�ǂ������鏈��������
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();//!�G�̗͂̎擾

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾
			auto maxSpeed = Enemy->GetMaxSpeed();

			auto distance = PlayerPosition - EnemyPosition;//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * maxSpeed;//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)
			Enemy->SetForce(Force);//!�͂�ݒ�


			Vec3 PEvector = PlayerPosition - EnemyPosition;//!�v���C���[�ƓG�̃x�N�g�����擾
			auto Enemyfront = ptrEnemyTrans->GetForword();//!�G�̐��ʂ��擾
			PEvector.normalize();//!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / 6.0f;//!360��6�Ŋ����Ċp�x���o���B

			float f = bsm::length(PlayerPosition - EnemyPosition);//!�v���C���[�ƓG�̋���

			
			if (f > BrettGramRange)//!�v���C���[�ƓG�̋�����蒷���Ȃ�����
			{
				Enemy->ChangeState(BrettGramState::Instance());//!�X�e�[�g��ύX����
			}

			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!�X�e�[�g��ύX����
			}
		}
		void SurprisedState::Exit(BaseEnemy* Enemy)
		{
			//!���U�铮�������
		}
		//!-----------------------------------------------------------
		
		//!�ǂ�������X�e�[�g-----------------------------------------

		//!�C���X�^���X�̐���(���̂̍쐬)
		SeekState* SeekState::Instance()
		{
			static SeekState instance;
			return &instance;
		}


		void SeekState::Enter(BaseEnemy* Enemy)
		{
			

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


			Vec3 PEvector = PlayerPosition - EnemyPosition;//!�v���C���[�ƓG�̃x�N�g�����擾
			auto Enemyfront = ptrEnemyTrans->GetForword();//!�G�̐��ʂ��擾
			PEvector.normalize();//!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / 6.0f;//!360��6�Ŋ����Ċp�x���o���B

			float f = bsm::length(PlayerPosition - EnemyPosition);//!�v���C���[�ƓG�̋���

			if (f > SeekArriveRange)//!�v���C���[�ƓG�̋�����蒷���Ȃ�����
			{
				if (angle <= chk && angle >= -chk)//!�G���猩��+60�x��-60�x�Ƀv���C���[����������
				{
					Enemy->ChangeState(PatrolState::Instance());//!�X�e�[�g��ύX����
				}
			}
			if (f > BrettGramRange)//!�v���C���[�ƓG�̋�����蒷���Ȃ�����
			{
				Enemy->ChangeState(BrettGramState::Instance());//!�X�e�[�g��ύX����
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
			//!�n���^�[�̓���Ƀr�b�N���}�[�N�̃e�N�X�`�����o��
			auto loseSightOfTarget=Enemy->GetloseSightOfTarget();
			loseSightOfTarget = true;
			Enemy->SetloseSightOfTarget(loseSightOfTarget);


		}


		void PatrolState::Execute(BaseEnemy* Enemy)
		{

			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();//!�G�̗͂̎擾
			auto m_patrolPoints = Enemy->GetEnemyPatorolPoints();//!�p�g���[���|�C���g
			auto maxSpeed = Enemy->GetMaxSpeed();

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾

			//!�p�g���[���|�C���g��z��ɓ����
			std::vector<Vec3> patrol;
			for (auto& a : m_patrolPoints)
			{
				patrol.push_back(a);
			}

			auto& app = App::GetApp();//!�A�v���̎擾
			float delta = app->GetElapsedTime();//!���Ԃ̎擾
			auto patrolPoint = Enemy->GetEnemyPatorolindex();//!�p�g���[���|�C���g�̃C���f�b�N�X�̎擾
			Vec3 start = patrol[patrolPoint];//!�X�^�[�g�̈ʒu�Ƀp�g���[���|�C���g��ݒ�
			const int movePointsCount = patrol.size();//!�p�g���[���|�C���g�̔z��̒���
			Vec3 end = patrol[(patrolPoint + 1) % movePointsCount];//!�G�����Ɍ������|�C���g�̐ݒ�

			auto distance = end - EnemyPosition;//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * maxSpeed;//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)

			float pointdistance = bsm::length(end - EnemyPosition);//!�G���������|�C���g����G�܂ł̋���



			if (pointdistance <= PatrolArriveRange)//!�G���������|�C���g����G�܂ł̋��������̋����߂Â�����
			{

				patrolPoint++;//!���̃|�C���g�Ɉړ�

				if (patrolPoint >= movePointsCount)//!�p�g���[���z��̍Ō�̗v�f�ɂȂ�����B
				{
					patrolPoint = 0;//!�p�g���[���z��̍ŏ��̗v�f�ɖ߂�
				}
				Enemy->SetEnemyPatorolindex(patrolPoint);//!�p�g���[���|�C���g�̃C���f�b�N�X��ݒ肷��

			}
			Enemy->SetForce(Force);//!�͂�ݒ�


			Vec3 PEvector = PlayerPosition - EnemyPosition;//!�v���C���[�ƓG�̃x�N�g�����擾
			auto Enemyfront = ptrEnemyTrans->GetForword();//!�G�̐��ʂ��擾
			PEvector.normalize();//!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto angle = angleBetweenNormals(Enemyfront, PEvector);//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / 6.0f;//!360��6�Ŋ����Ċp�x���o���B
			float f = bsm::length(PlayerPosition - EnemyPosition);//!�G�ƃv���C���[�̋���

			auto playerChange = Enemy->GetTarget()->GetPlayerCange();

			if (playerChange == static_cast<int>(PlayerModel::wolf)) 
			{
			    if (angle <= chk && angle >= -chk)//!�G���猩��+60�x��-60�x�Ƀv���C���[����������
				{
					if (f < PatrolArriveRange)//!�G�ƃv���C���[�̋�������苗���߂Â�����
					{
						Enemy->ChangeState(SurprisedState::Instance());//!�X�e�[�g��ύX����
					}
				}
			}

			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!�X�e�[�g��ύX����
			}
		}

		void PatrolState::Exit(BaseEnemy* Enemy)
		{}

		//!-------------------------------------------------------------

	   //!�u���b�g�O�����X�e�[�g---------------------------------------
		BrettGramState* BrettGramState::Instance()
		{
			static BrettGramState instance;
			return &instance;
		}

		void BrettGramState::Enter(BaseEnemy* Enemy)
		{
			BrettGramindex = 0;

			auto m_BrettGramPoints = Enemy->GetTarget()->GetPlayerPositionOnSecond();//!�v���C���[�̖��b�擾���Ă���ʒu�̎擾
			for (int i = 0; i < m_BrettGramPoints.size(); i++)
			{
				auto EnemyPosition = Enemy->GetComponent<Transform>()->GetPosition();//!�G�̈ʒu�̎擾
				auto pointdistance = bsm::length(m_BrettGramPoints[i] - EnemyPosition);//!�u���b�g�u�����̃|�C���g�ƓG�̈ʒu����߂����擾
				if (Neardistance > pointdistance)//!���̋߂��|�C���g��荡�̃|�C���g���߂�������
				{
					Vec3 NearPoint = m_BrettGramPoints[i];//!���̃|�C���g����ԋ߂�
					start = NearPoint;//!�u���b�g�N�����̃X�^�[�g�������Ɍ���
				}
			}
		}

		void BrettGramState::Execute(BaseEnemy* Enemy)
		{
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();//!�G�̗͂̎擾

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾

			auto m_BrettGramPoints = Enemy->GetTarget()->GetPlayerPositionOnSecond();//!�v���C���[�̖��b���Ƃ̈ʒu�̎擾

			if (m_BrettGramPoints.size() == 0) //!�z��̒��g���Ȃ���
			{
				return;
			}

			start = m_BrettGramPoints[BrettGramindex];//!�ŏ��̃u���b�g�N�����|�C���g�̐ݒ�
			const int movePointsCount = m_BrettGramPoints.size();//!�u���b�g�N�����̔z��̑傫��
			Vec3 end = m_BrettGramPoints[(BrettGramindex + 1) % movePointsCount];//!�G���������|�C���g�̐ݒ�

			auto distance = end - EnemyPosition;//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * Enemy->GetMaxSpeed();//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)

			float Brettpointdistance = bsm::length(end - EnemyPosition);//!���Ɍ������u���b�g�|�C���g�ƓG�̈ʒu�̋���

			if (Brettpointdistance <= BrettGramArriveRange)//!��̋������T�ȉ��ɂȂ�����
			{

				BrettGramindex++;//!���̃|�C���g�Ɉڍs����

				if (BrettGramindex == 49)//!�C���f�b�N�X��19�����炻����z�������B
				{
					BrettGramindex = 0;//!�z��̈�ԍŏ��������B
				}
			}

			Enemy->SetForce(Force);//!�͂�ݒ�
			float PEdistance = bsm::length(PlayerPosition - EnemyPosition);//!�v���C���[�ƓG�̋���

			if (PEdistance <= 10.0f)//!5���߂Â�����
			{
				Enemy->ChangeState(SeekState::Instance());//!�X�e�[�g�̕ύX
			}
			if (PEdistance >= 60)//!�v���C���[�ƓG�̋�����蒷���Ȃ�����
			{
				Enemy->ChangeState(PatrolState::Instance());//!�X�e�[�g��ύX����
			}
		}
		void BrettGramState::Exit(BaseEnemy* Enemy)
		{}
		//!-------------------------------------------------------------
		
			//!�E���ꂽ�Ƃ��̃X�e�[�g-----------------------------------------

		//!�C���X�^���X�̐���(���̂̍쐬)
		DedState* DedState::Instance()
		{
			static DedState instance;
			return &instance;

		}

		void DedState::Enter(BaseEnemy* Enemy)
		{
			auto maxSpeed = Enemy->GetMaxSpeed();
			maxSpeed = 0;

		}

		void DedState::Execute(BaseEnemy* Enemy)
		{
			Vec3 EnemyVelocity = Enemy->GetVelocity();//!�G�̑��x�̎擾
			EnemyVelocity = Vec3(0);
			Enemy->SetVelocity(EnemyVelocity);
			Vec3 Force = Enemy->GetForce();//!�G�̗͂̎擾
			
			
		}
		void DedState::Exit(BaseEnemy* Enemy)
		{
			//!���U�铮�������

		}

	
	}
}