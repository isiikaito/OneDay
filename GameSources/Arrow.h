/*!
@file Arrow.h
@author Kaito Isii
@brief ���̕\��
*/

#pragma once
#include "stdafx.h"
#include "GameUI.h"
namespace basecross {


	class Arrow : public GameUI {
	private:
		bool m_Trace;         //!����
		Vec2 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureKey; //!�e�N�X�`��
		int m_RustLife;		  //!�Ō�̃��C�t
		Vec3 m_secondPosition;//!�x���x�Q�[�W�����x��2�̎�
		Vec3 m_firstPosition; //!�x���x�Q�[�W�����x��3�̎�

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		Arrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		virtual ~Arrow();

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@������
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�X�V
		*/
		virtual void OnUpdate()override;

	};



}
//end basecross
