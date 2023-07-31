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
		//!���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-StartScale.x,  StartScale.y, 0),m_TextureColor,m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(StartScale.x,  StartScale.y, 0),m_TextureColor,m_RightUpperSummit)},
			{ VertexPositionColorTexture(Vec3(-StartScale.x, -StartScale.y, 0), m_TextureColor,m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(StartScale.x, -StartScale.y, 0), m_TextureColor,m_RightLowerSummit) },
		};

		
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };				//!�C���f�b�N�X�z��
		SetAlphaActive(Trace);											//!���������邩�ǂ���
		auto PtrTransform = GetComponent<Transform>();					//!�g�����X�t�H�[���̎擾
		PtrTransform->SetRotation(m_StartRotation);						//!��]�̐ݒ�
		PtrTransform->SetPosition(StartPos);							//!�ʒu�̐ݒ�
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);	//!���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);				//!�d�ˍ��킹�̖�����������
		PtrDraw->SetTextureResource(TextureKey);						//!�e�N�X�`���̖��O�̐ݒ�
		SetDrawActive(false);											//!�\�����邩�ǂ���
	}
	void GameUI::OnCreate()
	{
		
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);//!UI�̐���


	}

	void GameUI::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
		auto gemeStrat = scene->GetGameStrat();			//!�Q�[���X�^�[�g���Ă��邩�ǂ���
		//!�Q�[���X�^�[�g���Ă�����
		if (!gemeStrat)
		{
			SetDrawActive(true);//!�\������
			
		}

	}

}