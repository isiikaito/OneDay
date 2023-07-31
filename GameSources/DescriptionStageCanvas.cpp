/*!
@file DescriptionStageCanvas.cpp
@author Kaito Isii
@brief  説明書ステージで使うUIの管理
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "DescriptionStageCanvas.h"
#include "DescriptionSpriteFront.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	説明書キャンバス
	//--------------------------------------------------------------------------------------

	DescriptionStageCanvas::DescriptionStageCanvas(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}


	//!テクスチャの(スケール,ローテーション,ポジション)の構造体
	struct TextureTransformCreateDate
	{
		//!構造体テンプレート
		Vec2 scale = Vec2(0.0f);	//!大きさ
		Vec3 position = Vec3(0.0f);	//!位置

		TextureTransformCreateDate() :
			TextureTransformCreateDate(Vec2(0.0f), Vec3(0.0f))
		{}
		//!構造体の初期化
		TextureTransformCreateDate(
			const Vec2& scale,
			const Vec3& position
		) :
			scale(scale),
			position(position)
		{}
	};

	//!csvからデータの取り出し
	std::vector<TextureTransformCreateDate>DescriptionSpriteTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!トランスフォームのデータを保存する配列
		vector<wstring>LineVec;							//!変数名
		auto& app = App::GetApp();						//!アプリの取得
		wstring DateDir;								//!データ
		App::GetApp()->GetDataDirectory(DateDir);		//!データを取得する
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"DescriptionTextureTransform.csv";//!特定のcsvの取得
		CsvFile csvFile;						//!csvの保存
		csvFile.SetFileName(fullPass);			//!ファイルの名前を保存する
		csvFile.ReadCsv();						//!csvを読みこっむ
		csvFile.GetSelect(LineVec, 0, keyName);	//!1行めが指定の文字か判別

		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;						//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');	//!トークン(カラム)単位で文字列を抽出(',')

			//!トークン(カラム)をスケール、回転、位置に読み込む
			Vec2 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			//!位置
			Vec3 Pos(
				(float)_wtof(Tokens[3].c_str()),
				(float)_wtof(Tokens[4].c_str()),
				(float)_wtof(Tokens[5].c_str())
			);



			result.push_back(TextureTransformCreateDate(Scale, Vec3(Pos.x, Pos.y, Pos.z)));

		}
		return result;//!構造体の中身を配列に入れて返す
	}


	//表の説明書のスプライトの作成
	void DescriptionStageCanvas::CreateDescriptionSpriteFront() {
		auto descriptionSprite1s = DescriptionSpriteTransformDate(L"DescriptionSprite1");//!指定のキーの行を取得
		//!データ分回す
		for (auto& data : descriptionSprite1s)
		{
			m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(
				L"DescriptionSprite1_TX", //!テクスチャ
				false,					  //!透明処理
				data.scale,				  //!大きさ 
				data.position			  //!位置(x,y,z)z奥行きは0.0f～1.0fの間
				));
		}

		auto descriptionSprite2 = DescriptionSpriteTransformDate(L"DescriptionSprite2");//!指定のキーの行を取得
		//!データ分回す
		for (auto& data : descriptionSprite2)
		{
			m_DescriptionSprites.push_back(GetStage()->AddGameObject<DescriptionSpriteFront>(
				L"DescriptionSprite2_TX", //!テクスチャ
				false,					  //!透明処理
				data.scale,				  //!大きさ 
				data.position			  //!位置(x,y,z)z奥行きは0.0f～1.0fの間
				));
		}

	}

	void DescriptionStageCanvas::OnCreate()
	{
		//スプライトの作成
		CreateDescriptionSpriteFront();
	}

	void DescriptionStageCanvas::OnUpdate()
	{


	}


}