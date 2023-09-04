/*!
@file StateMchine.h
@brief ステートマシン
@author Kaito Isii
*/
#pragma once
#include"stdafx.h"
namespace basecross
{
	namespace kaito
	{
		template<class entity_type>
		class State
		{
		public:
			State(){}
			virtual~State(){}

			//!純粋仮想関数
			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートに入ったときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Enter(entity_type*) = 0;

			//--------------------------------------------------------------------------------------
			/*!
			@brief	更新ステップごとに自分のステートを更新する関数によって呼ばれる
			@param	ステートを実装しているクラス
			*/
			virtual void Execute(entity_type*) = 0;	

			//--------------------------------------------------------------------------------------
			/*!
			@brief	ステートを出るときに一度呼ばれる処理
			@param	ステートを実装しているクラス
			*/
			virtual void Exit(entity_type*) = 0;

		};

		//!StateMachineクラス
		template<class entity_type>
		class StateMachine
		{
		private:
			entity_type* m_Owner;				//!このインスタンスを所持するエージェントへのポインタ
			State<entity_type>* m_CurrentState;	//!現在のステート
			State<entity_type>* m_PreviousState;//!エージェントの直前のステートの記録

		public:
			StateMachine(entity_type* owner) :
				m_Owner(owner),
				m_CurrentState(NULL),
				m_PreviousState(NULL)
			{}

			//!有限状態機械を初期化するときに関数を使う
			void SetCurrentState(State<entity_type>* s) { m_CurrentState = s; }
			void SetPreviousState(State<entity_type>* s) { m_PreviousState }

			//!有限状態機械を初期化するときに関数を使う
			void Update()const
			{
				if (m_CurrentState)m_CurrentState->Execute(m_Owner);//!現在と同じステートがあるならExeuteを呼ぶ

			}

			void ChangeState(State<entity_type>* NewState)
			{
				assert(NewState&&"<StateMachine::ChangeState::trying to change to a null sate>");//!新しいステートあ入っていればtrue入っていなければfalse
				m_PreviousState = m_CurrentState;	//!以前のステートを記録する
				m_CurrentState->Exit(m_Owner);		//!存在するステートの終了関数を呼ぶ
				m_CurrentState = NewState;			//!新しいステートに変更する
				m_CurrentState->Enter(m_Owner);		//!新しいステートの開始関数を呼ぶ

			}
			void RevertToPreviousState()
			{
				ChangeState(m_PreviousState);

			}

			//!アクセサ
			State<entity_type>* CurrentState()const { return m_CurrentState; }
			State<entity_type>* PreviousState()const { return m_PreviousState; }

			bool isInstate(const State<entity_type>& st)const {};//!現在のステートの型とパラメータで渡されたクラスの型が同じならtrueを返す

		};
	}
}