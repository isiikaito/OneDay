/*!
@file MeatGageBackGround.h
@author isii kaito
@brief �Q�[�W�̔w�i�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MeatGageBackGround : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureClock; //!�e�N�X�`��


	public:

		MeatGageBackGround(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~MeatGageBackGround() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}

	};
}
//end basecross

