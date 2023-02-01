/**
*@file StageGate.cpp
*@brief �Q�[���X�e�[�W�̖�̎�������`����Ă���\�[�X�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̖�̎��̎���
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
	StageGate::StageGate(const shared_ptr<Stage>& StagePtr,
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
	void StageGate::OnCreate() {
		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.3f, 0.1f, 0.09f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(-0.1f, -0.5f, 0.0f)  //!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g
		//auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		//Coll->SetDrawActive(true);
		//Coll->SetFixed(true);                             //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j

		////!�e�̌`�i���b�V���j��ݒ�
		//ptrShadow->SetMeshResource(L"STAGEGATE_MESH");
		//ptrShadow->SetMeshToTransformMatrix(spanMat);

		////!���b�V���̐ݒ�
		//ptrDraw->SetMeshResource(L"STAGEGATE_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//Coll->SetDrawActive(true);
		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		
		ptrShadow->SetMeshResource(L"GateAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"GateAnimation_MESH_WITH_TAN");
		ptrDraw->AddAnimation(L"Open", 0, 60, true, 20.0f);
		ptrDraw->ChangeCurrentAnimation(L"Open");


	}

	void StageGate::OnUpdate() {
		auto AnimaptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//!�A�j���[�V����
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();

		AnimaptrDraw->SetEmissive(Col4(m_time - m_colLimit, m_time - m_colLimit, m_time - m_colLimit, 1.0f)); // !��ɂ��鏈��

		float elapsedTime = App::GetApp()->GetElapsedTime();
		
		AnimaptrDraw->UpdateAnimation(elapsedTime);

	}

}