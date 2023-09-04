/*!
@file TitleStageCanvas.h
@author Kaito Isii
@brief �^�C�g���X�e�[�W�Ŏg��UI�̐����Ǘ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class TitleStageCanvas : public GameObject {

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�^�C�g����ʂ̃X�v���C�g�̍쐬
		*/
		void CreateTitleSprite();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		TitleStageCanvas(const shared_ptr<Stage>& StagePtr);

		
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~TitleStageCanvas() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		void OnUpdate(){}
	};



}
//end basecross

