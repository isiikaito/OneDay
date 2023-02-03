/**
*@file GoalPlayer.h
*@brief �S�[�����̃v���C���[�̃w�b�_�t�@�C��
*@author Ayumu Muroi
*@details �S�[�����̃v���C���[�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�S�[���v���C���[�N���X
	//--------------------------------------------------------------------------------------
	class GoalPlayer : public GameObject {
	private:
		Vec3 m_Position; //!�ʒu
		Vec3 m_Rotation; //!��]
		Vec3 m_Scale; //!�傫��

	public:

		//�\�z�Ɣj��
		GoalPlayer(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~GoalPlayer() {}
		//������
		void OnCreate()override;

		//void OnDestroy();

		//�X�V
		void OnUpdate()override;
	};
}
//end basecross
