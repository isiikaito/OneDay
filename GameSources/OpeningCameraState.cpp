/*!
@file OpeningCameraState.cpp
@brief �I�[�v�j���O�J�����X�e�[�g
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCameraState.h"

namespace basecross {

	namespace kaito
	{

		//!�C���X�^���X�̐���(���̂̍쐬)
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
			//!�X�e�[�g�`�F���W
			if (OpeningCamera->MoveCamera(3.0f))
			{
				OpeningCamera->ChangeState(OpeningCameraComebackStartState::Instance());//!�X�e�[�g��ύX����
			}
		}

		void OpeningCameraPatrolState::Exit(OpeningCameraMan* OpeningCamera)
		{}



		//-----------------------------------------------------------

		//!�C���X�^���X�̐���(���̂̍쐬)
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
			//!�X�e�[�g�`�F���W
			if (OpeningCamera->MoveCamera(3.0f))
			{
				OpeningCamera->ChangeState(ChangeCameraState::Instance());//!�X�e�[�g��ύX����
			}
		}



		void OpeningCameraComebackStartState::Exit(OpeningCameraMan* OpeningCamera)
		{}

		//-------------------------------------------------------------------------
		//!�C���X�^���X�̐���(���̂̍쐬)
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
