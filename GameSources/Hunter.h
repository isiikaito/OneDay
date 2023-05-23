#pragma once
/*!
@file Hunter.h
@brief ハンターの作成
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "BaseEnemy.h"
namespace basecross
{
	//--------------------------------------------------------
	//!ハンター
	//--------------------------------------------------------
	class Hunter :public BaseEnemy
	{
	private:

		std::vector<Vec3> m_patrolPoints;//!巡回ポイント
		Vec3  m_Position;				 //!位置
		Vec3 m_Rotation;				 //!回転
		Vec3 m_Scale;					 //!大きさ
		int m_playerChange;				 //!プレイヤーの状態
		float m_Speed;					 //!スピード
		int m_patrolindex;				 //!巡回ポイント
		float m_StateChangeSize;		 //!ステートを切り替える大きさ
		bool m_playerDed;				 //!プレイヤーの死亡
		bool m_IsGameOver;				 //!ゲームオーバーしたかどうかの判定
		float m_dedTime;				 //!死んでからの時間
		int m_damage;					 //!ダメージを与える
									    

	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		Hunter(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const std::vector<Vec3>& patrolPoints
		);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~Hunter(){}
	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターのスピードの取得
		@return ハンターのスピード
		*/
		float GetSpeed()
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターのスピードの設定
		@引数　 ハンターのスピード
		*/
		void SetSpeed(float HunterSpeed)
		{
			m_Speed = HunterSpeed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートチェンジサイズの取得
		@return ステートチェンジサイズ
		*/
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの死亡判定の取得
		@return プレイヤーの死亡判定
		*/
		bool GetPlayerDed()
		{
			return m_playerDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの死亡判定の設定
		@引数 　プレイヤーの死亡判定

		*/
		void SetPlayerDed(bool playerDed)
		{
			m_playerDed = playerDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーを捕まえる
		*/
		void PlayerCatch();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターが死んだとき
		*/
		void HunterDed();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate();

	};



}
//!end basecross
