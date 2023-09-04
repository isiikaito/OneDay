/**
*@file WoodenBox.cpp
*@brief 木箱の実装が定義されているソースファイル
*@author kaito isii
*@details 木箱の実体実装
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
#include "WoodenBoxState.h"
namespace basecross {

	constexpr float COLLIMIT = 0.2;//!色の変化値
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	WoodenBox::WoodenBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_woodenBoxModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
			Vec3(0.06f, 0.06f, 0.06f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   
			Vec3(0.0f, -0.2f, 0.0f)  ,
				L"BOX_MESH"
			}
		)
	{
		m_StateMachine = new kaito::StateMachine<WoodenBox>(this);
		m_StateMachine->SetCurrentState(kaito::WoodenBoxMiddayState::Instance());	//!現在のステート
	}

	//初期化
	void WoodenBox::OnCreate() {
		
		AddComponent<StaticModelComponent>(m_woodenBoxModelData);				//!モデルデータ生成
		
		auto group = GetStage()->GetSharedObjectGroup(L"WoodBox_ObjGroup");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<WoodenBox>());
		
	}


	void WoodenBox::ChangeState(kaito::State<WoodenBox>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!ステートを変更する
	}

	void WoodenBox::OnUpdate() {
		m_StateMachine->Update();
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		auto scene = App::GetApp()->GetScene<Scene>();//!シーンの取得
		auto m_time = scene->GetEmissiveChangeTime();
		ptrDraw->SetEmissive(Col4(m_time - COLLIMIT, m_time - COLLIMIT, m_time - COLLIMIT, 1.0f)); // !夜にする処理
	}

}