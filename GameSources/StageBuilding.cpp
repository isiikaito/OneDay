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
	constexpr float TRANCE = 1.0f;	//!�����x

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
		m_Time(1),
		m_oneday(0),
		m_buildingModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.09f, 0.09f, 0.09f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 80.1f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f),
				L"STAGEBUILDING_MESH"
			}
		)
		
	{
	}


	//������
	void StageBuilding::OnCreate() {

		AddComponent<StaticModelComponent>(m_buildingModelData);				//!���f���f�[�^����
		auto group = GetStage()->GetSharedObjectGroup(L"StageBuilding_Group");	//!�O���[�v���擾
		group->IntoGroup(GetThis<StageBuilding>());								//!�O���[�v�ɃX�e�[�W�̕ǂ�����
		SetAlphaActive(true);													//!SetDiffiuse�̃J���[�ύX��K�p
		m_ptrDrow= GetComponent<PNTStaticModelDraw>();							//!�`��R���|�[�l���g
	}

	void StageBuilding::OnUpdate() {

		float elapsedTime = GameManager::GetElpasedTiem();//!elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		auto scene = App::GetApp()->GetScene<Scene>();
		auto m_time = scene->GetEmissiveChangeTime();
		m_ptrDrow.lock()->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !��ɂ��鏈��
				
	}

}