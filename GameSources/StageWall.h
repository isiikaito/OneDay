/**
*@file StageWall.h
*@brief �Q�[���X�e�[�W�̕ǂ̎�������`����Ă���w�b�_�[�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̕ǂ̎���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	class StageWall : public GameObject {
	private:
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu
		float m_shadowbuilding; // !�e��t�����Ƃɂ���
		float m_Time; // !�؂�ւ��鎞��
		float m_Color; // !�F��ς���
		int m_oneday; // !���Ɩ�ɕω�����

		enum class Oneday {
			midday,
			night
		};

	public:
		/**
		* �R���X�g���N�^
		*/
		StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~StageWall() {}

		/**
		* �Q�[���X�e�[�W�̏��̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}