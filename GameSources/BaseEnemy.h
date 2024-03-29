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

	protected:
		//!ステートマシーン
		kaito::StateMachine<BaseEnemy>* m_StateMachine;	//!ステートマシンクラスのインスタンスの生成
		std::vector<Vec3>m_EnemyPatrolPoints;			//!敵の巡回ポイント
		Vec3 m_Force;									//!フォース
		Vec3 m_Velocity;								//!速度
		float m_MaxSpeed;								//!最大の速度
		int m_Enemypatorolindex;						//!敵の巡回ポイントの数
		int m_randomCount;								//!特定の値になると敵が周りを見渡す
		bool m_seekCondition;							//!敵が追いかけているかどうか
        bool m_loseSightOfTarget;						//!プレイヤーを見失っているとき
		bool m_SurprisedSprite;							//!プレイヤーを見つけた時
		bool m_IspositionLiset;							//!ポジションのリセット
		bool m_IsEnemyDed;								//!敵の死亡判定
		float m_eyeRange;								//!敵の視野の長さ
		float m_surprisedTime;							//!驚いている時間
		float m_rotationTime;							//!回転している速度
		float m_randomTime;								//!ランダムにするための時間
		bool m_patrolRotation;							//!巡回中に周りを見渡す
		bool m_dedAnimationEnd;							//!倒れたアニメーションが終わったかどうか
	protected:
		

		
		

		//--------------------------------------------------------------------------------------
		/*!
		@brief 適応力
		*/
		void ApplyForce();

		//--------------------------------------------------------------------------------------
		/*!
		@brief アニメーションの更新
		*/
		void AnimationUpdate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief 障害物を避ける行動
		*/
		void ObstacleAvoidance();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターの死体を消す処理
		*/
		void HunterDisappear();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村人の死体を消す処理
		*/
		void VillagerDisappear();

		//--------------------------------------------------------------------------------------
		/*!
		@brief 移動方向に向く処理
		*/
		void Facade();

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵のランダムで回転する
		*/
		void EnemyRandomRotation();


	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief  構造と破棄
		*/
		BaseEnemy(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		virtual ~BaseEnemy()noexcept = default;

		//--------------------------------------------------------------------------------------
		/*!
		@brief ステートマシーンのアクセッサ
		@return ステートマシンの情報を返す
		*/
		const kaito::StateMachine<BaseEnemy>* GetFSM()const
		{
			return m_StateMachine;
		}

		


		//--------------------------------------------------------------------------------------
		/*!
		@brief 力の取得
		@return	力
		*/
		const Vec3& GetForce()const
		{
			return m_Force;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 力の設定
		@param	力
		*/
		void SetForce(const Vec3& f)
		{
			m_Force = f;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 力の追加
		@param	力
		*/
		void AddForce(const Vec3& f)
		{
			m_Force += f;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 現在の速度の取得
		@return	現在の速度
		*/
		const Vec3& GetVelocity()const
		{
			return m_Velocity;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 現在の速度の設定
		@param	現在の速度
		*/
		void SetVelocity(const Vec3& v)
		{
			m_Velocity = v;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 最大の速度の取得
		@return	最大速度
		*/
		float GetMaxSpeed() const
		{
			return m_MaxSpeed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 最大の速度の設定
		@param	最大の速度
		*/
		void SetMaxSpeed(float MaxSpeed)
		{
			m_MaxSpeed = MaxSpeed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の巡回ポイントの取得
		@return 敵の巡回ポイント
		*/
		std::vector<Vec3>GetEnemyPatorolPoints()const
		{
			return m_EnemyPatrolPoints;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の巡回ポイントの設定
		@param	敵の巡回ポイント
		*/
		void SetpatorolPoints(const std::vector<Vec3>& path)
		{
			m_EnemyPatrolPoints = path;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の巡回ポイント数の取得
		@return 敵の巡回ポイント
		*/
		int GetEnemyPatorolindex() const
		{
			return m_Enemypatorolindex;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の巡回ポイント数の設定
		@param	敵の巡回ポイント数
		*/
		void SetEnemyPatorolindex(int& patrolindex)
		{
			m_Enemypatorolindex = patrolindex;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵がプレイヤーを見失ったとき取得
		@return 敵がプレイヤーを見失っているかどうか
		*/
		bool GetloseSightOfTarget() const
		{
			return m_loseSightOfTarget;
		}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵がプレイヤーを見失ったときの設定
		@param	敵がプレイヤーを見失ったとき
		*/
		void SetloseSightOfTarget( bool loseSightOfTarget)
		{
			m_loseSightOfTarget = loseSightOfTarget;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵がプレイヤーを追いかけている状態の取得
		@return 敵がプレイヤーを追いかけている状態
		*/
		bool GetseekCondition() const
		{
			return m_seekCondition;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵がプレイヤーを追いかけている状態の設定
		@param	敵がプレイヤーを追いかけている状態
		*/
		void SetseekCondition(bool seekCondition)
		{
			m_seekCondition = seekCondition;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーの位置のリセットの取得
		@return	プレイヤーの位置のリセットするかどうか
		*/
		bool GetIspositionLiset() const
		{
			return m_IspositionLiset;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーの位置のリセットの設定
		@param	プレイヤーの位置のリセット
		*/
		void SetIspositionLiset(bool IspositionLiset)
		{
			m_IspositionLiset= IspositionLiset;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の生死の取得
		@return	敵の生死
		*/
		bool GetIsEnemyDed() const
		{
			return m_IsEnemyDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief　敵の生死の設定
		@param	敵の生死
		*/
		void SetIsEnemyDed(bool IsEnemyDed)
		{
			m_IsEnemyDed = IsEnemyDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の視野の取得
		@return	敵の視野
		*/
		float GetEyeRang() const
		{
			return m_eyeRange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵の視野の設定
		@param	敵の視野
		*/
		void SetEyeRang(float eyeRange)
		{
			m_eyeRange = eyeRange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵がプレイヤーを見つけた時の取得
		@return 敵がプレイヤーを見つけたかどうか
		*/
		bool GetSurprisedSprite() const
		{
			return m_SurprisedSprite;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief 敵がプレイヤーを見つけた時の設定
		@param	敵がプレイヤーを見つけたかどうか
		*/
		void SetSurprisedSprite(bool SurprisedSprite)
		{
			m_SurprisedSprite = SurprisedSprite;
		}

		
		//--------------------------------------------------------------------------------------
		/*!
		@brief 死んだときのアニメーションが終わっているかどうか
		@param	死んだときのアニメーションが終わっているかどうか
		*/
		void SetDedAnimationEnd(bool dadAnimationend)
		{
			m_dedAnimationEnd = dadAnimationend;
		}

		

		//--------------------------------------------------------------------------------------
		/*!
		@brief ステートの変更
		@param	変更するステート
		*/
		virtual void ChangeState(kaito::State<BaseEnemy>* NewState);

		//--------------------------------------------------------------------------------------
		/*!
		@brief ターゲットの取得
		*/
		shared_ptr<Player>GetTarget()const;

		
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief　更新の処理
		*/
		virtual void OnUpdate()override;
	};

}
