/*!
@file DateChangeCommentNight.cpp
@author Kaito Isii
@brief  ���̕\��
*/


#include "stdafx.h"
#include "Project.h"
#include "DateChangeCommentNight.h"

namespace basecross
{
	constexpr int first = 1;
	constexpr int second = 2;
	constexpr float m_textureWSpeed = 2;
	constexpr float m_textureWMaxValue = 1.0f;
	constexpr float m_startScaleZ = 1.0f;
	constexpr float m_startPosZ = 0.1f;
	constexpr float m_helfSize = 0.5f;

	//--------------------------------------------------------------------------------------
	///	�������ɕς�鎞�̃R�����g
	//--------------------------------------------------------------------------------------

	DateChangeCommentNight::DateChangeCommentNight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0),
		m_IstexturemaxW(true),
		m_textureW(0.0f),
		m_totalTime(0.0f)
	{}

	void DateChangeCommentNight::OnCreate()
	{
		float HelfSize = m_helfSize;

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_startScaleZ);
		ptrTransform->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_startPosZ); // 0.1����O�A0.9�͉�

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		m_drawComponent = AddComponent<PCTSpriteDraw>(vertices, indices);
		m_drawComponent->SetSamplerState(SamplerState::LinearWrap);
		m_drawComponent->SetTextureResource(m_TextureKey);
		SetDrawActive(true);

	}

	void DateChangeCommentNight::TextureFadeIn()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		auto playerCondition = player->GetPlayerCange();//!�v���C���[�̏�Ԃ̎擾
		 m_IstexturemaxW = player->GetPlayerTaskNight();
		//!�l�ԏ�Ԃ̎�
			//!�t�F�[�h�A�E�g���J�n����Ƃ�
			if (m_IstexturemaxW == true)
			{
				auto Diffuse = m_drawComponent->GetDiffuse();//!�F�̎擾
				auto fadeinTime = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
				m_textureW += fadeinTime / m_textureWSpeed;//!�t�F�[�h�A�E�g�̃X�s�[�h
				m_drawComponent->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));//!�e�N�X�`����RGBW�̐ݒ�
				//!�e�N�X�`�����\�����ꂽ��
				if (m_textureW >= m_textureWMaxValue)
				{

					
					player->SetPlayerTaskNight(false);//!�t�F�[�h�A�E�g�Ɉڍs
				}
			}

		
	}

	void DateChangeCommentNight::TextureFadeOut()
	{
		if (m_IstexturemaxW == false)
		{
			if (m_textureW >= 0.0f)
			{
				auto Diffuse = m_drawComponent->GetDiffuse();//!�F�̎擾
				auto fadeOutTime = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
				m_textureW -= fadeOutTime / m_textureWSpeed;//!�t�F�[�h�A�E�g�X�s�[�h
				m_drawComponent->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));//!�e�N�X�`����RGBW�̐ݒ�
			}
		}
	}

	void DateChangeCommentNight::OnUpdate()
	{
		TextureFadeIn();
		TextureFadeOut();
	}



}
