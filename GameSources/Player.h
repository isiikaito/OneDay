/*!
@file Player.h
@brief �v���C���[�Ȃ�
*@author isii kaito
*/

#pragma once
#include "stdafx.h"
#include "MoveComponent.h"
#include "BoneModelComponent.h"
#include "EffectManager.h"


namespace basecross
{

	namespace kaito
	{
		//!�O���錾
		template<class entity_type>
		class State;
		//!�O���錾
		template <class entity_type>
		class StateMachine;
	}

	enum class PlayerModel {
		human,
		wolf
	};


	class Player : public GameObject
	{
	private:

		PlayerModel m_playerChange;							//!�v���C���[�̌����ڂ̏��
		int m_KeyCount;										//!���������Ă�����J�E���g
		const float m_Ded;									//!���S
		int m_PlayerPositionOnSecondMax;					//!�v���C���[�̈ʒu�̔z��̍ő�̒���
		int m_PlayerHp;										//!�v���C���[�̗̑�
		int m_meatCount;									//!�����擾������
		const int m_reset;									//1���[�v���Z�b�g
		float m_PlayerPositionTime;							//!�v���C���[�̈ʒu���擾����܂ł̎���
		float m_vibrationTime;								//!�U�����Ă��鎞��
		float m_GetPlayerPositionTime;						//!�v���C���[�̈ʒu�̎擾
		bool m_playerTaskDay;								//!���̃~�b�V�����̕\��
		bool m_playerTaskNight;								//!��̃~�b�V�����̕\��
		bool m_IsPlayerDed;									//!�v���C���[�����񂾂��ǂ����̔���
		bool m_IsvibrationOn;								//!�U�����Ă��邩�ǂ���
		std::vector<Vec3>m_PlayerPositionOnSecond;			//!�v���C���[�̖��b���Ƃ̈ʒu�̎擾
		kaito::StateMachine<Player>* m_StateMachine;		//!�v���C���[�̃X�e�[�g�}�V��
		WORD m_vibration;									//!�R���g���[���[�̐U��
		Vec3 m_meatPosition = Vec3(0);						//!���̃|�W�V����
		std::weak_ptr<PlayerMoveComponent> m_playermove;	//!�v���C���[�𓮂����R���|�[�l���g
		BoneModelDeta m_playerBoneModelDeta;				//!�v���C���[�̃��f���f�[�^
		std::weak_ptr<BcPNTnTBoneModelDraw>	m_draw;			//!�`��
		EffectManager* m_effectManager;						//!�G�t�F�N�g�}�l�[�W���[

		shared_ptr<SoundItem>m_Wolk;						//!������
		shared_ptr<SoundItem>m_Howling;						//!�I�I�J�~�̖���


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�𓮂���
		*/
		void MovePlayer();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���l���E������
		*/
		void Villagerkiller();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�n���^�[���E������
		*/
		void Hunterkiller();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�̃|�W�V��������萔�擾�̏���
		*/
		void GetPlayerPositionBrett();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�G��|�����Ƃ��̉�
		*/
		void EnemyDedSound();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�ؔ��̔j��̏���
		*/
		void BreakWoodBox();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	1�T�ԂŎ��ʏ���
		*/
		void OneWeek();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�U���G�t�F�N�g
		*/
		void AttackEffect();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���g���[���̐U������
		*/
		void Controllervibration();

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in] StagePtr	�X�e�[�W
		*/
		Player(const shared_ptr<Stage>& StagePtr);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		virtual ~Player() {}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������
		*/
		virtual void OnCreate() override;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V
		*/
		virtual void OnUpdate();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���g���[���[�̃{�^������B
		*/
		void OnPushB();

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�G�t�F�N�g�}�l�[�W���[�̎擾
		*/
		EffectManager* GetEffectManager()
		{
			return m_effectManager;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�̏�Ԃ̎擾
		@retrun �v���C���[�̏��
		*/
		PlayerModel GetPlayerChange()const
		{
			return m_playerChange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����̎擾
		@retrun ����
		*/
		shared_ptr<SoundItem> GetWolkSound()
		{
			return 	m_Wolk;

		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�E�o����
		*/
		void Escape();


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�̏�Ԃ̐ݒ�
		@�����@�v���C���[�̏��
		*/
		void SetPlayerChange(PlayerModel playerChange)
		{
			m_playerChange = playerChange;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b���Ƃ̃v���C���[�̈ʒu�̎擾
		@retrun ���b���Ƃ̃v���C���[�̈ʒu
		*/
		const std::vector<Vec3>& GetPlayerPositionOnSecond() const
		{
			return m_PlayerPositionOnSecond;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���b���Ƃ̃v���C���[�̈ʒu�̐ݒ�
		@retrun	���b���Ƃ̃v���C���[�̈ʒu
		*/
		void SetPlayerPositionOnSecond(const std::vector<Vec3>& PlayerPositionOnSecond)
		{
			m_PlayerPositionOnSecond = PlayerPositionOnSecond;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[��HP�擾
		@retrun �v���C���[��HP
		*/
		int GetPlayerHp() const
		{
			return m_PlayerHp;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[��HP�̐ݒ�
		@�����@�v���C���[��hP
		*/
		void SetPlayerHp(int PlayerHp)
		{
			m_PlayerHp = PlayerHp;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�s�[�h�̎擾
		@retrun �v���C���[�̃X�s�[�h
		*/
		float GetSpeed() const
		{
			return m_playermove.lock()->GetSpeed();
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�s�[�h�̐ݒ�
		@�����@�v���C���[�̃X�s�[�h
		*/
		void SetSpeed(float speed)
		{
			m_playermove.lock()->SetSpeed(speed);
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�����񂾂��ǂ����̎擾
		@retrun �v���C���[�����񂾂��ǂ���
		*/
		bool GetIsplayerDed() const
		{
			return m_IsPlayerDed;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�����񂾂��ǂ����̎擾
		@�����@�v���C���[�����񂾂��ǂ���
		*/
		void SetIsplayerDed(bool playerDed)
		{
			m_IsPlayerDed = playerDed;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���g���[���[�̐U�����邩�̐ݒ�
		@�����@�R���g���[���[���U�����邩�ǂ���
		*/
		void SetVibrationOn(bool VibrationOn)
		{
			m_IsvibrationOn = VibrationOn;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	�v���C���[�ƃJ�M�̏Փ˔���
		@�����@�Q�[���I�u�W�F�N�g
		*/
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�}�V���̃A�N�Z�b�T
		@return �X�e�[�g�}�V��
		*/
		const kaito::StateMachine<Player>* GetFSM()const
		{
			return m_StateMachine;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�e�[�g�̕ύX
		@�����@�N���X�ɑΉ������X�e�[�g
		*/
		virtual void ChangeState(kaito::State<Player>* NewState);

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������������̎擾
		@return �H�ׂ����̐�
		*/
		int GetMeatCount() const
		{
			return m_meatCount;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	������������̐ݒ�
		@�����@�H�ׂ����̐�
		*/
		void SetMeatCount(int MeatCount)
		{
			m_meatCount = MeatCount;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	�J�M����������̎擾
		@return �擾�����J�M�̐�
		*/
		int GetKeyCount() const
		{
			return m_KeyCount;
		}



		//--------------------------------------------------------------------------------------
		/*!
		@brief	���̃v���C���[�̃^�X�N�̎擾
		*/
		bool GetPlayerTaskDay() const
		{
			return m_playerTaskDay;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	���̃v���C���[�̃^�X�N�̐ݒ�
		*/
		void SetPlayerTaskDay(bool PlayerTaskDay)
		{
			m_playerTaskDay = PlayerTaskDay;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	��̃v���C���[�̃^�X�N�̎擾
		*/
		bool GetPlayerTaskNight() const
		{
			return m_playerTaskNight;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief	��̃v���C���[�̃^�X�N�̐ݒ�
		*/
		void SetPlayerTaskNight(bool PlayerTaskNight)
		{
			m_playerTaskNight = PlayerTaskNight;
		}


		//--------------------------------------------------------------------------------------
		/*!
		@brief	���̃|�W�V�����擾
		@return	���̃|�W�V����
		*/
		Vec3 GetMeatPosition() const
		{
			return m_meatPosition;
		}

	};
}

//end basecross

