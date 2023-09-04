/*!
@file FadeOut.cpp
@briefフェードアウトの実体
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "GameOver.h"
namespace basecross {
	//ゲージ
	constexpr float FADEOUTSPEED = 2.0f;//!フェイドアウトする時間
	FadeOut::FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_TextureColor(Col4(0.0f, 0.0f, 0.0f, 0.0f))

	{}

	FadeOut::~FadeOut() {}
	void FadeOut::OnCreate() {



		//頂点配列
		m_BackupVertices = {
			//カラー　透明度
		{ VertexPositionColor(Vec3(-m_StartScale.x,  m_StartScale.y, 0),m_TextureColor) },
		{ VertexPositionColor(Vec3(m_StartScale.x,  m_StartScale.y, 0), m_TextureColor) },
		{ VertexPositionColor(Vec3(-m_StartScale.x, -m_StartScale.y, 0), m_TextureColor) },
		{ VertexPositionColor(Vec3(m_StartScale.x, -m_StartScale.y, 0), m_TextureColor) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//頂点とインデックスを指定してスプライト作成

		auto ptrTrans = GetComponent<Transform>();								//!トランスフォームの取得
		ptrTrans->SetPosition(m_StartPos);										//!位置の設定
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);	//!描画コンポーネントの取得
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);					//!頂点とインデックスを指定してスプライト作成
	}
	//点滅処理（Elapsedtimeを利用している）
	void FadeOut::OnUpdate() {

		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto gameOver = scene->GetGameOverSprite();//!ゲームオーバーかどうかの取得
		if (gameOver)
		{
			float elapsedTime = App::GetApp()->GetElapsedTime();//!時間の取得
			m_TotalTime += elapsedTime;							//!時間の更新
			//!フェイドアウトを終えていたら
			if (m_TotalTime >= XM_PI / FADEOUTSPEED) 
			{
				m_TotalTime = XM_PI / FADEOUTSPEED;			//!フェイドアウトのまま
				auto gameOverSprite = GetStage()->GetSharedGameObject<GameOverSprite>(L"GameOverSprite");
				gameOverSprite->SetDrawActive(true);
			
			}
			vector<VertexPositionColor> newVertices;			//!頂点の取得

			//!頂点の数分回す
			for (size_t i = 0; i < m_BackupVertices.size(); i++)
			{
				Col4 col = m_BackupVertices[i].color;	//!頂点の色の取得
				col.w = sin(m_TotalTime);				//sinで0～１までにして0の時は透明１の時は表示としている
				auto v = VertexPositionColor
				(
					m_BackupVertices[i].position,		//!頂点の位置
					col									//!頂点の色
				);
				newVertices.push_back(v);				//!更新した頂点を配列に入れる
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();//!描画コンポーネントの取得
			ptrDraw->UpdateVertices(newVertices);		//!頂点の更新

		}

	}
}