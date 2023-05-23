/*!
@file LoseSightOf.cpp
@author Kaito Isii
@brief �G�̃v���C���[�����������Ƃ��̂͂Ăȃ}�[�N�̕\��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float helfSize = 0.5f;//!�|���S���T�C�Y
	constexpr float MaxLosefSeghtOfTime = 2.0f;//!�e�N�X�`����\�����鎞��
	void LoseSightOf::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		// ���_�f�[�^
		float HelfSize = helfSize;

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		// ���_�C���f�b�N�X�i���_���Ȃ����ԁj
		std::vector<uint16_t> indices = {
			// �Ȃ��鏇�Ԃ��u�E���(���v���)�v���ƕ\�ʂɂȂ�
			0, 1, 2, // ����̎O�p�|���S��
			2, 1, 3  // �E���̎O�p�|���S��
		};

		// Position : ���_���W
		// Normal : �@���x�N�g���i���_�̌����A�|���S���̌��� �� ���̔��˂̌v�Z�Ɏg���j
		// Color : ���_�F
		// Texture : �e�N�X�`�����W(UV���W)
		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"LoseSightOf_TX");			//!�e�N�X�`���̐ݒ�
		drawComp->SetDepthStencilState(DepthStencilState::None);	// �d�ˍ��킹�̖�����������
		SetAlphaActive(true);
		SetDrawActive(false);
		auto transComp = GetComponent<Transform>();					// �g�����X�t�H�[���F�ϊ��s��(Transform Matrix)		
		transComp->SetScale(m_scale);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
	}

	void LoseSightOf::Billboard()
	{
		
		auto ptrTransform = GetComponent<Transform>();				//!���g�̃g�����X�t�H�[���̎擾
		auto& PtrCamera = GetStage()->GetView()->GetTargetCamera();	//!�J�����̎擾

		Quat Qt;
		//�������r���{�[�h�ɂ���
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		ptrTransform->SetQuaternion(Qt);							//!�r���{�[�h��������ݒ肷��
		auto EnemyTransform = parent->GetComponent<Transform>();	//!�G�̃g�����X�t�H�[���̎擾
		auto EnemyPosition=EnemyTransform->GetPosition();			//!�G�̃|�W�V�����̎擾
		//!�r���{�[�h�����̓I�u�W�F�N�g�̉�]�܂Ŕ��f���Ă��܂����߃|�W�V������ύX����
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);

	}

	
	void LoseSightOf::LoseSight()
	{
		auto GetHunter = std::dynamic_pointer_cast<BaseEnemy>(parent);


		auto loseSightOfTarget = GetHunter->GetloseSightOfTarget();

		//!�v���C���[������������
		if (loseSightOfTarget == true)
		{
			float Time = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
			m_LoseSeghtOfTime += Time;

			SetDrawActive(true);
			//!2�b��������
			if (m_LoseSeghtOfTime >= MaxLosefSeghtOfTime)
			{
				loseSightOfTarget = false;
				GetHunter->SetloseSightOfTarget(loseSightOfTarget);
			}

		}
		//!����ɖ߂�
		if (loseSightOfTarget == false)
		{
			m_LoseSeghtOfTime = 0.0f;	//!�����������Ԃ�0�b�ɂ���
			SetDrawActive(false);		//!�`�����߂�

		}
	}

	void LoseSightOf::OnUpdate()
	{
		Billboard();
		
		LoseSight();
	}
}