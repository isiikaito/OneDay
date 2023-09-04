/*!
@file BoneModelComponent.h
@author Kaito Isii
@brief  �{�[���t�����f���̎���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross
{

	struct BoneModelDeta
	{
		Vec3 scale;					//!�傫��
		Vec3 rotation;				//!��]
		Vec3 position;				//!�ʒu
		Vec3 modelScale;			//!���b�V���̑傫��
		Vec3 modelRotOrigin;		//!��]�̋N��
		Vec3 modelRotation;			//!���b�V���̉�]
		Vec3 modelPosition;			//!���b�V���̈ʒu
		wstring meshName;			//!���b�V���̖��O
		wstring tnaMeshName;		//!�^���W�F���g�t�����b�V���̖��O
		wstring nomalMapTex;		//!�@���}�b�v�e�N�X�`��
	
	};

	class BoneModelComponent :public Component
	{

		BoneModelDeta m_modelData;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g
		*/
		explicit BoneModelComponent(const shared_ptr<GameObject>& GameObjectPtr, BoneModelDeta& modelData) :
			Component(GameObjectPtr),
			m_modelData(modelData) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~BoneModelComponent() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V����
		*/
		virtual void OnUpdate()override{}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�`�揈���B�f�t�H���g�͉����s��Ȃ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}
