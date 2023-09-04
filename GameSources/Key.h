/*!
@file Key.h
@brief �J�M�Ɋւ��鏈��
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Key : public GameObject {
	private:
		float m_RotationSpeed;	//!��]���鑬�x 
		StaticModelDeta m_keyModelData;			//!�J�M�̃��f���f�[�^

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		Key(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~Key() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	����������
		*/
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V����
		*/
		virtual void OnUpdate()override;

		
	};
}

//end basecross
