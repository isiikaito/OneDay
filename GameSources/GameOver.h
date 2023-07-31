/*!
@file GameOver.h
@brief �Q�[���I�[�o�[
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"
#include "GameUI.h"
namespace basecross {
//--------------------------------------------------------------------------------------
///	�Q�[���I�[�o�[�X�v���C�g
//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameUI {
	private:
		bool m_Trace;			//!�\�����邩�ǂ���
		Vec2 m_StartScale;		//�X�^�[�g�̑傫��
		Vec3 m_StartPos;		//�X�^�[�g�ʒu
		wstring m_TextureKey;	//!�g�p�e�N�X�`���̖��O

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		GameOverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~GameOverSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate()override;
	};
}
//end basecross
