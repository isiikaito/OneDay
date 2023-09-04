/**
*@file StageBuilding.h
*@brief �Q�[���X�e�[�W�̌����̎�������`����Ă���w�b�_�[�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̌����̎���
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {




	class StageBuilding : public GameObject {
	private:
		float m_Time;									//!�؂�ւ��鎞��
		int m_oneday;									//!���Ɩ�ɕω�����
		StaticModelDeta m_buildingModelData;			//!�Ƃ̃��f���f�[�^
		std::weak_ptr<PNTStaticModelDraw> m_ptrDrow;	//!�`�揈��

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