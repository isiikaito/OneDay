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
	constexpr float HELFSIZE = 0.5f;//!�|���S���T�C�Y


	void HeadManComment::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		// ���_�f�[�^
		

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HELFSIZE, HELFSIZE, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HELFSIZE, HELFSIZE, 0), m_TextureColor,m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HELFSIZE, -HELFSIZE, 0), m_TextureColor, m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HELFSIZE, -HELFSIZE, 0), m_TextureColor, m_RightLowerSummit) },
		};

		// ���_�C���f�b�N�X�i���_���Ȃ����ԁj
		std::vector<uint16_t> indices = {
			// �Ȃ��鏇�Ԃ��u�E���(���v���)�v���ƕ\�ʂɂȂ�
			0, 1, 2, // ����̎O�p�|���S��
			2, 1, 3  // �E���̎O�p�|���S��
		};

		
		auto drawComp = AddComponent<PCTStaticDraw>();					//!�`��R���|�[�l���g�̎擾
		drawComp->CreateOriginalMesh(vertices, indices);				//!���b�V���̐���
		drawComp->SetOriginalMeshUse(true);								//!���b�V���̓K�p
		drawComp->SetTextureResource(L"HeadManCommet1_TX");				//!�g���e�N�X�`���̓ǂݍ���
		drawComp->SetDepthStencilState(DepthStencilState::None);		//!�d�ˍ��킹�̖�����������
		SetAlphaActive(true);											//!��������������
		auto transComp = GetComponent<Transform>();						//!�g�����X�t�H�[���F�ϊ��s��(Transform Matrix)		
		transComp->SetScale(m_scale);									//!�傫���̐ݒ�
		auto EnemyTransform = parent->GetComponent<Transform>();		//!�g�����X�t�H�[���̎擾
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());		//!�G�̊J�X�ɍ��킹��
		SetDrawActive(false);											//!�\�����Ȃ�

	}

	void HeadManComment::Billboard()
	{

		auto ptrTransform = GetComponent<Transform>();					//!�g�����X�t�H�[���̎擾
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();		//!�J�����̎擾
		Quat Qt;
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());		//!�������r���{�[�h�ɂ���
		ptrTransform->SetQuaternion(Qt);								//!��]�̐ݒ�
		auto EnemyTransform = parent->GetComponent<Transform>();		//!�g�����X�t�H�[���̎擾
		auto EnemyPosition = EnemyTransform->GetPosition();				//!�G�̈ʒu�̎擾
		//!�r���{�[�h�����̓I�u�W�F�N�g�̉�]�܂Ŕ��f���Ă��܂����߃|�W�V������ύX����
		ptrTransform->SetPosition(EnemyPosition.x, m_spritePositionY, EnemyPosition.z);

	}


	void HeadManComment::Comment()
	{
		auto headMan=GetStage()->GetSharedGameObject<HeadMan>(L"HeadMan");	//!�����̎擾
		auto CommentOn=headMan->GetHeadManComment();						//!�R�����g���o�����ǂ���

		//!�R�����g���o����
		if (CommentOn == true)
		{
			SetDrawActive(true);//!�\������
		}
		else
		{
			SetDrawActive(false);//!�\�����Ȃ�

		}

		
		auto drawComp = AddComponent<PCTStaticDraw>();	//!�`��R���|�[�l���g
		auto scene = App::GetApp()->GetScene<Scene>();	//!�V�[���̎擾
		auto date = scene->GetDate();					//!���t�̎擾

		//!���ɂ����Ƃ̃R�����g
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