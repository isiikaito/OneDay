/*!
@file DateChangeCommentDay.cpp
@author Kaito Isii
@brief  昼間のタスクの表示
*/


#include "stdafx.h"
#include "Project.h"
#include "DateChangeCommentDay.h"
#include "GameUI.h"

namespace basecross
{
	
	constexpr float m_textureWSpeed = 2;      //!フェードアウトの速さ
	constexpr float m_textureWMaxValue = 1.0f;//!テクスチャが完全に表示された
	
	//--------------------------------------------------------------------------------------
	///	昼から夜に変わる時のコメント
	//--------------------------------------------------------------------------------------

	DateChangeCommentDay::DateChangeCommentDay(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameUI(StagePtr, TextureKey, Trace, StartScale, StartPos),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0),
		m_IstexturemaxW(true),
		m_textureW(0.0f),
		m_totalTime(0.0f)
	{}

	void DateChangeCommentDay::OnCreate()
	{
		CreateGameUI(m_TextureKey, m_Trace, m_StartScale, m_StartPos);
		SetDrawActive(true);
	}

	void DateChangeCommentDay::TextureFadeIn()
	{
		auto ptrDraw=GetComponent<PCTSpriteDraw>();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");	//!プレイヤーの取得
		auto playerCondition = player->GetPlayerCange();					//!プレイヤーの状態の取得
		m_IstexturemaxW = player->GetPlayerTaskDay();

		//!フェードアウトを開始するとき
		if (m_IstexturemaxW == true)
		{
			
            auto Diffuse = ptrDraw->GetDiffuse();				//!色の取得
			auto fadeinTime = App::GetApp()->GetElapsedTime();	//!時間の取得
			m_textureW += fadeinTime / m_textureWSpeed;			//!フェードアウトのスピード
			ptrDraw->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));//!テクスチャのRGBWの設定
			//!テクスチャが表示されたら
			if (m_textureW >= m_textureWMaxValue)
			{

				player->SetPlayerTaskDay(false);//!フェードアウトに移行
			}

		}


	}

	void DateChangeCommentDay::TextureFadeOut()
	{
		if (m_IstexturemaxW == false)
		{
			if (m_textureW >= 0.0f)
			{
				auto ptrDraw = GetComponent<PCTSpriteDraw>();
				auto Diffuse = ptrDraw->GetDiffuse();				//!色の取得
				auto fadeOutTime = App::GetApp()->GetElapsedTime();	//!時間の取得
				m_textureW -= fadeOutTime / m_textureWSpeed;		//!フェードアウトスピード
				ptrDraw->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));//!テクスチャのRGBWの設定

			}


		}
	}

	void DateChangeCommentDay::OnUpdate()
	{
		TextureFadeIn();
		TextureFadeOut();
	}


}

