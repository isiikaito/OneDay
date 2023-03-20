/*!
@file Arrow.cpp
@author Kaito Isii
@brief  矢印の表示
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr int first = 1;//!警戒度レベル1
	constexpr int second = 2;//!警戒度レベル2
	constexpr float m_startScaleZ = 1.0f;//!大きさ
	constexpr float m_startPosZ = 0.2f;  //!奥行き
	constexpr float m_helfSize = 0.5f;   //!半分の大きさ
	//--------------------------------------------------------------------------------------
	///	矢印
	//--------------------------------------------------------------------------------------

	Arrow::Arrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale,  const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0),
		m_secondPosition(Vec3(460.0f, 330.0f, 0.0f)),
		m_firstPosition(Vec3(530.0f, 330.0f, 0.0f))
	{}

	Arrow::~Arrow() {}
	void Arrow::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
	}

	void Arrow::OnUpdate()
	{
		GameUI::OnUpdate();

		//auto alertlevelCount = App::GetApp()->GetScene<Scene>()->GetAlertlevelCount();//!シーンの取得
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayrHp = GetPlayer->GetPlayerHp();
		auto ptrTransform = GetComponent<Transform>();//!矢印のテクスチャの取得
		//!警戒度が2の時
		if (PlayrHp == second)
		{
          ptrTransform->SetPosition(m_secondPosition);
		}
		//!警戒度が3の時
		if (PlayrHp == first)
		{
			ptrTransform->SetPosition(Vec3(530.0f, 330.0f, 0.0f));
		}
		
			
	}

}
