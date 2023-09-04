/*!
@file AnimationComponent.h
@author Kaito Isii
@brief  �A�j���[�V�����̓ǂݍ��ݏ���
*/
#pragma once
#include "stdafx.h"

/**basecross���ʂ̃l�[���y�[�X*/
namespace basecross
{
	struct ReadAnimationData
	{
		wstring animationName;	//!�A�j���[�V�����̖��O
		int startSample;		//!�A�j���[�V�����̃T���v��
		int sampleLengeth;		//!�A�j���[�V�����̒���
		bool loop;				//!�A�j���[�V���������[�v�w���邩�ǂ���
		float samplesParSecond;	//!�A�j���[�V�����̍Đ��X�s�[�h
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
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g
		@param[in out]	useObjAnimation	�g���I�u�W�F�N�g�̃A�j���[�V����
		@param[in]	currentAnimation	���݂̃A�j���[�V����
		*/
		explicit AnimationComponent(
			const shared_ptr<GameObject>& GameObjectPtr,wstring useObjAnimation,wstring currentAnimation) :
			Component(GameObjectPtr), m_useObjAnimation(useObjAnimation), m_currentAnimation(currentAnimation) {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~AnimationComponent() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate()override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�A�j���[�V�����f�[�^�̓ǂݍ���
		@param	keyName�@���o�������A�j���[�V�����̃I�u�W�F�N�g�̖��O
		*/
		std::vector<ReadAnimationData> AnimationDates(const wstring& keyName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V����
		*/
		virtual void OnUpdate()override{}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�`�揈���B�f�t�H���g�͉����s��Ȃ�
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	};
}

