/**
*@file Wood.h
*@brief �؂̎�������`����Ă���w�b�_�[�t�@�C��
*@author kanazawa yuuma
*@details �؂̎���
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	

	class Wood : public GameObject {
	private:
		StaticModelDeta m_woodModelData;//!�Ƃ̃��f���f�[�^

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
