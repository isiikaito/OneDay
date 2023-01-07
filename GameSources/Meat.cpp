/*!
@file Meat.cpp
@brief ���̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "Meat.h"


namespace basecross {
	Meat::Meat(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Time(0.0f),
		m_MeatNamber(0)

	{
	}

	void Meat::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.15f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, 0.0f)  //!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�


		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"MEAT_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"MEAT_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetDiffuse(Col4(1.0, 0.2, 0.0, 1.0));
		Coll->SetDrawActive(false);
		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		auto group = GetStage()->GetSharedObjectGroup(L"Meat_ObjGroup");

		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Meat>());

	}
	void Meat::OnUpdate()
	{
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto ptrTrans = GetComponent<Transform>();
		auto& app = App::GetApp();//!�A�v���̎擾
		auto time = app->GetElapsedTime();
		m_Time += time;
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.15f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, m_Time, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, 0.0f)  //!�ʒu
		);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


	}
}
//end basecross