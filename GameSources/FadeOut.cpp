/*!
@file FadeOut.cpp
@briefフェードアウトの実体
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//ゲージ
	constexpr float m_fadeOutSpeed = 2.0f;
	FadeOut::FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)

	{}

	FadeOut::~FadeOut() {}
	void FadeOut::OnCreate() {



		//頂点配列
		m_BackupVertices = {
			//カラー　透明度
{ VertexPositionColor(Vec3(-m_StartScale.x,  m_StartScale.y, 0),Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(m_StartScale.x,  m_StartScale.y, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(-m_StartScale.x, -m_StartScale.y, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(m_StartScale.x, -m_StartScale.y, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//頂点とインデックスを指定してスプライト作成

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_StartPos);
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);

		//頂点とインデックスを指定してスプライト作成
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);




	}
	//点滅処理（Elapsedtimeを利用している）
	void FadeOut::OnUpdate() {

		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameOver = scene->GetGameOver();
		if (gameOver)
		{
			//時間の取得
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_TotalTime += elapsedTime;
			if (m_TotalTime >= XM_PI / m_fadeOutSpeed) {
				m_TotalTime = XM_PI / m_fadeOutSpeed;
			}
			//頂点の取得
			vector<VertexPositionColor> newVertices;
			for (size_t i = 0; i < m_BackupVertices.size(); i++) {
				Col4 col = m_BackupVertices[i].color;
				//sinで0～１までにして0の時は透明１の時は表示としている
				col.w = sin(m_TotalTime);
				auto v = VertexPositionColor(
					m_BackupVertices[i].position,
					col
				);
				newVertices.push_back(v);
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->UpdateVertices(newVertices);

		}

	}
}