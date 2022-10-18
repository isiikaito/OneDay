/*!
@file Hunter.cpp
@brief �n���^�[�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
  Hunter::Hunter(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
		
  {}

  Hunter::~Hunter(){}
  //!������
  void Hunter::OnCreate() {
	  //�����ʒu�Ȃǂ̐ݒ�
	  auto ptrTrans = GetComponent<Transform>();
	  ptrTrans->SetScale(1.0f, 1.4f, 1.4f);
	  ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
	  ptrTrans->SetPosition(0.0f,5.0f,0.0f);
	 

	  //CollisionSphere�Փ˔����t����
	  auto Coll = AddComponent<CollisionObb>();

	  Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
	  spanMat.affineTransformation(
		  Vec3(0.35f, 0.2f, 0.4f),//!�傫��
		  Vec3(0.0f, 0.0f, 0.0f),
		  Vec3(0.0f, 0.0f, 0.0f),   //!��]
		  Vec3(0.0f, -0.5f, -0.05f)  //!�ʒu
	  );
	  //�d�͂�����
	  AddComponent<Gravity>();

	  //�e������i�V���h�E�}�b�v��`�悷��j
	  auto ptrShadow = AddComponent<Shadowmap>();

	  //�e�̌`�i���b�V���j��ݒ�
	  ptrShadow->SetMeshResource(L"HUNTER_MESH");
	  ptrShadow->SetMeshToTransformMatrix(spanMat);

	  //�`��R���|�[�l���g�̐ݒ�
	  auto ptrDraw = AddComponent<PNTStaticModelDraw>();               //!�`��R���|�[�l���g


	  //!���b�V���̐ݒ�
	  ptrDraw->SetMeshResource(L"HUNTER_MESH");
	  ptrDraw->SetMeshToTransformMatrix(spanMat);
	  Coll->SetDrawActive(true);
  }

}
//!end basecross
