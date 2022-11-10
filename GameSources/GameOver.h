/*!
@file GameOver.h
@brief �Q�[���I�[�o�[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
//--------------------------------------------------------------------------------------
///	�Q�[���I�[�o�[�X�v���C�g
//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameObject {
	private:
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:

		GameOverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//�j��
		virtual ~GameOverSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
//end basecross
