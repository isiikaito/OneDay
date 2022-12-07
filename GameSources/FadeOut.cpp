/*!
@file FadeOut.cpp
@brief�t�F�[�h�A�E�g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�Q�[�W

	FadeOut::FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)

	{}

	FadeOut::~FadeOut() {}
	void FadeOut::OnCreate() {


		float helfSize = 0.5f;
		//���_�z��
		m_BackupVertices = {
			//�J���[�@�����x
{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);




	}
	//�_�ŏ����iElapsedtime�𗘗p���Ă���j
	void FadeOut::OnUpdate() {

		////�v���C���[�̎擾
		//auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		//auto Exit = ptrPlayer->GetExitCount();
		//ptrPlayer->SetExitCount(Exit);

		//���Ԃ̎擾
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= XM_PI / 2) {
			m_TotalTime = XM_PI / 2;
		}
		//���_�̎擾
		vector<VertexPositionColor> newVertices;
		for (size_t i = 0; i < m_BackupVertices.size(); i++) {
			Col4 col = m_BackupVertices[i].color;
			//sin��0�`�P�܂łɂ���0�̎��͓����P�̎��͕\���Ƃ��Ă���
			col.w = sin(m_TotalTime);
			auto v = VertexPositionColor(
				m_BackupVertices[i].position,
				col
			);
			newVertices.push_back(v);
		}
		auto ptrDraw = GetComponent<PCSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
		if (m_TotalTime >= 1)
		{
			//1���̃V�[���ւ̕b��.
			//2�n���ق��̃|�C���^
			//3�n�����ق�
			//�o�^���������𗘗p���Ĉړ�
			//       1            2                  3                     4
		 /* PostEvent(0.0f, GetThis<FadeOut>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");*/
		}
	}
}