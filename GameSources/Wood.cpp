//* @author kanazawa yuuma
//* @details 木の実体実装
//* /

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
namespace basecross {

	constexpr float COLLIMIT = 0.2;	//色の変化値
	constexpr float TRANCE = 1.0f;		//!透明度
	//--------------------------------------------------------------------------------------
	//	class Wood : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Wood::Wood(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_woodModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.06f, 0.06f, 0.06f),	
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),		
				Vec3(0.0f, -0.5f, 0.0f),	
				L"STAGE_WOOD"
			}
		)

	{
	}

	//初期化
	void Wood::OnCreate() {
		AddComponent<StaticModelComponent>(m_woodModelData);				//!モデルデータ生成
	}

	void Wood::OnUpdate() {

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto m_time = scene->GetEmissiveChangeTime();

		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, TRANCE)); // !夜にする処理

	}

}