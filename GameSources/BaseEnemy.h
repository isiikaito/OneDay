/*!
@file BaseEnemy.h
@brief �G�̍쐬
@autohor isii kaito
*/
#pragma once
#include "stdafx.h"

//!���ۃN���X
namespace basecross
{
	namespace kaito
	{
		//!�O���錾
		template<class entity_type>
		class State;
		//!�O���錾
		template <class entity_type>
		class StateMachine;
	}

	class BaseEnemy :public GameObject
	{
		//!�X�e�[�g�}�V�[��
		kaito::StateMachine<BaseEnemy>* m_StateMachine;//!�X�e�[�g�}�V���N���X�̃C���X�^���X�̐���
		std::vector<Vec3>m_EnemyPatrolPoints;//!�G�̏���|�C���g
		Vec3 m_Force;//!�t�H�[�X
		Vec3 m_Velocity;//!���x
		float m_StateChangeSize;//!�X�e�[�g�̕ύX
		float m_MaxSpeed;//!�ő�̑��x
		int m_Enemypatorolindex;//!�G�̏���|�C���g�̐�
		bool m_seekCondition;//!�G���ǂ������Ă��邩�ǂ���
        bool m_loseSightOfTarget;//!�v���C���[���������Ă���Ƃ�
		bool m_IspositionLiset;//!�|�W�V�����̃��Z�b�g
	protected:
		

		//!�\���Ɣj��
		BaseEnemy(const shared_ptr<Stage>& StagePtr);

		//!�f�X�g���N�^
		virtual ~BaseEnemy()noexcept = default;

	public:
		//!�A�N�Z�b�T

		//!�X�e�[�g�}�V�[���̃A�N�Z�b�T
		const kaito::StateMachine<BaseEnemy>* GetFSM()const
		{
			return m_StateMachine;
		}
		//!�X�e�[�g��ύX���钷���̎擾
		float GatStateChangeSize()const
		{
			return m_StateChangeSize;
		}

		//!�X�e�[�g��ύX���钷���̐ݒ�
		void SetStageChangeSize(float& ChangeSize)
		{
			m_StateChangeSize = ChangeSize;
		}

		//!�͂̎擾
		const Vec3& GetForce()const
		{
			return m_Force;
		}

		//!�͂̐ݒ�
		void SetForce(const Vec3& f)
		{
			m_Force = f;
		}

		//!�͂̒ǉ�
		void AddForce(const Vec3& f)
		{
			m_Force += f;
		}

		//!���݂̑��x�̎擾
		const Vec3& GetVelocity()const
		{
			return m_Velocity;
		}

		//!���݂̑��x�̐ݒ�
		void SetVelocity(const Vec3& v)
		{
			m_Velocity = v;
		}

		//!�ő�̑��x�̎擾
		float& GetMaxSpeed()
		{
			return m_MaxSpeed;
		}

		//!�ő�̑��x�̎擾
		void SetMaxSpeed(float& MaxSpeed)
		{
			m_MaxSpeed = MaxSpeed;
		}

		//!�G�̏���|�C���g�̎擾
		std::vector<Vec3>GetEnemyPatorolPoints()const
		{
			return m_EnemyPatrolPoints;
		}

		//!�G�̏���|�C���g�̐ݒ�
		void SetpatorolPoints(const std::vector<Vec3>& path)
		{
			m_EnemyPatrolPoints = path;
		}

		//!�G�̏���|�C���g���̎擾
		int GetEnemyPatorolindex()
		{
			return m_Enemypatorolindex;
		}

		//!�G�̏���|�C���g���̐ݒ�
		void SetEnemyPatorolindex(int& patrolindex)
		{
			m_Enemypatorolindex = patrolindex;
		}

		//!�G���v���C���[�����������Ƃ��擾
		bool GetloseSightOfTarget()
		{
			return m_loseSightOfTarget;
		}
		
		//!�G���v���C���[�����������Ƃ��̐ݒ�
		void SetloseSightOfTarget( bool loseSightOfTarget)
		{
			m_loseSightOfTarget = loseSightOfTarget;
		}

		//!�G���v���C���[��ǂ������Ă����Ԃ̎擾
		bool GetseekCondition()
		{
			return m_seekCondition;
		}

		//!�G���v���C���[��ǂ������Ă����Ԃ̐ݒ�
		void SetseekCondition(bool seekCondition)
		{
			m_seekCondition = seekCondition;
		}

		//!�v���C���[�̈ʒu�̃��Z�b�g�̎擾
		bool GetIspositionLiset()
		{
			return m_IspositionLiset;
		}

		//!�v���C���[�̈ʒu�̃��Z�b�g�̐ݒ�
		void SetIspositionLiset(bool IspositionLiset)
		{
			m_IspositionLiset= IspositionLiset;
		}

		
		//!�K����
		void ApplyForce();

		//!�X�e�[�g�̕ύX
		virtual void ChangeState(kaito::State<BaseEnemy>* NewState);

		//!�^�[�Q�b�g�̎擾
		shared_ptr<Player>GetTarget()const;

		//!�������̏���
		virtual void OnCreate()override ;

		//!�X�V�̏���
		virtual void OnUpdate()override;
	};

}
