/*!
@file StaticModelComponent.cpp
@brief �X�^�e�B�b�N���f���̎���
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "StaticModelComponent.h"
namespace basecross
{
	void StaticModelComponent::OnCreate()
	{
		auto ptrTransform = GetGameObject()->GetComponent<Transform>();
		ptrTransform->SetScale(m_modelData.scale);			//!�傫��
		ptrTransform->SetRotation(m_modelData.rotation);	//!��]
		ptrTransform->SetPosition(m_modelData.position);	//!�ʒu

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(m_modelData.modelScale),
			Vec3(m_modelData.modelRotOrigin),
			Vec3(m_modelData.modelRotation),
			Vec3(m_modelData.modelPosition)
		);

		auto ptrColl = GetGameObject()->AddComponent<CollisionObb>();				//!CollisionObb�Փ˔����t����						
		auto shadowPtr = GetGameObject()->AddComponent<Shadowmap>();				//!�e������i�V���h�E�}�b�v��`�悷��j
		shadowPtr->SetMeshResource(m_modelData.meshName);							//!�e�̌`�i���b�V���j��ݒ�								
		shadowPtr->SetMeshToTransformMatrix(spanMat);								//!���b�V���̑傳�ݒ�
		auto ptrDraw = GetGameObject()->AddComponent<PNTStaticModelDraw>();			//!�`��R���|�[�l���g�̐ݒ�								
		ptrColl->SetFixed(true);													//!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
		ptrDraw->SetMeshResource(m_modelData.meshName);								//!���b�V���̐ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);
	}
}
