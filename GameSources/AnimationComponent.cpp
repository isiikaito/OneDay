/*!
@file AnimationComponent.cpp
@brief アニメーションを読み込む実体
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross
{
	void AnimationComponent::OnCreate()
	{
		auto ptrDraw = GetGameObject()->GetComponent<BcPNTnTBoneModelDraw>();

		auto animationDatas = AnimationDates(m_useObjAnimation);//!指定のオブジェクトアニメーションを読み込む

		//!アニメーションのデータ分回す
		for (auto& animationData : animationDatas)
		{
			ptrDraw->AddAnimation
			(
				animationData.animationName,
				animationData.startSample,
				animationData.sampleLengeth,
				animationData.loop,
				animationData.samplesParSecond
			);
		}
		ptrDraw->ChangeCurrentAnimation(m_currentAnimation);//!最初のアニメーションを設定する


	}

	

	//!アニメーションの読み込み関数
	std::vector<ReadAnimationData> AnimationComponent::AnimationDates(const wstring& keyName)
	{
		std::vector<ReadAnimationData>result;												//!変数名
		vector<wstring>LineVec;																//!CSVの行単位の配列
		auto& app = App::GetApp();															//!アプリの取得
		wstring DataDir;																	//!データ
		App::GetApp()->GetDataDirectory(DataDir);											//!データを取得
		auto fullPass = DataDir + L"csvFolder\\" L"Animation\\" + L"ObjectAnimation.csv";	//!ファイルの特定
		CsvFile csvFile;
		csvFile.SetFileName(fullPass);														//!特定したcsvファイルを読み込む
		csvFile.ReadCsv();

		csvFile.GetSelect(LineVec, 0, keyName);												//!0番目のカラムがL""である行を抜き出す
		
		//!取得した行の情報
		for (auto& v : LineVec)
		{
			vector<wstring>Tokens;															//!トークン(カラム)の配置
			Util::WStrToTokenVector(Tokens, v, L',');										//!トークン(カラム)単位で文字列を抽出(',')
			wstring	animationName = Tokens[1];												//!アニメーションの名前の取得
			int startSample = (int)_wtof(Tokens[2].c_str());								//!アニメーションのサンプルの取得
			int sampleLengeth = (int)_wtof(Tokens[3].c_str());								//!アニメーションの長さの取得
			bool loop = (bool)_wtof(Tokens[4].c_str());										//!アニメーションをループ指せるかどうか取得
			float samplesParSecond = (float)_wtof(Tokens[5].c_str());						//!アニメーションの再生スピード取得
				
			
			result.push_back(ReadAnimationData(animationName, startSample, sampleLengeth, loop, samplesParSecond));//!アニメーションのデータが入った配列に格納

		}

		return result;
	}

}