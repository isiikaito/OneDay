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
			Vec3 Temp = Line;				//!�e�N�X�`���ƃJ�����Ԃ̃x�N�g��
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
		float m_LoseSeghtOfTime;		//!���Ă��鎞��
		const float m_spritePositionY;	//!�|�W�V����
		Vec3 m_scale;					//!�e�N�X�`���̑傫��
		

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		LoseSightOf(const std::shared_ptr<Stage>& stage, const std::shared_ptr<GameObject>& parent)
		: GameObject(stage), parent(parent), m_LoseSeghtOfTime(0.0f), m_spritePositionY(8.0f), m_scale(Vec3(5.0f)) {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~LoseSightOf(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���l���v���C���[������������
		*/
		void LoseSight();
	
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