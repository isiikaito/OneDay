/*!
@file LoseSightOf.h
@author Kaito Isii
@brief �G�̃v���C���[�����������Ƃ��̂͂Ăȃ}�[�N�̕\��
*/

#pragma once
#include "stdafx.h"
namespace basecross
{
	
	class LoseSightOf :public GameObject
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
		//!�\�z�Ɣj��
		LoseSightOf(const std::shared_ptr<Stage>& stage, const std::shared_ptr<GameObject>& parent)
		: GameObject(stage), parent(parent), m_LoseSeghtOfTime(0.0f), m_spritePositionY(8.0f) {}
		virtual ~LoseSightOf(){}
		//!���l������������
		void LoseSight();
	
		//!�r���{�[�h����
		void Billboard();
		//!������
		virtual void OnCreate() override;
		//!�X�V
		virtual void OnUpdate() override;

	};
}