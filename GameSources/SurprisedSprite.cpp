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

	constexpr float MaxSurprisedTime = 2.0f;
	constexpr float m_maxSurprisedTime = 2.0f;
	constexpr float helfSize = 0.5f;

	void SurprisedSprite::OnCreate()
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
		//drawComp->SetMeshResource(L"DEFAULT_SQUARE");
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"Surprised_TX");
		drawComp->SetDepthStencilState(DepthStencilState::None); // �d�ˍ��킹�̖�����������
		SetAlphaActive(true);
		SetDrawActive(false);
		auto transComp = GetComponent<Transform>();  // �g�����X�t�H�[���F�ϊ��s��(Transform Matrix)		
		transComp->SetScale(m_scale);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
	}

	void SurprisedSprite::Billboard()
	{

		auto ptrTransform = GetComponent<Transform>();
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

		Quat Qt;
		//�������r���{�[�h�ɂ���
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		ptrTransform->SetQuaternion(Qt);
		auto EnemyTransform = parent->GetComponent<Transform>();
		auto EnemyPosition = EnemyTransform->GetPosition();
		//!�r���{�[�h�����̓I�u�W�F�N�g�̉�]�܂Ŕ��f���Ă��܂����߃|�W�V������ύX����
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);

	}


	void SurprisedSprite::Surprised()
	{
		auto GetEnemy = std::dynamic_pointer_cast<BaseEnemy>(parent);


		auto SurprisedTarget = GetEnemy->GetSurprisedSprite();

		//!�v���C���[������������
		if (SurprisedTarget == true)
		{
			auto Time = App::GetApp()->GetElapsedTime();
			m_surprisedTime += Time;
			if (m_surprisedTime >= m_maxSurprisedTime)
			{
				GetEnemy->SetSurprisedSprite(false);
			}
		
			SetDrawActive(true);
		}

		else
		{
			m_surprisedTime = 0.0f;
			SetDrawActive(false);
		}
		

		

	}

	void SurprisedSprite::OnUpdate()
	{
		Billboard();
		Surprised();
	}
}
