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
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		float m_LoseSeghtOfTime;
		const float m_spritePositionY;


	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		HeadManComment(const std::shared_ptr<Stage>& stage, const std::shared_ptr<GameObject>& parent)
			: GameObject(stage), parent(parent), m_LoseSeghtOfTime(0.0f), m_spritePositionY(17.0f) {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~HeadManComment() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���l���v���C���[�������������̏���
		*/
		void Comment();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�r���{�[�h����
		*/
		void Billboard();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�X�V
		*/
		virtual void OnUpdate() override;

	};
}