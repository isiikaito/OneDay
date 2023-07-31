
/*!
@file EnmeyState.cpp
@brief �G�̃X�e�[�g
@author Kaito Isii
*/
#include "stdafx.h"
#include "Project.h"
#include "Utility.h"

namespace basecross
{
	namespace kaito
	{
		constexpr float EYERANG = 40.0f;			//!�v���C���[��������͈�
		constexpr float MAXLOSTTIME = 5.0f;			//!�v���C���[���������܂ł̎���
		constexpr float MAXPEDISTANCE = 40.0f;		//!�v���C���[�ƓG�̍ő勗��
		constexpr float MAXPOINTDISTANCE = 5.0f;	//!�G������|�C���g�ɂ��ǂ蒅������
		constexpr float ANGLELIMITSIX = 6.0f;		//!�v���C���[�̎���̐���
		constexpr float ANGLELIMITNINE = 9.0f;		//!�v���C���[�̎���̐���
		constexpr int ADDINDEX = 1;					//!���̃C���f�b�N�X�֐i�߂�

		//!�ǂ�������X�e�[�g-----------------------------------------

		//!�C���X�^���X�̐���(���̂̍쐬)
		SeekState* SeekState::Instance()
		{
			static SeekState instance;
			return &instance;
		}

		void SeekState::Enter(BaseEnemy* Enemy)
		{
			auto seekCondition = Enemy->GetseekCondition();
			seekCondition = true;
			Enemy->SetseekCondition(seekCondition);

		}

		void SeekState::Execute(BaseEnemy* Enemy)
		{


			//!�ǂ������鏈��������
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();				//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();					//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();							//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();										//!�G�̗͂̎擾
			auto maxSpeed = Enemy->GetMaxSpeed();								//!�G�̍ő呬�x
			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();				//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾
			auto distance = PlayerPosition - EnemyPosition;						//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();												//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * maxSpeed;							//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;								//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)
			Enemy->SetForce(Force);												//!�͂�ݒ�
			float f = bsm::length(PlayerPosition - EnemyPosition);				//!�v���C���[�ƓG�̋���
			//!��Q���̎擾
			auto& app = App::GetApp();//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

			for (auto& Obj : Objects)//!�I�u�W�F�N�g�̗v�f��
			{
				auto stageBuilding = dynamic_pointer_cast<StageBuilding>(Obj);//!�����̎擾
				if (stageBuilding)
				{
					auto StageBuildingObb = stageBuilding->GetComponent<CollisionObb>()->GetObb();//!�X�e�[�W�̕ǂ�Obb�̎擾

					if (HitTest::SEGMENT_OBB(PlayerPosition, EnemyPosition, StageBuildingObb))//!�J�����Ǝ��_�̊Ԃɕǂ���������
					{
						Enemy->ChangeState(BrettGramState::Instance());//!�v���C���[�ƓG�̊Ԃɏ�Q�����������Ƃ��X�e�[�g��ύX����
					}
				}
			}

			//!�G���E���ꂽ�Ƃ����S�̃X�e�[�g�ɐ؂�ւ��
			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!�X�e�[�g��ύX����
			}
		}
		void SeekState::Exit(BaseEnemy* Enemy)
		{
		}

		//!����X�e�[�g-------------------------------------------------
		PatrolState* PatrolState::Instance()
		{
			static PatrolState instance;
			return &instance;
		}

		void PatrolState::Enter(BaseEnemy* Enemy)
		{
			auto patrolPoint = Enemy->GetEnemyPatorolindex();//!�p�g���[���|�C���g�̃C���f�b�N�X�̎擾
			patrolPoint = 0;
			Enemy->SetEnemyPatorolindex(patrolPoint);//!�p�g���[���|�C���g�̃C���f�b�N�X��ݒ肷��

			auto seekCondition = Enemy->GetseekCondition();
			seekCondition = false;
			Enemy->SetseekCondition(seekCondition);
		}

		void PatrolState::Execute(BaseEnemy* Enemy)
		{

			//!�G�̃p�����[�^�[�̎擾
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();	//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();		//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();				//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();							//!�G�̗͂̎擾
			auto m_patrolPoints = Enemy->GetEnemyPatorolPoints();	//!�p�g���[���|�C���g
			auto maxSpeed = Enemy->GetMaxSpeed();					//!�G�̍ő呬�x�̎擾
			auto patrolPoint = Enemy->GetEnemyPatorolindex();		//!�p�g���[���|�C���g�̃C���f�b�N�X�̎擾
			//1�v���C���[�̃p�����[�^�[�̎擾
			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();				//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾

			//!���񂷂鏈��
			auto movePointsCount = m_patrolPoints.size();							//!�p�g���[���|�C���g�̔z��̒���
			Vec3 end = m_patrolPoints[(patrolPoint + ADDINDEX) % movePointsCount];//!�G�����Ɍ������|�C���g�̐ݒ�
			auto distance = end - EnemyPosition;									//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();													//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * maxSpeed;								//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;									//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)
			float pointdistance = bsm::length(end - EnemyPosition);					//!�G���������|�C���g����G�܂ł̋���
			if (pointdistance <= MAXPOINTDISTANCE)//!�G���������|�C���g����G�܂ł̋��������̋����߂Â�����
			{

				patrolPoint++;						//!���̃|�C���g�Ɉړ�

				if (patrolPoint >= movePointsCount)	//!�p�g���[���z��̍Ō�̗v�f�ɂȂ�����B
				{
					patrolPoint = 0;				//!�p�g���[���z��̍ŏ��̗v�f�ɖ߂�
				}
				Enemy->SetEnemyPatorolindex(patrolPoint);//!�p�g���[���|�C���g�̃C���f�b�N�X��ݒ肷��

			}
			Enemy->SetForce(Force);//!�͂�ݒ�


			Vec3 PEvector = PlayerPosition - EnemyPosition;			//!�v���C���[�ƓG�̃x�N�g�����擾
			PEvector.normalize();									//!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto Enemyfront = ptrEnemyTrans->GetForword();			//!�G�̐��ʂ��擾
			auto angle = angleBetweenNormals(Enemyfront, PEvector);	//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / ANGLELIMITSIX;						//!360��6�Ŋ����Ċp�x���o���B
			float f = bsm::length(PlayerPosition - EnemyPosition);	//!�G�ƃv���C���[�̋���

			auto playerChange = Enemy->GetTarget()->GetPlayerChange();
			//!�v���C���[���T�j
			if (playerChange == PlayerModel::wolf)
			{
				if (f < EYERANG)//!�G�ƃv���C���[�̋�������苗���߂Â�����
				{
					if (angle <= chk && angle >= -chk)//!�G���猩��+60�x��-60�x�Ƀv���C���[����������
					{

						Enemy->ChangeState(SeekState::Instance());//!�X�e�[�g��ύX����
					}
				}

			}

			//!�G���E���ꂽ�Ƃ�
			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!�X�e�[�g��ύX����
			}
		}

		void PatrolState::Exit(BaseEnemy* Enemy)
		{
			//!�r�b�N���}�[�N�̏o��
			auto Surprised = Enemy->GetSurprisedSprite();
			Surprised = true;
			Enemy->SetSurprisedSprite(Surprised);
			auto player = Enemy->GetTarget();
			player->SetVibrationOn(true);


		}

		//!-------------------------------------------------------------

	   //!�u���b�g�O�����X�e�[�g---------------------------------------

		void BrettGramState::HitStageBuildingObb(BaseEnemy* Enemy)
		{
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();				//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();					//!�G�̃|�W�V�����̎擾
			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();				//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾
			//!��Q���̎擾
			auto& app = App::GetApp();											//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();				//!�X�e�[�W�̎擾
			auto& Objects = Stage->GetGameObjectVec();							//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾

			for (auto& Obj : Objects)//!�I�u�W�F�N�g�̗v�f��

			{
				auto stageBuilding = dynamic_pointer_cast<StageBuilding>(Obj);//!�����̎擾
				if (stageBuilding)
				{

					auto StageBuildingObb = stageBuilding->GetComponent<CollisionObb>()->GetObb();//!�X�e�[�W�̕ǂ�Obb�̎擾

					if (HitTest::SEGMENT_OBB(PlayerPosition, EnemyPosition, StageBuildingObb))//!�J�����Ǝ��_�̊Ԃɕǂ���������
					{
						auto elapsdtime = app->GetElapsedTime();
						m_lostTime += elapsdtime;
						if (m_lostTime >= MAXLOSTTIME)
						{

							Enemy->ChangeState(LostStata::Instance());//!�X�e�[�g�̕ύX

						}
						if (m_lostTime >= MAXLOSTTIME)
						{
							m_lostTime = 0.0f;
						}

					}

				}
			}
		}

		BrettGramState* BrettGramState::Instance()
		{
			static BrettGramState instance;
			return &instance;
		}

		void BrettGramState::Enter(BaseEnemy* Enemy)
		{
			BrettGramindex = 0;

			auto m_BrettGramPoints = Enemy->GetTarget()->GetPlayerPositionOnSecond();	//!�v���C���[�̖��b�擾���Ă���ʒu�̎擾
			//!�ۑ������|�W�V�����̐�����
			for (int i = 0; i < m_BrettGramPoints.size(); i++)
			{
				auto EnemyPosition = Enemy->GetComponent<Transform>()->GetPosition();	//!�G�̈ʒu�̎擾
				auto pointdistance = bsm::length(m_BrettGramPoints[i] - EnemyPosition);	//!�u���b�g�u�����̃|�C���g�ƓG�̈ʒu����߂����擾
				//!���̋߂��|�C���g��荡�̃|�C���g���߂�������
				if (Neardistance > pointdistance)
				{
					Vec3 NearPoint = m_BrettGramPoints[i];	//!���̃|�C���g����ԋ߂�
					start = NearPoint;						//!�u���b�g�N�����̃X�^�[�g�������Ɍ���
				}
			}
			m_lostTime = 0.0f;
		}

		void BrettGramState::Execute(BaseEnemy* Enemy)
		{
			BrettGramindex = 0;
			auto ptrEnemyTrans = Enemy->GetComponent<Transform>();	//!�G�̃g�����X�t�H�[���̎擾
			auto EnemyPosition = ptrEnemyTrans->GetPosition();		//!�G�̃|�W�V�����̎擾
			Vec3 EnemyVelocity = Enemy->GetVelocity();				//!�G�̑��x�̎擾
			Vec3 Force = Enemy->GetForce();							//!�G�̗͂̎擾
			auto maxSpeed = Enemy->GetMaxSpeed();					//!�X�s�[�h�̎擾

			auto ptrPlayerTrans = Enemy->GetTarget()->GetComponent<Transform>();//!�^�[�Q�b�g(�v���C���[)�̃g�����X�t�H�[���̎擾
			auto PlayerPosition = ptrPlayerTrans->GetPosition();				//!�^�[�Q�b�g(�v���C���[)�̍��W�̎擾

			auto m_BrettGramPoints = Enemy->GetTarget()->GetPlayerPositionOnSecond();//!�v���C���[�̖��b���Ƃ̈ʒu�̎擾

			if (m_BrettGramPoints.size() == 0) //!�z��̒��g���Ȃ���
			{
				return;
			}

			start = m_BrettGramPoints[BrettGramindex];								//!�ŏ��̃u���b�g�N�����|�C���g�̐ݒ�
			auto movePointsCount = m_BrettGramPoints.size();						//!�u���b�g�N�����̔z��̑傫��
			Vec3 end = m_BrettGramPoints[(BrettGramindex + 1) % movePointsCount];	//!�G���������|�C���g�̐ݒ�
			auto distance = end - EnemyPosition;									//!�v���C���[�̍��W����G�̍��W�������x�N�g���̌v�Z
			distance.normalize();													//!�x�N�g�����m�[�}���C�Y��
			auto Requiredspeed = distance * maxSpeed;								//!���x�̎擾
			Force += Requiredspeed - EnemyVelocity;									//!�ō����x�����݂̑��x�ň���(����̑����Ȃǂ̗͂����܂�)
			float Brettpointdistance = bsm::length(end - EnemyPosition);			//!���Ɍ������u���b�g�|�C���g�ƓG�̈ʒu�̋���

			if (Brettpointdistance <= BrettGramArriveRange)//!��̋������T�ȉ��ɂȂ�����
			{
				BrettGramindex++;//!���̃|�C���g�Ɉڍs����

				if (BrettGramindex == maxBrettGramindex)//!�C���f�b�N�X��40�����炻����z�������B
				{
					BrettGramindex = 0;	//!�z��̈�ԍŏ��������B
				}
			}

			Enemy->SetForce(Force);											//!�͂�ݒ�
			float PEdistance = bsm::length(PlayerPosition - EnemyPosition);	//!�v���C���[�ƓG�̋���
			//!�G�̎���
			Vec3 PEvector = PlayerPosition - EnemyPosition;					//!�v���C���[�ƓG�̃x�N�g�����擾
			auto Enemyfront = ptrEnemyTrans->GetForword();					//!�G�̐��ʂ��擾
			PEvector.normalize();											//!�v���C���[�ƓG�̃x�N�g���𐳋K��
			auto angle = angleBetweenNormals(Enemyfront, PEvector);			//!�G�̐��ʂƃv���C���[�ƓG�̃x�N�g�����擾���p�x�ɕϊ�
			auto chk = XM_PI / ANGLELIMITNINE;							//!360��9�Ŋ����Ċp�x���o���B

			//!�G���猩��+60�x��-60�x�Ƀv���C���[����������
			if (angle <= chk && angle >= -chk)
			{
				if (PEdistance <= MAXPEDISTANCE)
				{
					Enemy->ChangeState(SeekState::Instance());//!�X�e�[�g��ύX����
				}
			}

			HitStageBuildingObb(Enemy);
			if (maxSpeed == 0)
			{
				Enemy->ChangeState(DedState::Instance());//!�X�e�[�g��ύX����
			}

		}

		void BrettGramState::Exit(BaseEnemy* Enemy)
		{

		}
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
			auto enemyDed = Enemy->GetIsEnemyDed();	//!�G���|�ꂽ���ǂ���
			enemyDed = true;						//!�|�ꂽ
			Enemy->SetIsEnemyDed(enemyDed);			//!�|�ꂽ���ǂ����ݒ肷��
			auto player = Enemy->GetTarget();		//!�v���C���[�̎擾
			player->SetVibrationOn(true);			//!�R���g���[���̐U��


		}

		void DedState::Execute(BaseEnemy* Enemy)
		{
			Vec3 EnemyVelocity = Enemy->GetVelocity();	//!�G�̑��x�̎擾
			EnemyVelocity = Vec3(0);					//!�G�̃x�N�g�����Z�b�g
			Enemy->SetVelocity(EnemyVelocity);			//!�x�N�g���̐ݒ�
			auto& app = App::GetApp();					//!�A�v���̎擾
			auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾



		}
		void DedState::Exit(BaseEnemy* Enemy)
		{
			//!���U�铮�������

		}


		//!�G�����������Ƃ��̃X�e�[�g---------------------------------

		//!�C���X�^���X�̐���(���̂̍쐬)
		LostStata* LostStata::Instance()
		{
			static LostStata instance;
			return &instance;

		}

		//!�v���C���[��������
		void LostStata::Enter(BaseEnemy* Enemy)
		{
			//!���l�̓���ɂ͂Ăȃ}�[�N�̃e�N�X�`�����o��
			auto loseSightOfTarget = Enemy->GetloseSightOfTarget();
			loseSightOfTarget = true;
			Enemy->SetloseSightOfTarget(loseSightOfTarget);
		}

		void LostStata::Execute(BaseEnemy* Enemy)
		{

			auto EnemyTrans = Enemy->GetComponent<Transform>();	//!�G�̃g�����X�t�H�[�����擾����
			auto EnemyPosition = EnemyTrans->GetPosition();		//!�G�̃|�W�V�������擾����
			auto patorolPoint = Enemy->GetEnemyPatorolPoints();	//!�G�̃p�g���[���|�C���g���擾
			auto& app = App::GetApp();							//!�A�v���̎擾
			auto time = app->GetElapsedTime();					//!���Ԃ̎擾
			m_lostTime += time;
			if (m_lostTime >= MAXLOSTTIME)						//!�͂Ăȃ}�[�N�̕\�����鎞��
			{
				EnemyPosition = patorolPoint[0];					//!�G�̃p�g���[���|�C���g�̃C���f�b�N�X��0�ɂ���
				EnemyTrans->SetPosition(EnemyPosition);				//!�G�������̃p�g���[���|�C���g�̈ʒu�ɂ���
				Enemy->ChangeState(PatrolState::Instance());		//!�X�e�[�g��ύX����
			}

		}
		void LostStata::Exit(BaseEnemy* Enemy)
		{
			//!���U�铮�������
			//!���l�̓���ɂ͂Ăȃ}�[�N�̃e�N�X�`��������
			auto loseSightOfTarget = Enemy->GetloseSightOfTarget();
			loseSightOfTarget = false;
			Enemy->SetloseSightOfTarget(loseSightOfTarget);

		}


	}
	//!-------------------------------------------------------------

}
