/*!
@file OpeningCameraMan.h
@brief オープニングカメラ
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
		Vec3 m_startPos;
		Vec3 m_endPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_totalTime;
	public:
		//!ステートマシーンのアクセッサ
		const kaito::StateMachine<OpeningCameraMan>* GetFSM()const
		{
			return m_StateMachine;
		}
		//構築と破棄
		OpeningCameraMan(const shared_ptr<Stage>& StagePtr);
		void OpeningCameraStatus(Vec3 StartPos, Vec3 EndPos, Vec3 AtStartPos, Vec3 AtEndPos, float TotalTime);
		virtual ~OpeningCameraMan() {}
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;

		bool MoveCamera(float totaltime);




		Vec3 GetAtPos() const {
			return m_AtPos;
		}


		//!ステートの変更
		virtual void ChangeState(kaito::State<OpeningCameraMan>* NewState);

	};
}
