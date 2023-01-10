/*!
@file DateChangeCommentNight.h
@author Kaito Isii
@brief �������ɕς�鎞�̃R�����g�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class DateChangeCommentNight : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;

	public:

		DateChangeCommentNight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//!�j��
		virtual ~DateChangeCommentNight() {}
		//!������
		virtual void OnCreate() override;


	};



}
//end basecross
