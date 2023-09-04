/*!
@file Key.cpp
@brief �J�M�Ɋւ��鏈��
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	Key::Key(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_RotationSpeed(0.0f),
		m_keyModelData
		(
			{
			    Scale ,
				Rotation ,
				Position,
				Vec3(0.2f, 0.1f, 0.5f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.6f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f),
				L"KEY_MESH"

			}
		)
	{
	}

	void Key::OnCreate() {

		AddComponent<StaticModelComponent>(m_keyModelData);				//!���f���f�[�^����	                           

		auto group = GetStage()->GetSharedObjectGroup(L"key_ObjGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Key>());
	
	}
	void Key::OnUpdate()
	{
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto ptrTrans = GetComponent<Transform>();
		auto& app = App::GetApp();//!�A�v���̎擾
		auto time = app->GetElapsedTime();
		m_RotationSpeed += time;
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.1f, 0.5f),				//!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, m_RotationSpeed, 0.0f),   //!��]
			Vec3(0.0f, -0.5f, 0.0f)				//!�ʒu
		);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
	}
}
//end basecross