/*!
@file PlayerHeartSprite.cpp
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/


#include "stdafx.h"
#include "Project.h"
#include "PlayerHurteSprite.h"

namespace basecross
{
	constexpr int m_MaxhurteCount = 3; // !HP�_�ł̉񐔐���
	constexpr float m_feadOutTime = 0.5;//!�n�[�g�̓_�Ŏ��ɏ����鎞��
	constexpr float m_feadInTime = 1.0f;//!�n�[�g�̓_�Ŏ����t������
	//--------------------------------------------------------------------------------------
	///	�����̃n�[�g�X�v���C�g
	//--------------------------------------------------------------------------------------

	PlayerHurteSprite::PlayerHurteSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos, int currentHp,bool hurtDefise) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(2),
		m_hurt(false),
		m_hurtCount(0),
		m_hurtDefise(hurtDefise),
		m_dedTime(0),
		m_GameOver(false),
		m_Time(0.0f),
		m_currentHp(currentHp)
	{}


	void PlayerHurteSprite::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
	}

	void PlayerHurteSprite::FlashingHurteSprite(int currentHp)
	{
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player"); //!�v���C���[�̎擾
		auto PlayrHp = GetPlayer->GetPlayerHp(); //!�v���C���[��Hp�̎擾
		
		if (PlayrHp <= currentHp && m_hurtDefise == true) //!�v���C���[��Hp��0�̎����E���C�t���\������Ă���Ƃ�
		{

			m_hurt = true; //!���C�t�̓_�ł�true
			if (m_hurt == true)
			{
				// !HP�\���̃n�[�g���_�ł��鏈��
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				if (m_Time >= m_feadOutTime)
				{
					SetDrawActive(false);

					if (m_Time >= m_feadInTime)
					{
						SetDrawActive(true);
						m_hurtCount++; //!�_�ł�����
						m_Time = 0;
					}
					return;
				}
			}

			// !�n�[�g�̓_�ŉ񐔂��ő�ɂȂ�����
			if (m_hurtCount == m_MaxhurteCount) //!���̉񐔓_�ł�����
			{
				m_hurtDefise = false;
				
                SetDrawActive(false); //!���C�t�̕\�������S�ɏ���
				
			}
		}

	}

	void PlayerHurteSprite::OnUpdate()
	{
		if (m_hurtDefise)
		{
		 GameUI::OnUpdate();
		}

		FlashingHurteSprite(m_currentHp);

	}


}