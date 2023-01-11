/*!
@file KeyFrame.h
@author isii kaito
@brief �J�M�̘g�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class KeyFrame : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureClock; //!�e�N�X�`��


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		KeyFrame(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~KeyFrame(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�X�V
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}

	};
}
//end basecross

