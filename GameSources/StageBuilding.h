/**
*@file StageBuilding.h
*@brief �Q�[���X�e�[�W�̌����̎�������`����Ă���w�b�_�[�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̌����̎���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	class StageBuilding : public GameObject {
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu

	public:
		/**
		* �R���X�g���N�^
		*/
		StageBuilding(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~StageBuilding() {}

		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;
	};
}