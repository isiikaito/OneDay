/*!
@file Title.h
@brief �^�C�g�����
*/

#pragma once
#include "stdafx.h"

namespace basecross {

//--------------------------------------------------------------------------------------
///	�^�C�g���X�v���C�g
//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		
		TitleSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~TitleSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
//end basecross

