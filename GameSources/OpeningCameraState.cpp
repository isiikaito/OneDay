/*!
@file OpeningCameraState.cpp
@brief オープニングカメラステート
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCameraState.h"

namespace basecross {

	namespace kaito
	{

		//!インスタンスの生成(実体の作成)
		OpeningCameraPatrolState* OpeningCameraPatrolState::Instance()
		{
			static OpeningCameraPatrolState instance;
			return &instance;
		}


		void OpeningCameraPatrolState::Enter(OpeningCameraMan* OpeningCamera)
		{
			m_startPos = Vec3(18.0f, 2.0f, 10.0f);
			m_endPos = Vec3(0.0f, 3.0f, -5.0f);
			m_atStartPos = Vec3(18.0f, 0.0f, 18.0f);
			m_atEndPos = Vec3(0.0f, 0.0f, 0.0f);
			m_totalTime = 0.0f;
			OpeningCamera->OpeningCameraStatus(m_startPos, m_endPos, m_atStartPos, m_atEndPos, m_totalTime);
		}

		void OpeningCameraPatrolState::Execute(OpeningCameraMan* OpeningCamera)
		{
			//!ステートチェンジ
			if (OpeningCamera->MoveCamera(3.0f))
			{
				OpeningCamera->ChangeState(OpeningCameraComebackStartState::Instance());//!ステートを変更する
			}
		}

		void OpeningCameraPatrolState::Exit(OpeningCameraMan* OpeningCamera)
		{}



		//-----------------------------------------------------------

		//!インスタンスの生成(実体の作成)
		OpeningCameraComebackStartState* OpeningCameraComebackStartState::Instance()
		{
			static OpeningCameraComebackStartState instance;
			return &instance;
		}

		void OpeningCameraComebackStartState::Enter(OpeningCameraMan* OpeningCamera) {
			m_startPos = Vec3(60.0f, 50.0f, -60.0f);
			m_endPos = Vec3(60.0f, 50.0f, 60.0f);
			m_atStartPos = Vec3(18.0f, 0.0f, 18.0f);
			m_atEndPos = Vec3(0.0f, 0.0f, 0.0f);
			m_totalTime = 0.0f;
			OpeningCamera->OpeningCameraStatus(m_startPos, m_endPos, m_atStartPos, m_atEndPos, m_totalTime);

		}

		void OpeningCameraComebackStartState::Execute(OpeningCameraMan* OpeningCamera)
		{
			//!ステートチェンジ
			if (OpeningCamera->MoveCamera(3.0f))
			{
				OpeningCamera->ChangeState(ChangeCameraState::Instance());//!ステートを変更する
			}
		}



		void OpeningCameraComebackStartState::Exit(OpeningCameraMan* OpeningCamera)
		{}

		//-------------------------------------------------------------------------
		//!インスタンスの生成(実体の作成)
		ChangeCameraState* ChangeCameraState::Instance()
		{
			static ChangeCameraState instance;
			return &instance;
		}

		void ChangeCameraState::Enter(OpeningCameraMan* OpeningCamera) {
			auto ptrGameGtage = OpeningCamera->GetTypeStage<GameStage>();
			ptrGameGtage->ToMyCamera();

		}

		void ChangeCameraState::Execute(OpeningCameraMan* OpeningCamera) {
		}

		void ChangeCameraState::Exit(OpeningCameraMan* OpeningCamera) {
		}

	}
}
