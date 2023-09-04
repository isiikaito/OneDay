/*!
@file PlayerMoveComponent.h
@author Kaito Isii
@brief  プレイヤーの動く処理
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross 
{

	class PlayerMoveComponent :public Component
	{
		float m_Speed;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プレイヤーの移動
		*/
		void MovePlayer();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラーの情報
		@return 左スティックのxy座標
		*/
		Vec2 GetControlerInformation() const;

		

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	このコンポーネントを所持するゲームオブジェクト
		*/
		explicit PlayerMoveComponent(
			const shared_ptr<GameObject>& GameObjectPtr):
			Component(GameObjectPtr),
			m_Speed(20.0f) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~PlayerMoveComponent(){}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラから方向ベクトルを得る
		@return コントローラから方向ベクトル
		*/
		Vec3 GetMoveVector() const;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	スピードの取得
		@retrun プレイヤーのスピード
		*/
		float GetSpeed() const
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
		@brief	更新処理
		*/
		virtual void OnUpdate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}
