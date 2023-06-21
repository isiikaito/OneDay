/*!
@file SurprisedSprite.cpp
@author Kaito Isii
@brief �r�b�N���}�[�N�̕\��
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�r�b�N���}�[�N�X�v���C�g
	//--------------------------------------------------------------------------------------

	constexpr float m_maxSurprisedTime = 2.0f;//!�e�N�X�`����\�����Ă��鎞��
	constexpr float helfSize = 0.5f;//!�|���S���T�C�Y

	void SurprisedSprite::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		// ���_�f�[�^
		float HelfSize = helfSize;

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0),m_TextureColor, m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), m_TextureColor,m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),m_TextureColor,m_RightLowerSummit) },
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
		auto drawComp = AddComponent<PCTStaticDraw>();				//!�`��R���|�[�l���g�̎擾
		drawComp->CreateOriginalMesh(vertices, indices);			//!���b�V���̐���
		drawComp->SetOriginalMeshUse(true);							//!�I���W�i�����b�V�����g��
		drawComp->SetTextureResource(L"Surprised_TX");				//!�e�N�X�`���̐ݒ�
		drawComp->SetDepthStencilState(DepthStencilState::None);	//!�d�ˍ��킹�̖�����������
		SetAlphaActive(true);										//!��������
		SetDrawActive(false);										//!��\��
		auto transComp = GetComponent<Transform>();					//!�g�����X�t�H�[���F�ϊ��s��(Transform Matrix)		
		transComp->SetScale(m_scale);								//!�傫���̐ݒ�
		auto EnemyTransform = parent->GetComponent<Transform>();	//!�G�̃g�����X�t�H�[���̎擾
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());	//!�����̉�]�ɓG�̉�]���擾
	}

	void SurprisedSprite::Billboard()
	{

		auto ptrTransform = GetComponent<Transform>();				//!�g�����X�t�H�[���̎擾
		auto& PtrCamera = GetStage()->GetView()->GetTargetCamera();	//!�J�����̎擾
		Quat Qt;
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());	//�������r���{�[�h�ɂ���
		ptrTransform->SetQuaternion(Qt);							//!�����̉�]��ݒ�
		auto EnemyTransform = parent->GetComponent<Transform>();	//!�G�̃g�����X�t�H�[���̎擾
		auto EnemyPosition = EnemyTransform->GetPosition();			//!�G�̈ʒu�̎擾
		//!�r���{�[�h�����̓I�u�W�F�N�g�̉�]�܂Ŕ��f���Ă��܂����߃|�W�V������ύX����
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);
	}


	void SurprisedSprite::Surprised()
	{
		auto GetEnemy = std::dynamic_pointer_cast<BaseEnemy>(parent);	//!�y�A�����g�̓G�̎擾
		auto SurprisedTarget = GetEnemy->GetSurprisedSprite();			//!�X�v���C�g�̎擾
		//!�v���C���[������������
		if (SurprisedTarget == true)
		{
			auto elapsedTime = App::GetApp()->GetElapsedTime();			//!�G���p�\�^�C���̎擾
			m_surprisedTime += elapsedTime;								//!���Ԃ̍X�V
			//!�\�����Ԃ��߂�����
			if (m_surprisedTime >= m_maxSurprisedTime)
			{
				GetEnemy->SetSurprisedSprite(false);					//!��\��������
			}
		
			SetDrawActive(true);//!�\������
		}

		else
		{
			m_surprisedTime = 0.0f;	//!���Ԃ̃��Z�b�g
			SetDrawActive(false);	//!�\�����Ȃ�
		}
	}

	void SurprisedSprite::OnUpdate()
	{
		Billboard();
		Surprised();
	}
}
