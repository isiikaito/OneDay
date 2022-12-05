/*!
@file FadeOut.h
@brief �t�F�[�h�A�E�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�Q�[�W
	class FadeOut : public GameObject
	{
		bool m_Trace;      //����
		Vec2 m_StartScale;//�傫��
		Vec3 m_StartPos;  //�ʒu
		float m_TotalTime;//���Ԃ̎擾


		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor>m_BackupVertices;


	public:
		FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~FadeOut();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;


	};
}
