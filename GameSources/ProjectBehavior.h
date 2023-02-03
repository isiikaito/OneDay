/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//A�{�^��
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
			//!�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected)
			{
				//!�\���L�[�̉E
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					Obj->PushHandleCrossRight();
				}

				//!�\���L�[�̍�
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					Obj->PushHandleCrossLeft();
				}
			}
		}
	};
}

//end basecrossuy
