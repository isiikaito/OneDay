/*!
@file SurprisedSprite.cpp
@author Kaito Isii
@brief �r�b�N���}�[�N�̕\��
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�r�b�N���}�[�N�X�v���C�g
	//--------------------------------------------------------------------------------------

	SurprisedSprite::SurprisedSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_SurprisedTime(0.0f)

	{}

	SurprisedSprite::~SurprisedSprite() {}
	void SurprisedSprite::OnCreate()
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
		SetDrawActive(false);


	}

	void SurprisedSprite::OnUpdate()
	{
		auto GetPlayer=GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerFound=GetPlayer->GetPlayerFound();
		//!�v���C���[������������
		if (PlayerFound == true)
		{
			float Time = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
			m_SurprisedTime += Time;
			
			auto PtrDraw = GetComponent<PCTSpriteDraw>();//!�`��R���|�[�l���g
				SetDrawActive(true);
				//!2�b��������
			if (m_SurprisedTime >= 2)
			{

				PlayerFound = false;//!��������߂�
				GetPlayer->SetPlayerFound(PlayerFound);
			}
			
		}
		//!�����邱�Ƃ���߂���
		if (PlayerFound == false)
		{
			m_SurprisedTime = 0.0f;//!�������Ԃ�0�b�ɂ���
			SetDrawActive(false);
			
		}
		
	}
}
