/*!
@file MyCamera.cpp
@brief カメラ実体
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
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraMan>(GetCameraObject());
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();
			SetAt(pos);
		}
		Camera::OnUpdate();
	};
}