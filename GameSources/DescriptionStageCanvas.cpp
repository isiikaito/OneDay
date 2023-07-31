/*!
@file DescriptionStageCanvas.cpp
@author Kaito Isii
@brief  �������X�e�[�W�Ŏg��UI�̊Ǘ�
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "DescriptionStageCanvas.h"
#include "DescriptionSpriteFront.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�������L�����o�X
	//--------------------------------------------------------------------------------------

	DescriptionStageCanvas::DescriptionStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
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
	std::vector<TextureTransformCreateDate>DescriptionSpriteTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!�g�����X�t�H�[���̃f�[�^��ۑ�����z��
		vector<wstring>LineVec;							//!�ϐ���
		auto& app = App::GetApp();						//!�A�v���̎擾
		wstring DateDir;								//!�f�[�^
		App::GetApp()->GetDataDirectory(DateDir);		//!�f�[�^���擾����
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"DescriptionTextureTransform.csv";//!�����csv�̎擾
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


	//�\�̐������̃X�v���C�g�̍쐬
	void DescriptionStageCanvas::CreateDescriptionSpriteFront() {
		auto descriptionSprite1s = DescriptionSpriteTransformDate(L"DescriptionSprite1");//!�w��̃L�[�̍s���擾
		//!�f�[�^����
		for (auto& data : descriptionSprite1s)
		{
			m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(
				L"DescriptionSprite1_TX", //!�e�N�X�`��
				false,					  //!��������
				data.scale,				  //!�傫�� 
				data.position			  //!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				));
		}

		auto descriptionSprite2 = DescriptionSpriteTransformDate(L"DescriptionSprite2");//!�w��̃L�[�̍s���擾
		//!�f�[�^����
		for (auto& data : descriptionSprite2)
		{
			m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(
				L"DescriptionSprite2_TX", //!�e�N�X�`��
				false,					  //!��������
				data.scale,				  //!�傫�� 
				data.position			  //!�ʒu(x,y,z)z���s����0.0f�`1.0f�̊�
				));
		}

	}

	void DescriptionStageCanvas::OnCreate()
	{
		//�X�v���C�g�̍쐬
		CreateDescriptionSpriteFront();
	}

	void DescriptionStageCanvas::OnUpdate()
	{


	}


}