/*!
@file OpeningCameraState.cpp
@brief オープニングカメラステート
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCameraState.h"

namespace basecross {
	constexpr float CHANGESTATETIME = 3.0f;//!カメラの移動時間
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
			OpeningCamera->OpeningCameraStatus(m_startPos, m_endPos, m_atStartPos, m_atEndPos, m_totalTime);
		}

		void OpeningCameraPatrolState::Execute(OpeningCameraMan* OpeningCamera)
		{
			//!ステートチェンジ
			if (OpeningCamera->MoveCamera(CHANGESTATETIME))
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
			
			OpeningCamera->OpeningCameraStatus(m_startPos, m_endPos, m_atStartPos, m_atEndPos, m_totalTime);

		}

		void OpeningCameraComebackStartState::Execute(OpeningCameraMan* OpeningCamera)
		{
			//!ステートチェンジ
			if (OpeningCamera->MoveCamera(CHANGESTATETIME))
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
