/**
*@file StageFloor.cpp
*@brief �Q�[���X�e�[�W�̏��̎�������`����Ă���\�[�X�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���X�e�[�W�̏��̎��̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	constexpr float COLLIMIT = 0.2;	//�F�̕ω��n
	constexpr float TRANCE = 1.0f;		//!�����x
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
		m_stageFloorModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.04f, 1.0f, 0.04f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),	
				Vec3(0.0f, 0.5f, -0.003f),
				L"GROUND_MESH"
			}
		)
	{
	}

	//������
	void StageFloor::OnCreate() {
		AddComponent<StaticModelComponent>(m_stageFloorModelData);				//!���f���f�[�^����
	
	}

	void StageFloor::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !��ɂ��鏈��
	}

}