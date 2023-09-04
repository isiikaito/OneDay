/**
*@file WoodenBox.h
*@brief �ؔ��̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito isii
*@details �ؔ��̎���
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross���ʂ̃l�[���y�[�X*/
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

	class WoodenBox : public GameObject {
	private:
		StaticModelDeta m_woodenBoxModelData;			//!�ؔ����f���f�[�^
		kaito::StateMachine<WoodenBox>* m_StateMachine;		//!�v���C���[�̃X�e�[�g�}�V��

	public:
		//--------------------------------------------------------------------------------------
		/**
		* �R���X�g���N�^
		*/
		WoodenBox(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~WoodenBox() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�}�V���̃A�N�Z�b�T
		@return �X�e�[�g�}�V��
		*/
		const kaito::StateMachine<WoodenBox>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�̕ύX
		@�����@�N���X�ɑΉ������X�e�[�g
		*/
		virtual void ChangeState(kaito::State<WoodenBox>* NewState);

		//--------------------------------------------------------------------------------------
		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/**
�@�@�@�@* �X�V
�@�@�@�@*/
		virtual void OnUpdate() override;
	};
}
