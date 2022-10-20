/*!
@file Hunter.h
@brief �n���^�[�̍쐬
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	
	//--------------------------------------------------------
	//!�n���^�[
	//--------------------------------------------------------
	class Enemy :public GameObject
	{

		//�X�e�[�g�}�V�[��(��Ԃ�\��)
		unique_ptr< StateMachine<Enemy> >  m_StateMachine;
		Vec3  m_StartPos;//!�X�^�[�g�|�W�V����
		Vec3 m_Force;//!�����̗�
		Vec3 m_Velocity;//!���x
		float m_StateChangeSize;
		void ApplyForce();//!�K����
		Vec3 PEvector;



	protected:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Enemy();
	public:

		//�A�N�Z�T
		const unique_ptr<StateMachine<Enemy>>& GetStateMachine() {
			return m_StateMachine;
		}

		//!�X�^�[�g�|�W�V�������擾����
		Vec3 GetStartPos() const {
			return m_StartPos;
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
		virtual void NearBehavior() = 0;//!�X�e�[�g���v���C���[����߂��ʒu�ɂ���Ƃ��ɖ��^�[���Ă΂��
		virtual void FarBehavior() = 0;//!�X�e�[�g���v���C���[���牓���ʒu�ɂ���Ƃ��ɖ��^�[���Ă΂��
		virtual void OnCreate();//������
		virtual void OnUpdate();//!�X�V

	};

	//--------------------------------------------------------------------------------------
	//	�v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class FarState : public ObjState<Enemy>
	{
		FarState() {}
	public:
		static shared_ptr<FarState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;//!�����ɓ���
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;//!���������s����
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;//!�������o��
	};

	//--------------------------------------------------------------------------------------
	//	 �v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class NearState : public ObjState<Enemy>
	{
		NearState() {}
	public:
		static shared_ptr<NearState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;
	};


	//--------------------------------------------------------------------------------------
	//!�p�X�����񂷂�z�u�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class Hunter : public Enemy {
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Hunter(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Hunter();

		virtual void OnCreate() override;//!������
		//����
		virtual void NearBehavior() override;//!�X�e�[�g���߂���
		virtual void FarBehavior() override;//!�X�e�[�g��������
	};

}
//!end basecross
