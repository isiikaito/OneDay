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
		int m_playerChange;				 //!プレイヤーの状態
		float m_Speed;					 //!スピード
		int m_patrolindex;				 //!巡回ポイント
		BoneModelDeta m_enemyBoneModelDeta;				//!敵のモデルデータ

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



		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターのスピードの取得
		@return ハンターのスピード
		*/
		float GetSpeed() const
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターのスピードの設定
		@param	ハンターのスピード
		*/
		void SetSpeed(float HunterSpeed)
		{
			m_Speed = HunterSpeed;
		}

		

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
