/*!
@file Hunter.h
@brief ハンターの作成
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	
	//--------------------------------------------------------
	//!ハンター
	//--------------------------------------------------------
	class Enemy :public GameObject
	{

		//ステートマシーン(状態を表す)
		unique_ptr< StateMachine<Enemy> >  m_StateMachine;
		Vec3  m_StartPos;//!スタートポジション
		Vec3 m_Force;//!動きの力
		Vec3 m_Velocity;//!速度
		float m_StateChangeSize;
		void ApplyForce();//!適応力
		Vec3 PEvector;



	protected:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Enemy();
	public:

		//アクセサ
		const unique_ptr<StateMachine<Enemy>>& GetStateMachine() {
			return m_StateMachine;
		}

		//!スタートポジションを取得する
		Vec3 GetStartPos() const {
			return m_StartPos;
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
		virtual void NearBehavior() = 0;//!ステートがプレイヤーから近い位置にあるときに毎ターン呼ばれる
		virtual void FarBehavior() = 0;//!ステートがプレイヤーから遠い位置にあるときに毎ターン呼ばれる
		virtual void OnCreate();//初期化
		virtual void OnUpdate();//!更新

	};

	//--------------------------------------------------------------------------------------
	//	プレイヤーから遠いときの移動
	//--------------------------------------------------------------------------------------
	class FarState : public ObjState<Enemy>
	{
		FarState() {}
	public:
		static shared_ptr<FarState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;//!処理に入る
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;//!処理を実行する
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;//!処理を出る
	};

	//--------------------------------------------------------------------------------------
	//	 プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class NearState : public ObjState<Enemy>
	{
		NearState() {}
	public:
		static shared_ptr<NearState> Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;
	};


	//--------------------------------------------------------------------------------------
	//!パスを巡回する配置オブジェクト
	//--------------------------------------------------------------------------------------
	class Hunter : public Enemy {
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Hunter(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Hunter();

		virtual void OnCreate() override;//!初期化
		//操作
		virtual void NearBehavior() override;//!ステートが近い時
		virtual void FarBehavior() override;//!ステートが遠い時
	};

}
//!end basecross
