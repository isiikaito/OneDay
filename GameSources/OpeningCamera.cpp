/*!
@file MyCamera.cpp
@brief カメラ実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCamera.h"
#include "OpeningCameraMan.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	オープニングカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	OpeningCamera::OpeningCamera() :
		Camera()
	{}
	OpeningCamera::~OpeningCamera() {}

	void OpeningCamera::OnUpdate() {
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraMan>(GetCameraObject());//!カメラマンの取得
		//!オープニングカメラ
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();	//!ポジションの取得
			SetAt(pos);									//!ポジションの更新
		}
		Camera::OnUpdate();
	};
}