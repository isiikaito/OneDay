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
		CsvFile m_EnemyCsv;//!�G�̃g�����X�t�H�[��csv�t�@�C��
		CsvFile m_Point;//!����|�C���gcsv�t�@�C��	
       InputHandler<GameStage> m_InputHandler;//!���̓n���h���[
		float m_TotalTime;//!�g�[�^������(�^�C�}�[�̍쐬)
		const float m_GameTime = 31.0f;


	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),m_TotalTime(m_GameTime) {}
		virtual ~GameStage() {}

		void CreateViewLight();  //!�r���[�̍쐬
		void CreateStageFloor(); //!�X�e�[�W�̏�
		void CreatePlayer();//!�v���C���[�̍쐬
		void CreateStageWall(); //!�X�e�[�W�̕�
		void CreateStageBuilding(); //!�X�e�[�W�̌���
		void CreateKey();//!���̍쐬
		void CreateStageGate(); //!�X�e�[�W�̖�
		void CerateHunter();//!�n���^�[�̍쐬
		void CreateLightingCol();//!���C�g�̐F��ς��鏈��
		void CreateTimerSprite();//!�^�C�}�[�X�v���C�g�쐬
		void CreateSuprisedSprite();
		shared_ptr<SoundItem>m_BGM;
		void CreatePlayBGM();//!BGM�쐬
		void CreateHeartSprite();

		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy() override;


		
		void OnPushA();//!A�{�^��
		
		

	};
}
//end basecross

