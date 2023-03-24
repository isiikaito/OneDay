/*!
@file HungerGage.cpp
@briefゲージの背景の表示
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "HungerGage.h"

namespace basecross {
	
	//--------------------------------------------------------------------------------------
	///	キーフレームスプライト
	//--------------------------------------------------------------------------------------
	HungerGage::HungerGage(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	void HungerGage::OnCreate() {
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
		SetDrawActive(true);
	}

	void HungerGage::ChangeGage()
	{
		auto PtrTransform = GetComponent<Transform>();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player"); //!プレイヤーの取得
		player->GetMeatCount();

		auto MeatCount = player->GetMeatCount();

		switch (MeatCount)
		{

		case(static_cast<int>(EatCondition::notEat)):
			//!ゲージがなくなったとき
			SetDrawActive(false);
			break;
		case(static_cast<int>(EatCondition::firstEat)):
            //!ゲージが一個溜まったとき
			SetDrawActive(true);

		    PtrTransform->SetScale(0.26f, 0.7f, 1.0f);
		     PtrTransform->SetPosition(340.0f, -320.0f, 0.4f);
		    break;
		case(static_cast<int>(EatCondition::secondEat)):
			//!ゲージが二個溜まったとき
			PtrTransform->SetScale(0.55f, 0.7f, 1.0f);
		    PtrTransform->SetPosition(390.0f, -320.0f, 0.4f);
		    break;
		case(static_cast<int>(EatCondition::thirdEat)):
            //!満タンの時
			 PtrTransform->SetScale(0.95f, 0.7f, 1.0f);
		   PtrTransform->SetPosition(420.0f, -320.0f, 0.4f);
		break;

		}

		
	}

	void HungerGage::OnUpdate()
	{
		ChangeGage();

	}


}
//end basecross