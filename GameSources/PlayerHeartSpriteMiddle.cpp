/*!
@file PlayerHeartSpriteMiddle.cpp
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr int m_MaxhurteCount = 3; // !HP�_�ł̉񐔐���
	constexpr float m_feadOutTime = 0.5;//!�n�[�g�̓_�Ŏ��ɏ����鎞��
	constexpr float m_feadInTime = 1.0f;//!�n�[�g�̓_�Ŏ����t������
	 //--------------------------------------------------------------------------------------
	 ///	�^�񒆂̃n�[�g�X�v���C�g
	 //--------------------------------------------------------------------------------------

	PlayerHeartSpriteMiddle::PlayerHeartSpriteMiddle(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_MiddleLife(1),
		m_hurt(false),
		m_tiem(0.0f),
		m_hurtCount(0),
		m_hurtDefise(true)
	{}

	PlayerHeartSpriteMiddle::~PlayerHeartSpriteMiddle() {}
	void PlayerHeartSpriteMiddle::OnCreate()
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

	void PlayerHeartSpriteMiddle::OnUpdate()
	{
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayrHp = GetPlayer->GetPlayerHp();

		if (PlayrHp <= m_MiddleLife && m_hurtDefise == true) //!�v���C���[��Hp��0�̎����E���C�t���\������Ă���Ƃ�
		{

			m_hurt = true; //!���C�t�̓_�ł�true
			if (m_hurt == true)
			{
				// !HP�\���̃n�[�g���_�ł��鏈��
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_tiem += elapsedTime;
				if (m_tiem >= m_feadOutTime)
				{
					auto PtrDraw = GetComponent<PCTSpriteDraw>();
					SetDrawActive(false);

					if (m_tiem >= m_feadInTime)
					{
						SetDrawActive(true);
						m_hurtCount++; //!�_�ł�����
						m_tiem = 0;
					}
					return;
				}
			}

			// !�n�[�g�̓_�ŉ񐔂��ő�ɂȂ�����
			if (m_hurtCount == m_MaxhurteCount) //!���̉񐔓_�ł�����
			{
				SetDrawActive(false); //!���C�t�̕\�������S�ɏ���
				m_hurtDefise = false;
			}
		}
	}
}