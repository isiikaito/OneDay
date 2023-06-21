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
	private:
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu
		float m_Time; // !�؂�ւ��鎞��
		int m_oneday; // !���Ɩ�ɕω�����

		enum class Oneday {
			midday,
			night
		};

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g
		*/
		StageBuilding(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~StageBuilding() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Q�[���X�e�[�W�̏��̏�����
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Q�[���X�e�[�W�̏��̍X�V
		*/
		virtual void OnUpdate() override;
	};
}