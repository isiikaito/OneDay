/*!
@file OpeningCameraState.cpp
@brief �I�[�v�j���O�J�����X�e�[�g
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCameraState.h"

namespace basecross {
	constexpr float CHANGESTATETIME = 3.0f;//!�J�����̈ړ�����
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
			OpeningCamera->OpeningCameraStatus(m_startPos, m_endPos, m_atStartPos, m_atEndPos, m_totalTime);
		}

		void OpeningCameraPatrolState::Execute(OpeningCameraMan* OpeningCamera)
		{
			//!�X�e�[�g�`�F���W
			if (OpeningCamera->MoveCamera(CHANGESTATETIME))
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
			
			OpeningCamera->OpeningCameraStatus(m_startPos, m_endPos, m_atStartPos, m_atEndPos, m_totalTime);

		}

		void OpeningCameraComebackStartState::Execute(OpeningCameraMan* OpeningCamera)
		{
			//!�X�e�[�g�`�F���W
			if (OpeningCamera->MoveCamera(CHANGESTATETIME))
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
