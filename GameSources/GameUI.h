/*!
@file GameUI.h
@author Kaito Isii
@brief �Q�[����ʂ�UI�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class GameUI : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartRotation;//!��]
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale,Vec3&Rotation, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�|���S���̐����ƃe�N�X�`���̌���
		*/
		void CreateGameUI( const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos);
	

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~GameUI();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�����x�̐ݒ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTrace(bool trace)
		{
			m_Trace = trace;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�傫���̐ݒ�
		*/
		//--------------------------------------------------------------------------------------
		void SetScale(Vec2 scale)
		{
			m_StartScale = scale;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �ʒu�̐ݒ�
		*/
		//--------------------------------------------------------------------------------------
		void SetPos(Vec3 pos)
		{
			m_StartPos = pos;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �e�N�X�`���l�[���̐ݒ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTexturekey(wstring texturekey)
		{
			m_TextureKey = texturekey;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		//--------------------------------------------------------------------------------------
		 void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�X�V
		*/
		//--------------------------------------------------------------------------------------
		 void OnUpdate();
	};



}
//end basecross