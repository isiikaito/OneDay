/**
*@file StageBuilding.cpp
*@brief �Q�[���X�e�[�W�̌����̎�������`����Ă���\�[�X�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̌����̎��̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	
	

	constexpr float COLLIMIT = 0.2;	//�F�̕ω��l

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	StageBuilding::StageBuilding(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Time(1),
		m_oneday(0)
		
	{
	}


	//������
	void StageBuilding::OnCreate() {
		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.09f, 0.09f, 0.09f),	//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 80.1f, 0.0f),	//!��]
			Vec3(0.0f, -0.5f, 0.0f)		//!�ʒu
		);


		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);                             //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
		auto group = GetStage()->GetSharedObjectGroup(L"StageBuilding_Group");//!�O���[�v���擾
		group->IntoGroup(GetThis<StageBuilding>());//!�O���[�v�ɃX�e�[�W�̕ǂ�����


		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGEBUILDING_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		
		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"STAGEBUILDING_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
		
		SetAlphaActive(true);//!SetDiffiuse�̃J���[�ύX��K�p

		
	}

	void StageBuilding::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		float elapsedTime = GameManager::GetElpasedTiem();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		auto scene = App::GetApp()->GetScene<Scene>();
		auto m_time = scene->GetEmissiveChangeTime();
		
		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, 1.0f)); // !��ɂ��鏈��
				
	}

}