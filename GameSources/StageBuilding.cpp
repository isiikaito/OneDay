/**
*@file StageBuilding.cpp
*@brief ゲームステージの建物の実装が定義されているソースファイル
*@author Ayumu Muroi
*@details ゲームステージの建物の実体実装
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	constexpr float COLLIMIT = 0.2;	//色の変化値
	constexpr float TRANCE = 1.0f;	//!透明度

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	StageBuilding::StageBuilding(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Time(1),
		m_oneday(0),
		m_buildingModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.09f, 0.09f, 0.09f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 80.1f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f),
				L"STAGEBUILDING_MESH"
			}
		)
		
	{
	}


	//初期化
	void StageBuilding::OnCreate() {

		AddComponent<StaticModelComponent>(m_buildingModelData);				//!モデルデータ生成
		auto group = GetStage()->GetSharedObjectGroup(L"StageBuilding_Group");	//!グループを取得
		group->IntoGroup(GetThis<StageBuilding>());								//!グループにステージの壁を入れる
		SetAlphaActive(true);													//!SetDiffiuseのカラー変更を適用
		m_ptrDrow= GetComponent<PNTStaticModelDraw>();							//!描画コンポーネント
	}

	void StageBuilding::OnUpdate() {

		float elapsedTime = GameManager::GetElpasedTiem();//!elapsedTimeを取得することにより時間を使える
		auto scene = App::GetApp()->GetScene<Scene>();
		auto m_time = scene->GetEmissiveChangeTime();
		m_ptrDrow.lock()->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !夜にする処理
				
	}

}