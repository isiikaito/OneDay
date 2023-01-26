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
		m_CameraUnderRot(2.0f),   //!�J�����������鉺���p�x
		m_RadXZ(0.0f),            //!�J������Z���̈ʒu
		m_ArmLen(5.0f),           //!�r�̒����̐ݒ�
		m_MaxArm(60.0f),          //!�r�̍ő�̒���
		m_MinArm(60.0f),          //!�r�̍ŏ��̒���
		m_LRBaseMode(true),       //!���E�X�e�B�b�N�ύX�̃��[�h
		m_UDBaseMode(true)        //!�㉺�̃X�e�B�b�N�ύX���[�h
	{}

	MyCamera::MyCamera(float ArmLen) :
		Camera(),
		m_ToTargetLerp(1.0f),
		m_TargetToAt(0, 0, 0),
		m_CameraUnderRot(2.0f),
		m_ArmLen(5.0f),
		m_MaxArm(60.0f),
		m_MinArm(60.0f),
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


	//!�^�[�Q�b�g����J�������_�ւ̒����x�N�g���𓾂�
	bsm::Vec3 MyCamera::GetTargetToAt() const {
		return m_TargetToAt;

	}

	//!�^�[�Q�b�g����J�������_�ւ̒����x�N�g����ݒ肷��
	void MyCamera::SetTargetToAt(const bsm::Vec3& v) {
		m_TargetToAt = v;
	}



	//!R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
	bool MyCamera::IsLRBaseMode() const {
		return m_LRBaseMode;

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
		
		armVec.y = sin(2.0f); // �㉺�̊p�x��t����

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

		//�ڎw�������ꏊ�ɃA�[���̒l�Ƙr�x�N�g����Eye�𒲐�
		Vec3 toEye = newAt + armVec * m_ArmLen;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0, 1.0f, m_ToTargetLerp, Lerp::Linear);
		
		SetAt(newAt);
		SetEye(newEye);
		UpdateArmLengh();
		Camera::OnUpdate();
		
		//!��p��ς��邱�Ƃ��o����
		//auto chk = XM_PI / 9.0f;//!360��6�Ŋ����Ċp�x���o���B
		//SetFovY(chk);

		auto& app = App::GetApp();//!�A�v���̎擾
		auto Stage = app->GetScene<Scene>()->GetActiveStage();//!�X�e�[�W�̎擾
	
		auto Objects = Stage->GetGameObjectVec();//!�X�e�[�W�̒��̃I�u�W�F�N�g���擾
		
		for (auto& Obj : Objects)//!�I�u�W�F�N�g�̗v�f��
		{

			auto stageWall = dynamic_pointer_cast<StageWall>(Obj);//!�ǂ̎擾
			if (stageWall)
			{
				auto StageWallObb = stageWall->GetComponent<CollisionObb>()->GetObb();//!�X�e�[�W�̕ǂ�Obb�̎擾
				
				if (HitTest::SEGMENT_OBB(GetEye(), GetAt(), StageWallObb))//!�J�����Ǝ��_�̊Ԃɕǂ���������
				{
					stageWall->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.3f));//!�ǂ𔼓����ɂ���
					
				}
				
				else//!�J�����Ǝ��_�̊Ԃɕǂ�����������
				{
					stageWall->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.4f, 0.4f, 0.4f, 1.0f));//!�ǂ̔���������������
				}
				
			}

			auto stageBuilding = dynamic_pointer_cast<StageBuilding>(Obj);//!�����̎擾
			if (stageBuilding)
			{
				auto StageBuildingObb = stageBuilding->GetComponent<CollisionObb>()->GetObb();//!�X�e�[�W�̕ǂ�Obb�̎擾

				if (HitTest::SEGMENT_OBB(GetEye(), GetAt(), StageBuildingObb))//!�J�����Ǝ��_�̊Ԃɕǂ���������
				{
					stageBuilding->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.3f));//!�ǂ𔼓����ɂ���

				}

				else//!�J�����Ǝ��_�̊Ԃɕǂ�����������
				{
					stageBuilding->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.5f, 0.5f, 0.5, 1.0f));//!�ǂ̔���������������
				}

			}





		}

		
			
	

	}

}