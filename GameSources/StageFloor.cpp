/**
*@file StageFloor.cpp
*@brief ゲームステージの床の実装が定義されているソースファイル
*@author Ayumu Muroi
*@details ゲームステージの床の実体実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	constexpr float COLLIMIT = 0.2;	//色の変化地
	constexpr float TRANCE = 1.0f;		//!透明度
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_stageFloorModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.04f, 1.0f, 0.04f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),	
				Vec3(0.0f, 0.5f, -0.003f),
				L"GROUND_MESH"
			}
		)
	{
	}

	//初期化
	void StageFloor::OnCreate() {
		AddComponent<StaticModelComponent>(m_stageFloorModelData);				//!モデルデータ生成
	
	}

	void StageFloor::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !夜にする処理
	}

}