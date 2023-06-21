/*!
@file Player.h
@brief プレイヤーなど
*@author isii kaito
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	namespace kaito
	{
		//!前方宣言
		template<class entity_type>
		class State;
		//!前方宣言
		template <class entity_type>
		class StateMachine;
	}

	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	enum class PlayerModel {
		human,
		wolf
	};


	class Player : public GameObject
	{
	private:

		Vec3 m_scale;					//!大きさ
		Vec3 m_rotation;				//!回転
		Vec3 m_position;				//!位置
		int m_playerChange;				//!プレイヤーの見た目の状態
		int m_KeyCount;					//!鍵を持っている個数カウント
		int m_AlertleveCount;			//!警戒度のカウント
		int m_MaxKeyCount;				//!鍵の所持数の最大
		const float m_Ded;				//!死亡
		int m_PlayerPositionOnSecondMax;//!プレイヤーの位置の配列の最大の長さ
		int m_PlayerHp;					//!プレイヤーの体力
		int m_meatCount;				//!肉を取得した数
		const int m_reset;				//1ループリセット
		float m_wolfPlayerSpeed;		//!狼男になったときのスピード
		float m_humanPlayerSpeed;		//!人間の時のスピード
		float m_PlayerPositionTime;		//!プレイヤーの位置を取得するまでの時間
		float m_wolfHowlingTime;		//!狼男が鳴く時間
		float m_dedTime;				//!プレイヤーが死んでからの時間
		float m_Speed;					//!スピード
		float m_ChangeTime;				//!時間
		float m_vibrationTime;			//!振動している時間
		float m_GetPlayerPositionTime;	//!プレイヤーの位置の取得
		const float m_humanTime;		//!人間の時間
		const float m_wolfTime;			//!狼の時間
		bool m_playerTaskDay;			//!昼のミッションの表示
		bool m_playerTaskNight;			//!夜のミッションの表示
		bool m_IsPlayerFound;			//!プレイヤーが見つかった稼働羽化
		bool m_IsPlayerDed;				//!プレイヤーが死んだかどうかの判定
		bool m_IsFastHowling;			//!初めて狼男が鳴くとき
		bool m_IsvibrationOn;			//!振動しているかどうか
		bool m_gameOverDrawActive;		//!ゲームオーバースプライトの表示
		bool m_IsPlayerChangeEffect;	//プレイヤーが狼に変身した時のエフェクト
		InputHandlerB<Player> m_InputHandlerB;		//!コントローラーのボタンの取得B
		std::vector<Vec3>m_PlayerPositionOnSecond;	//!プレイヤーの毎秒ごとの位置の取得
		kaito::StateMachine<Player>* m_StateMachine;//!プレイヤーのステートマシン
		float m_gameTime;							//!ゲームの時間
		WORD m_vibration;							//コントローラーの振動
		Vec3 m_meatPosition = Vec3(0);				//!肉のポジション
		
		//エフェクト
		shared_ptr<EfkEffect> m_KeyEfkEffect;		//鍵を取った時のエフェクト
		shared_ptr<EfkEffect> m_ScratchEfkEffect;	//攻撃した時のエフェクト
		shared_ptr<EfkEffect> m_TransformEfkEffect;	//狼に変身した時のエフェクト
		shared_ptr<EfkEffect> m_MeatEfkEffect;		//狼に変身した時のエフェクト
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_KeyEfkPlay;
		shared_ptr<EfkPlay> m_ScratchEfkPlay;
		shared_ptr<EfkPlay> m_TransformEfkPlay;
		shared_ptr<EfkPlay> m_MeatEfkPlay;


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
		@brief	プレイヤーが使用するコントローラーの入力
		@return スティックの情報
		*/
		Vec2 GetInputState() const;//!プレイヤーが使用するコントローラーの入力

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラから方向ベクトルを得る
		@return コントローラから方向ベクトル
		*/
		Vec3 GetMoveVector() const;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの移動
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
		@brief	脱出処理
		*/
		void Escape();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラーのボタン判定B
		*/
		void OnPushB();

		shared_ptr<SoundItem>m_Wolk;
		shared_ptr<SoundItem>m_Howling;


		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの状態の取得
		@retrun プレイヤーの状態
		*/
		int GetPlayerCange()const
		{
			return m_playerChange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの状態の設定
		@引数　プレイヤーの状態
		*/
		void SetPlayerChange(int playerChange)
		{
			m_playerChange = playerChange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	毎秒ごとのプレイヤーの位置の取得
		@retrun 毎秒ごとのプレイヤーの位置
		*/
		std::vector<Vec3>GetPlayerPositionOnSecond()const
		{
			return m_PlayerPositionOnSecond;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	毎秒ごとのプレイヤーの位置の設定
		@引数　毎秒ごとのプレイヤーの位置
		*/
		void SetPlayerPositionOnSecond(const std::vector<Vec3>PlayerPositionOnSecond)
		{
			m_PlayerPositionOnSecond = PlayerPositionOnSecond;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーのHP取得
		@retrun プレイヤーのHP
		*/
		int GetPlayerHp()
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
		@brief	プレイヤーが見つかった判定の取得
		@retrun　プレイヤーが見つかったかどうか
		*/
		bool GetPlayerFound()
		{
			return m_IsPlayerFound;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーが見つかった判定の設定
		@引数　プレイヤーが見つかった判定
		*/
		void SetPlayerFound(bool PlayerFound)
		{
			m_IsPlayerFound = PlayerFound;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	スピードの取得
		@retrun プレイヤーのスピード
		*/
		float GetSpeed()
		{
			return m_Speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	スピードの設定
		@引数　プレイヤーのスピード
		*/
		void SetSpeed(float speed)
		{
			m_Speed = speed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーが死んだかどうかの取得
		@retrun プレイヤーが死んだかどうか
		*/
		bool GetIsplayerDed()
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
		@brief	ゲームオーバースプライトを表示するかの取得
		@retrun ゲームオーバースプライトを表示するかどうか
		*/
		bool GetGameOverDrawActive()
		{
			return m_gameOverDrawActive;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオーバースプライトを表示するかの設定
		@引数　ゲームオーバースプライトを表示するかどうか
		*/
		void SetGameOverDrawActive(bool gameOverDrawActive)
		{
			m_gameOverDrawActive = gameOverDrawActive;
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
		@brief	ゲームステージの時間
		@return ゲームステージの時間
		*/
		float GetGameTime()
		{
			return m_gameTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームステージの時間
		@引数　ゲームステージの時間
		*/
		void SetGameTime(float gameTime)
		{
			m_gameTime = gameTime;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーとカギの衝突判定
		@引数　ゲームオブジェクト
		*/
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);


		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーが死んだ時の処理
		*/
		void PlayerDed();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオーバーの処理
		*/
		void PlayerGameOver();

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
		@brief	コントローラの振動処理
		*/
		void Controllervibration();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉を取った数の取得
		@return 食べた肉の数
		*/
		int GetMeatCount()
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
		int GetKeyCount()
		{
			return m_KeyCount;
		}

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
		@brief	昼のプレイヤーのタスクの取得
		*/
		bool GetPlayerTaskDay()
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
		bool GetPlayerTaskNight()
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
		@brief	変身エフェクトの取得
		@return 変身エフェクト
		*/
		shared_ptr<EfkEffect>GetTransformEfkEffect()
		{
			return m_TransformEfkEffect;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	変身エフェクトの設定
		*/
		void SetTransformEfkPlay(shared_ptr<EfkPlay> TransformEfkPlay)
		{
			m_TransformEfkPlay = TransformEfkPlay;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉の取得エフェクトの取得
		@return 肉の取得エフェクト
		*/
		shared_ptr<EfkEffect>GetMeatEfkEffect()
		{
			return m_MeatEfkEffect;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉の取得エフェクトの設定
		*/
		void SetMeatEfkPlay(shared_ptr<EfkPlay> MeatEfkPlay)
		{
			m_MeatEfkPlay = MeatEfkPlay;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	肉のポジション取得
		@return 肉のポジション
		*/
		Vec3 GetMeatPosition()
		{
			return m_meatPosition;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	攻撃エフェクト
		*/
		void AttackEffect();

		
	};
}
//end basecross

