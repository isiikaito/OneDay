/*!
@file OpeningCameraState.h
@brief �I�[�v�j���O�J�����X�e�[�g
*@author isii kaito
*/

#include "stdafx.h"
#include "StateMchine.h"
#include "OpeningCameraMan.h"
#include "Player.h"

namespace basecross
{
	namespace kaito
	{
		//!�I�[�v�j���O�J�������Ǐ]���Ă���Ƃ�
		class OpeningCameraPatrolState :public State<OpeningCameraMan>
		{

		private:
			OpeningCameraPatrolState() {}
			//!�V���O���g���p�^�[��
			OpeningCameraPatrolState(const OpeningCameraPatrolState&) = delete;
			OpeningCameraPatrolState& operator =(const OpeningCameraPatrolState&) = delete;
			Vec3 m_startPos;
			Vec3 m_endPos;
			Vec3 m_atStartPos;
			Vec3 m_atEndPos;
			Vec3 m_atPos;
			float m_totalTime = 0.0f;

		public:
			static OpeningCameraPatrolState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;
			bool MoveCamera(OpeningCameraMan* OpeningCamera, float totaltime);
		};

		class OpeningCameraComebackStartState : public State<OpeningCameraMan>
		{
			OpeningCameraComebackStartState() {}
			//!�V���O���g���p�^�[��
			OpeningCameraComebackStartState(const OpeningCameraComebackStartState&) = delete;
			OpeningCameraComebackStartState& operator =(const OpeningCameraComebackStartState&) = delete;
			Vec3 m_startPos;
			Vec3 m_endPos;
			Vec3 m_atStartPos;
			Vec3 m_atEndPos;
			Vec3 m_atPos;
			float m_totalTime = 0.0f;

		public:
			static OpeningCameraComebackStartState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;
		};

		class ChangeCameraState : public State<OpeningCameraMan>
		{
			ChangeCameraState() {}
			//!�V���O���g���p�^�[��
			ChangeCameraState(const ChangeCameraState&) = delete;
			ChangeCameraState& operator =(const ChangeCameraState&) = delete;
			Vec3 m_startPos;
			Vec3 m_endPos;
			Vec3 m_atStartPos;
			Vec3 m_atEndPos;
			Vec3 m_atPos;
			float m_totalTime = 0.0f;

		public:
			static ChangeCameraState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;
		};

	}
}
