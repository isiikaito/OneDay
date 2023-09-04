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
		BoneModelDeta m_goalPlayerBoneModelDeta;				//!�v���C���[�̃��f���f�[�^

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


	};
}
//end basecross
