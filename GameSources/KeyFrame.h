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

		KeyFrame(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~KeyFrame(){}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}

	};
}
//end basecross

