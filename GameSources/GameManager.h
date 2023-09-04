/*!
@file GameManager.h
@brief ゲームステージ時間マネージャー
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "Player.h"
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
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameManager:public GameObject
	{
		
	private:
		kaito::StateMachine<GameManager>* m_StateMachine;		//!プレイヤーのステートマシン


	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		GameManager(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステージ時間の取得
		@retrun	時間を返す
		*/
		static float GetElpasedTiem() ;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	変身する時間の取得
		@retrun	時間を返す
		*/
		static float GetDayTiem();


		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートマシンのアクセッサ
		@return ステートマシン
		*/
		const kaito::StateMachine<GameManager>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステートの変更
		@引数　クラスに対応したステート
		*/
		virtual void ChangeState(kaito::State<GameManager>* NewState);


		//--------------------------------------------------------------------------------------
		/*!
		@brief プレイヤーの取得
		*/
		shared_ptr<Player>GetPlayer()const;

		virtual void OnUpdate() override;
	};
}
//end basecross


