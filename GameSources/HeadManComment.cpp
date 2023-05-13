/*!
@file HeadManComment.cpp
@author Kaito Isii
@brief �����̃R�����g�̕\��
*/

#include "stdafx.h"
#include "Project.h"
#include "HeadManComment.h"
#include "HeadMan.h"

namespace basecross
{
	constexpr float MaxLosefSeghtOfTime = 2.0f;//!�e�N�X�`����\�����Ă��鎞��
	constexpr float helfSize = 0.5f;//!�|���S���T�C�Y


	void HeadManComment::OnCreate()
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
		drawComp->SetTextureResource(L"HeadManCommet1_TX");
		drawComp->SetDepthStencilState(DepthStencilState::None); // �d�ˍ��킹�̖�����������
		SetAlphaActive(true);
		//SetDrawActive(false);
		auto transComp = GetComponent<Transform>();  // �g�����X�t�H�[���F�ϊ��s��(Transform Matrix)		
		transComp->SetScale(15, 15, 15);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
		SetDrawActive(false);

	}

	void HeadManComment::Billboard()
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


	void HeadManComment::Comment()
	{
		auto headMan=GetStage()->GetSharedGameObject<HeadMan>(L"HeadMan");
		auto CommentOn=headMan->GetHeadManComment();
		if (CommentOn == true)
		{
			SetDrawActive(true);
		}
		else
		{
			SetDrawActive(false);

		}

		//!��Œ���
		auto drawComp = AddComponent<PCTStaticDraw>();
		auto scene = App::GetApp()->GetScene<Scene>();
		auto date = scene->GetDate();

		switch (date)
		{
		case(static_cast<int>(Day::FirstDay)):
			drawComp->SetTextureResource(L"HeadManCommet1_TX");
				break;
		case(static_cast<int>(Day::SecondDay)):
			drawComp->SetTextureResource(L"HeadManCommet1_TX");
			break;
		case(static_cast<int>(Day::ThirdDay)):
			drawComp->SetTextureResource(L"HeadManCommet1_TX");
			break;
		case(static_cast<int>(Day::ForceDay)):
			drawComp->SetTextureResource(L"HeadManCommet2_TX");
			break;
		case(static_cast<int>(Day::FiveDay)):
			drawComp->SetTextureResource(L"HeadManCommet2_TX");
			break;
		case(static_cast<int>(Day::SixDay)):
			drawComp->SetTextureResource(L"HeadManCommet3_TX");
			break;
		}
	}

	void HeadManComment::OnUpdate()
	{
		Billboard();
		Comment();
	}
}