/*!
@file HungerGage.cpp
@brief�Q�[�W�̔w�i�̕\��
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "HungerGage.h"

namespace basecross {
	
	//--------------------------------------------------------------------------------------
	///	�L�[�t���[���X�v���C�g
	//--------------------------------------------------------------------------------------
	HungerGage::HungerGage(const shared_ptr<Stage>& StagePtr, const wstring& TextureClock, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureClock(TextureClock),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	void HungerGage::OnCreate() {
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
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.5f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureClock);

	}

	void HungerGage::ChangeGage()
	{
		auto PtrTransform = GetComponent<Transform>();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player"); //!�v���C���[�̎擾
		player->GetMeatCount();

		auto MeatCount = player->GetMeatCount();

		switch (MeatCount)
		{

		case(static_cast<int>(EatCondition::notEat)):
			//!�Q�[�W���Ȃ��Ȃ����Ƃ�
			SetDrawActive(false);
			break;
		case(static_cast<int>(EatCondition::firstEat)):
            //!�Q�[�W����������Ƃ�
			SetDrawActive(true);

		    PtrTransform->SetScale(110.0f, 80.0f, 1.0f);
		     PtrTransform->SetPosition(340.0f, -320.0f, 0.5f);
		    break;
		case(static_cast<int>(EatCondition::secondEat)):
            //!�Q�[�W���������
		    PtrTransform->SetScale(220.0f, 80.0f, 1.0f);
		    PtrTransform->SetPosition(390.0f, -320.0f, 0.5f);
		    break;
		case(static_cast<int>(EatCondition::thirdEat)):
            //!���^���̎�
			 PtrTransform->SetScale(390.0f, 80.0f, 1.0f);
		   PtrTransform->SetPosition(420.0f, -320.0f, 0.5f);
		break;

		}

		
	}

	void HungerGage::OnUpdate()
	{
		ChangeGage();

	}


}
//end basecross