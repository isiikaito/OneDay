/*!
@file OpeningCameraMan.h
@brief オープニングカメラ
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
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	class OpeningCameraMan : public GameObject {
	private:
		kaito::StateMachine<OpeningCameraMan>* m_StateMachine;//!ステートマシンクラスのインスタンスの生成
		Vec3 m_startPos;	//!スタートポジション
		Vec3 m_endPos;		//!終わりのポジション
		Vec3 m_AtStartPos;	//!視点の始まりの位置
		Vec3 m_AtEndPos;	//!視点の終わり位置
		Vec3 m_AtPos;		//!視点の位置
		float m_totalTime;	//!カメラの時間
	public:
		//!ステートマシーンのアクセッサ
		const kaito::StateMachine<OpeningCameraMan>* GetFSM()const
		{
			return m_StateMachine;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		OpeningCameraMan(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	オープニングカメラの設定
		*/
		void OpeningCameraStatus(Vec3 StartPos, Vec3 EndPos, Vec3 AtStartPos, Vec3 AtEndPos, float TotalTime);
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~OpeningCameraMan() {}
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate() override;
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	動くカメラ
		@return カメラを使うかどうか
		*/
		bool MoveCamera(float totaltime);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	視点の位置を取得
		@return 視点の位置
		*/
		Vec3 GetAtPos() const {
			return m_AtPos;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステート変更
		*/
		virtual void ChangeState(kaito::State<OpeningCameraMan>* NewState);

	};
}
