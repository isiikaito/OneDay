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
		m_Time(0.0f),
		m_meatModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.2f, 0.2f, 0.15f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f),
				L"MEAT_MESH",

			}
		)

	{
	}

	void Meat::OnCreate() {

		AddComponent<StaticModelComponent>(m_meatModelData);				//!���f���f�[�^����
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