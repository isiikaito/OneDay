/*!
@file LoseSightOf.cpp
@author Kaito Isii
@brief �G�̃v���C���[�����������Ƃ��̂͂Ăȃ}�[�N�̕\��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void LoseSightOf::OnCreate()
	{

		auto PtrTransform = GetComponent<Transform>();
		// ���_�f�[�^
		float HelfSize = 0.5f;

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
		drawComp->SetTextureResource(L"LoseSightOf_TX");
		/*drawComp->SetDiffuse(Col4(1, 1, 1, 0.5f));*/ // �g�U���ˁi�A���t�@�����͓��ߏ����Ɏg����j
		//drawComp->SetEmissive(color); // ���Ȕ���
		drawComp->SetDepthStencilState(DepthStencilState::None); // �d�ˍ��킹�̖�����������
		SetAlphaActive(true);
		SetDrawActive(false);
		auto transComp = GetComponent<Transform>();  // �g�����X�t�H�[���F�ϊ��s��(Transform Matrix)
		transComp->SetParent(parent); // �e�I�u�W�F�N�g���w�肷��
		transComp->SetPosition(0.0f, 5.0f, 0.0f);
		transComp->SetScale(10, 10, 10);
		auto EnemyTransform = parent->GetComponent<Transform>();
		transComp->SetQuaternion(EnemyTransform->GetQuaternion());
	}

	void LoseSightOf::Billboard()
	{
		auto ptrTransform = GetComponent<Transform>();
		auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

		Quat Qt;
		//�������r���{�[�h�ɂ���
		Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

		ptrTransform->SetQuaternion(Qt);

	}

	void LoseSightOf::LoseSight()
	{
		
	}

	void LoseSightOf::OnUpdate()
	{
		Billboard();
		//std::dynamic_pointer_cast<BaseEnemy>();
		//auto group =GetStage()->GetSharedObjectGroup(L"Hunter_ObjGroup");
		//auto vecEnemy = group->GetGroupVector();//!�Q�[���I�u�W�F�N�g�̔z��̎擾
		////!�n���^�[�z��I�u�W�F�N�g�̔z�񕪉�
		//for (auto& v : vecEnemy) {
		//	auto HunterPtr = v.lock();//!�n���^�[�̃O���[�v����1���b�N����
		//	auto loseSightOfTarget = dynamic_pointer_cast<Hunter>(HunterPtr);

		//	auto loseSightOfTarget=loseSightOfTarget->GetloseSightOfTarget();

		//	//!�v���C���[������������
		//	if (loseSightOfTarget == true)
		//	{
		//		float Time = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
		//		m_LoseSeghtOfTime += Time;

		//		auto PtrDraw = GetComponent<PCTSpriteDraw>();//!�`��R���|�[�l���g
		//		SetDrawActive(true);
		//		//!2�b��������
		//		if (loseSightOfTarget >= 2)
		//		{

		//			loseSightOfTarget = false;//!��������߂�
		//			SetloseSightOfTarget(loseSightOfTarget);
		//		}

		//	}
		//}
		//////!�����邱�Ƃ���߂���
		////if (loseSightOfTarget == false)
		////{
		////	m_LoseSeghtOfTime = 0.0f;//!�������Ԃ�0�b�ɂ���
		////	SetDrawActive(false);//!�`�����߂�

		////}
		///*LoseSight();*/
	}
}