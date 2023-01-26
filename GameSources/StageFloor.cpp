/**
*@file StageFloor.cpp
*@brief �Q�[���X�e�[�W�̏��̎�������`����Ă���\�[�X�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̏��̎��̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float DrawTime = 31.0f;
	constexpr float m_colLimit = 0.2;

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr,
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
	void StageFloor::OnCreate() {
		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.04f, 1.0f, 0.04f),//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //!��]
			Vec3(0.0f, 0.5f, -0.003f)  //!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);                             //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"GROUND_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		ptrDraw->SetOwnShadowActive(true); // �e�̉f�肱�݂�L���ɂ���

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"GROUND_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
	
	}

	void StageFloor::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - m_colLimit, m_time - m_colLimit, m_time - m_colLimit, 1.0f)); // !��ɂ��鏈��
	}

}