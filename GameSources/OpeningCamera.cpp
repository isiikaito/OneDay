/*!
@file MyCamera.cpp
@brief �J��������
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "OpeningCamera.h"
#include "OpeningCameraMan.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�I�[�v�j���O�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	OpeningCamera::OpeningCamera() :
		Camera()
	{}
	OpeningCamera::~OpeningCamera() {}

	void OpeningCamera::OnUpdate() {
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraMan>(GetCameraObject());//!�J�����}���̎擾
		//!�I�[�v�j���O�J����
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();	//!�|�W�V�����̎擾
			SetAt(pos);									//!�|�W�V�����̍X�V
		}
		Camera::OnUpdate();
	};
}