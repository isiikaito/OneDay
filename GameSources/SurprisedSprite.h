/*!
@file SurprisedSprite.h
@author Kaito Isii
@brief �r�b�N���}�[�N�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {




	class SurprisedSprite :public GameObject
	{
	private:
		std::shared_ptr<GameObject> parent; // �e�I�u�W�F�N�g
		float m_surprisedTime;
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
		Vec3 m_scale;

		float m_SurprisedTime;//!�|����\�����鎞��
		const float m_spritePositionY;//!�|����Y���̃|�W�V����
		bool m_IsFoundPlayer;//!�v���C���[�𔭌������Ƃ�
		

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		SurprisedSprite(const std::shared_ptr<Stage>& stage, const std::shared_ptr<GameObject>& parent)
			: GameObject(stage), parent(parent), m_SurprisedTime(0.0f), m_spritePositionY(8.0f) , m_IsFoundPlayer(false), m_surprisedTime(0.0f), m_scale(Vec3(5.0f, 5.0f, 5.0f)) {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~SurprisedSprite() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���l������������
		*/
		void Surprised();

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
		/*
		@brief�@�X�V
		*/
		virtual void OnUpdate() override;

	};



}
//end basecross