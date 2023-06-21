/*!
@file ClearStageCanvas.cpp
@author Kaito Isii
@brief  �N���A�X�e�[�W�Ŏg��UI�̊Ǘ�
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "ClearStageCanvas.h"


namespace basecross
{
	constexpr float m_clearTime = 6.0f;//!�N���A����
	//--------------------------------------------------------------------------------------
	///	�Q�[���L�����o�X
	//--------------------------------------------------------------------------------------

	ClearStageCanvas::ClearStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_clearTime(0.0f)
	{}

	//!�e�N�X�`����(�X�P�[��,���[�e�[�V����,�|�W�V����)�̍\����
	struct TextureTransformCreateDate
	{
		//!�\���̃e���v���[�g
		Vec2 scale = Vec2(0.0f);	//!�傫��
		Vec3 position = Vec3(0.0f);	//!�ʒu

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
	std::vector<TextureTransformCreateDate>ClearStageTextureTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!�g�����X�t�H�[���̃f�[�^��ۑ�����z��
		vector<wstring>LineVec;							//!�ϐ���
		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DateDir;								//!�f�[�^
		App::GetApp()->GetDataDirectory(DateDir);		//!�f�[�^���擾����
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"ClearStageTextureTransform.csv";//!�����csv�̎擾
		CsvFile csvFile;						//!csv�̕ۑ�
		csvFile.SetFileName(fullPass);			//!�t�@�C���̖��O��ۑ�����
		csvFile.ReadCsv();						//!csv��ǂ݂�����
		csvFile.GetSelect(LineVec, 0, keyName);	//!1�s�߂��w��̕���������

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;						//!�g�[�N��(�J����)�̔z�u
			Util::WStrToTokenVector(Tokens, v, L',');	//!�g�[�N��(�J����)�P�ʂŕ�����𒊏o(',')

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
		return result;//!�\���̂̒��g��z��ɓ���ĕԂ�
	}
	//�X�v���C�g�̍쐬
	void ClearStageCanvas::CreateGameClearSprite()
	{
		auto datas = ClearStageTextureTransformDate(L"GameClearTexture");//!�w��̃L�[�̍s���擾
		//!�f�[�^����
		for (auto& data : datas)
		{

			auto gameClearSprite = GetStage()->AddGameObject<GameUI>(L"GAMECLEAR_TX", false,
				data.scale, data.position);
			GetStage()->SetSharedGameObject(L"gameClearSprite", gameClearSprite);
		}
	}


	void ClearStageCanvas::OnCreate()
	{
		CreateGameClearSprite();
	}

	void ClearStageCanvas::OnUpdate()
	{
		auto gameClearSprite = GetStage()->GetSharedGameObject<GameUI>(L"gameClearSprite");//!�N���A�X�v���C�g�̎擾
		auto elapsedTIme = App::GetApp()->GetElapsedTime();									//!�G���p�\�^�C���̎擾
		m_clearTime += elapsedTIme;															//!���Ԃ̕ϐ��ɃG���p�\�^�C���𑫂�
		//!�N���A���ԂɂȂ�����
		if (m_clearTime <= m_clearTime)
		{        
		gameClearSprite->SetDrawActive(true);//!�\������
		}
		else {
			gameClearSprite->SetDrawActive(false);

		}
		

	}

}