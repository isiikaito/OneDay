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
		int m_playerChange;//!�v���C���[�̌����ڂ̏��
		int m_KeyCount;//!���������Ă�����J�E���g
		const float m_humanTime;//!�l�Ԃ̎���
		const float m_wolfTime;//!�T�̎���
		const int m_reset;//1���[�v���Z�b�g
		int m_MaxKeyCount;//!���̏������̍ő�
		int m_Ded;//!�G�̎��S

		InputHandler<Player> m_InputHandler;  //�R���g���[���[�̃{�^���̎擾
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
		void AppearanceChange();//!�v���C���[�̌����ڂ̕ω�
		void OnPushA(){}//!//�R���g���[���[�̃{�^������A
		void OnPushB();//!�R���g���[���[�̃{�^������B

		int GetPlayerCange()const//!�v���C���[�̏�Ԃ̎擾
		{
			return m_playerChange;
		}
		void SetPlayerChange(int playerChange)//!�v���C���[�̏�Ԃ̐ݒ�
		{
			m_playerChange = playerChange;
		}

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//�v���C���[�ƃJ�M�̏Փ˔���
	};
}
//end basecross

