/*!
@file OpeningCameraState.h
@brief オープニングカメラステート
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
		//!オープニングカメラが追従しているとき
		class OpeningCameraPatrolState :public State<OpeningCameraMan>
		{

		private:
			OpeningCameraPatrolState() {}
			//!シングルトンパターン
			OpeningCameraPatrolState(const OpeningCameraPatrolState&) = delete;
			OpeningCameraPatrolState& operator =(const OpeningCameraPatrolState&) = delete;
			Vec3 m_startPos = Vec3(18.0f, 2.0f, 10.0f);
			Vec3 m_endPos = Vec3(0.0f, 3.0f, -5.0f);
			Vec3 m_atStartPos = Vec3(18.0f, 0.0f, 18.0f);
			Vec3 m_atEndPos = Vec3(0.0f, 0.0f, 0.0f);
			float m_totalTime = 0.0f;

		public:
			static OpeningCameraPatrolState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;	//!ステートに入ったときに実行
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;	//!ステートに入っている間実行
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;	//!ステートから出るとき実行

		};

		class OpeningCameraComebackStartState : public State<OpeningCameraMan>
		{
			OpeningCameraComebackStartState() {}
			//!シングルトンパターン
			OpeningCameraComebackStartState(const OpeningCameraComebackStartState&) = delete;
			OpeningCameraComebackStartState& operator =(const OpeningCameraComebackStartState&) = delete;
			Vec3 m_startPos = Vec3(60.0f, 50.0f, -60.0f);
			Vec3 m_endPos = Vec3(60.0f, 50.0f, 60.0f);
			Vec3 m_atStartPos = Vec3(18.0f, 0.0f, 18.0f);
			Vec3 m_atEndPos = Vec3(0.0f, 0.0f, 0.0f);
			float m_totalTime = 0.0f;

		public:
			static OpeningCameraComebackStartState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;	//!ステートに入ったときに実行
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;	//!ステートに入っている間実行
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;	//!ステートから出るとき実行
		};
		//!オープニングカメラが終わったら
		class ChangeCameraState : public State<OpeningCameraMan>
		{
			ChangeCameraState() {}
			//!シングルトンパターン
			ChangeCameraState(const ChangeCameraState&) = delete;
			ChangeCameraState& operator =(const ChangeCameraState&) = delete;
			

		public:
			static ChangeCameraState* Instance();

			virtual void Enter(OpeningCameraMan* OpeningCamera) override;	//!ステートに入ったときに実行
			virtual void Execute(OpeningCameraMan* OpeningCamera) override;	//!ステートに入っている間実行
			virtual void Exit(OpeningCameraMan* OpeningCamera) override;	//!ステートから出るとき実行
		};

	}
}
