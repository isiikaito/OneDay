/*!
@file FadeOut.h
@brief �t�F�[�h�A�E�g
@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�Q�[�W
	class FadeOut : public GameObject
	{
		bool m_Trace;			//����
		Vec2 m_StartScale;		//�傫��
		Vec3 m_StartPos;		//�ʒu
		float m_TotalTime;		//���Ԃ̎擾
		Col4 m_TextureColor;	//!�e�N�X�`���̐F


		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor>m_BackupVertices;


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~FadeOut();

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
