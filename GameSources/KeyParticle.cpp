/*!
@file KeyParticle.cpp
@brief　カギを取った時の処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// パーティクルクラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MultiSpark::MultiSpark(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiSpark::~MultiSpark() {}

	//初期化
	void MultiSpark::OnCreate() {
		SetAddType(true);
	}

	void MultiSpark::OnUpdate() {
		for (auto ptrParticle : GetParticleVec()) {
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
				if (rParticleSprite.m_Active) {
					rParticleSprite.m_Color.z += 0.05f;
					if (rParticleSprite.m_Color.z >= 1.0f) {
						rParticleSprite.m_Color.z = 1.0f;
					}
				}
			}
		}
		//親クラスのOnUpdate()を呼ぶ
		MultiParticle::OnUpdate();
	}

	void MultiSpark::InsertSpark(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(16);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"SPARK_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;

			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;

			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 50.0f,
				rParticleSprite.m_LocalPos.y * 50.0f,
				rParticleSprite.m_LocalPos.z * 50.0f
			);
			//色の指定
			//rParticleSprite.m_Color = Col4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}
}