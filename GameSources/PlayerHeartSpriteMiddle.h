/*!
@file PlayerHeartSprite.h
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/

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
		bool m_hurt;//!���C�t�̓_�ł��J�n���邩�ǂ���
		int m_MiddleLife;//!���݂�HP
		float m_tiem;//!�_�ł��Ă��鎞��
		int m_hurtCount;//!�_�ł�����
		bool m_hurtDefise;//!�n�[�g�̕\��������


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		PlayerHeartSpriteMiddle(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerHeartSpriteMiddle();

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
		virtual void OnUpdate()override;
	};
}
