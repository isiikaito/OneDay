/*!
@file OpeningCameraMan.h
@brief �I�[�v�j���O�J����
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

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
	//�@�I�[�v�j���O�J�����}��
	//--------------------------------------------------------------------------------------
	class OpeningCameraMan : public GameObject {
	private:
		kaito::StateMachine<OpeningCameraMan>* m_StateMachine;//!�X�e�[�g�}�V���N���X�̃C���X�^���X�̐���
		Vec3 m_startPos;	//!�X�^�[�g�|�W�V����
		Vec3 m_endPos;		//!�I���̃|�W�V����
		Vec3 m_AtStartPos;	//!���_�̎n�܂�̈ʒu
		Vec3 m_AtEndPos;	//!���_�̏I���ʒu
		Vec3 m_AtPos;		//!���_�̈ʒu
		float m_totalTime;	//!�J�����̎���
	public:
		//!�X�e�[�g�}�V�[���̃A�N�Z�b�T
		const kaito::StateMachine<OpeningCameraMan>* GetFSM()const
		{
			return m_StateMachine;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		OpeningCameraMan(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�I�[�v�j���O�J�����̐ݒ�
		*/
		void OpeningCameraStatus(Vec3 StartPos, Vec3 EndPos, Vec3 AtStartPos, Vec3 AtEndPos, float TotalTime);
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~OpeningCameraMan() {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate() override;
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����J����
		@return �J�������g�����ǂ���
		*/
		bool MoveCamera(float totaltime);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���_�̈ʒu���擾
		@return ���_�̈ʒu
		*/
		Vec3 GetAtPos() const {
			return m_AtPos;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�ύX
		*/
		virtual void ChangeState(kaito::State<OpeningCameraMan>* NewState);

	};
}
