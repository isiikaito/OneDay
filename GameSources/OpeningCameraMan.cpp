/*!
@file OpeningCamera.cpp
@brief オープニングカメラ
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCameraMan.h"
#include "OpeningCameraState.h"

namespace basecross {

	OpeningCameraMan::OpeningCameraMan(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),

		m_startPos(60.0f, 50.0f, 60.0f),
		m_endPos(-60.0f, 50.0f, 60.0f),
		m_AtStartPos(18.0f, 0.0f, 18.0f),
		m_AtEndPos(0.0f, 0.0f, 0.0f),
		m_AtPos(m_AtStartPos),
		m_totalTime(0.0f)

	{
		m_StateMachine = new kaito::StateMachine<OpeningCameraMan>(this);
		m_StateMachine->SetCurrentState(kaito::OpeningCameraPatrolState::Instance());
	}

	void OpeningCameraMan::OnCreate() {

		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_startPos);

	}

	void OpeningCameraMan::OnUpdate()
	{
		m_StateMachine->Update();
	}

	bool OpeningCameraMan::MoveCamera(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
		m_totalTime += ElapsedTime;							//!時間
		//!動く時間以上になったら
		if (m_totalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_startPos, m_endPos, m_totalTime, totaltime);//!ターゲットポジションの計算
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_totalTime, totaltime);//!視点の位置の計算
		auto OpeningCameraTrans = GetComponent<Transform>();											//!カメラのトランスフォームの取得
		OpeningCameraTrans->SetPosition(TgtPos);														//!カメラの位置の設定
		return false;
	}

	void OpeningCameraMan::ChangeState(kaito::State<OpeningCameraMan>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!ステートの変更
	}

	void OpeningCameraMan::OpeningCameraStatus(Vec3 StartPos, Vec3 EndPos, Vec3 AtStartPos, Vec3 AtEndPos, float TotalTime)
	{
		m_startPos = StartPos;
		m_endPos = EndPos;
		m_AtStartPos = AtStartPos;
		m_AtEndPos = AtEndPos;
		m_AtPos = AtStartPos;
		m_totalTime = 0.0f;
	}

}