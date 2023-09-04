/*!
@file GameStage.cpp
@brief ゲームステージ実体
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "EffectManager.h"


namespace basecross
{
	
		//!インスタンスの生成(実体の作成)
		EffectManager* EffectManager::Instance()
		{
			
			static EffectManager instance;
			return &instance;
		}

		void EffectManager::OnCreate()
		{
			//エフェクトの初期化
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);

			//!エフェクト作成
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();


			wstring keyEffectStr = DataDir + L"Effects\\key.efk";										//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
			m_KeyEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, keyEffectStr);				//!取得したエフェクトで作る

			wstring ScratchEffectStr = DataDir + L"Effects\\kill.efk";									//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
			m_ScratchEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, ScratchEffectStr);		//!取得したエフェクトで作る

			wstring TransformEffectStr = DataDir + L"Effects\\Transform2.efk";							//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
			m_TransformEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, TransformEffectStr);	//!取得したエフェクトで作る

			wstring MeatEffectStr = DataDir + L"Effects\\smoke.efk";									//!エフェクトの保存されているフォルダ\\保存したエフェクトの名前
			m_MeatEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, MeatEffectStr);			//!取得したエフェクトで作る

		

		}
	
}