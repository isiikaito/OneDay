/*!
@file GameUI.cpp
@author Kaito Isii
@brief  ゲーム画面のUIの表示
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	警戒度のスプライト
	//--------------------------------------------------------------------------------------

	GameUI::GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_StartRotation(0.0f),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	GameUI::GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, Vec3& Rotation,const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartRotation(Rotation),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	
	GameUI::~GameUI() {}

	void GameUI::CreateGameUI(const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos)
	{
		//!頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-StartScale.x,  StartScale.y, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(StartScale.x,  StartScale.y, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-StartScale.x, -StartScale.y, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(StartScale.x, -StartScale.y, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//!インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetRotation(m_StartRotation);
		PtrTransform->SetPosition(StartPos);

		//!頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(TextureKey);
		SetDrawActive(false);
	}
	void GameUI::OnCreate()
	{
		
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);//!UIの生成


	}

	void GameUI::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!シーンの取得
		auto gemeStrat = scene->GetGameStrat();			//!ゲームスタートしているかどうか
		//!ゲームスタートしていたら
		if (!gemeStrat)
		{
			SetDrawActive(true);//!表示する
			
		}

	}

}