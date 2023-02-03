/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//Aボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
			}
		}
	};

	template<typename T>
	struct InputHandlerB {
		void PushHandleB(const shared_ptr<T>& Obj)
		{
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected)
			{
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					Obj->OnPushB();
				}
			}

		}


	};

	template<typename T>
	struct InputHandlerCrossKey
	{
		void PushHandleCrossKey(const shared_ptr<T>&Obj)
		{
			//!コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected)
			{
				//!十字キーの右
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					Obj->PushHandleCrossRight();
				}

				//!十字キーの左
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					Obj->PushHandleCrossLeft();
				}
			}
		}
	};
}

//end basecrossuy
