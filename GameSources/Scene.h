/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
	private:

		int m_keyNamber;				//!鍵を保存しているCSVを識別する数字
		int m_AlertlevelCount;			//!警戒度の数字
		bool m_IsGameOver;				//!ゲームオーバーしたかどうか
		bool m_IsGameOverSprite;		//!ゲームオーバースプライトの表示ができているか
		float m_gameStageTime;			//!昼と夜の時間
		int m_meatNumber;				//!肉の位置が保存されたCSVの数字
		int m_date;						//!現在の日付
		bool m_IsplayerChangeDirecting;	//!プレイヤーの変身するかどうか
		float m_dayTime;				//!一日の時間
		float m_playerConditionTime;	//!プレイヤーの状態の時間
		bool m_gameStrat;				//!ゲームのスタート
		float m_emissiveChangeTime;		//!ライトタイム
		int m_descriptionStageNumber;	//!説明書のページ数
		bool m_IsmoveForwardInaPage;	//!ページを進ませているかどうか
		bool m_IspageBackTo;			//!ページを戻しているかどうか
		bool m_goleGateParameter;		//!ゴールステージの時の門のパラメータを適応する
		float m_soundvolume;			//!効果音の大きさ

	public:
		//----------------------------------------------------------------------(----------------
		/*!
		@brief リソース
		*/
		void CreateResourses();

		//----------------------------------------------------------------------(----------------
		/*!
		@brief コンストラクタ
		*/
		Scene() :SceneBase(),
			m_goleGateParameter(false),
			m_IsmoveForwardInaPage(true),
			m_IspageBackTo(true),
			m_AlertlevelCount(0),
			m_emissiveChangeTime(1.0f),
			m_date(0),
			m_playerConditionTime(0.0f),
			m_IsplayerChangeDirecting(0.0f),
			m_IsGameOver(false),
			m_dayTime(0.0f),
			m_IsGameOverSprite(false),
			m_gameStageTime(0.0f),
			m_keyNamber(0),
			m_meatNumber(0),
			m_gameStrat(true),
			m_descriptionStageNumber(0),
			m_soundvolume(0.7f)

		{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		virtual ~Scene();

		//--------------------------------------------------------------------------------------	
		/*!
		@brief 初期化
		@return	なし
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief 警戒度の取得
		@return	警戒度のカウント
		*/
		int GetAlertlevelCount() const
		{
			return m_AlertlevelCount;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 警戒度の設定
		@param 警戒度
		@return	なし
		*/
		void SetAlertlevelCount(int AlertlevelCount);

		//--------------------------------------------------------------------------------------
		/*!
		@brief 追加の敵の作成
		@return	なし
		*/
		void CreateEnemy();

		//--------------------------------------------------------------------------------------
		/*!
		@brief ゲームオーバーの取得
		@return	ゲームオーバーしたかどうか
		*/
		bool GetGameOver() const
		{
			return m_IsGameOver;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ゲームオーバーの設定
		@param ゲームオーバーかどうか
		@return	　なし
		*/
		void SetGameOver(bool gameOver)
		{
			m_IsGameOver = gameOver;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ゲームオーバースプライト表示の取得
		@return	ゲームオーバーしたかどうか
		*/
		bool GetGameOverSprite() const
		{
			return m_IsGameOverSprite;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ゲームオーバースプライト表示の設定
		@param ゲームオーバースプライト表示
		@return	なし
		*/
		void SetGameOverSprite(bool gameOverSprite)
		{
			m_IsGameOverSprite = gameOverSprite;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 鍵のcsvのナンバーの取得
		@return	ゲームオーバーしたかどうか
		*/
		int GetKeyNamber() const
		{
			return m_keyNamber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 鍵のcsvのナンバーの設定
		@param 鍵のcsvのナンバー
		@return	なし
		*/
		void SetKeyNamber(int keyNamber)
		{
			m_keyNamber = keyNamber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ゲームの時間の取得
		@return ゲームの時間
		*/
		float GetGameTime() const
		{
			return m_gameStageTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ゲームの時間の設定
		@param ゲームの時間
		*/
		void SetGameTime(float gameStageTime)
		{
			m_gameStageTime = gameStageTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 鍵のcsvのナンバーの取得
		@return	ゲームオーバーしたかどうか
		*/
		int GetMeatNamber() const
		{
			return m_meatNumber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 日付の設定
		@param 日付
		*/
		void SetDate(int Date)
		{
			m_date = Date;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 日付の取得
		@return	現在の日付
		*/
		int GetDate() const
		{
			return m_date;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 肉のcsvのナンバーの設定
		@param 肉のcsvのナンバー
		*/
		void SetMeatNamber(int MeatNamber)
		{
			m_meatNumber = MeatNamber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief テクスチャの読み込み
		@param テクスチャの名前
		@param[in] 使うときのテクスチャの名前
		*/
		void RoadTexture(const wstring& TextureName, const wstring& UseTextureName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief サウンドの読み込み
		@param 音の名前
		@param[in] 使うときの音の名前
		*/
		void RoadSound(const wstring& soundDataName, const wstring& soundName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief スタティックモデルの読み込み
		@param スタティックモデルbmfの名前
		@param[in] 使うときのスタティックモデルの名前
		*/
		void RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief ボーンモデルのの読み込み
		@param ボーンモデルのbmfの名前
		@param[in] ボーンモデルのメッシュの名前
		@param[in out] 使うときのボーンモデルの名前
		*/
		void RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーが変身するかどうかの取得
		@return	プレイヤーが変身するかどうか
		*/
		bool GetPlayerChangeDirecting() const
		{
			return m_IsplayerChangeDirecting;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーの見た目を変更する時間の設定
		@param プレイヤーの見た目を変更する時間
		*/
		void SetPlayerChangeDirecting(bool PlayerChangeDirecting)
		{
			m_IsplayerChangeDirecting = PlayerChangeDirecting;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief 日にちの取得
		@return	現在の日にち
		*/
		float GetDayTime() const
		{
			return m_dayTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 一日の時間の設定
		@param 一日の時間
		*/
		void SetDayTime(float DayTime)
		{
			m_dayTime = DayTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　プレイヤーの状態の時間の取得
		@return プレイヤーの状態の時間を返す
		*/
		float GetPlayerConditionTime() const
		{
			return m_playerConditionTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　プレイヤーの状態の時間の設定
		@param プレイヤーの状態の時間
		*/
		void SetPlayerConditionTime(float PlayerConditionTime)
		{
			m_playerConditionTime = PlayerConditionTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ゲームがスタートしたことを伝える
		@return ゲームがスタートしたかどうか
		*/
		bool GetGameStrat() const
		{
			return m_gameStrat;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ゲームスタートしたときの設定
		@param ゲームスタートしたかどうか
		*/
		void SetGameStrat(bool gameStrat)
		{
			m_gameStrat = gameStrat;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　エミッシブカラーの変わる時間の取得
		@return オブジェクトの明るさ変更
		*/
		float GetEmissiveChangeTime() const
		{
			return m_emissiveChangeTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　エミッシブカラーの変わる時間の設定
		@param エミッシブカラーの変わる時間
		*/
		void SetEmissiveChangeTime(float emissiveChangeTime)
		{
			m_emissiveChangeTime = emissiveChangeTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　説明書のページ数
		@return 説明書のページ数を返す
		*/
		int GetDescriptionStageNumber() const
		{
			return m_descriptionStageNumber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　説明書のページ数の設定
		@param 説明書のページ数
		*/
		void SetDescriptionStageNumber(int descriptionStageNumber)
		{
			m_descriptionStageNumber = descriptionStageNumber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ページをめくっているかどうかの取得
		*/
		bool GetIsMoveForwardInaPage() const
		{
			return m_IsmoveForwardInaPage;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ページをめくっているかどうかの設定
		@param ページをめくっているかどうか
		*/
		void SetIsMoveForwardInaPage(bool IsmoveForwardInaPage)
		{
			m_IsmoveForwardInaPage = IsmoveForwardInaPage;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief　ページを戻しているかどうか
		*/
		bool GetIspageBackTo() const
		{
			return m_IspageBackTo;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ページをもどしているかどうかの設定
		@param ページをもどしているかどうか
		*/
		void SetIsPageBackTo(bool IspageBackTo)
		{
			m_IspageBackTo = IspageBackTo;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ゴールパラメータの門を適用するかどうか
		*/
		bool GetGoleGateParameter() const
		{
			return m_goleGateParameter;

		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　ゴールパラメータの門を適用するかどうか
		@param ゴールパラメータの門を適用するかどうか
		*/
		void SetGoleGateParameter(bool goleGateParameter)
		{
			m_goleGateParameter = goleGateParameter;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーが変身するかどうかの取得
		*/
		float GetSoundvolume() const
		{
			return m_soundvolume;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 音量の設定
		@param 音量
		*/
		void SetSoundvolume(float soundvolume)
		{
			m_soundvolume = soundvolume;
		}
	};

}

//end basecross