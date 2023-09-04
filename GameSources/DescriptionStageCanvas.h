/*!
@file DescriptionStageCanvas.h
@author Kaito Isii
@brief �������X�e�[�W�Ŏg��UI�̐����Ǘ�
*/

#pragma once
#include "stdafx.h"
#include "DescriptionSpriteFront.h"

namespace basecross {


	class DescriptionStageCanvas : public GameObject {
	private:

		std::vector<shared_ptr<DescriptionSpriteFront>> m_DescriptionSprites;//!�������̃f�[�^����ꂽ�z��

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�\�̐������̃X�v���C�g�̍쐬
		*/
		void CreateDescriptionSpriteFront();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		DescriptionStageCanvas(const shared_ptr<Stage>& StagePtr);


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~DescriptionStageCanvas() {}

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�������̎擾
		*/
		std::vector<shared_ptr<DescriptionSpriteFront>>GetDescriptionSprites() const
		{
			return m_DescriptionSprites;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		void OnUpdate();


	};



}
//end basecross


