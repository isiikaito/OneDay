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
	class Player : public GameObject
	{
		Vec2 GetInputState() const;//!プレイヤーが使用するコントローラーの入力
		Vec3 GetMoveVector() const;//!コントローラから方向ベクトルを得る
		void MovePlayer();         //!プレイヤーの移動
		float m_Speed;             //!スピード
		float m_idleTime;          //!時間

		InputHandler<Player> m_InputHandler;  //コントローラーのボタンの取得

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
		void OnPushA();//!//コントローラーのボタン判定A

	};
}
//end basecross

