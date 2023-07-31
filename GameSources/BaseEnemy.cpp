/*!
@file BaseEnemy.cpp
@brief �G�̐e�̎���
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float MAXROTATIONTIME = 4.0f;	//!���n������
	constexpr int RANDOMRANGE = 6;			//!�����̏��
	constexpr int RANDOMNUMBER = 4;			//!����̗���
	constexpr float ROTTOHEAD = 1.0f;		//!���ʂ������l
	//!-------------------------------------
	//! �G�̃I�u�W�F�N�g�̐e
	//! ------------------------------------

	//!�\���Ɣj��
	BaseEnemy::BaseEnemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Force(0),
		m_Velocity(0),
		m_MaxSpeed(20),
		m_StateChangeSize(20.0f),
		m_Enemypatorolindex(0),
		m_loseSightOfTarget(false),
		m_IsEnemyDed(false),
		m_eyeRange(0),
		m_IspositionLiset(false),
		m_SurprisedSprite(false),
		m_seekCondition(false),
		m_surprisedTime(0.0f),
		m_patrolRotation(false),
		m_rotationTime(0.0f),
		m_randomTime(0.0f),
		m_randomCount(0),
		m_dedAnimationEnd(false)
	{
		m_StateMachine = new kaito::StateMachine<BaseEnemy>(this);
		m_StateMachine->SetCurrentState(kaito::PatrolState::Instance());
	}

	
	void BaseEnemy::ApplyForce()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		m_Velocity += m_Force * elapsedTime;				//!���x�ɗ͂����Z
		auto ptrTrans = GetComponent<Transform>();			//!�g�����X�t�H�[���̎擾
		auto pos = ptrTrans->GetPosition();					//!�|�W�V�����̎擾
		pos += m_Velocity * elapsedTime;					//!���x���|�W�V�����ɉ��Z
		ptrTrans->SetPosition(pos);							//!�V�����|�W�V�����ɐݒ�
	}

	void BaseEnemy::ChangeState(kaito::State<BaseEnemy>* NewState)
	{

		m_StateMachine->ChangeState(NewState);//!�X�e�[�g��ύX����
	}

	shared_ptr<Player>BaseEnemy::GetTarget()const {
		return std::dynamic_pointer_cast<Player>(GetStage()->GetSharedObject(L"Player"));//!�v���C���[�̎擾
	}


	void BaseEnemy::HunterDisappear()
	{

		auto group = GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");//!���l�̃I�u�W�F�N�g�O���[�v�̎擾
		auto& vecHunter = group->GetGroupVector();						  //!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!�n���^�[�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecHunter)
		{
			auto hunterPtr = v.lock();									  //!�n���^�[�̃O���[�v����1���b�N����
			Vec3 ret;													  //!�ŋߐړ_�̑��
			auto ptrHunter = dynamic_pointer_cast<Hunter>(hunterPtr);	  //!���b�N�����������o��
			if (ptrHunter)
			{
				auto hunterSpeed = ptrHunter->GetSpeed();				  //!���l�̃X�s�[�h���擾
				//!�n���^�[�̑��x��0�̎�
				if (hunterSpeed == 0.0f)
				{

					GetStage()->RemoveGameObject<Hunter>(ptrHunter);	  //!�n���^�[�I�u�W�F�N�g���폜
					m_dedAnimationEnd = false;							  //!�A�j���[�V�������n�߂�

				}
			}

		}


	}

	void BaseEnemy::VillagerDisappear()
	{
		
		auto group = GetStage()->GetSharedObjectGroup(L"Villager_ObjGroup");//!���l�̃O���[�v
		auto& vecVillager = group->GetGroupVector();						//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		//!���l�z��I�u�W�F�N�g�̔z�񕪉�
		for (auto& v : vecVillager)
		{

			auto VillagerPtr = v.lock();									//!���l�̃O���[�v����1���b�N����
			Vec3 ret;														//!�ŋߐړ_�̑��
			auto ptrVillager = dynamic_pointer_cast<Villager>(VillagerPtr);	//!���b�N�����������o��

			//!�v���C���[�͈̔͂ɓG����������
			if (ptrVillager)
			{

				auto VillagerSpeed = ptrVillager->GetSpeed();				//!���l�̃X�s�[�h���擾
				//!���l�̑��x��0�ɂȂ�����
				if (VillagerSpeed == 0.0f)
				{

					GetStage()->RemoveGameObject<Villager>(VillagerPtr);//!���l�̃I�u�W�F�N�g���폜
					m_dedAnimationEnd = false;							//!�A�j���[�V�������n�߂�

				}
			}
		}

	}

	void BaseEnemy::AnimationUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//!�A�j���[�V�����̎擾
		ptrDraw->UpdateAnimation(elapsedTime);				//!�A�j���[�V�����̍X�V
	}

	void BaseEnemy::ObstacleAvoidance()
	{
		auto ptrAvoidance = GetBehavior<ObstacleAvoidanceSteering>();//!��Q���������s��
		m_Force += ptrAvoidance->Execute(m_Force, GetVelocity());	 //!�͂Ɍv�Z�����l�����Ĕ�����
	}

	void BaseEnemy::Facade()
	{
		auto ptrUtil = GetBehavior<UtilBehavior>();//!Behavior�̎擾
		ptrUtil->RotToHead(ROTTOHEAD);		   //!���ʂ̒l�����ăI�u�W�F�N�g�𐳖ʂɌ�������
	}

	void BaseEnemy::EnemyRandomRotation()
	{
		auto& app = App::GetApp();				//!�A�v���̎擾
		auto time = app->GetElapsedTime();		//!���Ԃ̎擾
		m_randomTime += time;					//!�����_���^�C���Ɏ��Ԃ𑫂�

		srand(0);								//!�����̏�����
		m_randomCount = rand() % RANDOMRANGE;//!����̒l�Ŋ��肻�̗]����󂯎�邱�Ƃɂ�肻��ȏ�͕Ԃ��Ă��Ȃ��悤�ɂ���

		//!�����_���ɕς��ϐ�������̐����ɕς�����Ƃ�
		if (m_randomCount == RANDOMNUMBER)
		{
			m_patrolRotation = true;//!�G�̌��n��������true�ɂ���
		}
		//!���n���Ă���Ƃ�
		if (m_patrolRotation == true)
		{
			auto EnemyTransform = GetComponent<Transform>();	//!�G�̃g�����X�R���t�H�[���R���|�[�l���g���擾
			auto elapsdTime = App::GetApp()->GetElapsedTime();	//!�G���p�\�^�C���̎擾
			m_rotationTime += elapsdTime;						//!�ϐ��ɖ��t���[���G���p�\�^�C���𑫂�
			EnemyTransform->SetRotation(0, m_rotationTime, 0);	//!Y���̉�]��ύX

			//!����I��������]�̏��������s���Ȃ�
			if (m_rotationTime >= MAXROTATIONTIME)
			{
				m_patrolRotation = false;						//!���n�����I������
			}

			//!�ǂ������Ă���Ƃ��͉�]�̏��������s���Ȃ�
			if (m_seekCondition == true)
			{
				m_patrolRotation = false;						//!���n�����I������
			}

		}

	}

	void BaseEnemy::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();			//!�V�[���̎擾
		auto playerChange = scene->GetPlayerChangeDirecting();	//!�v���C���[�̕ϐg���J�n����
		auto gameOver = scene->GetGameOver();					//!�Q�[���I�[�o�[���ǂ����̎擾
		//!�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ��Ƃ�
		if (!gameOver)
		{
			//!�v���C���[���ԐM���Ă��Ȃ��Ƃ�
			if (!playerChange)
			{
				//!�|�ꂽ�A�j���[�V�����I����
				if (m_dedAnimationEnd)
				{
					VillagerDisappear();//!���l������
					HunterDisappear();	//!�n���^�[������
				}


				AnimationUpdate();		 //!�A�j���[�V�����̍X�V
				m_StateMachine->Update();//!�X�e�[�g�}�V���̍X�V
				ObstacleAvoidance();	 //!��Q�����
				EnemyRandomRotation();   //!��������n��
				//!���n���Ă��Ȃ��Ƃ�
				if (m_patrolRotation == false)
				{
					m_rotationTime = 0.0f;//!���n�����Ԃ�0�ɂ���
					ApplyForce();		  //!�K����
				}

				m_Force = Vec3(0);		  //!�͂̏�����
				Facade();				  //!�i�s����������

			}
		}
	}

}