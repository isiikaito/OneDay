#pragma once
#include "stdafx.h"
#include "StateMchine.h"
#include "Player.h"

namespace basecross
{
	namespace kaito
	{
		enum class EatCondition {
			notEat,
			firstEat,
			secondEat,
			thirdEat
		};
		//!�v���C���[���l�ԏ�Ԃ̎��̃X�e�[�g---------------------------
		class HumanState :public State<Player>
		{
		private:
			HumanState() {}
			float m_HumanChangeTime = 0.0f;
			CsvFile m_MeatPositon;//!���̃|�W�V������CSV�t�@�C��
			int m_MeatNumber=0;//!���̈ʒu���ۑ����ꂽCSV�t�@�C���̔ԍ�
			CsvFile m_GameStageCsvD;// !�����̔z�u4
			//!�V���O���g���p�^�[��
			HumanState(const HumanState&) = delete;//!�֐����폜����
			HumanState& operator=(const HumanState&) = delete;//!operator�̒��ɂ���=���폜�i�R�s�[����Ȃ��悤�Ɂj

		public:
			static HumanState* Instance();

			void CreateMeat();
			void CreateWoodBox();//!�ؔ��̍쐬
			void ReadCsv(const wstring& FileNume);
			virtual void Enter(Player* Player)override;
			virtual void Execute(Player* Player)override;
			virtual void Exit(Player* Player)override;
		};

		//-------------------------------------------------------------------


		//!�v���C���[���T�j��Ԃ̎��̃X�e�[�g---------------------------
		class WolfState :public State<Player>
		{
		private:
			WolfState() {}
			WolfState(const WolfState&) = delete;//!�֐����폜����
			WolfState& operator=(const WolfState&) = delete;//!operator�̒��ɂ���=���폜(�R�s�[����Ȃ��悤��)
			float m_WolfChangeTime = 0.0f;
			int m_Date = 0;//!���t
			shared_ptr<EfkEffect> m_TransformEfkEffect;
			shared_ptr<EfkPlay> m_TransformEfkPlay;
		


		public:
			static WolfState* Instance();
			//!���̈ʒu���Z�b�g
			void RemoveMeat();
            //!�ؔ��̃��Z�b�g
			void RemoveWoodBox();
			void MeatEat(Player* Player);
			virtual void Enter(Player* Player)override;
			virtual void Execute(Player* Player)override;
			virtual void Exit(Player* Player)override;
		};
	}
	//-------------------------------------------------------------------
}