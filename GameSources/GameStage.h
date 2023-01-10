/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "EfkInterfece.h"
namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	private:
		CsvFile m_GameStageCsvA; // !�����̔z�u
		CsvFile m_GameStageCsvB; // !�����̔z�u2
		CsvFile m_GameStageCsvC; // !�����̔z�u3
		CsvFile m_GameStageCsvD;// !�����̔z�u4
		CsvFile m_KeyPositon; // !���̔z�u
		CsvFile m_StageCsv;   //!�X�e�[�WCSV�t�@�C��
		CsvFile m_MeatPositon;//!���̃|�W�V������CSV�t�@�C��
		shared_ptr<SoundItem>m_BGM; //!BGM
		shared_ptr<SoundItem>m_GameOverBGM; //!�Q�[���I�[�o�[��BGM
		float m_TotalTime;//!�g�[�^������(�^�C�}�[�̍쐬)
		const float m_GameTime;
		float m_MeatTime;//!���̈ʒu�������_���ɂ��鎞��
		int m_MeatNumber;//!���̈ʒu��ۑ�����CSV�̔ԍ�
		int m_Date;//!���t
		
		InputHandler<GameStage> m_InputHandler;//!���̓n���h���[
		shared_ptr<EfkInterface> m_EfkInterface;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),m_TotalTime(31.0f), m_GameTime(31.0f), m_MeatNumber(0), m_MeatTime(0.0f), m_Date(0) {}
		virtual ~GameStage() {}

		void CreateViewLight();  //!�r���[�̍쐬
		void CreateStageFloor(); //!�X�e�[�W�̏�
		void CreatePlayer();//!�v���C���[�̍쐬
		void CreateStageWall(); //!�X�e�[�W�̕�
		void CreateStageBuilding(); //!�X�e�[�W�̌���
		void CreateKey();//!���̍쐬
		void CreateClockSprite(); //!���v�̃X�v���C�g�̍쐬
		void CreateCircleClockSprite(); //!���v�̉~�Ղ̃X�v���C�g
		void CreateStageGate(); //!�X�e�[�W�̖�
		void CerateVillager();//!���l�̍쐬
		void CerateHunter();//!�n���^�[�̍쐬
		void CreateAlertlevelGauge();//!�x���x�Q�[�W�̍쐬
		void CreateLightingCol();//!���C�g�̐F��ς��鏈��
		void CreateWoodenBox();//!�ؔ��̍쐬
		void CreateWood();//�؂̍쐬
		void CreateTimerSprite();//!�^�C�}�[�X�v���C�g�쐬
		void CreatePlayBGM();//!BGM�쐬
		void CreateGameOverBGM(); //!�Q�[���I�[�o�[��BGM
		void DestroyGameOverBGM(); //!�Q�[���I�[�o�[��BGM�̍폜
		void CreateHeartSprite();//!�n���^�[�̃��C�t�̍쐬
		void CreateArrow();//!���̍쐬
		void CreateGameOver();//!�Q�[���I�[�o�[�X�v���C�g
		void CreateHeadMan();//!�����̍쐬
		void GameTime();//!���Ɩ��ς��鎞��
		void CreateMeat();//!���̍쐬
		void CreateKeyFrame();//!�J�M�̃t���[��
		void CreateMeatGageBackGround();//!�����̃Q�[�W�̔w�i
		void CreateHungerGage();//!�󕠃Q�[�W�̍쐬
		void CreateMeatGageFrame();//!�󕠃Q�[�W�̘g�̍쐬
		void CreateClockArrow();//!���v�̐j
	
		//������
		virtual void OnCreate()override;

		shared_ptr<EfkInterface> GetEfkInterface() const
		{
			return m_EfkInterface;
		}

		virtual void OnUpdate()override;

		virtual void OnDraw() override;

		virtual void OnDestroy() override;

		
		void OnPushA();//!A�{�^��
		
		

	};
}
//end basecross

