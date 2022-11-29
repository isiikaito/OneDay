#pragma once
#include "stdafx.h"

namespace basecross 
{

	class PlayerHeartSpriteRight : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RightLife;

	public:

		PlayerHeartSpriteRight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~PlayerHeartSpriteRight();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;
	};


}

