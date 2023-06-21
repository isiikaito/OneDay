/*!
@file HungerGage.h
@author isii kaito
@brief �Q�[�W�̔w�i�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

		enum class EatCondition {
		notEat,
		firstEat,
		secondEat,
		thirdEat
	};
	class HungerGage : public GameUI {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		Vec3 m_firstEatScale; //!�Q�[�W������܂����Ƃ�
		Vec3 m_firstEatPos;   //!�Q�[�W������܂����Ƃ�
		Vec3 m_secondEatScale;//!�Q�[�W������܂����Ƃ�
		Vec3 m_secondEatPos;  //!�Q�[�W������܂����Ƃ�
		Vec3 m_thirdEatScale; //!���^���̎�
		Vec3 m_thirdEatPos;   //!���^���̎�


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		HungerGage(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~HungerGage() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Q�[�W�̕ύX
		*/
		void ChangeGage();

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

