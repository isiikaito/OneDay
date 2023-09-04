/**
*@file StageGate.h
*@brief �Q�[���X�e�[�W�̖�̎�������`����Ă���w�b�_�[�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̖�̎���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	class StageGate : public GameObject {
	private:
		Vec3 m_Scale;				//!�傫��
		Vec3 m_Rotation;			//!��]
		Vec3 m_Position;			//!�ʒu
		Vec3 modelScale;			//!���b�V���̑傫��
		Vec3 modelRotOrigin;		//!��]�̋N��
		Vec3 modelRotation;			//!���b�V���̉�]
		Vec3 modelPosition;			//!���b�V���̈ʒu


	public:
		/**
		* �R���X�g���N�^
		*/
		StageGate(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~StageGate() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �A�j���[�V�����̐؂�ւ�
		*/
		//--------------------------------------------------------------------------------------
		void AnimationChange();
		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}