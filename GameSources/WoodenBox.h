/**
*@file WoodenBox.h
*@brief 木箱の実装が定義されているヘッダーファイル
*@author Kaito isii
*@details 木箱の実装
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/**basecross共通のネームペース*/
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

	class WoodenBox : public GameObject {
	private:
		StaticModelDeta m_woodenBoxModelData;			//!木箱モデルデータ
		kaito::StateMachine<WoodenBox>* m_StateMachine;		//!プレイヤーのステートマシン

	public:
		//--------------------------------------------------------------------------------------
		/**
		* コンストラクタ
		*/
		WoodenBox(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		//--------------------------------------------------------------------------------------
		/**
　　　　* デストラクタ
　　　　*/
		virtual ~WoodenBox() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートマシンのアクセッサ
		@return ステートマシン
		*/
		const kaito::StateMachine<WoodenBox>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートの変更
		@引数　クラスに対応したステート
		*/
		virtual void ChangeState(kaito::State<WoodenBox>* NewState);

		//--------------------------------------------------------------------------------------
		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/**
　　　　* 更新
　　　　*/
		virtual void OnUpdate() override;
	};
}
