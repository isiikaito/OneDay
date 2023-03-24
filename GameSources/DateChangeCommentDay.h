/*!
@file DateChangeCommentDay.h
@author Kaito Isii
@brief �������ɕς�鎞�̃R�����g�̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class DateChangeCommentDay : public GameUI {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;
		float m_textureW;//!�e�N�X�`���A���t�@�l
		float m_totalTime;//!�t�F�[�h�A�E�g�C���̎���
		bool m_IstexturemaxW;//!�A���t�@�l���ő�̎�
		//�o�b�N�A�b�v���_�f�[�^
		shared_ptr<PCTSpriteDraw> m_drawComponent;//!�`�揈��
		vector<VertexPositionColor>m_BackupVertices;



	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		DateChangeCommentDay(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~DateChangeCommentDay() {}

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
		virtual void OnUpdate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�t�F�[�h�C��
		*/
		//--------------------------------------------------------------------------------------
		void TextureFadeIn();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�t�F�[�h�A�E�g
		*/
		//--------------------------------------------------------------------------------------
		void TextureFadeOut();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�t�F�[�h�C���̊J�n���邩�ǂ����̎擾
		*/
		//--------------------------------------------------------------------------------------
		bool GetIstexturemaxW()
		{
			return m_IstexturemaxW;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�t�F�[�h�C���̊J�n���邩�ǂ����̐ݒ�
		*/
		//--------------------------------------------------------------------------------------
		void SetIstexturemaxW(bool IstexturemaxW)
		{
			m_IstexturemaxW = IstexturemaxW;
		}
	};



}
//end basecross

