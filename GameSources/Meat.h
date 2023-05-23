/*!
@file Meat.h
@brief ���̍쐬
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Meat : public GameObject {
	private:
		Vec3 m_Scale;    //!�傫��
		Vec3 m_Rotation; //!��]
		Vec3 m_Position; //!�ʒu
		float m_Time;	 //!y����]
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		Meat(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~Meat() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate()override;


	};
}

//end basecross
