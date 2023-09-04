/*!
@file BoneModelComponent.cpp
@brief �{�[���t�����f���̎���
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "BoneModelComponent.h"
namespace basecross
{
	void BoneModelComponent::OnCreate()
	{
		auto ptrTransform = GetGameObject()->GetComponent<Transform>();
		ptrTransform->SetScale(m_modelData.scale);		//!�傫��
		ptrTransform->SetRotation(m_modelData.rotation);	//!��]
		ptrTransform->SetPosition(m_modelData.position);	//!�ʒu
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(m_modelData.modelScale),
			Vec3(m_modelData.modelRotOrigin),
			Vec3(m_modelData.modelRotation),
			Vec3(m_modelData.modelPosition)
		);
		
		auto ptrColl = GetGameObject()->AddComponent<CollisionCapsule>();								//!CollisionSphere�Փ˔����t����						
		auto ptrGra = GetGameObject()->AddComponent<Gravity>();											//!�d�͂�����											
		auto shadowPtr = GetGameObject()->AddComponent<Shadowmap>();									//!�e������i�V���h�E�}�b�v��`�悷��j
		shadowPtr->SetMeshResource(m_modelData.meshName);												//!�e�̌`�i���b�V���j��ݒ�								
		shadowPtr->SetMeshToTransformMatrix(spanMat);													//!���b�V���̑傫���ݒ�
		auto ptrDraw = GetGameObject()->AddComponent<BcPNTnTBoneModelDraw>();							//!�`��R���|�[�l���g�̐ݒ�								
		ptrDraw->SetMeshResource(m_modelData.tnaMeshName);												//!�`�悷�郁�b�V����ݒ�								
		ptrDraw->SetMeshToTransformMatrix(spanMat);														//!���b�V���̑傫���ݒ�
		ptrDraw->SetNormalMapTextureResource(m_modelData.nomalMapTex);									//!�@���}�b�v�̐ݒ�

	}
}
