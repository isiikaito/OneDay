/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {

		CsvFile m_CsvC;          //!CSV�t�@�C������C
		void CreateViewLight();  //!�r���[�̍쐬
		void CreateStageFloor(); //!�X�e�[�W�̏�
		void CreatePlayer();//!�v���C���[�̍쐬
		void CreateStageWall(); //!�X�e�[�W�̕�

		void CerateHunter();//!�n���^�[�̍쐬

		void CreateTimerSprite();//!�^�C�}�[�X�v���C�g�쐬
		void CreateTraceSprite();//!�������̃X�v���C�g�쐬
		void CreateWallSprite();//!�ǖ͗l�̃X�v���C�g�쐬
		void CreateScrollSprite();//!�X�N���[������X�v���C�g�쐬
		void CreateScoreSprite();//!�X�R�A�X�v���C�g�쐬

		float m_TotalTime;//!�g�[�^������(�^�C�}�[�̍쐬)


	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),m_TotalTime(30.0f) {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;
	};


}
//end basecross

