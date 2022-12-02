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
		Vec3  m_Position;//!位置
		Vec3 m_Rotation;//!回転
		Vec3 m_Scale;//!大きさ
	    int m_playerChange;//!プレイヤーの状態
		int m_Speed;//!スピード
		int m_patrolindex;
		float m_StateChangeSize;	
		bool m_dedDecision;//!生死の判定
		

	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
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
		//--------------------------------------------------------------------------------------
		virtual ~Hunter();
	public:
     
	
	   //!ハンターのスピードの取得
		int GetSpeed()
		{
			return m_Speed;
	    }

		//!ハンターのスピードの設定
		void SetSpeed(int HunterSpeed)
		{
			m_Speed = HunterSpeed;
		}

		//!ハンターの生死の判定の取得
		bool GetDedDecision()const
		{
			return m_dedDecision;
		}
		//!ハンターの生死の設定
		void SetDedDecision(bool DedDecision)
		{
			m_dedDecision = DedDecision;
		}

		//!ステートチェンジサイズ
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

	
		
		
		virtual void OnCreate();//初期化
		virtual void OnUpdate();//!更新
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//プレイヤーとエネミーの衝突判定

	};

	

}
//!end basecross
