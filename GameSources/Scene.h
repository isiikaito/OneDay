/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
	private:

		int m_keyNamber;				//!����ۑ����Ă���CSV�����ʂ��鐔��
		int m_AlertlevelCount;			//!�x���x�̐���
		bool m_IsGameOver;				//!�Q�[���I�[�o�[�������ǂ���
		bool m_IsGameOverSprite;		//!�Q�[���I�[�o�[�X�v���C�g�̕\�����ł��Ă��邩
		float m_gameStageTime;			//!���Ɩ�̎���
		int m_meatNumber;				//!���̈ʒu���ۑ����ꂽCSV�̐���
		int m_date;						//!���݂̓��t
		bool m_IsplayerChangeDirecting;	//!�v���C���[�̕ϐg���邩�ǂ���
		float m_dayTime;				//!����̎���
		float m_playerConditionTime;	//!�v���C���[�̏�Ԃ̎���
		bool m_gameStrat;				//!�Q�[���̃X�^�[�g
		float m_emissiveChangeTime;		//!���C�g�^�C��
		int m_descriptionStageNumber;	//!�������̃y�[�W��
		bool m_IsmoveForwardInaPage;	//!�y�[�W��i�܂��Ă��邩�ǂ���
		bool m_IspageBackTo;			//!�y�[�W��߂��Ă��邩�ǂ���
		bool m_goleGateParameter;		//!�S�[���X�e�[�W�̎��̖�̃p�����[�^��K������
		float m_soundvolume;			//!���ʉ��̑傫��

	public:
		//----------------------------------------------------------------------(----------------
		/*!
		@brief ���\�[�X
		*/
		void CreateResourses();

		//----------------------------------------------------------------------(----------------
		/*!
		@brief �R���X�g���N�^
		*/
		Scene() :SceneBase(),
			m_goleGateParameter(false),
			m_IsmoveForwardInaPage(true),
			m_IspageBackTo(true),
			m_AlertlevelCount(0),
			m_emissiveChangeTime(1.0f),
			m_date(0),
			m_playerConditionTime(0.0f),
			m_IsplayerChangeDirecting(0.0f),
			m_IsGameOver(false),
			m_dayTime(0.0f),
			m_IsGameOverSprite(false),
			m_gameStageTime(0.0f),
			m_keyNamber(0),
			m_meatNumber(0),
			m_gameStrat(true),
			m_descriptionStageNumber(0),
			m_soundvolume(0.7f)

		{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		virtual ~Scene();

		//--------------------------------------------------------------------------------------	
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief �x���x�̎擾
		@return	�x���x�̃J�E���g
		*/
		int GetAlertlevelCount() const
		{
			return m_AlertlevelCount;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �x���x�̐ݒ�
		@param �x���x
		@return	�Ȃ�
		*/
		void SetAlertlevelCount(int AlertlevelCount);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �ǉ��̓G�̍쐬
		@return	�Ȃ�
		*/
		void CreateEnemy();

		//--------------------------------------------------------------------------------------
		/*!
		@brief �Q�[���I�[�o�[�̎擾
		@return	�Q�[���I�[�o�[�������ǂ���
		*/
		bool GetGameOver() const
		{
			return m_IsGameOver;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �Q�[���I�[�o�[�̐ݒ�
		@param �Q�[���I�[�o�[���ǂ���
		@return	�@�Ȃ�
		*/
		void SetGameOver(bool gameOver)
		{
			m_IsGameOver = gameOver;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �Q�[���I�[�o�[�X�v���C�g�\���̎擾
		@return	�Q�[���I�[�o�[�������ǂ���
		*/
		bool GetGameOverSprite() const
		{
			return m_IsGameOverSprite;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �Q�[���I�[�o�[�X�v���C�g�\���̐ݒ�
		@param �Q�[���I�[�o�[�X�v���C�g�\��
		@return	�Ȃ�
		*/
		void SetGameOverSprite(bool gameOverSprite)
		{
			m_IsGameOverSprite = gameOverSprite;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ����csv�̃i���o�[�̎擾
		@return	�Q�[���I�[�o�[�������ǂ���
		*/
		int GetKeyNamber() const
		{
			return m_keyNamber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ����csv�̃i���o�[�̐ݒ�
		@param ����csv�̃i���o�[
		@return	�Ȃ�
		*/
		void SetKeyNamber(int keyNamber)
		{
			m_keyNamber = keyNamber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �Q�[���̎��Ԃ̎擾
		@return �Q�[���̎���
		*/
		float GetGameTime() const
		{
			return m_gameStageTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �Q�[���̎��Ԃ̐ݒ�
		@param �Q�[���̎���
		*/
		void SetGameTime(float gameStageTime)
		{
			m_gameStageTime = gameStageTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ����csv�̃i���o�[�̎擾
		@return	�Q�[���I�[�o�[�������ǂ���
		*/
		int GetMeatNamber() const
		{
			return m_meatNumber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ���t�̐ݒ�
		@param ���t
		*/
		void SetDate(int Date)
		{
			m_date = Date;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ���t�̎擾
		@return	���݂̓��t
		*/
		int GetDate() const
		{
			return m_date;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ����csv�̃i���o�[�̐ݒ�
		@param ����csv�̃i���o�[
		*/
		void SetMeatNamber(int MeatNamber)
		{
			m_meatNumber = MeatNamber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �e�N�X�`���̓ǂݍ���
		@param �e�N�X�`���̖��O
		@param[in] �g���Ƃ��̃e�N�X�`���̖��O
		*/
		void RoadTexture(const wstring& TextureName, const wstring& UseTextureName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �T�E���h�̓ǂݍ���
		@param ���̖��O
		@param[in] �g���Ƃ��̉��̖��O
		*/
		void RoadSound(const wstring& soundDataName, const wstring& soundName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�^�e�B�b�N���f���̓ǂݍ���
		@param �X�^�e�B�b�N���f��bmf�̖��O
		@param[in] �g���Ƃ��̃X�^�e�B�b�N���f���̖��O
		*/
		void RoadStaticModelMesh(const wstring& staticModelbmfName, const wstring& staticModelMeshName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �{�[�����f���̂̓ǂݍ���
		@param �{�[�����f����bmf�̖��O
		@param[in] �{�[�����f���̃��b�V���̖��O
		@param[in out] �g���Ƃ��̃{�[�����f���̖��O
		*/
		void RoadBoneModel(const wstring& BoneModelbmfName, const wstring& BoneModelMeshName, const wstring& BomeModelMeshTangentName);

		//--------------------------------------------------------------------------------------
		/*!
		@brief �v���C���[���ϐg���邩�ǂ����̎擾
		@return	�v���C���[���ϐg���邩�ǂ���
		*/
		bool GetPlayerChangeDirecting() const
		{
			return m_IsplayerChangeDirecting;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �v���C���[�̌����ڂ�ύX���鎞�Ԃ̐ݒ�
		@param �v���C���[�̌����ڂ�ύX���鎞��
		*/
		void SetPlayerChangeDirecting(bool PlayerChangeDirecting)
		{
			m_IsplayerChangeDirecting = PlayerChangeDirecting;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief ���ɂ��̎擾
		@return	���݂̓��ɂ�
		*/
		float GetDayTime() const
		{
			return m_dayTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ����̎��Ԃ̐ݒ�
		@param ����̎���
		*/
		void SetDayTime(float DayTime)
		{
			m_dayTime = DayTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�v���C���[�̏�Ԃ̎��Ԃ̎擾
		@return �v���C���[�̏�Ԃ̎��Ԃ�Ԃ�
		*/
		float GetPlayerConditionTime() const
		{
			return m_playerConditionTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�v���C���[�̏�Ԃ̎��Ԃ̐ݒ�
		@param �v���C���[�̏�Ԃ̎���
		*/
		void SetPlayerConditionTime(float PlayerConditionTime)
		{
			m_playerConditionTime = PlayerConditionTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�Q�[�����X�^�[�g�������Ƃ�`����
		@return �Q�[�����X�^�[�g�������ǂ���
		*/
		bool GetGameStrat() const
		{
			return m_gameStrat;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�Q�[���X�^�[�g�����Ƃ��̐ݒ�
		@param �Q�[���X�^�[�g�������ǂ���
		*/
		void SetGameStrat(bool gameStrat)
		{
			m_gameStrat = gameStrat;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�G�~�b�V�u�J���[�̕ς�鎞�Ԃ̎擾
		@return �I�u�W�F�N�g�̖��邳�ύX
		*/
		float GetEmissiveChangeTime() const
		{
			return m_emissiveChangeTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�G�~�b�V�u�J���[�̕ς�鎞�Ԃ̐ݒ�
		@param �G�~�b�V�u�J���[�̕ς�鎞��
		*/
		void SetEmissiveChangeTime(float emissiveChangeTime)
		{
			m_emissiveChangeTime = emissiveChangeTime;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�������̃y�[�W��
		@return �������̃y�[�W����Ԃ�
		*/
		int GetDescriptionStageNumber() const
		{
			return m_descriptionStageNumber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�������̃y�[�W���̐ݒ�
		@param �������̃y�[�W��
		*/
		void SetDescriptionStageNumber(int descriptionStageNumber)
		{
			m_descriptionStageNumber = descriptionStageNumber;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�y�[�W���߂����Ă��邩�ǂ����̎擾
		*/
		bool GetIsMoveForwardInaPage() const
		{
			return m_IsmoveForwardInaPage;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�y�[�W���߂����Ă��邩�ǂ����̐ݒ�
		@param �y�[�W���߂����Ă��邩�ǂ���
		*/
		void SetIsMoveForwardInaPage(bool IsmoveForwardInaPage)
		{
			m_IsmoveForwardInaPage = IsmoveForwardInaPage;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�y�[�W��߂��Ă��邩�ǂ���
		*/
		bool GetIspageBackTo() const
		{
			return m_IspageBackTo;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�y�[�W�����ǂ��Ă��邩�ǂ����̐ݒ�
		@param �y�[�W�����ǂ��Ă��邩�ǂ���
		*/
		void SetIsPageBackTo(bool IspageBackTo)
		{
			m_IspageBackTo = IspageBackTo;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�S�[���p�����[�^�̖��K�p���邩�ǂ���
		*/
		bool GetGoleGateParameter() const
		{
			return m_goleGateParameter;

		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief�@�S�[���p�����[�^�̖��K�p���邩�ǂ���
		@param �S�[���p�����[�^�̖��K�p���邩�ǂ���
		*/
		void SetGoleGateParameter(bool goleGateParameter)
		{
			m_goleGateParameter = goleGateParameter;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �v���C���[���ϐg���邩�ǂ����̎擾
		*/
		float GetSoundvolume() const
		{
			return m_soundvolume;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief ���ʂ̐ݒ�
		@param ����
		*/
		void SetSoundvolume(float soundvolume)
		{
			m_soundvolume = soundvolume;
		}
	};

}

//end basecross