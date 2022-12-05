/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
    ///	�v���C���[
	//--------------------------------------------------------------------------------------
	enum class PlayerModel {
		human,
		wolf
	};
	

	class Player : public GameObject
	{
	private:
		float m_Speed;            //!�X�s�[�h
		float m_ChangeTime;          //!����
		float m_GetPlayerPositionTime;//!�v���C���[�̈ʒu�̎擾
		int m_playerChange;//!�v���C���[�̌����ڂ̏��
		int m_KeyCount;//!���������Ă�����J�E���g
		const float m_humanTime;//!�l�Ԃ̎���
		const float m_wolfTime;//!�T�̎���
		const int m_reset;//1���[�v���Z�b�g
		int m_MaxKeyCount;//!���̏������̍ő�
		int m_Ded;//!���S
		int m_PlayerPositionOnSecondMax;//!�v���C���[�̈ʒu�̔z��̍ő�̒���
		int m_PlayerHp;//!�v���C���[�̗̑�
		std::vector<Vec3>m_PlayerPositionOnSecond;//!�v���C���[�̖��b���Ƃ̈ʒu�̎擾
		float m_PlayerPositionTime;//!�v���C���[�̈ʒu���擾����܂ł̎���
		bool m_IsPlayerFound;//!�v���C���[�����������ғ��H��
		int m_AlertleveCount;
	
		InputHandlerB<Player> m_InputHandlerB;//!�R���g���[���[�̃{�^���̎擾B


	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() ;
        Vec2 GetInputState() const;//!�v���C���[���g�p����R���g���[���[�̓���
		Vec3 GetMoveVector() const;//!�R���g���[����������x�N�g���𓾂�
		void MovePlayer();         //!�v���C���[�̈ړ�
		void Villagerkiller();//!���l���E������
		void CreateKeySprite();//!���̃X�v���C�g�̍쐬
		void AppearanceChange();//!�v���C���[�̌����ڂ̕ω�
		void OnPushB();//!�R���g���[���[�̃{�^������B

        //!�v���C���[�̏�Ԃ̎擾
		int GetPlayerCange()const
		{
			return m_playerChange;
		}

		//!�v���C���[�̏�Ԃ̐ݒ�
		void SetPlayerChange(int playerChange)
		{
			m_playerChange = playerChange;
		}

		//!���b���Ƃ̃v���C���[�̈ʒu�̎擾
		std::vector<Vec3>GetPlayerPositionOnSecond()const
		{
			return m_PlayerPositionOnSecond;
		}

		//!���b���Ƃ̃v���C���[�̈ʒu�̐ݒ�
		void SetPlayerPositionOnSecond(const std::vector<Vec3>PlayerPositionOnSecond)
		{
			m_PlayerPositionOnSecond = PlayerPositionOnSecond;
		}

		//!�v���C���[��HP�擾
		int GetPlayerHp()
		{
			return m_PlayerHp;
		}
		//!�v���C���[��HP�̐ݒ�
		void SetPlayerHp(int PlayerHp)
		{
			m_PlayerHp = PlayerHp;
		}

		//!�v���C���[��������������̎擾
		bool GetPlayerFound()
		{
			return m_IsPlayerFound;
		}

		//!�v���C���[��������������̐ݒ�
		void SetPlayerFound(bool PlayerFound)
		{
			m_IsPlayerFound = PlayerFound;
		}

		//!�x���x�̃J�E���g
		int GetAlertleveCount()const
		{
			return m_AlertleveCount;
		}

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//�v���C���[�ƃJ�M�̏Փ˔���
	};
}
//end basecross

