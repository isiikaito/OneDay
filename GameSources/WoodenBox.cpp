/**
*@file WoodenBox.cpp
*@brief �ؔ��̎�������`����Ă���\�[�X�t�@�C��
*@author kaito isii
*@details �ؔ��̎��̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
#include "WoodenBoxState.h"
namespace basecross {

	constexpr float COLLIMIT = 0.2;//!�F�̕ω��l
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
		m_woodenBoxModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
			Vec3(0.06f, 0.06f, 0.06f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   
			Vec3(0.0f, -0.2f, 0.0f)  ,
				L"BOX_MESH"
			}
		)
	{
		m_StateMachine = new kaito::StateMachine<WoodenBox>(this);
		m_StateMachine->SetCurrentState(kaito::WoodenBoxMiddayState::Instance());	//!���݂̃X�e�[�g
	}

	//������
	void WoodenBox::OnCreate() {
		
		AddComponent<StaticModelComponent>(m_woodenBoxModelData);				//!���f���f�[�^����
		
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<WoodenBox>());
		
	}


	void WoodenBox::ChangeState(kaito::State<WoodenBox>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!�X�e�[�g��ύX����
	}

	void WoodenBox::OnUpdate() {
		m_StateMachine->Update();
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto m_time = scene->GetEmissiveChangeTime();
		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, 1.0f)); // !��ɂ��鏈��
	}

}