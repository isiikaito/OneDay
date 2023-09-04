/*!
@file HeadMan.h
@brief �����̍쐬
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
namespace basecross
{
	//--------------------------------------------------------
	//!����
	//--------------------------------------------------------
	class HeadMan :public GameObject
	{
	private:
		bool m_IsheadManCommentOn;				//!�������b���Ă��邩�ǂ���
		BoneModelDeta m_headManBoneModelDeta;	//!�v���C���[�̃��f���f�[�^

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�������R�����g��\�����鏈��
		*/
		void HeadManComment();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����̃A�j���[�V�����X�V
		*/
		void HeadManAnimation();


	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		HeadMan(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~HeadMan() {}

		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�������R�����g���Ă��邩�ǂ����̎擾
		@return �������R�����g���Ă��邩�ǂ���
		*/
		bool GetHeadManComment() const
		{
			return m_IsheadManCommentOn;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate();
	};
}
