/*!
@file HeadManComment.h
@author Kaito Isii
@brief �����̕\��
*/

#pragma once
#include "stdafx.h"
namespace basecross
{
	enum class Day
	{
		FirstDay,
		SecondDay,
		ThirdDay,
		ForceDay,
		FiveDay,
		SixDay
	};

	class HeadManComment :public GameObject
	{
	private:
		std::shared_ptr<GameObject> parent; // �e�I�u�W�F�N�g

		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		const float m_spritePositionY;	//!�R�����g�̍���
		const Vec3 m_scale;				//!�傫��
		const Vec2 m_LeftUpperSummit;	//!����̒��_
		const Vec2 m_LeftLowerSummit;	//!�����̒��_
		const Vec2 m_RightUpperSummit;	//!�E��̒��_
		const Vec2 m_RightLowerSummit;	//!�E���̒��_
		Col4 m_TextureColor;			//!�e�N�X�`���̐F


	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		HeadManComment(const std::shared_ptr<Stage>& stage, 
			const std::shared_ptr<GameObject>& parent)
			: GameObject(stage), parent(parent), 
			m_spritePositionY(17.0f), 
			m_scale(Vec3(15.0f)),
			m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
			m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
			m_RightUpperSummit(Vec2(1.0f, 0.0f)),
			m_RightLowerSummit(Vec2(1.0f, 1.0f)),
			m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
		{}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~HeadManComment() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���l���v���C���[�������������̏���
		*/
		void Comment();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�r���{�[�h����
		*/
		void Billboard();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate() override;

	};
}