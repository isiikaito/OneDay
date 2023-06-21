/**
*@file Time.h
*@brief ���Ԍo�߂�\������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details �X�e�[�W�J�n������S�[���܂łɂ����������Ԃ̕\��
*/

#pragma once
#include "stdafx.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class Timer : public GameObject {
	private:
		bool m_Trace;				//!����
		Vec2 m_StartScale;			//!�傫��
		Vec3 m_StartPos;			//!�ʒu
		wstring m_TextureKey;		//!�e�N�X�`��
		float m_Score;				//!����
		UINT m_NumberOfDigits;		//!����
		Vec2 m_LeftUpperSummit;		//!����̒��_
		Vec2 m_LeftLowerSummit;		//!�����̒��_
		Vec2 m_RightUpperSummit;	//!�E��̒��_
		Vec2 m_RightLowerSummit;	//!�E���̒��_


		vector<VertexPositionTexture> m_BackupVertices;//!�o�b�N�A�b�v���_�f�[�^

		
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~Timer() {}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�o�߂������Ԃ��X�V
		@param	���݂̎���
		*/
		void SetScore(float f) {
			m_Score = f;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����Ƃ̐����̎擾
		@param[out] verNum ���Ԗڂ̒��_���𔻕ʂ���
		@param[in] num ���̒��̐������擾����
		@param[out] newVertices �ʒu�ƃe�N�X�`���������_�̒�`
		*/
		void SetUVPos(int& verNum, UINT num, vector<VertexPositionTexture>& newVertices);


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����̃e�N�X�`���̏�����������֐�
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����̃e�N�X�`���̍X�V������֐�
		*/
		virtual void OnUpdate();

	};
}
//end basecross