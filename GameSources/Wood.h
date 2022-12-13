/**
*@file Wood.h
*@brief �؂̎�������`����Ă���w�b�_�[�t�@�C��
*@author kanazawa yuuma
*@details �؂̎���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	class Wood : public GameObject {
	private:
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu
		float m_shadowbuilding; // !�e��t�����Ƃɂ���
		float m_Time; // !�؂�ւ��鎞��
		int m_oneday; // !���Ɩ�ɕω�����

		enum class Oneday {
			midday,
			night
		};

	public:
		/**
		* �R���X�g���N�^
		*/
		Wood(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~Wood() {}

		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
