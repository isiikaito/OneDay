/*!
@file PlayerHeartSprite.cpp
@author Kaito Isii
@brief �v���C���[�̃n�[�g�̕\��
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
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
		    m_RustLife(0)
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
			PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

			//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
			auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
			PtrDraw->SetSamplerState(SamplerState::LinearWrap);
			PtrDraw->SetTextureResource(m_TextureKey);
			SetDrawActive(true);

			
		}

		void PlayerHeartSpriteLeft::OnUpdate()
		{
			auto GetPlayer=GetStage()->GetSharedGameObject<Player>(L"Player");
			auto PlayrHp=GetPlayer->GetPlayerHp();
			if (PlayrHp == m_RustLife)
			{
				auto PtrDraw = GetComponent<PCTSpriteDraw>();
				SetDrawActive(false);
			}

		}

		



	
}