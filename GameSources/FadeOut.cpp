/*!
@file FadeOut.cpp
@brief�t�F�[�h�A�E�g�̎���
@author Kaito Isii
*/

#include "stdafx.h"
#include "Project.h"
#include "GameOver.h"
namespace basecross {
	//�Q�[�W
	constexpr float FADEOUTSPEED = 2.0f;//!�t�F�C�h�A�E�g���鎞��
	FadeOut::FadeOut(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_TextureColor(Col4(0.0f, 0.0f, 0.0f, 0.0f))

	{}

	FadeOut::~FadeOut() {}
	void FadeOut::OnCreate() {



		//���_�z��
		m_BackupVertices = {
			//�J���[�@�����x
		{ VertexPositionColor(Vec3(-m_StartScale.x,  m_StartScale.y, 0),m_TextureColor) },
		{ VertexPositionColor(Vec3(m_StartScale.x,  m_StartScale.y, 0), m_TextureColor) },
		{ VertexPositionColor(Vec3(-m_StartScale.x, -m_StartScale.y, 0), m_TextureColor) },
		{ VertexPositionColor(Vec3(m_StartScale.x, -m_StartScale.y, 0), m_TextureColor) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬

		auto ptrTrans = GetComponent<Transform>();								//!�g�����X�t�H�[���̎擾
		ptrTrans->SetPosition(m_StartPos);										//!�ʒu�̐ݒ�
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);	//!�`��R���|�[�l���g�̎擾
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);					//!���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
	}
	//�_�ŏ����iElapsedtime�𗘗p���Ă���j
	void FadeOut::OnUpdate() {

		auto scene = App::GetApp()->GetScene<Scene>();//!�V�[���̎擾
		auto gameOver = scene->GetGameOverSprite();//!�Q�[���I�[�o�[���ǂ����̎擾
		if (gameOver)
		{
			float elapsedTime = App::GetApp()->GetElapsedTime();//!���Ԃ̎擾
			m_TotalTime += elapsedTime;							//!���Ԃ̍X�V
			//!�t�F�C�h�A�E�g���I���Ă�����
			if (m_TotalTime >= XM_PI / FADEOUTSPEED) 
			{
				m_TotalTime = XM_PI / FADEOUTSPEED;			//!�t�F�C�h�A�E�g�̂܂�
				auto gameOverSprite = GetStage()->GetSharedGameObject<GameOverSprite>(L"GameOverSprite");
				gameOverSprite->SetDrawActive(true);
			
			}
			vector<VertexPositionColor> newVertices;			//!���_�̎擾

			//!���_�̐�����
			for (size_t i = 0; i < m_BackupVertices.size(); i++)
			{
				Col4 col = m_BackupVertices[i].color;	//!���_�̐F�̎擾
				col.w = sin(m_TotalTime);				//sin��0�`�P�܂łɂ���0�̎��͓����P�̎��͕\���Ƃ��Ă���
				auto v = VertexPositionColor
				(
					m_BackupVertices[i].position,		//!���_�̈ʒu
					col									//!���_�̐F
				);
				newVertices.push_back(v);				//!�X�V�������_��z��ɓ����
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();//!�`��R���|�[�l���g�̎擾
			ptrDraw->UpdateVertices(newVertices);		//!���_�̍X�V

		}

	}
}