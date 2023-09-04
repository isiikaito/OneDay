/*!
@file PlayerMoveComponent.cpp
@brief プレイヤーの動く処理実体
*@author isii kaito
*/
#include "stdafx.h"
#include "Project.h"
#include "MoveComponent.h"
namespace basecross 
{
	constexpr float ROTTOHEAD = 1.0f;					//!正面

	Vec2 PlayerMoveComponent::GetControlerInformation() const
	{
		Vec2 ret;
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//!コントローラの取得
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		//!接続されているコントローラ
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;//!左スティックx座標
			ret.y = cntlVec[0].fThumbLY;//!左スティックy座標
		}
		return ret;
	}


	Vec3 PlayerMoveComponent::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//デフォルトはビューのカメラから取り出す
		auto& StageView = GetStage()->GetView();
		
		//!入力の取得
		auto inPut = GetControlerInformation();
		float moveX = inPut.x;
		float moveZ = inPut.y;

		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;											//!動いた時のスピード
			auto& ptrCamera = StageView->GetTargetCamera();							//!カメラの取得
			auto ptrTransform = GetGameObject()->GetComponent<Transform>();
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();	//!進行方向の向きを計算
			front.y = 0;
			front.normalize();												//!進行方向の向きを正規化
			float frontAngle = atan2(front.z, front.x);						//!進行方向向きからの角度を算出
			Vec2 moveVec(moveX, moveZ);										//!コントローラの向き計算
			float moveSize = moveVec.length();								//!動く大きさ
			float cntlAngle = atan2(-moveX, moveZ);							//!コントローラの向きから角度を計算
			float totalAngle = frontAngle + cntlAngle;						//!トータルの角度を算出
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));				//!角度からベクトルを作成
			angle.normalize();												//!正規化する
			angle *= moveSize;												//!移動サイズを設定
			angle.y = 0;													//!Y軸は変化させない
		}
		return angle;
	}
	void PlayerMoveComponent::MovePlayer() {


		
		float elapsedTime = App::GetApp()->GetElapsedTime();			 //!エルパソタイムの取得
		auto angle = GetMoveVector();									 //!ベクトルの取得
		auto volume = App::GetApp()->GetScene<Scene>()->GetSoundvolume();//!効果音量
		auto ptrTransform = GetGameObject()->GetComponent<Transform>();
		//!スティックが傾いていたら
		if (angle.length() > 0.0f) {
			auto pos = ptrTransform->GetPosition();		 //!自身のポジションの取得
			pos += angle * elapsedTime * m_Speed;						 //!ポジションの更新
			ptrTransform->SetPosition(pos);				 //!ポジションの設定

		}

		//!回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetGameObject()->GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, ROTTOHEAD);		//!正面を向く
		}
	}
	void PlayerMoveComponent::OnUpdate()
	{
		MovePlayer();
	}

}