/*!
@file AlertlevelGauge.h
@author Kaito Isii
@brief �x���x�̃P�[�W�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class AlertlevelGauge : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;


	public:

		AlertlevelGauge(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//!�j��
		virtual ~AlertlevelGauge();
		//!������
		virtual void OnCreate() override;
	
	};



}
//end basecross

