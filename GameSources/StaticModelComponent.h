/*!
@file StaticModelComponent.h
@author Kaito Isii
@brief  �X�^�e�B�b�N���f���̍쐬
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross
{

	struct StaticModelDeta
	{
		Vec3 scale;					//!�傫��
		Vec3 rotation;				//!��]
		Vec3 position;				//!�ʒu
		Vec3 modelScale;			//!���b�V���̑傫��
		Vec3 modelRotOrigin;		//!��]�̋N��
		Vec3 modelRotation;			//!���b�V���̉�]
		Vec3 modelPosition;			//!���b�V���̈ʒu
		wstring meshName;			//!���b�V���̖��O

	};

	class StaticModelComponent :public Component
	{

		StaticModelDeta m_modelData;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g
		*/
		explicit StaticModelComponent(const shared_ptr<GameObject>& GameObjectPtr, StaticModelDeta& modelData) :
			Component(GameObjectPtr),
			m_modelData(modelData) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~StaticModelComponent() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V����
		*/
		virtual void OnUpdate()override {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�`�揈���B�f�t�H���g�͉����s��Ȃ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}
