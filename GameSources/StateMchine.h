/*!
@file StateMchine.h
@brief �X�e�[�g�}�V��
@author Kaito Isii
*/
#pragma once
#include"stdafx.h"
namespace basecross
{
	namespace kaito
	{
		template<class entity_type>
		class State
		{
		public:
			State(){}
			virtual~State(){}

			//!�������z�֐�
			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g�ɓ������Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Enter(entity_type*) = 0;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�V�X�e�b�v���ƂɎ����̃X�e�[�g���X�V����֐��ɂ���ČĂ΂��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Execute(entity_type*) = 0;	

			//--------------------------------------------------------------------------------------
			/*!
			@brief	�X�e�[�g���o��Ƃ��Ɉ�x�Ă΂�鏈��
			@param	�X�e�[�g���������Ă���N���X
			*/
			virtual void Exit(entity_type*) = 0;

		};

		//!StateMachine�N���X
		template<class entity_type>
		class StateMachine
		{
		private:
			entity_type* m_Owner;				//!���̃C���X�^���X����������G�[�W�F���g�ւ̃|�C���^
			State<entity_type>* m_CurrentState;	//!���݂̃X�e�[�g
			State<entity_type>* m_PreviousState;//!�G�[�W�F���g�̒��O�̃X�e�[�g�̋L�^

		public:
			StateMachine(entity_type* owner) :
				m_Owner(owner),
				m_CurrentState(NULL),
				m_PreviousState(NULL)
			{}

			//!�L����ԋ@�B������������Ƃ��Ɋ֐����g��
			void SetCurrentState(State<entity_type>* s) { m_CurrentState = s; }
			void SetPreviousState(State<entity_type>* s) { m_PreviousState }

			//!�L����ԋ@�B������������Ƃ��Ɋ֐����g��
			void Update()const
			{
				if (m_CurrentState)m_CurrentState->Execute(m_Owner);//!���݂Ɠ����X�e�[�g������Ȃ�Exeute���Ă�

			}

			void ChangeState(State<entity_type>* NewState)
			{
				assert(NewState&&"<StateMachine::ChangeState::trying to change to a null sate>");//!�V�����X�e�[�g�������Ă����true�����Ă��Ȃ����false
				m_PreviousState = m_CurrentState;	//!�ȑO�̃X�e�[�g���L�^����
				m_CurrentState->Exit(m_Owner);		//!���݂���X�e�[�g�̏I���֐����Ă�
				m_CurrentState = NewState;			//!�V�����X�e�[�g�ɕύX����
				m_CurrentState->Enter(m_Owner);		//!�V�����X�e�[�g�̊J�n�֐����Ă�

			}
			void RevertToPreviousState()
			{
				ChangeState(m_PreviousState);

			}

			//!�A�N�Z�T
			State<entity_type>* CurrentState()const { return m_CurrentState; }
			State<entity_type>* PreviousState()const { return m_PreviousState; }

			bool isInstate(const State<entity_type>& st)const {};//!���݂̃X�e�[�g�̌^�ƃp�����[�^�œn���ꂽ�N���X�̌^�������Ȃ�true��Ԃ�

		};
	}
}