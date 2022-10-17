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
	class Player : public GameObject
	{
		Vec2 GetInputState() const;//!�v���C���[���g�p����R���g���[���[�̓���
		Vec3 GetMoveVector() const;//!�R���g���[����������x�N�g���𓾂�
		void MovePlayer();         //!�v���C���[�̈ړ�
		float m_Speed;             //!�X�s�[�h
		float m_idleTime;          //!����

		InputHandler<Player> m_InputHandler;  //�R���g���[���[�̃{�^���̎擾

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
		void OnPushA();//!//�R���g���[���[�̃{�^������A

	};
}
//end basecross

