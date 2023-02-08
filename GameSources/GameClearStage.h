/**
*@file GameClear.h
*@brief �Q�[���N���A��ʂ̃w�b�_�[�t�@�C��
*@author Ayumu Muroi
*@details �Q�[���N���A��ʂ̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���N���A�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameClearStage : public Stage {
	private:
		InputHandler<GameClearStage> m_InputHandler;//!���̓n���h���[		
		shared_ptr<SoundItem>m_BGM; //!BGM
		CsvFile m_StageCsv;   //!�X�e�[�WCSV�t�@�C��
		float m_stageChangeTime =0.0f;
		bool m_setTexture=false;

	public:
		
		//�r���[�̍쐬
		void CreateViewLight();
		void CreatePlayer(); //!�v���C���[�̒ǉ�
		//�X�v���C�g�̍쐬
		void CreateGameClearSprite();
		void CreateStageFloor(); //!��
		void CreateStageBuilding(); //!���� 
		void CreateStageWall(); //!��
		void CreateStageGate(); //!��
		void CerateGoalPlayer(); //!�S�[���̃v���C���[
		CsvFile m_GameStageCsvD;// !�����̔z�u4

		//�\�z�Ɣj��
		GameClearStage() :Stage() {}
		virtual ~GameClearStage() {}
		//������
		virtual void OnCreate()override;

		void OnPushA();//!A�{�^��
		
		//--------------------------------------------------------------------------------------
		/*!
		@brief ����
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDestroy() override;
		//�X�V
		virtual void OnUpdate()override;
	 };
}
//end basecross
