/*!
@file Arrow.cpp
@author Kaito Isii
@brief  ���̕\��
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr int first = 1;//!�x���x���x��1
	constexpr int second = 2;//!�x���x���x��2
	constexpr float m_startScaleZ = 1.0f;//!�傫��
	constexpr float m_startPosZ = 0.2f;  //!���s��
	constexpr float m_helfSize = 0.5f;   //!�����̑傫��
	//--------------------------------------------------------------------------------------
	///	���
	//--------------------------------------------------------------------------------------

	Arrow::Arrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale,  const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0),
		m_secondPosition(Vec3(460.0f, 330.0f, 0.0f)),
		m_firstPosition(Vec3(530.0f, 330.0f, 0.0f))
	{}

	Arrow::~Arrow() {}
	void Arrow::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
	}

	void Arrow::OnUpdate()
	{
		GameUI::OnUpdate();

		//auto alertlevelCount = App::GetApp()->GetScene<Scene>()->GetAlertlevelCount();//!�V�[���̎擾
		auto GetPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayrHp = GetPlayer->GetPlayerHp();
		auto ptrTransform = GetComponent<Transform>();//!���̃e�N�X�`���̎擾
		//!�x���x��2�̎�
		if (PlayrHp == second)
		{
          ptrTransform->SetPosition(m_secondPosition);
		}
		//!�x���x��3�̎�
		if (PlayrHp == first)
		{
			ptrTransform->SetPosition(Vec3(530.0f, 330.0f, 0.0f));
		}
		
			
	}

}
