/*!
@file HungerGage.cpp
@brief�Q�[�W�̔w�i�̕\��
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "HungerGage.h"

namespace basecross {
	
	//--------------------------------------------------------------------------------------
	///	�L�[�t���[���X�v���C�g
	//--------------------------------------------------------------------------------------
	HungerGage::HungerGage(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_firstEatScale(Vec3(0.26f, 0.7f, 1.0f)),
		m_firstEatPos(Vec3(340.0f, -320.0f, 0.4f)),
		m_secondEatScale(Vec3(0.55f, 0.7f, 1.0f)),
		m_secondEatPos(Vec3(390.0f, -320.0f, 0.4f)),
		m_thirdEatScale(Vec3(0.95f, 0.7f, 1.0f)),
		m_thirdEatPos(Vec3(420.0f, -320.0f, 0.4f))
	{}

	void HungerGage::OnCreate() {
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
		SetDrawActive(true);
	}

	void HungerGage::ChangeGage()
	{
		auto PtrTransform = GetComponent<Transform>();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player"); //!�v���C���[�̎擾
		player->GetMeatCount();

		auto MeatCount = player->GetMeatCount();

		switch (MeatCount)
		{

		case(static_cast<int>(EatCondition::notEat)):
			//!�Q�[�W���Ȃ��Ȃ����Ƃ�
			SetDrawActive(false);
			break;
		case(static_cast<int>(EatCondition::firstEat)):
            //!�Q�[�W������܂����Ƃ�
			SetDrawActive(true);

		    PtrTransform->SetScale(m_firstEatScale);
		     PtrTransform->SetPosition(m_firstEatPos);
		    break;
		case(static_cast<int>(EatCondition::secondEat)):
			//!�Q�[�W������܂����Ƃ�
			PtrTransform->SetScale(m_secondEatScale);
		    PtrTransform->SetPosition(m_secondEatPos);
		    break;
		case(static_cast<int>(EatCondition::thirdEat)):
            //!���^���̎�
			 PtrTransform->SetScale(m_thirdEatScale);
		   PtrTransform->SetPosition(m_thirdEatPos);
		break;

		}

		
	}

	void HungerGage::OnUpdate()
	{
		ChangeGage();

	}


}
//end basecross