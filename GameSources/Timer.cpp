/*!
@file Timer.cpp
@brief 時間の操作
*/

#include "stdafx.h"
#include "Project.h"
#include "Timer.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	スコア表示のスプライト
	//--------------------------------------------------------------------------------------
	//!スプライトの初期設定
	Timer::Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(0.0f)
	{}

	void Timer::OnCreate() {

		float xPiecesize = 1.0f / (float)m_NumberOfDigits;//!桁数ごとの位置
		float helfSize = 0.5f;                            //!桁ごとの大きさの半分

		//!インデックス配列
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -helfSize + xPiecesize * (float)i;//!左側の頂点
			float vertex1 = vertex0 + xPiecesize;             //!右側の頂点
			//!0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, helfSize, 0), Vec2(0.0f, 0.0f))//!頂点データ1
			);
			//!1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, helfSize, 0), Vec2(0.1f, 0.0f))//!頂点データ2
			);
			//!2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -helfSize, 0), Vec2(0.0f, 1.0f))//!頂点データ3
			);
			//!3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -helfSize, 0), Vec2(0.1f, 1.0f))//!頂点データ4
			);
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_Trace);                                 //!透明度
		auto ptrTrans = GetComponent<Transform>();               //!トランスコンポーネントの取得
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);//!大きさの設定
		ptrTrans->SetRotation(0, 0, 0);                          //!回転の設定
		ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0.1f); //!位置の設定
		//!頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);//!描画コンポーネントの取得
		ptrDraw->SetTextureResource(m_TextureKey);                           //!テクスチャの設定
		GetStage()->SetSharedGameObject(L"Time", GetThis<Timer>());         //!シェアドオブジェクトに読み込ませる
	}


	void Timer::SetUVPos(int& verNum, UINT num, vector<VertexPositionTexture>& newVertices)
	{

		Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;                 //!テクスチャの始まりの頂点データと位置
		uv0.x = (float)num / 10.0f;                                            //!取得した数字の位置に頂点を合わせる
		auto v = VertexPositionTexture(m_BackupVertices[verNum].position, uv0);//!テクスチャの頂点の位置
		newVertices.push_back(v);                                              //!取得した頂点の位置をnewVertcesの後ろに追加している

		verNum++;
		Vec2 uv1 = m_BackupVertices[verNum].textureCoordinate;
		uv1.x = uv0.x + 0.1f;
		v = VertexPositionTexture(
			m_BackupVertices[verNum].position,
			uv1
		);
		newVertices.push_back(v);

		verNum++;
		Vec2 uv2 = m_BackupVertices[verNum].textureCoordinate;
		uv2.x = uv0.x;

		v = VertexPositionTexture(
			m_BackupVertices[verNum].position,
			uv2
		);
		newVertices.push_back(v);
		verNum++;
		Vec2 uv3 = m_BackupVertices[verNum].textureCoordinate;
		uv3.x = uv0.x + 0.1f;

		v = VertexPositionTexture(
			m_BackupVertices[verNum].position,
			uv3
		);
		newVertices.push_back(v);

		verNum++;
	}

	void Timer::OnUpdate() {

		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		//!時間の数を取得
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(10, i);//!powは乗算という意味である。iは今処理している桁数が代入されている
			num = ((UINT)m_Score) % base;//!余りを出して少数切り捨て
			num = num / (base / 10);     //!残った数字がその桁に入る

			SetUVPos(verNum, num, newVertices);



		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();//!描画コンポーネント
		ptrDraw->UpdateVertices(newVertices);       //!頂点データの更新
	}



	

}
//end basecross
