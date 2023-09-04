/*!
@file GameManager.h
@brief �Q�[���X�e�[�W���ԃ}�l�[�W���[
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "Player.h"
namespace basecross {

	namespace kaito
	{
		//!�O���錾
		template<class entity_type>
		class State;
		//!�O���錾
		template <class entity_type>
		class StateMachine;
	}

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameManager:public GameObject
	{
		
	private:
		kaito::StateMachine<GameManager>* m_StateMachine;		//!�v���C���[�̃X�e�[�g�}�V��


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		GameManager(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�W���Ԃ̎擾
		@retrun	���Ԃ�Ԃ�
		*/
		static float GetElpasedTiem() ;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�ϐg���鎞�Ԃ̎擾
		@retrun	���Ԃ�Ԃ�
		*/
		static float GetDayTiem();


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�}�V���̃A�N�Z�b�T
		@return �X�e�[�g�}�V��
		*/
		const kaito::StateMachine<GameManager>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�̕ύX
		@�����@�N���X�ɑΉ������X�e�[�g
		*/
		virtual void ChangeState(kaito::State<GameManager>* NewState);


		//--------------------------------------------------------------------------------------
		/*!
		@brief �v���C���[�̎擾
		*/
		shared_ptr<Player>GetPlayer()const;

		virtual void OnUpdate() override;
	};
}
//end basecross


