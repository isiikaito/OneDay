//* @author kanazawa yuuma
//* @details �؂̎��̎���
//* /

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	constexpr float COLLIMIT = 0.2;	//�F�̕ω��l
	constexpr float TRANCE = 1.0f;		//!�����x
	//--------------------------------------------------------------------------------------
	//	class Wood : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Wood::Wood(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_woodModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.06f, 0.06f, 0.06f),	
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),		
				Vec3(0.0f, -0.5f, 0.0f),	
				L"STAGE_WOOD"
			}
		)

	{
	}

	//������
	void Wood::OnCreate() {
		AddComponent<StaticModelComponent>(m_woodModelData);				//!���f���f�[�^����
	}

	void Wood::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !��ɂ��鏈��

	}

}