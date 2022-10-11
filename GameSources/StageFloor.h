/**
*@file StageFloor.h
*@brief �Q�[���X�e�[�W�̏��̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details �Q�[���X�e�[�W�̏��̎���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	class StageFloor : public GameObject {
		Vec3 m_Scale;   //!�傫��11111
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu

	public:
		/**
		* �R���X�g���N�^
		*/
		StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~StageFloor() {}

		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;
	};
}