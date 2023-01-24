/*!
@file OpeningCameraMan.h
@brief �I�[�v�j���O�J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	namespace kaito
	{
		//!�O���錾
		template<class entity_type>
		class State;
		//!�O���錾
		template <class entity_type>
		class StateMachine;
	}

	//--------------------------------------------------------------------------------------
	//�@�I�[�v�j���O�J�����}��
	//--------------------------------------------------------------------------------------
	class OpeningCameraMan : public GameObject {
	private:
		kaito::StateMachine<OpeningCameraMan>* m_StateMachine;//!�X�e�[�g�}�V���N���X�̃C���X�^���X�̐���
		Vec3 m_startPos;
		Vec3 m_endPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_totalTime;
	public:
		//!�X�e�[�g�}�V�[���̃A�N�Z�b�T
		const kaito::StateMachine<OpeningCameraMan>* GetFSM()const
		{
			return m_StateMachine;
		}
		//�\�z�Ɣj��
		OpeningCameraMan(const shared_ptr<Stage>& StagePtr);
		void OpeningCameraStatus(Vec3 StartPos, Vec3 EndPos, Vec3 AtStartPos, Vec3 AtEndPos, float TotalTime);
		virtual ~OpeningCameraMan() {}
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;

		bool MoveCamera(float totaltime);




		Vec3 GetAtPos() const {
			return m_AtPos;
		}


		//!�X�e�[�g�̕ύX
		virtual void ChangeState(kaito::State<OpeningCameraMan>* NewState);

	};
}
