#pragma once

#include "stdafx.h"

namespace basecross 
{
	class PlayerHeartSpriteMiddle : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_MiddleLife;


	public:

		PlayerHeartSpriteMiddle(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~PlayerHeartSpriteMiddle();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;
	};
}
