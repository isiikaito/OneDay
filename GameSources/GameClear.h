/**
*@file GameClear.h
*@brief �Q�[���N���A��ʂ̃w�b�_�[�t�@�C��
*@author Kanazawa yuma
*@details �Q�[���N���A��ʂ̎���
*/
#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	�Q�[���N���A�X�v���C�g
//--------------------------------------------------------------------------------------
	class GameClearSprite : public GameObject {
	private:
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:

		GameClearSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~GameClearSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};

}
//end basecross

