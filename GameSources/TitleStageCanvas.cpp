/*!
@file TitleStageCanvas.cpp
@author Kaito Isii
@brief  タイトルステージで使うUIの管理
*/


#include "stdafx.h"
#include "Project.h"
#include "GameUI.h"
#include "TitleStageCanvas.h"


namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	ゲームキャンバス
	//--------------------------------------------------------------------------------------

	TitleStageCanvas::TitleStageCanvas(const shared_ptr<Stage>& StagePtr) :
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
	std::vector<TextureTransformCreateDate>TitleTextureTransformDate(const wstring& keyName)
	{
		std::vector<TextureTransformCreateDate>result;	//!トランスフォームのデータを保存する配列
		vector<wstring>LineVec;							//!変数名
		auto& app = App::GetApp();						//!アプリの取得
		wstring DateDir;								//!データ
		App::GetApp()->GetDataDirectory(DateDir);		//!データを取得する
		auto fullPass = DateDir + L"csvFolder\\" + L"TexturecsvFolder\\" + L"TitleStageTextureTransform.csv";//!特定のcsvの取得
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


	//!スプライトの作成
	void TitleStageCanvas::CreateTitleSprite() {
		auto datas = TitleTextureTransformDate(L"TitleTexture");//!指定のキーの行を取得
		//!データ分回す
		for (auto& data : datas)
		{
			auto titleSprite = GetStage()->AddGameObject<GameUI>(L"MESSAGE_TX", false,
				data.scale, data.position);
			titleSprite->SetDrawActive(true);
		}
	}
	

	void TitleStageCanvas::OnCreate()
	{
		//スプライトの作成
		CreateTitleSprite();
	}

	void TitleStageCanvas::OnUpdate()
	{


	}

}