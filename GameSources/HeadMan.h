/*!
@file HeadMan.h
@brief 村長の作成
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
namespace basecross
{
	//--------------------------------------------------------
	//!村長
	//--------------------------------------------------------
	class HeadMan :public GameObject
	{
	private:
		bool m_IsheadManCommentOn;				//!村長が話しているかどうか
		BoneModelDeta m_headManBoneModelDeta;	//!プレイヤーのモデルデータ

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村長がコメントを表示する処理
		*/
		void HeadManComment();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	村長のアニメーション更新
		*/
		void HeadManAnimation();


	public:
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		HeadMan(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		virtual ~HeadMan() {}

		
		//--------------------------------------------------------------------------------------
		/*!
		@brief	村長がコメントしているかどうかの取得
		@return 村長がコメントしているかどうか
		*/
		bool GetHeadManComment() const
		{
			return m_IsheadManCommentOn;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		*/
		virtual void OnCreate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新
		*/
		virtual void OnUpdate();
	};
}
