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
			Vec3 m_startPos = Vec3(18.0f, 2.0f, 10.0f);
			Vec3 m_endPos = Vec3(0.0f, 3.0f, -5.0f);
			Vec3 m_atStartPos = Vec3(18.0f, 0.0f, 18.0f);
			Vec3 m_atEndPos = Vec3(0.0f, 0.0f, 0.0f);
			float m_totalTime = 0.0f;

		public:
			static OpeningCameraPatrolState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g�ɓ������Ƃ��Ɏ��s
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g�ɓ����Ă���Ԏ��s
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g����o��Ƃ����s

		};

		class OpeningCameraComebackStartState : public State<OpeningCameraMan>
		{
			OpeningCameraComebackStartState() {}
			//!�V���O���g���p�^�[��
			OpeningCameraComebackStartState(const OpeningCameraComebackStartState&) = delete;
			OpeningCameraComebackStartState& operator =(const OpeningCameraComebackStartState&) = delete;
			Vec3 m_startPos = Vec3(60.0f, 50.0f, -60.0f);
			Vec3 m_endPos = Vec3(60.0f, 50.0f, 60.0f);
			Vec3 m_atStartPos = Vec3(18.0f, 0.0f, 18.0f);
			Vec3 m_atEndPos = Vec3(0.0f, 0.0f, 0.0f);
			float m_totalTime = 0.0f;

		public:
			static OpeningCameraComebackStartState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g�ɓ������Ƃ��Ɏ��s
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g�ɓ����Ă���Ԏ��s
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g����o��Ƃ����s
		};
		//!�I�[�v�j���O�J�������I�������
		class ChangeCameraState : public State<OpeningCameraMan>
		{
			ChangeCameraState() {}
			//!�V���O���g���p�^�[��
			ChangeCameraState(const ChangeCameraState&) = delete;
			ChangeCameraState& operator =(const ChangeCameraState&) = delete;
			

		public:
			static ChangeCameraState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g�ɓ������Ƃ��Ɏ��s
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g�ɓ����Ă���Ԏ��s
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;	//!�X�e�[�g����o��Ƃ����s
		};

	}
}
