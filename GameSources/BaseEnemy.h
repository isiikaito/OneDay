/*!
@file BaseEnemy.h
@brief 敵の作成
@autohor isii kaito
*/
#pragma once
#include "stdafx.h"

//!抽象クラス
namespace basecross
{
	namespace kaito
	{
		//!前方宣言
		template<class entity_type>
		class State;
		//!前方宣言
		template <class entity_type>
		class StateMachine;
	}

	class BaseEnemy :public GameObject
	{
		//!ステートマシーン
		kaito::StateMachine<BaseEnemy>* m_StateMachine;//!ステートマシンクラスのインスタンスの生成
		std::vector<Vec3>m_EnemyPatrolPoints;//!敵の巡回ポイント
		Vec3 m_Force;//!フォース
		Vec3 m_Velocity;//!速度
		float m_StateChangeSize;//!ステートの変更
		float m_MaxSpeed;//!最大の速度
		int m_Enemypatorolindex;//!敵の巡回ポイントの数
		bool m_seekCondition;//!敵が追いかけているかどうか
        bool m_loseSightOfTarget;//!プレイヤーを見失っているとき
		bool m_IspositionLiset;//!ポジションのリセット
	protected:
		

		//!構造と破棄
		BaseEnemy(const shared_ptr<Stage>& StagePtr);

		//!デストラクタ
		virtual ~BaseEnemy()noexcept = default;

	public:
		//!アクセッサ

		//!ステートマシーンのアクセッサ
		const kaito::StateMachine<BaseEnemy>* GetFSM()const
		{
			return m_StateMachine;
		}
		//!ステートを変更する長さの取得
		float GatStateChangeSize()const
		{
			return m_StateChangeSize;
		}

		//!ステートを変更する長さの設定
		void SetStageChangeSize(float& ChangeSize)
		{
			m_StateChangeSize = ChangeSize;
		}

		//!力の取得
		const Vec3& GetForce()const
		{
			return m_Force;
		}

		//!力の設定
		void SetForce(const Vec3& f)
		{
			m_Force = f;
		}

		//!力の追加
		void AddForce(const Vec3& f)
		{
			m_Force += f;
		}

		//!現在の速度の取得
		const Vec3& GetVelocity()const
		{
			return m_Velocity;
		}

		//!現在の速度の設定
		void SetVelocity(const Vec3& v)
		{
			m_Velocity = v;
		}

		//!最大の速度の取得
		float& GetMaxSpeed()
		{
			return m_MaxSpeed;
		}

		//!最大の速度の取得
		void SetMaxSpeed(float& MaxSpeed)
		{
			m_MaxSpeed = MaxSpeed;
		}

		//!敵の巡回ポイントの取得
		std::vector<Vec3>GetEnemyPatorolPoints()const
		{
			return m_EnemyPatrolPoints;
		}

		//!敵の巡回ポイントの設定
		void SetpatorolPoints(const std::vector<Vec3>& path)
		{
			m_EnemyPatrolPoints = path;
		}

		//!敵の巡回ポイント数の取得
		int GetEnemyPatorolindex()
		{
			return m_Enemypatorolindex;
		}

		//!敵の巡回ポイント数の設定
		void SetEnemyPatorolindex(int& patrolindex)
		{
			m_Enemypatorolindex = patrolindex;
		}

		//!敵がプレイヤーを見失ったとき取得
		bool GetloseSightOfTarget()
		{
			return m_loseSightOfTarget;
		}
		
		//!敵がプレイヤーを見失ったときの設定
		void SetloseSightOfTarget( bool loseSightOfTarget)
		{
			m_loseSightOfTarget = loseSightOfTarget;
		}

		//!敵がプレイヤーを追いかけている状態の取得
		bool GetseekCondition()
		{
			return m_seekCondition;
		}

		//!敵がプレイヤーを追いかけている状態の設定
		void SetseekCondition(bool seekCondition)
		{
			m_seekCondition = seekCondition;
		}

		//!プレイヤーの位置のリセットの取得
		bool GetIspositionLiset()
		{
			return m_IspositionLiset;
		}

		//!プレイヤーの位置のリセットの設定
		void SetIspositionLiset(bool IspositionLiset)
		{
			m_IspositionLiset= IspositionLiset;
		}

		
		//!適応力
		void ApplyForce();

		//!ステートの変更
		virtual void ChangeState(kaito::State<BaseEnemy>* NewState);

		//!ターゲットの取得
		shared_ptr<Player>GetTarget()const;

		//!初期化の処理
		virtual void OnCreate()override ;

		//!更新の処理
		virtual void OnUpdate()override;
	};

}
