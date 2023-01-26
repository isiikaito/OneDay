/*!
@file MyCamera.cpp
@brief カメラ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
		//	MyCameraカメラ（コンポーネントではない）
		//--------------------------------------------------------------------------------------
		//構築と破棄
	MyCamera::MyCamera() :
		Camera(),
		m_ToTargetLerp(1.0f),     //!目標を追いかける際の補間地
		m_TargetToAt(0, 0, 0),    //!目標から視点を調整する位置ベクトル
		m_CameraUnderRot(2.0f),   //!カメラを下げる下限角度
		m_RadXZ(0.0f),            //!カメラのZ軸の位置
		m_ArmLen(5.0f),           //!腕の長さの設定
		m_MaxArm(60.0f),          //!腕の最大の長さ
		m_MinArm(60.0f),          //!腕の最小の長さ
		m_LRBaseMode(true),       //!左右スティック変更のモード
		m_UDBaseMode(true)        //!上下のスティック変更モード
	{}

	MyCamera::MyCamera(float ArmLen) :
		Camera(),
		m_ToTargetLerp(1.0f),
		m_TargetToAt(0, 0, 0),
		m_CameraUnderRot(2.0f),
		m_ArmLen(5.0f),
		m_MaxArm(60.0f),
		m_MinArm(60.0f),
		m_LRBaseMode(true),
		m_UDBaseMode(true)
	{
		m_ArmLen = ArmLen;
		auto eye = GetEye();
		eye.y = m_ArmLen;
		SetEye(eye);
	}

	MyCamera::~MyCamera() {}//!アクセス

	//!カメラの位置の設定
	void MyCamera::SetEye(const bsm::Vec3& Eye)
	{
		Camera::SetEye(Eye);
		UpdateArmLengh();
	}

	void MyCamera::SetEye(float x, float y, float z) {
		Camera::SetEye(x, y, z);
		UpdateArmLengh();
	}

	//!カメラの目標オブジェクトを得る
	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	//!カメラの目標オブジェクトを設定する
	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	//!オブジェクトを追いかける場合の補間を得る
	float MyCamera::GetToTargetLerp() const {
		return m_ToTargetLerp;
	}

	//!オブジェクトを追いかける場合の補間を設定する
	void MyCamera::SetToTargetLerp(float f) {
		m_ToTargetLerp = f;
	}

	//!カメラの位置とカメラの視野の距離を得る
	float MyCamera::GetArmLengh() const {
		return m_ArmLen;
	}

	//!カメラの位置とカメラの視野の距離を更新
	void MyCamera::UpdateArmLengh() {
		auto vec = GetEye() - GetAt();
		m_ArmLen = bsm::length(vec);
		if (m_ArmLen >= m_MaxArm) {
			//m_MaxArm以上離れないようにする
			m_ArmLen = m_MaxArm;
		}
		if (m_ArmLen <= m_MinArm) {
			//m_MinArm以下近づかないようにする
			m_ArmLen = m_MinArm;
		}
	}

	//!カメラの位置とカメラの視野の距離の更新
	float MyCamera::GetMaxArm() const {
		return m_MaxArm;

	}

	//!カメラの位置とカメラの視野の距離の最大値設定
	void MyCamera::SetMaxArm(float f) {
		m_MaxArm = f;
	}

	//!カメラの位置とカメラの視野の距離の最小値を得る
	float MyCamera::GetMinArm() const {
		return m_MinArm;
	}

	//!カメラの位置とカメラの視野の距離の最小値を設定
	void MyCamera::SetMinArm(float f) {
		m_MinArm = f;
	}


	//!ターゲットからカメラ視点への調整ベクトルを得る
	bsm::Vec3 MyCamera::GetTargetToAt() const {
		return m_TargetToAt;

	}

	//!ターゲットからカメラ視点への調整ベクトルを設定する
	void MyCamera::SetTargetToAt(const bsm::Vec3& v) {
		m_TargetToAt = v;
	}



	//!Rスティックの左右変更をBaseモードにするかどうかを得る
	bool MyCamera::IsLRBaseMode() const {
		return m_LRBaseMode;

	}

	
	//!カメラの視点の設定
	void MyCamera::SetAt(const bsm::Vec3&At){
		Camera::SetAt(At);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
		}

	//!カメラ視点の設定
	void MyCamera::SetAt(float x, float y, float z) {
		Camera::SetAt(x, y, z);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
	}

	//!カメラの更新処理
	void MyCamera::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//前回のターンからの時間
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 newEye = GetEye();
		Vec3 newAt = GetAt();
		//計算に使うための腕角度（ベクトル）
		bsm::Vec3 armVec = newEye - newAt;
		//正規化しておく
		armVec.normalize();
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbRY = cntlVec[0].fThumbRY;
			fThumbRX = cntlVec[0].fThumbRX;
			wButtons = cntlVec[0].wButtons;
			
			
		}
		
		armVec.y = sin(2.0f); // 上下の角度を付ける

		//クオータニオンでY回転（つまりXZベクトルの値）を計算
		Quat qtXZ;
		qtXZ.rotation(m_RadXZ, bsm::Vec3(0, 1.0f, 0));
		qtXZ.normalize();
		//移動先行の行列計算することで、XZの値を算出
		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -1.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		//XZの値がわかったので腕角度に代入
		armVec.x = posXZ.x;
		armVec.z = posXZ.z;
		//腕角度を正規化
		armVec.normalize();

		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {
			//目指したい場所
			Vec3 toAt = ptrTarget->GetComponent<Transform>()->GetWorldMatrix().transInMatrix();
			toAt += m_TargetToAt;
			newAt = Lerp::CalculateLerp(GetAt(), toAt, 0, 1.0f, 1.0, Lerp::Linear);
		}

		//目指したい場所にアームの値と腕ベクトルでEyeを調整
		Vec3 toEye = newAt + armVec * m_ArmLen;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0, 1.0f, m_ToTargetLerp, Lerp::Linear);
		
		SetAt(newAt);
		SetEye(newEye);
		UpdateArmLengh();
		Camera::OnUpdate();
		
		//!画角を変えることが出来る
		//auto chk = XM_PI / 9.0f;//!360を6で割って角度を出す。
		//SetFovY(chk);

		auto& app = App::GetApp();//!アプリの取得
		auto Stage = app->GetScene<Scene>()->GetActiveStage();//!ステージの取得
	
		auto Objects = Stage->GetGameObjectVec();//!ステージの中のオブジェクトを取得
		
		for (auto& Obj : Objects)//!オブジェクトの要素分
		{

			auto stageWall = dynamic_pointer_cast<StageWall>(Obj);//!壁の取得
			if (stageWall)
			{
				auto StageWallObb = stageWall->GetComponent<CollisionObb>()->GetObb();//!ステージの壁のObbの取得
				
				if (HitTest::SEGMENT_OBB(GetEye(), GetAt(), StageWallObb))//!カメラと視点の間に壁が入ったら
				{
					stageWall->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.3f));//!壁を半透明にする
					
				}
				
				else//!カメラと視点の間に壁が無かったら
				{
					stageWall->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.4f, 0.4f, 0.4f, 1.0f));//!壁の半透明を解除する
				}
				
			}

			auto stageBuilding = dynamic_pointer_cast<StageBuilding>(Obj);//!建物の取得
			if (stageBuilding)
			{
				auto StageBuildingObb = stageBuilding->GetComponent<CollisionObb>()->GetObb();//!ステージの壁のObbの取得

				if (HitTest::SEGMENT_OBB(GetEye(), GetAt(), StageBuildingObb))//!カメラと視点の間に壁が入ったら
				{
					stageBuilding->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.3f));//!壁を半透明にする

				}

				else//!カメラと視点の間に壁が無かったら
				{
					stageBuilding->GetComponent<PNTStaticModelDraw>()->SetDiffuse(Col4(0.5f, 0.5f, 0.5, 1.0f));//!壁の半透明を解除する
				}

			}





		}

		
			
	

	}

}