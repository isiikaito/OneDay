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
	private:
		CsvFile m_GameStageCsvA; // !�����̔z�u
		CsvFile m_GameStageCsvB; // !�����̔z�u2
		CsvFile m_GameStageCsvC; // !�����̔z�u3
		CsvFile m_StageCsv;          //!�X�e�[�WCSV�t�@�C��
		float m_TotalTime;//!�g�[�^������(�^�C�}�[�̍쐬)
		const float m_GameTime;


	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),m_TotalTime(31.0f), m_GameTime(31.0f) {}
		virtual ~GameStage() {}

		void CreateViewLight();  //!�r���[�̍쐬
		void CreateStageFloor(); //!�X�e�[�W�̏�
		void CreatePlayer();//!�v���C���[�̍쐬
		void CreateStageWall(); //!�X�e�[�W�̕�
		void CreateStageBuilding(); //!�X�e�[�W�̌���
		void CreateKey();//!���̍쐬
		void CreateClockSprite(); //!���v�̃X�v���C�g�̍쐬
		void CreateStageGate(); //!�X�e�[�W�̖�
		void CerateVillager();//!���l�̍쐬
		void CerateHunter();//!�n���^�[�̍쐬
		void CreateAlertlevelGauge();//!�x���x�Q�[�W�̍쐬
		void CreateLightingCol();//!���C�g�̐F��ς��鏈��
		void CreateWoodenBox();//!�ؔ��̍쐬
		void CreateTimerSprite();//!�^�C�}�[�X�v���C�g�쐬
		shared_ptr<SoundItem>m_BGM;
		void CreatePlayBGM();//!BGM�쐬
		void CreateHeartSprite();//!�n���^�[�̃��C�t�̍쐬
		void CreateArrow();//!���̍쐬
		void CreateGameOver();//!�Q�[���I�[�o�[�X�v���C�g
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy() override;

		
		//void OnPushA();//!A�{�^��
		
		

	};
}
//end basecross

