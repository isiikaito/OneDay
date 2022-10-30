/*!
@file Hunter.h
@brief �n���^�[�̍쐬
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------
	//!�n���^�[
	//--------------------------------------------------------
	class Hunter :public GameObject
	{

		//�X�e�[�g�}�V�[��(��Ԃ�\��)
		unique_ptr< StateMachine<Hunter> >  m_StateMachine;
		Vec3  m_Position;//!�ʒu
		Vec3 m_Rotation;//!��]
		Vec3 m_Scale;//!�傫��
		Vec3 m_Force;//!�����̗�
		Vec3 m_Velocity;//!���x
		float m_StateChangeSize;
		void ApplyForce();//!�K����
		Vec3 PEvector;//!�v���C���[�ƓG�̃x�N�g��
		std::vector<Vec3> m_patrolPoints;//!����|�C���g


	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Hunter(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const std::vector<Vec3>& patrolPoints
		);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Hunter();
	public:

		//�A�N�Z�T
		const unique_ptr<StateMachine<Hunter>>& GetStateMachine() {
			return m_StateMachine;
		}

	

		//!�X�e�[�g�`�F���W�T�C�Y
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		//!�s���̗͂̎擾
		const Vec3& GetForce()const {
			return m_Force;
		}

		//!�s���̗͂̐ݒ�
		void SetForce(const Vec3& f) {
			m_Force = f;
		}

		//!�s���̗͂̔z�u
		void AddForce(const Vec3& f) {
			m_Force += f;
		}

		//!���x�̎擾
		const Vec3& GetVelocity()const {
			return m_Velocity;
		}

		//!���x�̐ݒ�
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}

		shared_ptr<GameObject>  GetTarget()const;//!�^�[�Q�b�g�̎擾
		virtual void NearBehavior();//!�X�e�[�g���v���C���[����߂��ʒu�ɂ���Ƃ��ɖ��^�[���Ă΂��
		virtual void FarBehavior();//!�X�e�[�g���v���C���[���牓���ʒu�ɂ���Ƃ��ɖ��^�[���Ă΂��
		virtual void OnCreate();//������
		virtual void OnUpdate();//!�X�V

	};

	//--------------------------------------------------------------------------------------
	//	�v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class FarState : public ObjState<Hunter>
	{
		FarState() {}
	public:
		static shared_ptr<FarState> Instance();
		virtual void Enter(const shared_ptr<Hunter>& Obj)override;//!�����ɓ���
		virtual void Execute(const shared_ptr<Hunter>& Obj)override;//!���������s����
		virtual void Exit(const shared_ptr<Hunter>& Obj)override;//!�������o��
	};

	//--------------------------------------------------------------------------------------
	//	 �v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class NearState : public ObjState<Hunter>
	{
		NearState() {}
	public:
		static shared_ptr<NearState> Instance();
		virtual void Enter(const shared_ptr<Hunter>& Obj)override;
		virtual void Execute(const shared_ptr<Hunter>& Obj)override;
		virtual void Exit(const shared_ptr<Hunter>& Obj)override;
	};



}
//!end basecross
