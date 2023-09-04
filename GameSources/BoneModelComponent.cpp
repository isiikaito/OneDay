/*!
@file BoneModelComponent.cpp
@brief ボーン付きモデルの実体
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "BoneModelComponent.h"
namespace basecross
{
	void BoneModelComponent::OnCreate()
	{
		auto ptrTransform = GetGameObject()->GetComponent<Transform>();
		ptrTransform->SetScale(m_modelData.scale);		//!大きさ
		ptrTransform->SetRotation(m_modelData.rotation);	//!回転
		ptrTransform->SetPosition(m_modelData.position);	//!位置
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(m_modelData.modelScale),
			Vec3(m_modelData.modelRotOrigin),
			Vec3(m_modelData.modelRotation),
			Vec3(m_modelData.modelPosition)
		);
		
		auto ptrColl = GetGameObject()->AddComponent<CollisionCapsule>();								//!CollisionSphere衝突判定を付ける						
		auto ptrGra = GetGameObject()->AddComponent<Gravity>();											//!重力をつける											
		auto shadowPtr = GetGameObject()->AddComponent<Shadowmap>();									//!影をつける（シャドウマップを描画する）
		shadowPtr->SetMeshResource(m_modelData.meshName);												//!影の形（メッシュ）を設定								
		shadowPtr->SetMeshToTransformMatrix(spanMat);													//!メッシュの大きさ設定
		auto ptrDraw = GetGameObject()->AddComponent<BcPNTnTBoneModelDraw>();							//!描画コンポーネントの設定								
		ptrDraw->SetMeshResource(m_modelData.tnaMeshName);												//!描画するメッシュを設定								
		ptrDraw->SetMeshToTransformMatrix(spanMat);														//!メッシュの大きさ設定
		ptrDraw->SetNormalMapTextureResource(m_modelData.nomalMapTex);									//!法線マップの設定

	}
}
