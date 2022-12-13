/*!
@file PlayerHeartSprite.cpp
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr int m_MaxhurteCount = 3.0f; // !HP�_�ł̉񐔐���

	//--------------------------------------------------------------------------------------
	///	�����̃n�[�g�X�v���C�g
	//--------------------------------------------------------------------------------------

	PlayerHeartSpriteLeft::PlayerHeartSpriteLeft(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(2),
		m_hurt(false),
		m_hurtCount(0),
		m_hurtDefise(true),
		m_dedTime(0),
		m_GameOver(false)
	{}

	PlayerHeartSpriteLeft::~PlayerHeartSpriteLeft() {}
	void PlayerHeartSpriteLeft::OnCreate()
	{
		float HelfSize = 0.5f;

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
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.8f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(true);


	}

	void PlayerHeartSpriteLeft::OnUpdate()
	{
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player"); //!�v���C���[�̎擾
		auto PlayrHp = GetPlayer->GetPlayerHp(); //!�v���C���[��Hp�̎擾

		if (PlayrHp == m_RustLife && m_hurtDefise == true) //!�v���C���[��Hp��0�̎����E���C�t���\������Ă���Ƃ�
		{

			m_hurt = true; //!���C�t�̓_�ł�true
			if (m_hurt == true)
			{
				// !HP�\���̃n�[�g���_�ł��鏈��
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				if (m_Time >= 0.5f)
				{
					auto PtrDraw = GetComponent<PCTSpriteDraw>();
					SetDrawActive(false);

					if (m_Time >= 1.0f)
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

}
