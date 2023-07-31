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

	constexpr float COLLIMIT = 0.2;	//!�J���[�̕ύX�l
	constexpr float TRANCE = 1.0f;		//!�����x
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

		auto scene = App::GetApp()->GetScene<Scene>();
		auto goleGateParameter = scene->GetGoleGateParameter();

		if (!goleGateParameter)
		{
			auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
			//Coll->SetDrawActive(true);
			Coll->SetFixed(true);
		}

		if (goleGateParameter)
		{


		}



		////!���b�V���̐ݒ�
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		ptrShadow->SetMeshResource(L"GateAnimation_MESH");//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"GateAnimation_MESH_WITH_TAN");
		ptrDraw->AddAnimation(L"Open", 0, 60, false, 20.0f);
		ptrDraw->AddAnimation(L"defoult", 0, 1, false, 20.0f);//!�J���Ȃ��A�j���[�V����
	}
	void StageGate::AnimationChange()
	{
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾

		auto goleGateParameter = scene->GetGoleGateParameter();//!��̃p�����[�^�̎擾
		//!�傪�S�[���X�e�[�W�ɂ���ꍇ
		if (goleGateParameter)
		{
			auto drowComponet = GetComponent<BcPNTnTBoneModelDraw>();//!�`��R���|�[�l���g�̎擾

			auto& AnimationName = drowComponet->GetCurrentAnimation();//!���݂̃A�j���[�V�����̎擾
			//!�A�j���[�V�������f�t�H���g�̎�
			if (AnimationName == L"defoult")
			{
				//!�J���A�j���[�V�����ɕς���
				drowComponet->ChangeCurrentAnimation(L"Open");

			}
		}

		else
		{
			auto drowComponet = GetComponent<BcPNTnTBoneModelDraw>();

			auto& AnimationName = drowComponet->GetCurrentAnimation();
			if (AnimationName == L"Open")
			{
				drowComponet->ChangeCurrentAnimation(L"defoult");//!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
				;
			}
		}
	}

	void StageGate::OnUpdate() {
		auto AnimaptrDraw = GetComponent<BcPNTnTBoneModelDraw>();	//!�A�j���[�V����
		auto scene = App::GetApp()->GetScene<Scene>();				//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();

		AnimaptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !��ɂ��鏈��

		float elapsedTime = App::GetApp()->GetElapsedTime();

		AnimationChange();

		  AnimaptrDraw->UpdateAnimation(elapsedTime);

	}

}