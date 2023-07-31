/*!
@file Timer.cpp
@brief ���Ԃ̑���
*/

#include "stdafx.h"
#include "Project.h"
#include "Timer.h"

namespace basecross {
	constexpr float HELFSIZE = 0.5f;		//!�|���S���T�C�Y
	constexpr float  STARTSCALEZ = 1.0f;	//!���傫��
	constexpr float STARTPOSZ = 0.1f;		//!�e�N�X�`���̉��s��
	constexpr float MAXNUM = 10.0f;		//!�e�N�X�`���̍ő吔��
	constexpr float RIGHTUV = 0.1f;		//!�E����uv���_
	constexpr float PICECPOS = 1.0f;		//!�����Ƃ̈ʒu
	constexpr int NUMBERQUANTITY = 4;		//!���_�z�u�f�[�^
	//--------------------------------------------------------------------------------------
	///	�X�R�A�\���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	//!�X�v���C�g�̏����ݒ�
	Timer::Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(0.0f),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(0.1f, 0.0f)),
		m_RightLowerSummit(Vec2(0.1f, 1.0f))
	{}

	void Timer::OnCreate() {

		float xPiecesize = PICECPOS / (float)m_NumberOfDigits;//!�������Ƃ̈ʒu

		//!�C���f�b�N�X�z��
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float vertex0 = -HELFSIZE + xPiecesize * (float)i;//!�����̒��_
			float vertex1 = vertex0 + xPiecesize;             //!�E���̒��_
			//!0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, HELFSIZE, 0), m_LeftUpperSummit)//!���_�f�[�^1
			);
			//!1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, HELFSIZE, 0), m_RightUpperSummit)//!���_�f�[�^2
			);
			//!2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex0, -HELFSIZE, 0), m_LeftLowerSummit)//!���_�f�[�^3
			);
			//!3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(vertex1, -HELFSIZE, 0), m_RightLowerSummit)//!���_�f�[�^4
			);
			indices.push_back(i * NUMBERQUANTITY + 0);
			indices.push_back(i * NUMBERQUANTITY + 1);
			indices.push_back(i * NUMBERQUANTITY + 2);
			indices.push_back(i * NUMBERQUANTITY + 1);
			indices.push_back(i * NUMBERQUANTITY + 3);
			indices.push_back(i * NUMBERQUANTITY + 2);
		}

		SetAlphaActive(m_Trace);                                 //!�����x
		auto ptrTrans = GetComponent<Transform>();               //!�g�����X�R���|�[�l���g�̎擾
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);//!�傫���̐ݒ�
		ptrTrans->SetPosition(m_StartPos.x, m_StartPos.y, STARTPOSZ); //!�ʒu�̐ݒ�
		//!���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);//!�`��R���|�[�l���g�̎擾
		ptrDraw->SetTextureResource(m_TextureKey);                           //!�e�N�X�`���̐ݒ�
		GetStage()->SetSharedGameObject(L"Time", GetThis<Timer>());         //!�V�F�A�h�I�u�W�F�N�g�ɓǂݍ��܂���
	}


	void Timer::SetUVPos(int& verNum, UINT num, vector<VertexPositionTexture>& newVertices)
	{

		Vec2 uv0 = m_BackupVertices[verNum].textureCoordinate;                 //!�e�N�X�`���̎n�܂�̒��_�f�[�^�ƈʒu
		uv0.x = (float)num / MAXNUM;                                            //!�擾���������̈ʒu�ɒ��_�����킹��
		auto v = VertexPositionTexture(m_BackupVertices[verNum].position, uv0);//!�e�N�X�`���̒��_�̈ʒu
		newVertices.push_back(v);                                              //!�擾�������_�̈ʒu��newVertces�̌��ɒǉ����Ă���

		verNum++;
		Vec2 uv1 = m_BackupVertices[verNum].textureCoordinate;
		uv1.x = uv0.x + RIGHTUV;
		v = VertexPositionTexture(
			m_BackupVertices[verNum].position,
			uv1
		);
		newVertices.push_back(v);

		verNum++;
		Vec2 uv2 = m_BackupVertices[verNum].textureCoordinate;
		uv2.x = uv0.x;

		v = VertexPositionTexture(
			m_BackupVertices[verNum].position,
			uv2
		);
		newVertices.push_back(v);
		verNum++;
		Vec2 uv3 = m_BackupVertices[verNum].textureCoordinate;
		uv3.x = uv0.x + RIGHTUV;

		v = VertexPositionTexture(
			m_BackupVertices[verNum].position,
			uv3
		);
		newVertices.push_back(v);

		verNum++;
	}

	void Timer::OnUpdate() {

		vector<VertexPositionTexture> newVertices;
		UINT num;
		int verNum = 0;
		//!���Ԃ̐����擾
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT base = (UINT)pow(MAXNUM, i);		//!pow�͏�Z�Ƃ����Ӗ��ł���Bi�͍��������Ă��錅�����������Ă���
			num = ((UINT)m_Score) % base;			//!�]����o���ď����؂�̂�
			num = num / (base /(UINT) MAXNUM);			//!�c�������������̌��ɓ���

			SetUVPos(verNum, num, newVertices);

		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();//!�`��R���|�[�l���g
		ptrDraw->UpdateVertices(newVertices);       //!���_�f�[�^�̍X�V
	}



	

}
//end basecross
