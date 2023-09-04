/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "EffectManager.h"


namespace basecross
{
	
		//!�C���X�^���X�̐���(���̂̍쐬)
		EffectManager* EffectManager::Instance()
		{
			
			static EffectManager instance;
			return &instance;
		}

		void EffectManager::OnCreate()
		{
			//�G�t�F�N�g�̏�����
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);

			//!�G�t�F�N�g�쐬
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();


			wstring keyEffectStr = DataDir + L"Effects\\key.efk";										//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
			m_KeyEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, keyEffectStr);				//!�擾�����G�t�F�N�g�ō��

			wstring ScratchEffectStr = DataDir + L"Effects\\kill.efk";									//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
			m_ScratchEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, ScratchEffectStr);		//!�擾�����G�t�F�N�g�ō��

			wstring TransformEffectStr = DataDir + L"Effects\\Transform2.efk";							//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
			m_TransformEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, TransformEffectStr);	//!�擾�����G�t�F�N�g�ō��

			wstring MeatEffectStr = DataDir + L"Effects\\smoke.efk";									//!�G�t�F�N�g�̕ۑ�����Ă���t�H���_\\�ۑ������G�t�F�N�g�̖��O
			m_MeatEfkEffect = ObjectFactory::Create<EfkEffect>(m_EfkInterface, MeatEffectStr);			//!�擾�����G�t�F�N�g�ō��

		

		}
	
}