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
	///	�J�M�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class KeySprite : public GameUI {
	private:
		bool m_Trace;			//!�����x
		Vec2 m_StartScale;		//!�ŏ��̑傫��
		Vec3 m_StartPos;		//!�ŏ��̈ʒu
		wstring m_TextureKey;	//!�e�N�X�`���̖��O
		int m_keyCount;			//!�J�M�̐�

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		KeySprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos,int keyCount);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~KeySprite(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���ݎ����Ă���J�M�̐��ɉ����ăJ�M�̃e�N�X�`���̕\��
		*/
		void CurrentKeySpriteDisplay(int keyCount);

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

