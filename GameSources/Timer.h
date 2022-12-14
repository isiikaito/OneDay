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
		bool m_Trace;         //!透明
		Vec2 m_StartScale;    //!大きさ
		Vec3 m_StartPos;      //!位置
		wstring m_TextureKey; //!テクスチャ
		float m_Score;        //!数字
		UINT m_NumberOfDigits;//!桁数

		vector<VertexPositionTexture> m_BackupVertices;//!バックアップ頂点データ

		
	public:

		/**
		* コンストラクタ
		*/
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~Timer() {}

		/**
　　　　* 経過した時間を更新して変数にいれている
　　　　*
　　　　* @return float 経過した時間を返している
　　　　*/
		void SetScore(float f) {
			m_Score = f;
		}
        /**
		* 桁ごとの数字の取得
		* @param[out] verNum 何番目の頂点かを判別する
		* @param[in] num 桁の中の数字を取得する
		* @param[out] newVertices 位置とテクスチャを持つ頂点の定義
		*/
		void SetUVPos(int& verNum, UINT num, vector<VertexPositionTexture>& newVertices);

		/**
		* 数字のテクスチャの初期化をする関数
		*/
		virtual void OnCreate() override;

		/**
		* 時間の経過に合わせて数字の更新をする関数
		*/
		virtual void OnUpdate();

	};
}
//end basecross