/*!
@file DescriptionSprite.h
@author Kaito Isii
@brief �������̕\��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	namespace kaito
	{
		//!�O���錾
		template<class entity_type>
		class State;
		//!�O���錾
		template <class entity_type>
		class StateMachine;
	}

	
	class DescriptionSpriteFront : public GameObject {
	private:
		bool m_Trace;         //!����
		Vec3 m_StartScale;    //!�傫��
		Vec3 m_StartPos;      //!�ʒu
		wstring m_TextureClock; //!�e�N�X�`��
		bool m_moveTexture;//!�e�N�X�`���̈ړ����邩�ǂ���
		bool m_pageBackTo;//!�y�[�W��߂�����
		//!�X�e�[�g�}�V�[��
		kaito::StateMachine<DescriptionSpriteFront>* m_StateMachine;//!�X�e�[�g�}�V���N���X�̃C���X�^���X�̐���

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		DescriptionSpriteFront(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec3& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�g�}�V�[���̃A�N�Z�b�T
		*/
		//--------------------------------------------------------------------------------------
		const kaito::StateMachine<DescriptionSpriteFront>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~DescriptionSpriteFront();

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
		@brief�@�e�N�X�`���𓮂������ǂ���
		*/
		//--------------------------------------------------------------------------------------
		bool GetMoveTexture()
		{
			return m_moveTexture;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�e�N�X�`���𓮂������ݒ肷��
		*/
		//--------------------------------------------------------------------------------------
		void SetMoveTexture(bool moveTexture)
		{
			m_moveTexture = moveTexture;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�y�[�W��߂����ǂ����̎擾
		*/
		//--------------------------------------------------------------------------------------
		bool GetPageBackTo()
		{
			return m_pageBackTo;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�y�[�W��߂����ǂ����̎擾
		*/
		//--------------------------------------------------------------------------------------
		void SetPageBackTo(bool pageBackTo)
		{
			m_pageBackTo = pageBackTo;
		}

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�g�̕ύX
		*/
		//--------------------------------------------------------------------------------------
		virtual void ChangeState(kaito::State<DescriptionSpriteFront>* NewState);

	};
}
//end basecross
