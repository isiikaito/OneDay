/*!
@file MyCamera.cpp
@brief �J��������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
		//	MyCamera�J�����i�R���|�[�l���g�ł͂Ȃ��j
		//--------------------------------------------------------------------------------------
		//�\�z�Ɣj��
	MyCamera::MyCamera() :
		Camera(),
		m_ToTargetLerp(1.0f),     //!�ڕW��ǂ�������ۂ̕�Ԓn
		m_TargetToAt(0, 0, 0),    //!�ڕW���王�_�𒲐�����ʒu�x�N�g��
		m_RadY(0.5f),             //!�J������Y���̈ʒu
		m_RadXZ(0),               //!�J������Z���̈ʒu
		m_CameraUpDownSpeed(2.0f),//!�J�����̏㉺�X�r�[�h
		m_CameraUnderRot(0.1f),   //!�J�����������鉺���p�x
		m_ArmLen(5.0f),           //!�r�̒����̐ݒ�
		m_MaxArm(100.0f),          //!�r�̍ő�̒���
		m_MinArm(20.0f),           //!�r�̍ŏ��̒���
		m_RotSpeed(1.0f),         //!��]�X�s�[�h
		m_ZoomSpeed(0.5f),        //!�X���[�Y�X�s�[�h
		m_LRBaseMode(true),       //!���E�X�e�B�b�N�ύX�̃��[�h
		m_UDBaseMode(true)        //!�㉺�̃X�e�B�b�N�ύX���[�h
	{}

	MyCamera::MyCamera(float ArmLen) :
		Camera(),
		m_ToTargetLerp(1.0f),
		m_TargetToAt(0, 0, 0),
		m_RadY(0.5f),
		m_RadXZ(0),
		m_CameraUpDownSpeed(10.0f),
		m_CameraUnderRot(0.1f),
		m_ArmLen(5.0f),
		m_MaxArm(20.0f),
		m_MinArm(2.0f),
		m_RotSpeed(1.0f),
		m_ZoomSpeed(0.1f),
		m_LRBaseMode(true),
		m_UDBaseMode(true)
	{
		m_ArmLen = ArmLen;
		auto eye = GetEye();
		eye.y = m_ArmLen;
		SetEye(eye);
	}

	MyCamera::~MyCamera() {}//!�A�N�Z�X

	//!�J�����̈ʒu�̐ݒ�
	void MyCamera::SetEye(const bsm::Vec3& Eye)
	{
		Camera::SetEye(Eye);
		UpdateArmLengh();
	}

	void MyCamera::SetEye(float x, float y, float z) {
		Camera::SetEye(x, y, z);
		UpdateArmLengh();
	}

	//!�J�����̖ڕW�I�u�W�F�N�g�𓾂�
	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	//!�J�����̖ڕW�I�u�W�F�N�g��ݒ肷��
	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	//!�I�u�W�F�N�g��ǂ�������ꍇ�̕�Ԃ𓾂�
	float MyCamera::GetToTargetLerp() const {
		return m_ToTargetLerp;
	}

	//!�I�u�W�F�N�g��ǂ�������ꍇ�̕�Ԃ�ݒ肷��
	void MyCamera::SetToTargetLerp(float f) {
		m_ToTargetLerp = f;
	}

	//!�J�����̈ʒu�ƃJ�����̎���̋����𓾂�
	float MyCamera::GetArmLengh() const {
		return m_ArmLen;
	}

	//!�J�����̈ʒu�ƃJ�����̎���̋������X�V
	void MyCamera::UpdateArmLengh() {
		auto vec = GetEye() - GetAt();
		m_ArmLen = bsm::length(vec);
		if (m_ArmLen >= m_MaxArm) {
			//m_MaxArm�ȏ㗣��Ȃ��悤�ɂ���
			m_ArmLen = m_MaxArm;
		}
		if (m_ArmLen <= m_MinArm) {
			//m_MinArm�ȉ��߂Â��Ȃ��悤�ɂ���
			m_ArmLen = m_MinArm;
		}
	}

	//!�J�����̈ʒu�ƃJ�����̎���̋����̍X�V
	float MyCamera::GetMaxArm() const {
		return m_MaxArm;

	}

	//!�J�����̈ʒu�ƃJ�����̎���̋����̍ő�l�ݒ�
	void MyCamera::SetMaxArm(float f) {
		m_MaxArm = f;
	}

	//!�J�����̈ʒu�ƃJ�����̎���̋����̍ŏ��l�𓾂�
	float MyCamera::GetMinArm() const {
		return m_MinArm;
	}

	//!�J�����̈ʒu�ƃJ�����̎���̋����̍ŏ��l��ݒ�
	void MyCamera::SetMinArm(float f) {
		m_MinArm = f;
	}

	//!�J�����̉�]�X�s�[�h�𓾂�
	float MyCamera::GetRotSpeed() const {
		return m_RotSpeed;

	}

	//!�J�����̉�]�X�s�[�h�̐ݒ�
	void MyCamera::SetRotSpeed(float f) {
		m_RotSpeed = abs(f);
	}

	//!�^�[�Q�b�g����J�������_�ւ̒����x�N�g���𓾂�
	bsm::Vec3 MyCamera::GetTargetToAt() const {
		return m_TargetToAt;

	}

	//!�^�[�Q�b�g����J�������_�ւ̒����x�N�g����ݒ肷��
	void MyCamera::SetTargetToAt(const bsm::Vec3& v) {
		m_TargetToAt = v;
	}


	//!R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
	bool MyCamera::GetLRBaseMode() const {
		return m_LRBaseMode;

	}

	//!R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
	bool MyCamera::IsLRBaseMode() const {
		return m_LRBaseMode;

	}

	//!R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ����ݒ肷��
	void MyCamera::SetLRBaseMode(bool b) {
		m_LRBaseMode = b;
	}

	//!R�X�e�B�b�N�̏㉺�ύX��Base���[�h�ɂ��邩�ǂ�������
	bool MyCamera::GetUDBaseMode() const {
		return m_UDBaseMode;

	}

	//!R�X�e�B�b�N�̏㉺�ύX��Base���[�h�ɂ��邩�ǂ�������
	bool MyCamera::IsUDBaseMode() const {
		return m_UDBaseMode;
	}

	//!R�X�e�B�b�N�̏㉺�ύX��Base���[�h�ɂ��邩�ǂ����ݒ肷��
	void MyCamera::SetUDBaseMode(bool b) {
		m_UDBaseMode = b;

	}
	
	//!�J�����̎��_�̐ݒ�
	void MyCamera::SetAt(const bsm::Vec3&At){
		Camera::SetAt(At);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
		}

	//!�J�������_�̐ݒ�
	void MyCamera::SetAt(float x, float y, float z) {
		Camera::SetAt(x, y, z);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
	}

	//!�J�����̍X�V����
	void MyCamera::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//�O��̃^�[������̎���
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 newEye = GetEye();
		Vec3 newAt = GetAt();
		//�v�Z�Ɏg�����߂̘r�p�x�i�x�N�g���j
		bsm::Vec3 armVec = newEye - newAt;
		//���K�����Ă���
		armVec.normalize();
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbRY = cntlVec[0].fThumbRY;
			fThumbRX = cntlVec[0].fThumbRX;
			wButtons = cntlVec[0].wButtons;
		}


		//!�㉺�p�x�̕ύX
		if (fThumbRY >= 0.1f) {
			if (IsUDBaseMode()) {
				m_RadY += m_CameraUpDownSpeed * elapsedTime;
			}
			else {
				m_RadY -= m_CameraUpDownSpeed * elapsedTime;
			}
		}
		else if (fThumbRY <= -0.1f) {
			if (IsUDBaseMode()) {
				m_RadY -= m_CameraUpDownSpeed * elapsedTime;
			}
			else {
				m_RadY += m_CameraUpDownSpeed * elapsedTime;
			}
		}
		if (m_RadY > XM_PI * 4 / 9.0f) {
			m_RadY = XM_PI * 4 / 9.0f;
		}
		else if (m_RadY <= m_CameraUnderRot) {
			//�J���������E���ɉ��������炻��ȏ㉺����Ȃ�
			m_RadY = m_CameraUnderRot;
		}
		armVec.y = sin(m_RadY);

		//������Y����]���쐬
		if (fThumbRX != 0 ) {
			//��]�X�s�[�h�𔽉f
			if (fThumbRX != 0) {
				if (IsLRBaseMode()) {
					m_RadXZ += fThumbRX * elapsedTime * m_RotSpeed;
				}
				else {
					m_RadXZ += -fThumbRX * elapsedTime * m_RotSpeed;
				}
			}
			
			
			if (abs(m_RadXZ) >= XM_2PI) {
				//1�T�������0��]�ɂ���
				m_RadXZ = 0;
			}
		}
		//�N�I�[�^�j�I����Y��]�i�܂�XZ�x�N�g���̒l�j���v�Z
		Quat qtXZ;
		qtXZ.rotation(m_RadXZ, bsm::Vec3(0, 1.0f, 0));
		qtXZ.normalize();
		//�ړ���s�̍s��v�Z���邱�ƂŁAXZ�̒l���Z�o
		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -1.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		//XZ�̒l���킩�����̂Řr�p�x�ɑ��
		armVec.x = posXZ.x;
		armVec.z = posXZ.z;
		//�r�p�x�𐳋K��
		armVec.normalize();

		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {
			//�ڎw�������ꏊ
			Vec3 toAt = ptrTarget->GetComponent<Transform>()->GetWorldMatrix().transInMatrix();
			toAt += m_TargetToAt;
			newAt = Lerp::CalculateLerp(GetAt(), toAt, 0, 1.0f, 1.0, Lerp::Linear);
		}

		//�A�[���̕ύX
		//D�p�b�h��
		if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN ) {
			//�J�����ʒu������
			m_ArmLen += m_ZoomSpeed;
			if (m_ArmLen >= m_MaxArm) {
				//m_MaxArm�ȏ㗣��Ȃ��悤�ɂ���
				m_ArmLen = m_MaxArm;
			}
		}

		//D�p�b�h��
		else if (wButtons & XINPUT_GAMEPAD_DPAD_UP) {
			//�J�����ʒu�����
			m_ArmLen -= m_ZoomSpeed;
			if (m_ArmLen <= m_MinArm) {
				//m_MinArm�ȉ��߂Â��Ȃ��悤�ɂ���
				m_ArmLen = m_MinArm;
			}
		}
		////�ڎw�������ꏊ�ɃA�[���̒l�Ƙr�x�N�g����Eye�𒲐�
		Vec3 toEye = newAt + armVec * m_ArmLen;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0, 1.0f, m_ToTargetLerp, Lerp::Linear);

		SetAt(newAt);
		SetEye(newEye);
		UpdateArmLengh();
		Camera::OnUpdate();
	}

}