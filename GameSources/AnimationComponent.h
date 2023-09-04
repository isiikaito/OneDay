/*!
@file AnimationComponent.h
@author Kaito Isii
@brief  アニメーションの読み込み処理
*/
#pragma once
#include "stdafx.h"

/**basecross共通のネームペース*/
namespace basecross
{
	struct ReadAnimationData
	{
		wstring animationName;	//!アニメーションの名前
		int startSample;		//!アニメーションのサンプル
		int sampleLengeth;		//!アニメーションの長さ
		bool loop;				//!アニメーションをループ指せるかどうか
		float samplesParSecond;	//!アニメーションの再生スピード
		ReadAnimationData(
			const wstring animationName,
			const int startSample,
			const int sampleLengeth,
			const bool loop,
			const float samplesParSecond
			):
			animationName(animationName),
			startSample(startSample),
			sampleLengeth(sampleLengeth),
			loop(loop),
			samplesParSecond(samplesParSecond)
		{}

	};

	class AnimationComponent :public Component
	{
		wstring m_useObjAnimation;
		wstring m_currentAnimation;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	このコンポーネントを所持するゲームオブジェクト
		@param[in out]	useObjAnimation	使うオブジェクトのアニメーション
		@param[in]	currentAnimation	現在のアニメーション
		*/
		explicit AnimationComponent(
			const shared_ptr<GameObject>& GameObjectPtr,wstring useObjAnimation,wstring currentAnimation) :
			Component(GameObjectPtr), m_useObjAnimation(useObjAnimation), m_currentAnimation(currentAnimation) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~AnimationComponent() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	アニメーションデータの読み込み
		@param	keyName　取り出したいアニメーションのオブジェクトの名前
		*/
		std::vector<ReadAnimationData> AnimationDates(const wstring& keyName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		*/
		virtual void OnUpdate()override{}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}

