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
		auto PtrTransform = GetComponent<Transform>();						//!トランスフォームの取得
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");	//!プレイヤーの取得											
		auto MeatCount = player->GetMeatCount();							//!肉の取得数
		//!肉の数に応じて
		switch (MeatCount)
		{
		//!ゲージがなくなったとき
		case(static_cast<int>(EatCondition::notEat)):
			SetDrawActive(false);											//!表示しない
			break;
		//!ゲージが一個溜まったとき
		case(static_cast<int>(EatCondition::firstEat)):
			SetDrawActive(true);											//!表示する
			PtrTransform->SetScale(m_firstEatScale);						//!一個の時のゲージの大きさにする
			PtrTransform->SetPosition(m_firstEatPos);						//!一個の時のゲージの位置にする
			break;
		//!ゲージが二個溜まったとき
		case(static_cast<int>(EatCondition::secondEat)):
			PtrTransform->SetScale(m_secondEatScale);						//!二個の時のゲージの大きさにする
			PtrTransform->SetPosition(m_secondEatPos);						//!二個の時のゲージの位置にする
			break;
		//!満タンの時
		case(static_cast<int>(EatCondition::thirdEat)):
			
			PtrTransform->SetScale(m_thirdEatScale);						//!満タンの時のゲージの大きさにする
			PtrTransform->SetPosition(m_thirdEatPos);						//!満タンの時のゲージの位置にする
			break;

		}

		
	}

	void HungerGage::OnUpdate()
	{
		ChangeGage();

	}


}
//end basecross