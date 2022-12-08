/*!
@file PlayerHeartSpriteLeft.h
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	
	class PlayerHeartSpriteLeft : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;
		float m_Time; // !�؂�ւ��鎞��
		int m_hurtCount; // !HP�̓_�ŉ�
		bool m_hurt; // !�n�[�g�̂���Ȃ�
		bool m_hurtDefise;
		float m_dedTime;
		bool m_GameOver;


	public:

		PlayerHeartSpriteLeft(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~PlayerHeartSpriteLeft();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;
	};

	
	
}
//end basecross
