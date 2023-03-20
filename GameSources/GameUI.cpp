/*!
@file GameUI.cpp
@author Kaito Isii
@brief  �Q�[����ʂ�UI�̕\��
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"

namespace basecross
{
	constexpr float m_startScaleZ = 1.0f;//!�傫��
	constexpr float m_startPosZ = 1.0f;	 //!���s��
	constexpr float m_helfSize = 0.5f;	 //!�����̑傫��
	//--------------------------------------------------------------------------------------
	///	�x���x�̃X�v���C�g
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
		//!���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-StartScale.x,  StartScale.y, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(StartScale.x,  StartScale.y, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-StartScale.x, -StartScale.y, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(StartScale.x, -StartScale.y, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//!�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetRotation(m_StartRotation);
		PtrTransform->SetPosition(StartPos);

		//!���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(TextureKey);
		SetDrawActive(false);
	}
	void GameUI::OnCreate()
	{
		
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);

		


	}

	void GameUI::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gemeStrat = scene->GetGameStrat();

		if (!gemeStrat)
		{
			SetDrawActive(true);
			
		}

	}

}