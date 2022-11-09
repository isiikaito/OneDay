/*!
@file Key.h
@brief �J�M�Ɋւ��鏈��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Key : public GameObject {
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu

	public:
		/**
		* �R���X�g���N�^
		*/
		Key(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~Key() {}

		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;
	

		
	};
}

//end basecross
