/**
*@file StageFloor.h
*@brief �Q�[���X�e�[�W�̏��̎�������`����Ă���w�b�_�[�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̏��̎���
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross {
	class StageFloor : public GameObject {
	private:
		StaticModelDeta m_stageFloorModelData;			//!���̃��f���f�[�^

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
		virtual void OnUpdate() override;
	};
}