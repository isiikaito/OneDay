/*!
@file DescriptionSpriteFront.cpp
@author Kaito Isii
@brief 説明書の表示
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionSpriteFront.h"
#include "DescriptionSpriteFrontState.h"
namespace basecross {

	//!定数
	constexpr float m_TimeSpeed = 30;
	
	constexpr float m_helfSize = 0.5f;

	//--------------------------------------------------------------------------------------
	///	説明のスプライト
	//--------------------------------------------------------------------------------------
	DescriptionSpriteFront::DescriptionSpriteFront(const shared_ptr<Stage>& StagePtr, const wstring& TextureClock, bool Trace,
		const Vec3& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureClock(TextureClock),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_moveTexture(false),
		m_pageBackTo(false)
	{
		m_StateMachine = new kaito::StateMachine<DescriptionSpriteFront>(this);
		m_StateMachine->SetCurrentState(kaito::DescriptionSpriteStandbyFrontState::Instance());
	}

	DescriptionSpriteFront::~DescriptionSpriteFront() {}
	void DescriptionSpriteFront::OnCreate() {
		float HelfSize = m_helfSize;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetRotation(0.0f,0.0f,0.0f);
		PtrTransform->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureClock);
		SetDrawActive(true);

	}

	void DescriptionSpriteFront::ChangeState(kaito::State<DescriptionSpriteFront>* NewState)
	{

		m_StateMachine->ChangeState(NewState);
	}

	void DescriptionSpriteFront::OnUpdate()
	{
		m_StateMachine->Update();
		
	}

}
//end basecross