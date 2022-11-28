/**
*@file StageGate.cpp
*@brief �Q�[���X�e�[�W�̖�̎�������`����Ă���\�[�X�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̖�̎��̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


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
			Vec3(1.0f, 0.1f, 0.09f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, 0.0f)  //!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);                             //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGEGATE_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"STAGEGATE_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		Coll->SetDrawActive(true);
		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

	}

	void StageGate::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		float elapsedTime = App::GetApp()->GetElapsedTime();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����

		// !�邩�璋�ɂȂ鏈��
		if (m_oneday == static_cast<int>(Oneday::midday))
		{
			m_Time += elapsedTime / 30; //!���Ԃ�ϐ��ɑ���
			ptrDraw->SetEmissive(Col4(m_Time, m_Time, m_Time, 1.0f)); // !��ɂ��鏈��
			if (m_Time >= 1.0f)
			{
				m_oneday = static_cast<int>(Oneday::night);
			}
		}

		// !�������ɂȂ鏈��
		if (m_oneday == static_cast<int>(Oneday::night))
		{
			m_Time += -elapsedTime / 30; //���Ԃ�ϐ��Ɍ��炷
			ptrDraw->SetEmissive(Col4(m_Time, m_Time, m_Time, 1.0f)); // !���ɂ��鏈��
			if (m_Time <= 0.0f)
			{
				m_oneday = static_cast<int>(Oneday::midday);
			}
		}

		return;
	}

}