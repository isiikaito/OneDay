/*!
@file Hunter.h
@brief ハンターの作成
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------
	//!ハンター
	//--------------------------------------------------------
	class Hunter :public GameObject
	{
	private:
		//ステートマシーン(状態を表す)
		unique_ptr< StateMachine<Hunter> >  m_StateMachine;
		Vec3  m_Position;//!位置
		Vec3 m_Rotation;//!回転
		Vec3 m_Scale;//!大きさ
		Vec3 m_Force;//!動きの力
		Vec3 m_Velocity;//!速度
		int m_Speed;//!スピード
		float m_StateChangeSize;	
		bool m_DedDecision;//!生死の判定
		Vec3 m_PEvector;//!プレイヤーと敵のベクトル
		std::vector<Vec3> m_patrolPoints;//!巡回ポイント
		int m_playerChange;//!プレイヤーの状態

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
       void ApplyForce();//!適応力
		//アクセサ
		const unique_ptr<StateMachine<Hunter>>& GetStateMachine() {
			return m_StateMachine;
		}

	   //!ハンターのスピードの取得
		int GetSpeed()const
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
			return m_DedDecision;
		}
		//!ハンターの生死の設定
		void SetDedDecision(bool DedDecision)
		{
			m_DedDecision = DedDecision;
		}

		//!ステートチェンジサイズ
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		//!行動の力の取得
		const Vec3& GetForce()const {
			return m_Force;
		}

		//!行動の力の設定
		void SetForce(const Vec3& f) {
			m_Force = f;
		}

		//!行動の力の配置
		void AddForce(const Vec3& f) {
			m_Force += f;
		}

		//!速度の取得
		const Vec3& GetVelocity()const {
			return m_Velocity;
		}

		//!速度の設定
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}

		shared_ptr<GameObject>  GetTarget()const;//!ターゲットの取得
		virtual void NearBehavior();//!ステートがプレイヤーから近い位置にあるときに毎ターン呼ばれる
		virtual void FarBehavior();//!ステートがプレイヤーから遠い位置にあるときに毎ターン呼ばれる
		virtual void OnCreate();//初期化
		virtual void OnUpdate();//!更新
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//プレイヤーとエネミーの衝突判定

	};

	//--------------------------------------------------------------------------------------
	//	プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class FarState : public ObjState<Hunter>
	{
		FarState() {}
	public:
		static shared_ptr<FarState> Instance();
		virtual void Enter(const shared_ptr<Hunter>& Obj)override;//!処理に入る
		virtual void Execute(const shared_ptr<Hunter>& Obj)override;//!処理を実行する
		virtual void Exit(const shared_ptr<Hunter>& Obj)override;//!処理を出る
	};

	//--------------------------------------------------------------------------------------
	//	 プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class NearState : public ObjState<Hunter>
	{
		NearState() {}
	public:
		static shared_ptr<NearState> Instance();
		virtual void Enter(const shared_ptr<Hunter>& Obj)override;
		virtual void Execute(const shared_ptr<Hunter>& Obj)override;
		virtual void Exit(const shared_ptr<Hunter>& Obj)override;
	};


}
//!end basecross
