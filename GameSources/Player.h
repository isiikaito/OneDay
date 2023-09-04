/*!
@file Player.h
@brief プレイヤーなど
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "MoveComponent.h"
#include "BoneModelComponent.h"
#include "EffectManager.h"


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

	enum class PlayerModel {
		human,
		wolf
	};


	class Player : public GameObject
	{
	private:

		PlayerModel m_playerChange;							//!プレイヤーの見た目の状態
		int m_KeyCount;										//!鍵を持っている個数カウント
		const float m_Ded;									//!死亡
		int m_PlayerPositionOnSecondMax;					//!プレイヤーの位置の配列の最大の長さ
		int m_PlayerHp;										//!プレイヤーの体力
		int m_meatCount;									//!肉を取得した数
		const int m_reset;									//1ループリセット
		float m_PlayerPositionTime;							//!プレイヤーの位置を取得するまでの時間
		float m_vibrationTime;								//!振動している時間
		float m_GetPlayerPositionTime;						//!プレイヤーの位置の取得
		bool m_playerTaskDay;								//!昼のミッションの表示
		bool m_playerTaskNight;								//!夜のミッションの表示
		bool m_IsPlayerDed;									//!プレイヤーが死んだかどうかの判定
		bool m_IsvibrationOn;								//!振動しているかどうか
		std::vector<Vec3>m_PlayerPositionOnSecond;			//!プレイヤーの毎秒ごとの位置の取得
		kaito::StateMachine<Player>* m_StateMachine;		//!プレイヤーのステートマシン
		WORD m_vibration;									//!コントローラーの振動
		Vec3 m_meatPosition = Vec3(0);						//!肉のポジション
		std::weak_ptr<PlayerMoveComponent> m_playermove;	//!プレイヤーを動かすコンポーネント
		BoneModelDeta m_playerBoneModelDeta;				//!プレイヤーのモデルデータ
		std::weak_ptr<BcPNTnTBoneModelDraw>	m_draw;			//!描画
		EffectManager* m_effectManager;						//!エフェクトマネージャー

		shared_ptr<SoundItem>m_Wolk;						//!歩く音
		shared_ptr<SoundItem>m_Howling;						//!オオカミの鳴き声


		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーを動かす
		*/
		void MovePlayer();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村人を殺す処理
		*/
		void Villagerkiller();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ハンターを殺す処理
		*/
		void Hunterkiller();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーのポジションを一定数取得の処理
		*/
		void GetPlayerPositionBrett();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	敵を倒したときの音
		*/
		void EnemyDedSound();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	木箱の破壊の処理
		*/
		void BreakWoodBox();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	1週間で死ぬ処理
		*/
		void OneWeek();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	攻撃エフェクト
		*/
		void AttackEffect();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラの振動処理
		*/
		void Controllervibration();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in] StagePtr	ステージ
		*/
		Player(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~Player() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラーのボタン判定B
		*/
		void OnPushB();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	エフェクトマネージャーの取得
		*/
		EffectManager* GetEffectManager()
		{
			return m_effectManager;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの状態の取得
		@retrun プレイヤーの状態
		*/
		PlayerModel GetPlayerChange()const
		{
			return m_playerChange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	足音の取得
		@retrun 足音
		*/
		shared_ptr<SoundItem> GetWolkSound()
		{
			return 	m_Wolk;

		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	脱出処理
		*/
		void Escape();


		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの状態の設定
		@引数　プレイヤーの状態
		*/
		void SetPlayerChange(PlayerModel playerChange)
		{
			m_playerChange = playerChange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	毎秒ごとのプレイヤーの位置の取得
		@retrun 毎秒ごとのプレイヤーの位置
		*/
		const std::vector<Vec3>& GetPlayerPositionOnSecond() const
		{
			return m_PlayerPositionOnSecond;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	毎秒ごとのプレイヤーの位置の設定
		@retrun	毎秒ごとのプレイヤーの位置
		*/
		void SetPlayerPositionOnSecond(const std::vector<Vec3>& PlayerPositionOnSecond)
		{
			m_PlayerPositionOnSecond = PlayerPositionOnSecond;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーのHP取得
		@retrun プレイヤーのHP
		*/
		int GetPlayerHp() const
		{
			return m_PlayerHp;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーのHPの設定
		@引数　プレイヤーのhP
		*/
		void SetPlayerHp(int PlayerHp)
		{
			m_PlayerHp = PlayerHp;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	スピードの取得
		@retrun プレイヤーのスピード
		*/
		float GetSpeed() const
		{
			return m_playermove.lock()->GetSpeed();
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	スピードの設定
		@引数　プレイヤーのスピード
		*/
		void SetSpeed(float speed)
		{
			m_playermove.lock()->SetSpeed(speed);
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーが死んだかどうかの取得
		@retrun プレイヤーが死んだかどうか
		*/
		bool GetIsplayerDed() const
		{
			return m_IsPlayerDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーが死んだかどうかの取得
		@引数　プレイヤーが死んだかどうか
		*/
		void SetIsplayerDed(bool playerDed)
		{
			m_IsPlayerDed = playerDed;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラーの振動するかの設定
		@引数　コントローラーが振動するかどうか
		*/
		void SetVibrationOn(bool VibrationOn)
		{
			m_IsvibrationOn = VibrationOn;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーとカギの衝突判定
		@引数　ゲームオブジェクト
		*/
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートマシンのアクセッサ
		@return ステートマシン
		*/
		const kaito::StateMachine<Player>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートの変更
		@引数　クラスに対応したステート
		*/
		virtual void ChangeState(kaito::State<Player>* NewState);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉を取った数の取得
		@return 食べた肉の数
		*/
		int GetMeatCount() const
		{
			return m_meatCount;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉を取った数の設定
		@引数　食べた肉の数
		*/
		void SetMeatCount(int MeatCount)
		{
			m_meatCount = MeatCount;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	カギを取った数の取得
		@return 取得したカギの数
		*/
		int GetKeyCount() const
		{
			return m_KeyCount;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	昼のプレイヤーのタスクの取得
		*/
		bool GetPlayerTaskDay() const
		{
			return m_playerTaskDay;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	昼のプレイヤーのタスクの設定
		*/
		void SetPlayerTaskDay(bool PlayerTaskDay)
		{
			m_playerTaskDay = PlayerTaskDay;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	夜のプレイヤーのタスクの取得
		*/
		bool GetPlayerTaskNight() const
		{
			return m_playerTaskNight;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	夜のプレイヤーのタスクの設定
		*/
		void SetPlayerTaskNight(bool PlayerTaskNight)
		{
			m_playerTaskNight = PlayerTaskNight;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉のポジション取得
		@return	肉のポジション
		*/
		Vec3 GetMeatPosition() const
		{
			return m_meatPosition;
		}

	};
}

//end basecross

