/*!
@file ClearStageCanvas.h
@author Kaito Isii
@brief �N���A�X�e�[�W�Ŏg��UI�̐����Ǘ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	class ClearStageCanvas : public GameObject {
	private:

		float m_clearTime;//!�N���A�X�e�[�W�̎���
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		ClearStageCanvas(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�N���A�X�v���C�g
		*/
		void CreateGameClearSprite();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~ClearStageCanvas() {}

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

