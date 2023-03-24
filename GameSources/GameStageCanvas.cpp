/*!
@file GameStageCanvas.cpp
@author Kaito Isii
@brief  �Q�[���X�e�[�W�Ŏg��UI�̊Ǘ�
*/


#include "stdafx.h"
#include "Project.h"
#include "GameStageCanvas.h"
#include "GameUI.h"
#include "PlayerHurteSprite.h"
#include "HungerGage.h"
#include "DateChangeCommentDay.h"
#include "DateChangeCommentNight.h"
#include "KeySprite.h"

namespace basecross
{
	constexpr int m_MaxKeyCount = 3;//!�J�M���擾�ł���ő��
	//--------------------------------------------------------------------------------------
	///	�Q�[���L�����o�X
	//--------------------------------------------------------------------------------------

	GameStageCanvas::GameStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	// !���v�̃X�v���C�g�̍쐬
	void GameStageCanvas::CreateClockSprite()
	{
		GetStage()->AddGameObject<GameUI>
			(
				L"Clock_TX",
				true,
				Vec2(170.0f, 128.0f),
				Vec3(-460.0f, 290.0f, 0.3f)
				);



	}

	// !���v�̉~�Ղ̃X�v���C�g�̍쐬
	void GameStageCanvas::CreateCircleClockSprite()
	{
		GetStage()->AddGameObject<CircleClockSprite>
			(
				L"Circle_TX",
				true,
				Vec2(65.0f, 70.0f),
				Vec3(-550.0f, 263.0f, 1.0f)
				);

	}

	void GameStageCanvas::CreateAlertlevelGauge()
	{

		GetStage()->AddGameObject<GameUI>
			(
				L"AlertlevelGaugeGauge_TX",
				true,
				Vec2(150.0f, 50.0f),       //!�傫��
				Vec3(460.0f, 350.0f, 1.0f) //!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);


	}

	//�X�R�A�X�v���C�g�쐬
	void GameStageCanvas::CreateTimerSprite() {
		GetStage()->AddGameObject<Timer>(2,
			L"NUMBER_TX",
			true,
			Vec2(50.0f, 40.0f),
			Vec3(-400.0f, 265.0f, 10.0f));

	}

	void GameStageCanvas::CreateHeartSprite()
	{


		//!�����̃n�[�g
		GetStage()->AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),        //!�傫��
				Vec3(370.0f, -250.0f, 0.2f),//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				2,//!���݂̃��C�t
				true//!�\������Ă��邩�ǂ���
				);

		//!�������̃n�[�g
		GetStage()->AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!�傫��
				Vec3(460.0f, -250.0f, 0.2f),//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				1,//!���݂̃��C�t
				true//!�\������Ă��邩�ǂ���
				);

		//!�E���̃n�[�g
		GetStage()->AddGameObject<PlayerHurteSprite>
			(
				L"PlayerHp_TX",
				true,
				Vec2(35.0f, 35.0f),       //!�傫��
				Vec3(550.0f, -250.0f, 0.2f),//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				0,//!���݂̃��C�t
				true//!�\������Ă��邩�ǂ���
				);

	}

	void GameStageCanvas::CreateArrow()
	{
		//!���̍쐬
		GetStage()->AddGameObject<Arrow>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),       //!�傫��
				Vec3(390.0f, 330.0f, 0.8f)//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);

	}

	void GameStageCanvas::CreateKeyFrame()
	{
		GetStage()->AddGameObject<GameUI>(
			L"ItemField_TX",//!�e�N�X�`��
			true,
			Vec2(200.0f, 150.0f), //!�傫��
			Vec3(-450.0f, -280.0f, 0.2f)//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
			);


	}

	void GameStageCanvas::CreateMeatGageBackGround()
	{
		GetStage()->AddGameObject<GameUI>
			(
				L"Background_TX",//!�e�N�X�`��
				true,
				Vec2(200.0f, 50.0f),//�傫��
				Vec3(420.0f, -320.0f, 1.0f)//���W
				);


	}

	void GameStageCanvas::CreateMeatGageFrame()
	{
		GetStage()->AddGameObject<GameUI>(
			L"Frame_TX",//!�e�N�X�`��
			true,
			Vec2(200.0f, 50.0f),//�傫��
			Vec3(420.0f, -320.0f, 0.2f)//���W
			);
	}


	void GameStageCanvas::CreateHungerGage()
	{
		GetStage()->AddGameObject<HungerGage>(
			L"Full_TX",//!�e�N�X�`��
			true,
			Vec2(200.0f, 50.0f),//�傫��
			Vec3(420.0f, -320.0f, 0.2f)//���W
			);
	}

	void GameStageCanvas::CreateClockArrow()
	{
		GetStage()->AddGameObject<GameUI>
			(
				L"Arrow_TX",
				true,
				Vec2(30.0f, 40.0f),//!�傫��
				Vec3(0.0f, 0.0f, 90.0f),//!��]
				Vec3(-500.0f, 300.0f, 0.2f)//!�ʒu
				);


	}

	void GameStageCanvas::CreateDateChangeCommentDay()
	{
		GetStage()->AddGameObject<DateChangeCommentDay>(
			L"CommentDay_TX",//!�e�N�X�`��
			true,
			Vec2(450.0f, 200.0f),//�傫��
			Vec3(0.0f, 200.0f, 0.1f)//���W
			);
	}

	void GameStageCanvas::CreateDateChangeCommentNight()
	{
		GetStage()->AddGameObject<DateChangeCommentNight>(
			L"CommentNignt_TX",//!�e�N�X�`��
			true,
			Vec2(450.0f, 200.0f),//�傫��
			Vec3(0.0f, 200.0f, 0.1f)//���W
			);


	}


	void GameStageCanvas::CreateGameOver()
	{
		GetStage()->AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.0f));

	}

	//!���̃X�v���C�g�̍쐬
	void GameStageCanvas::CreateKeySprite()
	{
		for (int i = 0; i < m_MaxKeyCount; i++)
		{
			GetStage()->AddGameObject<KeySprite>(
				L"KEY_TX",//!�e�N�X�`��
				true,
				Vec2(60.0f, 60.0f),//�傫��
				Vec3(-565.0f + (110.0f * (i)), -280.0f, 0.2f),//���W
				i//!�J�M�̌�
				);
		}
		
	}

	void GameStageCanvas::CreateFadeOut()
	{
        GetStage()->AddGameObject<FadeOut>(true,
		Vec2(650.0f, 450.0f), Vec3(0.0f, 0.0f, 0.1f));
	}
	
	
	
	void GameStageCanvas::OnCreate()
	{
		CreateClockSprite();//!���v�̃X�v���C�g
		CreateCircleClockSprite(); //!���v�̉~�Ղ̃X�v���C�g�̍쐬
		CreateAlertlevelGauge();//!�x���x�̃Q�[�W�̍쐬
		CreateTimerSprite();//!���Ԃ̃X�v���C�g�̍쐬
		CreateHeartSprite();//!�v���C���[��HP�̍쐬
		CreateArrow();//!���̍쐬
		CreateKeyFrame();//!�J�M�̘g�̍쐬
		CreateMeatGageBackGround();//!�󕠃Q�[�W�̔w�i
		CreateMeatGageFrame();//!�󕠃Q�[�W�̘g
		CreateHungerGage();//!�󕠃Q�[�W
		CreateClockArrow();//!���v�̐j
		CreateDateChangeCommentDay();//!�邩�璋�ɂł�e�N�X�`��
		CreateDateChangeCommentNight();//!�������ɂł�e�N�X�`��
		CreateGameOver();//!�Q�[���I�[�o�[
		CreateKeySprite();//!�J�M�̃X�v���C�g�̍쐬
		CreateFadeOut();//!�t�F�[�h�A�E�g�̍쐬
	}

	void GameStageCanvas::OnUpdate()
	{
		

	}

}