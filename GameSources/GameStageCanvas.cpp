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
	constexpr int MAXKEYCOUNT = 3;//!�J�M���擾�ł���ő��
	//--------------------------------------------------------------------------------------
	///	�Q�[���L�����o�X
	//--------------------------------------------------------------------------------------

	GameStageCanvas::GameStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	//!�e�N�X�`����(�X�P�[��,���[�e�[�V����,�|�W�V����)�̍\����
	struct TextureTransformCreateDate
	{
		//!�\���̃e���v���[�g
		Vec2 scale = Vec2(0.0f);//!�傫��
		Vec3 position = Vec3(0.0f);//!�ʒu

		TextureTransformCreateDate() :
			TextureTransformCreateDate(Vec2(0.0f), Vec3(0.0f))
		{}
		//!�\���̂̏�����
		TextureTransformCreateDate(
			const Vec2& scale,
			const Vec3& position
		) :
			scale(scale),
			position(position)
		{}
	};

	//!csv����f�[�^�̎��o��
	std::vector<TextureTransformCreateDate>GameStageTextureTransformDate(const wstring& FolderName, const wstring& csvName, const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;//!�g�����X�t�H�[���̃f�[�^��ۑ�����z��
		vector<wstring>LineVec;//!�ϐ���

		auto& app = App::GetApp();//!�A�v���̎擾
		wstring DateDir;
		App::GetApp()->GetDataDirectory(DateDir);
		auto fullPass = DateDir + L"csvFolder\\" + FolderName + csvName;

		CsvFile csvFile;
		csvFile.SetFileName(fullPass);
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')

			//!�g�[�N��(�J����)���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec2 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			//!�ʒu
			Vec3 Pos(
				(float)_wtof(Tokens[3].c_str()),
				(float)_wtof(Tokens[4].c_str()),
				(float)_wtof(Tokens[5].c_str())
			);

			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y, Pos.z)));

		}
		return result;
	}


	// !���v�̃X�v���C�g�̍쐬
	void GameStageCanvas::CreateClockSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"clockSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"Clock_TX",	//!�e�N�X�`��
					true,			//!��������
					data.scale,		//!�傫�� 
					data.position	//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
					);
		}


	}

	// !���v�̉~�Ղ̃X�v���C�g�̍쐬
	void GameStageCanvas::CreateCircleClockSprite()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"circleClockSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<CircleClockSprite>
				(
					L"Circle_TX",//!�e�N�X�`��
					true,		 //!��������
					data.scale,  //!�傫�� 
					data.position//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊� 
					);
		}

	}

	void GameStageCanvas::CreateAlertlevelGauge()
	{

		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"AlertlevelGaugeTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"AlertlevelGaugeGauge_TX",//!�e�N�X�`��
					true,					   //!��������
					data.scale,				   //!�傫��
					data.position			   //!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
					);
		}

	}

	//�X�R�A�X�v���C�g�쐬
	void GameStageCanvas::CreateTimerSprite() {
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"TimerSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<Timer>(2,
				L"NUMBER_TX",//!�e�N�X�`��
				true,		 //!��������
				data.scale,  //!�傫��
				data.position//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);
		}

	}

	void GameStageCanvas::CreateHeartSprite()
	{

		auto leftHurteSpriteTexture = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"LeftHurteSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : leftHurteSpriteTexture)
		{
			//!�����̃n�[�g
			GetStage()->AddGameObject<PlayerHurteSprite>
				(
					L"PlayerHp_TX",		//!�e�N�X�`��
					true,				//!��������
					data.scale,			//!�傫��
					data.position,		//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
					LeftHurteS,			//!���݂̃��C�t
					true				//!�\������Ă��邩�ǂ���
					);
		}

		auto centralHurteSpriteTexture = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"CentralHurteSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : centralHurteSpriteTexture)
		{
			//!�������̃n�[�g
			GetStage()->AddGameObject<PlayerHurteSprite>
				(
					L"PlayerHp_TX",		//!�e�N�X�`��
					true,				//!��������
					data.scale,			//!�傫��
					data.position,		//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
					CentraHurte,		//!���݂̃��C�t
					true				//!�\������Ă��邩�ǂ���
					);
		}

		auto rightHurteSpriteTexture = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"RightHurteSpriteTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : rightHurteSpriteTexture)
		{

			//!�E���̃n�[�g
			GetStage()->AddGameObject<PlayerHurteSprite>
				(
					L"PlayerHp_TX",//!�e�N�X�`��
					true,		   //!��������
					data.scale,		//!�傫��
					data.position,	//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
					RightHurte,		//!���݂̃��C�t
					true			//!�\������Ă��邩�ǂ���
					);
		}

	}

	void GameStageCanvas::CreateArrow()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"ArrowTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			//!���̍쐬
			GetStage()->AddGameObject<Arrow>
				(
					L"Arrow_TX", //!�e�N�X�`��
					true,		 //!��������
					data.scale,  //!�傫��
					data.position//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
					);
		}

	}

	void GameStageCanvas::CreateKeyFrame()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"KeyFrameTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>(
				L"ItemField_TX",//!�e�N�X�`��
				true,			//!��������
				data.scale,		//!�傫��
				data.position	//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);
		}


	}

	void GameStageCanvas::CreateMeatGageBackGround()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"MeatGageBackGroundTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"Background_TX",	//!�e�N�X�`��
					true,				//!��������
					data.scale,			//�傫��
					data.position		//���W
					);
		}


	}

	void GameStageCanvas::CreateMeatGageFrame()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"MeatGageFrameTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>(
				L"Frame_TX",	//!�e�N�X�`��
				true,			//!��������
				data.scale,		//�傫��
				data.position	//���W
				);
		}
	}


	void GameStageCanvas::CreateHungerGage()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"HungerGageTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<HungerGage>(
				L"Full_TX",		//!�e�N�X�`��
				true,			//!��������
				data.scale,		//�傫��
				data.position	//���W
				);
		}
	}

	void GameStageCanvas::CreateClockArrow()
	{
		Vec3 rotation = Vec3(0.0f, 0.0f, 90.0f);
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"ClockArrowTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameUI>
				(
					L"Arrow_TX",	//!�e�N�X�`��
					true,			//!��������
					data.scale,		//!�傫��
					rotation,		//!��]
					data.position	//!�ʒu
					);
		}

	}

	void GameStageCanvas::CreateDateChangeCommentDay()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"DateChangeCommentDayTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<DateChangeCommentDay>(
				L"CommentDay_TX",	//!�e�N�X�`��
				true,				//!��������
				data.scale,			//�傫��
				data.position		//���W
				);
		}
	}

	void GameStageCanvas::CreateDateChangeCommentNight()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"DateChangeCommentNightTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<DateChangeCommentNight>(
				L"CommentNignt_TX",	//!�e�N�X�`��
				true,				//!��������
				data.scale,			//�傫��
				data.position		//���W
				);

		}
	}


	void GameStageCanvas::CreateGameOver()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"GameOverTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<GameOverSprite>(
				L"GAMEOVER_TX",//!�e�N�X�`��
				false,		   //!��������
				data.scale,    //!�傫��
				data.position  //!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				);
		}

	}

	
	void GameStageCanvas::CreateKeySprite()
	{
	
		for (int i = 0; i < MAXKEYCOUNT; i++)
		{
			auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"KeySpriteTexture"+ Util::IntToWStr(i));//!csv�̍ŏ��̍s�̕����̎擾
			//!�f�[�^����
			for (auto& data : datas)
			{
					GetStage()->AddGameObject<KeySprite>(
						L"KEY_TX",		//!�e�N�X�`��
						true,			//!��������
						data.scale,		//!�傫��//!�傫��
						data.position,	//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
						i				//!�J�M�̌�
				    );
			}
		}
		
	}

	void GameStageCanvas::CreateFadeOut()
	{
		auto datas = GameStageTextureTransformDate(L"TexturecsvFolder\\", L"GameStageTextureTransform.csv", L"FadeOutTexture");//!csv�̍ŏ��̍s�̕����̎擾
		//!�f�[�^����
		for (auto& data : datas)
		{
			GetStage()->AddGameObject<FadeOut>(
				true,			//!��������//!�傫��
				data.scale,		//!�傫��//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				data.position);	//!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
		}						
	}
	
	
	
	void GameStageCanvas::OnCreate()
	{
		CreateClockSprite();			
		CreateCircleClockSprite();		
		CreateAlertlevelGauge();		
		CreateTimerSprite();			
		CreateHeartSprite();			
		CreateArrow();					
		CreateKeyFrame();				
		CreateMeatGageBackGround();		
		CreateMeatGageFrame();			
		CreateHungerGage();				
		CreateClockArrow();				
		CreateDateChangeCommentDay();	
		CreateDateChangeCommentNight();	
		CreateGameOver();				
		CreateKeySprite();				
		CreateFadeOut();				
	}

	
}