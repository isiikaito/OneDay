/*!
@file PlayerMoveComponent.cpp
@brief �v���C���[�̓�����������
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "MoveComponent.h"
namespace basecross 
{
	constexpr float ROTTOHEAD = 1.0f;					//!����

	Vec2 PlayerMoveComponent::GetControlerInformation() const
	{
		Vec2 ret;
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//!�R���g���[���̎擾
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		//!�ڑ�����Ă���R���g���[��
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;//!���X�e�B�b�Nx���W
			ret.y = cntlVec[0].fThumbLY;//!���X�e�B�b�Ny���W
		}
		return ret;
	}


	Vec3 PlayerMoveComponent::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//�f�t�H���g�̓r���[�̃J����������o��
		auto& StageView = GetStage()->GetView();
		
		//!���͂̎擾
		auto inPut = GetControlerInformation();
		float moveX = inPut.x;
		float moveZ = inPut.y;

		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;											//!���������̃X�s�[�h
			auto& ptrCamera = StageView->GetTargetCamera();							//!�J�����̎擾
			auto ptrTransform = GetGameObject()->GetComponent<Transform>();
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();	//!�i�s�����̌������v�Z
			front.y = 0;
			front.normalize();												//!�i�s�����̌����𐳋K��
			float frontAngle = atan2(front.z, front.x);						//!�i�s������������̊p�x���Z�o
			Vec2 moveVec(moveX, moveZ);										//!�R���g���[���̌����v�Z
			float moveSize = moveVec.length();								//!�����傫��
			float cntlAngle = atan2(-moveX, moveZ);							//!�R���g���[���̌�������p�x���v�Z
			float totalAngle = frontAngle + cntlAngle;						//!�g�[�^���̊p�x���Z�o
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));				//!�p�x����x�N�g�����쐬
			angle.normalize();												//!���K������
			angle *= moveSize;												//!�ړ��T�C�Y��ݒ�
			angle.y = 0;													//!Y���͕ω������Ȃ�
		}
		return angle;
	}
	void PlayerMoveComponent::MovePlayer() {


		
		float elapsedTime = App::GetApp()->GetElapsedTime();			 //!�G���p�\�^�C���̎擾
		auto angle = GetMoveVector();									 //!�x�N�g���̎擾
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!���ʉ���
		auto ptrTransform = GetGameObject()->GetComponent<Transform>();
		//!�X�e�B�b�N���X���Ă�����
		if (angle.length() > 0.0f) {
			auto pos = ptrTransform->GetPosition();		 //!���g�̃|�W�V�����̎擾
			pos += angle * elapsedTime * m_Speed;						 //!�|�W�V�����̍X�V
			ptrTransform->SetPosition(pos);				 //!�|�W�V�����̐ݒ�

		}

		//!��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetGameObject()->GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, ROTTOHEAD);		//!���ʂ�����
		}
	}
	void PlayerMoveComponent::OnUpdate()
	{
		MovePlayer();
	}

}