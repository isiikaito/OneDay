/*!
@file StaticModelComponent.cpp
@brief スタティックモデルの実体
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "StaticModelComponent.h"
namespace basecross
{
	void StaticModelComponent::OnCreate()
	{
		auto ptrTransform = GetGameObject()->GetComponent<Transform>();
		ptrTransform->SetScale(m_modelData.scale);			//!大きさ
		ptrTransform->SetRotation(m_modelData.rotation);	//!回転
		ptrTransform->SetPosition(m_modelData.position);	//!位置

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(m_modelData.modelScale),
			Vec3(m_modelData.modelRotOrigin),
			Vec3(m_modelData.modelRotation),
			Vec3(m_modelData.modelPosition)
		);

		auto ptrColl = GetGameObject()->AddComponent<CollisionObb>();				//!CollisionObb衝突判定を付ける						
		auto shadowPtr = GetGameObject()->AddComponent<Shadowmap>();				//!影をつける（シャドウマップを描画する）
		shadowPtr->SetMeshResource(m_modelData.meshName);							//!影の形（メッシュ）を設定								
		shadowPtr->SetMeshToTransformMatrix(spanMat);								//!メッシュの大さ設定
		auto ptrDraw = GetGameObject()->AddComponent<PNTStaticModelDraw>();			//!描画コンポーネントの設定								
		ptrColl->SetFixed(true);													//!ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）
		ptrDraw->SetMeshResource(m_modelData.meshName);								//!メッシュの設定
		ptrDraw->SetMeshToTransformMatrix(spanMat);
	}
}
