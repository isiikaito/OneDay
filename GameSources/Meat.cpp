/*!
@file Meat.cpp
@brief ���̎���
@author Kaito Isii
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
		m_Time(0.0f)

	{
	}

	void Meat::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu


		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.15f),	//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),		//!��]
			Vec3(0.0f, -0.5f, 0.0f)		//!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();						//!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();				//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();						//!�L���[�u�^�̓����蔻��̒ǉ�
		ptrShadow->SetMeshResource(L"MEAT_MESH");						//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);					//!���b�V���̑傫���ݒ�
		ptrDraw->SetMeshResource(L"MEAT_MESH");							//!���b�V���̐ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);						//!���b�V���̑傫���ݒ�
		auto group = GetStage()->GetSharedObjectGroup(L"Meat_ObjGroup");//!���g�̃O���[�v���쐬
		group->IntoGroup(GetThis<Meat>());								//�O���[�v�Ɏ������g��ǉ�

	}
	void Meat::OnUpdate()
	{
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();	//!�`��R���|�[�l���g
		auto ptrTrans = GetComponent<Transform>();			//!���g�̃g�����X�t�H�[���̎擾
		auto& app = App::GetApp();							//!�A�v���̎擾
		auto time = app->GetElapsedTime();					//!�G���p�\�^�C���̎擾
		m_Time += time;										//!y����]�ɃG���p�\�^�C�������Z����
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.15f),						//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, m_Time, 0.0f),						//!��]
			Vec3(0.0f, -0.5f, 0.0f)							//!�ʒu
		);
		ptrDraw->SetMeshToTransformMatrix(spanMat);			//!���b�V���̑傫���ݒ�


	}
}
//end basecross