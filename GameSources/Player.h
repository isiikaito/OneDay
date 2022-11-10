/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

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
		float m_Speed;             //!スピード
		float m_idleTime;          //!時間
		int m_playerChange;//!プレイヤーの見た目の状態
		int m_KeyCount;//!鍵を持っている個数カウント
		const float m_humanTime;//!人間の時間
		const float m_wolfTime;//!狼の時間
		const int m_reset;//1ループリセット

		InputHandler<Player> m_InputHandler;  //コントローラーのボタンの取得
		InputHandlerB<Player> m_InputHandlerB;

	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() ;
        Vec2 GetInputState() const;//!プレイヤーが使用するコントローラーの入力
		Vec3 GetMoveVector() const;//!コントローラから方向ベクトルを得る
		void MovePlayer();         //!プレイヤーの移動
		void Villagerkiller();//!村人を殺す処理
		void AppearanceChange();//!プレイヤーの見た目の変化
		void OnPushA(){}//!//コントローラーのボタン判定A
		void OnPushB();
		int GetPlayerCange()const
		{
			return m_playerChange;
		}
		void SetPlayerChange(int playerChange)
		{
			m_playerChange = playerChange;
		}

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//プレイヤーとカギの衝突判定
	};
}
//end basecross

