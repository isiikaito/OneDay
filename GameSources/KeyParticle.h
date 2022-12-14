
/*/*!
@file KeyParticle.h
@brief�@�J�M����������̃G�t�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	/// �p�[�e�B�N���N���X
	//--------------------------------------------------------------------------------------
	class MultiSpark : public MultiParticle {
	public:
		//�\�z�Ɣj��
		MultiSpark(shared_ptr<Stage>& StagePtr);
		virtual ~MultiSpark();
		//������
		virtual void OnCreate() override;
		void InsertSpark(const Vec3& Pos);
		virtual void OnUpdate() override;
	};
}
// end namespace basecross