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

		

		CsvFile m_StageCsv;          //!�X�e�[�WCSV�t�@�C��
		CsvFile m_EnemyCsv;//!�G�̃g�����X�t�H�[��csv�t�@�C��
		CsvFile m_Point;//!����|�C���gcsv�t�@�C��
		void CreateViewLight();  //!�r���[�̍쐬
		void CreateStageFloor(); //!�X�e�[�W�̏�
		void CreatePlayer();//!�v���C���[�̍쐬
		void CreateStageWall(); //!�X�e�[�W�̕�
		void CreateStageBuilding(); //!�X�e�[�W�̌���
		void CerateHunter();//!�n���^�[�̍쐬
		void CreateTimerSprite();//!�^�C�}�[�X�v���C�g�쐬
		

		float m_TotalTime;//!�g�[�^������(�^�C�}�[�̍쐬)

		const float m_GameTime = 31.0f;


	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),m_TotalTime(m_GameTime) {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;
	};
}
//end basecross

