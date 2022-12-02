/*!
@file Key.cpp
@brief �J�M�Ɋւ��鏈��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Key::Key(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
		
	{
	}

	void Key::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.1f, 0.5f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.6f, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, 0.0f) //!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		                           

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"KEY_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"KEY_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		Coll->SetDrawActive(false);
		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		auto group = GetStage()->GetSharedObjectGroup(L"key_ObjGroup");

		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Key>());
	
	}
	
}
//end basecross