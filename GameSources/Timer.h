/**
*@file Time.h
*@brief 時間経過を表示が定義されているヘッダーファイル
*@author Kaito Isii
*@details ステージ開始時からゴールまでにかかった時間の表示
*/

#pragma once
#include "stdafx.h"

/** basecross共通のネームスペース */
namespace basecross {

	class Timer : public GameObject {
	private:
		bool m_Trace;				//!透明
		Vec2 m_StartScale;			//!大きさ
		Vec3 m_StartPos;			//!位置
		wstring m_TextureKey;		//!テクスチャ
		float m_Score;				//!数字
		UINT m_NumberOfDigits;		//!桁数
		Vec2 m_LeftUpperSummit;		//!左上の頂点
		Vec2 m_LeftLowerSummit;		//!左下の頂点
		Vec2 m_RightUpperSummit;	//!右上の頂点
		Vec2 m_RightLowerSummit;	//!右下の頂点


		vector<VertexPositionTexture> m_BackupVertices;//!バックアップ頂点データ

		
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~Timer() {}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	経過した時間を更新
		@param	現在の時間
		*/
		void SetScore(float f) {
			m_Score = f;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	桁ごとの数字の取得
		@param[out] verNum 何番目の頂点かを判別する
		@param[in] num 桁の中の数字を取得する
		@param[out] newVertices 位置とテクスチャを持つ頂点の定義
		*/
		void SetUVPos(int& verNum, UINT num, vector<VertexPositionTexture>& newVertices);


		//--------------------------------------------------------------------------------------
		/*!
		@brief	数字のテクスチャの初期化をする関数
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	数字のテクスチャの更新をする関数
		*/
		virtual void OnUpdate();

	};
}
//end basecross