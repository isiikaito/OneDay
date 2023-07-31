/*!
@file DateChangeCommentNight.cpp
@author Kaito Isii
@brief  ��̃^�X�N�̕\��
*/


#include "stdafx.h"
#include "Project.h"
#include "DateChangeCommentNight.h"
#include "GameUI.h"
namespace basecross
{
	
	constexpr float TEXTUREWSPEED = 2;      //!�t�F�[�h�A�E�g�̑���
	constexpr float TEXTUREWMAXVALUE = 1.0f;//!�e�N�X�`�������S�ɕ\�����ꂽ

	//--------------------------------------------------------------------------------------
	///	�������ɕς�鎞�̃R�����g
	//--------------------------------------------------------------------------------------

	DateChangeCommentNight::DateChangeCommentNight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_IstexturemaxW(true),
		m_textureW(0.0f),
		m_totalTime(0.0f)
	{}

	void DateChangeCommentNight::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
		SetDrawActive(true);

	}

	void DateChangeCommentNight::TextureFadeIn()
	{
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//!�v���C���[�̎擾
		auto playerCondition = player->GetPlayerChange();				 //!�v���C���[�̏�Ԃ̎擾
		 m_IstexturemaxW = player->GetPlayerTaskNight();
		//!�l�ԏ�Ԃ̎�
			//!�t�F�[�h�A�E�g���J�n����Ƃ�
			if (m_IstexturemaxW == true)
			{
				auto Diffuse = ptrDraw->GetDiffuse();									//!�F�̎擾
				auto fadeinTime = App::GetApp()->GetElapsedTime();						//!���Ԃ̎擾
				m_textureW += fadeinTime / TEXTUREWSPEED;								//!�t�F�[�h�A�E�g�̃X�s�[�h
				ptrDraw->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));	//!�e�N�X�`����RGBW�̐ݒ�
				//!�e�N�X�`�����\�����ꂽ��
				if (m_textureW >= TEXTUREWMAXVALUE)
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
				auto ptrDraw = GetComponent<PCTSpriteDraw>();
				auto Diffuse = ptrDraw->GetDiffuse();									//!�F�̎擾
				auto fadeOutTime = App::GetApp()->GetElapsedTime();						//!���Ԃ̎擾
				m_textureW -= fadeOutTime / TEXTUREWSPEED;							//!�t�F�[�h�A�E�g�X�s�[�h
				ptrDraw->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));	//!�e�N�X�`����RGBW�̐ݒ�
			}
		}
	}

	void DateChangeCommentNight::OnUpdate()
	{
		TextureFadeIn();
		TextureFadeOut();
	}



}
