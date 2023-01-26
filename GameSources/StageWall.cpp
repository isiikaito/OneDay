/**
*@file StageWall.cpp
*@brief �Q�[���X�e�[�W�̕ǂ̎�������`����Ă���\�[�X�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̕ǂ̎��̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"

namespace basecross {

	constexpr float m_colLimit = 0.2;
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	StageWall::StageWall(const shared_ptr<Stage>& StagePtr,
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

	//������
	void StageWall::OnCreate() {
		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.8f, 0.14f, 0.045f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(-0.35f, -0.7f, 0.05f)  //!�ʒu
		);
		
		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);                             //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
		auto group = GetStage()->GetSharedObjectGroup(L"StageWall_Group");//!�O���[�v���擾
		group->IntoGroup(GetThis<StageWall>());//!�O���[�v�ɃX�e�[�W�̕ǂ�����

			
		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGE_FENCE");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"STAGE_FENCE");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		/*Coll->SetDrawActive(true);*/
		//!RigidbodyBox�̒ǉ�
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		
		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p
		//ptrDraw->SetEmissive(Col4(0.0f, 0.0f, 0.0f, 1.0f)); // !�Â����鏈��

	}

	void StageWall::OnUpdate() {

		
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - m_colLimit, m_time - m_colLimit, m_time - m_colLimit, 1.0f)); // !��ɂ��鏈��
	}

}