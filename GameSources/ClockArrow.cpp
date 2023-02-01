/*!
@file ClockArrow.cpp
@author Kaito Isii
@brief  ���̕\��
*/


#include "stdafx.h"
#include "Project.h"
#include "ClockArrow.h"

namespace basecross
{
	constexpr int first = 1;
	constexpr int second = 2;
	constexpr float m_startScaleZ = 1.0f;
	constexpr float m_startPosZ = 0.2f;
	constexpr float m_helfSize = 0.5f;

	//--------------------------------------------------------------------------------------
	///	���
	//--------------------------------------------------------------------------------------

	ClockArrow::ClockArrow(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const float& RotationZ, const Vec2& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_RustLife(0),
		m_rotationZ(RotationZ)
	{}

	void ClockArrow::OnCreate()
	{
		float HelfSize = m_helfSize;

		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_startScaleZ);
		ptrTransform->SetRotation(0.0f, 0.0f, m_rotationZ);
		ptrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_startPosZ); // 0.1����O�A0.9�͉�

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(true);

	}

	

}
