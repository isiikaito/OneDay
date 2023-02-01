/*!
@file DateChangeCommentNight.cpp
@author Kaito Isii
@brief  矢印の表示
*/


#include "stdafx.h"
#include "Project.h"
#include "DateChangeCommentNight.h"

namespace basecross
{
	constexpr int first = 1;
	constexpr int second = 2;
	constexpr float m_textureWSpeed = 2;
	constexpr float m_textureWMaxValue = 1.0f;
	constexpr float m_startScaleZ = 1.0f;
	constexpr float m_startPosZ = 0.1f;
	constexpr float m_helfSize = 0.5f;

	//--------------------------------------------------------------------------------------
	///	昼から夜に変わる時のコメント
	//--------------------------------------------------------------------------------------

	DateChangeCommentNight::DateChangeCommentNight(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0),
		m_IstexturemaxW(true),
		m_textureW(0.0f),
		m_totalTime(0.0f)
	{}

	void DateChangeCommentNight::OnCreate()
	{
		float HelfSize = m_helfSize;

		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_startScaleZ);
		ptrTransform->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_startPosZ); // 0.1が手前、0.9は奥

		//頂点とインデックスを指定してスプライト作成
		m_drawComponent = AddComponent<PCTSpriteDraw>(vertices, indices);
		m_drawComponent->SetSamplerState(SamplerState::LinearWrap);
		m_drawComponent->SetTextureResource(m_TextureKey);
		SetDrawActive(true);

	}

	void DateChangeCommentNight::TextureFadeIn()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//!プレイヤーの取得
		auto playerCondition = player->GetPlayerCange();//!プレイヤーの状態の取得
		 m_IstexturemaxW = player->GetPlayerTaskNight();
		//!人間状態の時
			//!フェードアウトを開始するとき
			if (m_IstexturemaxW == true)
			{
				auto Diffuse = m_drawComponent->GetDiffuse();//!色の取得
				auto fadeinTime = App::GetApp()->GetElapsedTime();//!時間の取得
				m_textureW += fadeinTime / m_textureWSpeed;//!フェードアウトのスピード
				m_drawComponent->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));//!テクスチャのRGBWの設定
				//!テクスチャが表示されたら
				if (m_textureW >= m_textureWMaxValue)
				{

					
					player->SetPlayerTaskNight(false);//!フェードアウトに移行
				}
			}

		
	}

	void DateChangeCommentNight::TextureFadeOut()
	{
		if (m_IstexturemaxW == false)
		{
			if (m_textureW >= 0.0f)
			{
				auto Diffuse = m_drawComponent->GetDiffuse();//!色の取得
				auto fadeOutTime = App::GetApp()->GetElapsedTime();//!時間の取得
				m_textureW -= fadeOutTime / m_textureWSpeed;//!フェードアウトスピード
				m_drawComponent->SetDiffuse(Col4(Diffuse.x, Diffuse.y, Diffuse.z, m_textureW));//!テクスチャのRGBWの設定
			}
		}
	}

	void DateChangeCommentNight::OnUpdate()
	{
		TextureFadeIn();
		TextureFadeOut();
	}



}
