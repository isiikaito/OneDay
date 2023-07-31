/*!
@file KeySprite.cpp
@brief �擾�����J�M��\������e�N�X�`��
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "KeySprite.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�擾�����J�M��\������e�N�X�`��
	//--------------------------------------------------------------------------------------
	KeySprite::KeySprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos,int keyCount) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_keyCount(keyCount)
	{}

	void KeySprite:: CurrentKeySpriteDisplay(int keyCount)
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto GetkeyCount = player->GetKeyCount();//!���ݎ擾�����J�M�̐�
		if (GetkeyCount > keyCount)
		{
			SetDrawActive(true);//!�e�N�X�`����\������
		}
	}

	
	void KeySprite::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
	
	}

	void KeySprite::OnUpdate()
	{
		
		CurrentKeySpriteDisplay(m_keyCount);//!�J�M�̐��ɉ����ăe�N�X�`����\������

	}
}
//end basecross