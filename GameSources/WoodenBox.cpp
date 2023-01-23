/**
*@file WoodenBox.cpp
*@brief �ؔ��̎�������`����Ă���\�[�X�t�@�C��
*@author kaito isii
*@details �ؔ��̎��̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	WoodenBox::WoodenBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_oneday(0),
		m_Time(1)

	{
	}

	//������
	void WoodenBox::OnCreate() {
		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.08f, 0.08f, 0.08f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, 0.0f)  //!�ʒu
		);

		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);                             //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"BOX_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"BOX_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		/*Coll->SetDrawActive(true);*/
		
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<WoodenBox>());

		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p

	}

	void WoodenBox::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		float elapsedTime = GameManager::GetElpasedTiem();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		

		// !�邩�璋�ɂȂ鏈��
		if (m_oneday == static_cast<int>(Oneday::midday))
		{
			m_Time += elapsedTime / 30; //!���Ԃ�ϐ��ɑ���
			ptrDraw->SetEmissive(Col4(m_Time - 0.1f, m_Time - 0.1f, m_Time - 0.1f, 1.0f)); // !��ɂ��鏈��
			if (m_Time >= 1.0f)
			{
				m_oneday = static_cast<int>(Oneday::night);
			}
		}

		// !�������ɂȂ鏈��
		if (m_oneday == static_cast<int>(Oneday::night))
		{
			m_Time += -elapsedTime / 30; //���Ԃ�ϐ��Ɍ��炷
			ptrDraw->SetEmissive(Col4(m_Time - 0.1f, m_Time - 0.1f, m_Time - 0.1f, 1.0f)); // !���ɂ��鏈��
			if (m_Time <= 0.0f)
			{
				m_oneday = static_cast<int>(Oneday::midday);
			}
		}

		return;
	}

}