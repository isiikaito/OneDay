/*!
@file GameManager.h
@brief ゲームステージ時間マネージャー
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "EfkInterfece.h"

namespace basecross
{

	class EffectManager
	{

	private:
		EffectManager() {}
		//!シングルトンパターン
		EffectManager(const EffectManager&) = delete;//!関数を削除する
		EffectManager& operator=(const EffectManager&) = delete;//!operatorの中にある=を削除（コピーされないように）
		//エフェクト
		shared_ptr<EfkEffect> m_KeyEfkEffect;				//鍵を取った時のエフェクト
		shared_ptr<EfkEffect> m_ScratchEfkEffect;			//攻撃した時のエフェクト
		shared_ptr<EfkEffect> m_TransformEfkEffect;			//狼に変身した時のエフェクト
		shared_ptr<EfkEffect> m_MeatEfkEffect;				//狼に変身した時のエフェクト
		//エフェクト実行オブジェクト
		shared_ptr<EfkPlay> m_KeyEfkPlay;
		shared_ptr<EfkPlay> m_ScratchEfkPlay;
		shared_ptr<EfkPlay> m_TransformEfkPlay;
		shared_ptr<EfkPlay> m_MeatEfkPlay;

		shared_ptr<EfkInterface> m_EfkInterface;			//!エフェクトインターフェース



	public:
		static EffectManager* Instance();

		void OnCreate();
		//----------------------------------------------------------------------------------
		/*!
		@brief	攻撃エフェクト
		@param[in]	position	エフェクト位置
		*/
		void ScratchEfkPlay(Vec3 position)
		{
			m_ScratchEfkPlay = ObjectFactory::Create<EfkPlay>(m_ScratchEfkEffect, position);//!エフェクトの作成
		}

		//----------------------------------------------------------------------------------
		/*!
		@brief	カギのエフェクト
		@param[in]	position	エフェクト位置
		*/
		void KeyEfkPlay(Vec3 position)
		{
			m_KeyEfkPlay = ObjectFactory::Create<EfkPlay>(m_KeyEfkEffect, position);//!エフェクトの作成
		}


		//----------------------------------------------------------------------------------
		/*!
		@brief	エフェクトインターフェースの取得
		*/
		shared_ptr<EfkInterface> GetEfkInterface()
		{
			return m_EfkInterface;
		}

		//----------------------------------------------------------------------------------
		/*!
		@brief	肉のエフェクト
		@param[in]	position	エフェクト位置
		*/
		void MeatEfkPlay(Vec3 position)
		{
			m_MeatEfkPlay = ObjectFactory::Create<EfkPlay>(m_MeatEfkEffect, position);//!エフェクトの作成

		}

		//----------------------------------------------------------------------------------
		/*!
		@brief	変身のエフェクト
		@param[in]	position	エフェクト位置
		*/
		void PlayerChangeEfkPlay(Vec3 position)
		{
			m_TransformEfkPlay = ObjectFactory::Create<EfkPlay>(m_TransformEfkEffect, position);//!エフェクトの作成
		}

	};
}
//end basecross


