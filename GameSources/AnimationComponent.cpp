/*!
@file AnimationComponent.cpp
@brief �A�j���[�V������ǂݍ��ގ���
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross
{
	void AnimationComponent::OnCreate()
	{
		auto ptrDraw = GetGameObject()->GetComponent<BcPNTnTBoneModelDraw>();

		auto animationDatas = AnimationDates(m_useObjAnimation);//!�w��̃I�u�W�F�N�g�A�j���[�V������ǂݍ���

		//!�A�j���[�V�����̃f�[�^����
		for (auto& animationData : animationDatas)
		{
			ptrDraw->AddAnimation
			(
				animationData.animationName,
				animationData.startSample,
				animationData.sampleLengeth,
				animationData.loop,
				animationData.samplesParSecond
			);
		}
		ptrDraw->ChangeCurrentAnimation(m_currentAnimation);//!�ŏ��̃A�j���[�V������ݒ肷��


	}

	

	//!�A�j���[�V�����̓ǂݍ��݊֐�
	std::vector<ReadAnimationData> AnimationComponent::AnimationDates(const wstring& keyName)
	{
		std::vector<ReadAnimationData>result;												//!�ϐ���
		vector<wstring>LineVec;																//!CSV�̍s�P�ʂ̔z��
		auto& app = App::GetApp();															//!�A�v���̎擾
		wstring DataDir;																	//!�f�[�^
		App::GetApp()->GetDataDirectory(DataDir);											//!�f�[�^���擾
		auto fullPass = DataDir + L"csvFolder\\" L"Animation\\" + L"ObjectAnimation.csv";	//!�t�@�C���̓���
		CsvFile csvFile;
		csvFile.SetFileName(fullPass);														//!���肵��csv�t�@�C����ǂݍ���
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);												//!0�Ԗڂ̃J������L""�ł���s�𔲂��o��
		
		//!�擾�����s�̏��
		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;															//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');										//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')
			wstring	animationName = Tokens[1];												//!�A�j���[�V�����̖��O�̎擾
			int startSample = (int)_wtof(Tokens[2].c_str());								//!�A�j���[�V�����̃T���v���̎擾
			int sampleLengeth = (int)_wtof(Tokens[3].c_str());								//!�A�j���[�V�����̒����̎擾
			bool loop = (bool)_wtof(Tokens[4].c_str());										//!�A�j���[�V���������[�v�w���邩�ǂ����擾
			float samplesParSecond = (float)_wtof(Tokens[5].c_str());						//!�A�j���[�V�����̍Đ��X�s�[�h�擾
				
			
			result.push_back(ReadAnimationData(animationName, startSample, sampleLengeth, loop, samplesParSecond));//!�A�j���[�V�����̃f�[�^���������z��Ɋi�[

		}

		return result;
	}

}