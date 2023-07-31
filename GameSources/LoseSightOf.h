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
		std::shared_ptr<GameObject> parent;		//!�e�I�u�W�F�N�g
		float m_LoseSeghtOfTime;				//!���Ă��鎞��
		const float m_spritePositionY;			//!�|�W�V����
		Vec3 m_scale;							//!�e�N�X�`���̑傫��
		const Vec2 m_LeftUpperSummit;			//!����̒��_
		const Vec2 m_LeftLowerSummit;			//!�����̒��_
		const Vec2 m_RightUpperSummit;			//!�E��̒��_
		const Vec2 m_RightLowerSummit;			//!�E���̒��_
		Col4 m_TextureColor;					//!�e�N�X�`���̐F
		float m_tempLength;						//!�Վ��̒���
		Vec3 m_defUp;							//!�ʏ�


		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;				//!�e�N�X�`���ƃJ�����Ԃ̃x�N�g��
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < m_tempLength) {
				DefUp = m_defUp;
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
		

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		LoseSightOf(const std::shared_ptr<Stage>& stage,
			const std::shared_ptr<GameObject>& parent)
		: GameObject(stage), parent(parent),
			m_LoseSeghtOfTime(0.0f), 
			m_spritePositionY(8.0f), 
			m_scale(Vec3(5.0f)),
			m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
			m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
			m_RightUpperSummit(Vec2(1.0f, 0.0f)),
			m_RightLowerSummit(Vec2(1.0f, 1.0f)),
			m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
			m_tempLength(0.1f),
			m_defUp(Vec3(0, 0, 1.0f))

		{}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~LoseSightOf(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���l���v���C���[������������
		*/
		void LoseSight();
	
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