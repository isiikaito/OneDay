#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "DescriptionSpriteFront.h"

namespace basecross
{
	namespace kaito
	{

		enum class PageNumber {
			farst,
			second,
			three,
			four
		};

		class DescriptionSpriteFrontState :public State<DescriptionSpriteFront>
		{
		private:
			DescriptionSpriteFrontState() {}
			float m_moveTime = 0.0f;
			float m_stateChangePositionX = -1300.0f;

			//!�V���O���g���p�^�[��
			DescriptionSpriteFrontState(const DescriptionSpriteFrontState&) = delete;//!�֐����폜����
			DescriptionSpriteFrontState& operator=(const DescriptionSpriteFrontState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static DescriptionSpriteFrontState* Instance();


			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};

		//-------------------------------------------------------------------


		class DescriptionSpriteStandbyFrontState :public State<DescriptionSpriteFront>
		{
		private:
			DescriptionSpriteStandbyFrontState() {}
			Vec3 m_textureResetPosition = Vec3(0.0f, 0.0f, 0.2f);
			//!�V���O���g���p�^�[��
			DescriptionSpriteStandbyFrontState(const DescriptionSpriteStandbyFrontState&) = delete;//!�֐����폜����
			DescriptionSpriteStandbyFrontState& operator=(const DescriptionSpriteStandbyFrontState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static DescriptionSpriteStandbyFrontState* Instance();


			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};


		class DescriptionPageBackToState :public State<DescriptionSpriteFront>
		{
		private:
			DescriptionPageBackToState() {}
			float m_moveTime = 0.0f;
			float m_stateChangePositionX = 0.0f;

			//!�V���O���g���p�^�[��
			DescriptionPageBackToState(const DescriptionPageBackToState&) = delete;//!�֐����폜����
			DescriptionPageBackToState& operator=(const DescriptionPageBackToState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static DescriptionPageBackToState* Instance();


			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};

		//-------------------------------------------------------------------



	}
}
