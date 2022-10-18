/*!
@file Hunter.h
@brief ハンターの作成
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	//--------------------------------------------------------
	//!ハンター
	//--------------------------------------------------------
	class Hunter :public GameObject
	{
		Vec3 m_StartPosition;

	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
        Hunter(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------

		virtual ~Hunter();
		//アクセサ
		//初期化
		virtual void OnCreate() ;
		
	};

}
//!end basecross
