/*!
@file DescriptionSpriteFront.cpp
@author Kaito Isii
@brief �������̕\��
*/

#include "stdafx.h"
#include "Project.h"
#include "DescriptionSpriteFront.h"
#include "DescriptionSpriteFrontState.h"
namespace basecross {

	

	//--------------------------------------------------------------------------------------
	///	�����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	DescriptionSpriteFront::DescriptionSpriteFront(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_moveTexture(false),
		m_pageBackTo(false)
	{
		m_StateMachine = new kaito::StateMachine<DescriptionSpriteFront>(this);
		m_StateMachine->SetCurrentState(kaito::DescriptionSpriteStandbyFrontState::Instance());
	}

	DescriptionSpriteFront::~DescriptionSpriteFront() {}
	void DescriptionSpriteFront::OnCreate() {
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);	//!UI�̐���
		SetDrawActive(true);											//!�����ɂ���
	}

	void DescriptionSpriteFront::ChangeState(kaito::State<DescriptionSpriteFront>* NewState)
	{

		m_StateMachine->ChangeState(NewState);//!�X�e�[�g�̕ύX
	}

	void DescriptionSpriteFront::OnUpdate()
	{
		m_StateMachine->Update();//!�X�e�[�g�̍X�V
		
	}

}
//end basecross