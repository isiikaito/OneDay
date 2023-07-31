/*!
@file KeySprite.cpp
@brief 取得したカギを表示するテクスチャ
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "KeySprite.h"
namespace basecross {
	//--------------------------------------------------------------------------------------
	///	取得したカギを表示するテクスチャ
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
		auto GetkeyCount = player->GetKeyCount();//!現在取得したカギの数
		if (GetkeyCount > keyCount)
		{
			SetDrawActive(true);//!テクスチャを表示する
		}
	}

	
	void KeySprite::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
	
	}

	void KeySprite::OnUpdate()
	{
		
		CurrentKeySpriteDisplay(m_keyCount);//!カギの数に応じてテクスチャを表示する

	}
}
//end basecross