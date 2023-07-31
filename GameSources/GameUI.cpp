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
	
	GameUI::GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_StartRotation(0.0f),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f)),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}

	GameUI::GameUI(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, Vec3& Rotation,const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartRotation(Rotation),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f)),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}

	
	GameUI::~GameUI() {}

	void GameUI::CreateGameUI(const wstring& TextureKey, bool Trace, const Vec2& StartScale, const Vec3& StartPos)
	{
		//!頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-StartScale.x,  StartScale.y, 0),m_TextureColor,m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(StartScale.x,  StartScale.y, 0),m_TextureColor,m_RightUpperSummit)},
			{ VertexPositionColorTexture(Vec3(-StartScale.x, -StartScale.y, 0), m_TextureColor,m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(StartScale.x, -StartScale.y, 0), m_TextureColor,m_RightLowerSummit) },
		};

		
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };				//!インデックス配列
		SetAlphaActive(Trace);											//!透明化するかどうか
		auto PtrTransform = GetComponent<Transform>();					//!トランスフォームの取得
		PtrTransform->SetRotation(m_StartRotation);						//!回転の設定
		PtrTransform->SetPosition(StartPos);							//!位置の設定
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);	//!頂点とインデックスを指定してスプライト作成
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);				//!重ね合わせの問題を解消する
		PtrDraw->SetTextureResource(TextureKey);						//!テクスチャの名前の設定
		SetDrawActive(false);											//!表示するかどうか
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