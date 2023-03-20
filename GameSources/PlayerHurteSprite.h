/*!
@file PlayerHeartSpriteLeft.h
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/

#pragma once
#include "stdafx.h"
#include "GameUI.h"

namespace basecross {

	
	class PlayerHurteSprite : public GameUI {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;       //!�E�̃n�[�g
		float m_Time;         // !�؂�ւ��鎞��
		int m_hurtCount;      // !HP�̓_�ŉ�
		bool m_hurt;          // !�n�[�g�̂���Ȃ�
		bool m_hurtDefise;    //!�n�[�g������
		float m_dedTime;      //!�_�ł��Ă��鎞��
		bool m_GameOver;      //!�Q�[���I�[�o�[�������ǂ���
		int m_currentHp;


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		PlayerHurteSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos,int currentHp,bool hurtDefise);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerHurteSprite(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@���C�t�̃e�N�X�`���̕\����_�ł�����
		*/
		//--------------------------------------------------------------------------------------
		void FlashingHurteSprite(int currentHp);
			
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
//end basecross
