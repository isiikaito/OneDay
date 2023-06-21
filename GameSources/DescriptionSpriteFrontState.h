/*!
@file DescriptionSpriteFrontState.h
@brief 説明書のステート
@author Kaito Isii
*/

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
			float m_moveTime = 0.0f;				//!動いている時間
			float m_stateChangePositionX = -1300.0f;//!テクスチャを横スライドする座標

			//!シングルトンパターン
			DescriptionSpriteFrontState(const DescriptionSpriteFrontState&) = delete;//!関数を削除する
			DescriptionSpriteFrontState& operator=(const DescriptionSpriteFrontState&) = delete;//!operatorの中にある=を削除（コピーされないように）

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
			Vec3 m_textureResetPosition = Vec3(0.0f, 0.0f, 0.2f);//!テクスチャのポジション
			//!シングルトンパターン
			DescriptionSpriteStandbyFrontState(const DescriptionSpriteStandbyFrontState&) = delete;//!関数を削除する
			DescriptionSpriteStandbyFrontState& operator=(const DescriptionSpriteStandbyFrontState&) = delete;//!operatorの中にある=を削除（コピーされないように）

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
			float m_moveTime = 0.0f;			//!動く時間
			float m_stateChangePositionX = 0.0f;//!ステートを変更する位置

			//!シングルトンパターン
			DescriptionPageBackToState(const DescriptionPageBackToState&) = delete;//!関数を削除する
			DescriptionPageBackToState& operator=(const DescriptionPageBackToState&) = delete;//!operatorの中にある=を削除（コピーされないように）

		public:
			static DescriptionPageBackToState* Instance();


			virtual void Enter(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Execute(DescriptionSpriteFront* descriptionSpriteFront)override;
			virtual void Exit(DescriptionSpriteFront* descriptionSpriteFront)override;
		};

		//-------------------------------------------------------------------



	}
}
