/*!
@file Arrow.h
@author Kaito Isii
@brief ���̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class Arrow : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;
		float m_rotationZ;//!��]��z����ς���

	public:

		Arrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale,const float& RotationZ,  const Vec2& StartPos);
		//!�j��
		virtual ~Arrow();
		//!������
		virtual void OnCreate() override;
		//!�X�V
		virtual void OnUpdate()override;

	};



}
//end basecross
