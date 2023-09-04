/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*@author isii kaito
*/

#include "stdafx.h"
#include "Project.h"
#include "GameManager.h"
#include "GameManagerState.h"


namespace basecross
{


	GameManager::GameManager(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr)
	{
		m_StateMachine = new kaito::StateMachine<GameManager>(this);
		m_StateMachine->SetCurrentState(kaito::OpeningCameraPlayState::Instance());	//!���݂̃X�e�[�g
	}
	float GameManager::GetElpasedTiem()
	{
		auto gameElpasedTime = App::GetApp()->GetScene<Scene>()->GetGameTime();//!�Q�[���̐i�s����
		return gameElpasedTime;
	}

	float GameManager::GetDayTiem()
	{
		auto dayTime = App::GetApp()->GetScene<Scene>()->GetDayTime();//!�ϐg���鎞��
		return dayTime;
	}
	void GameManager::OnUpdate()
	{
		m_StateMachine->Update();//!�X�e�[�g�}�V���̍X�V

	}

	void GameManager::ChangeState(kaito::State<GameManager>* NewState)
	{
		m_StateMachine->ChangeState(NewState);//!�X�e�[�g��ύX����
	}

	shared_ptr<Player>GameManager::GetPlayer()const 
	{
		return std::dynamic_pointer_cast<Player>(GetStage()->GetSharedObject(L"Player"));//!�v���C���[�̎擾
	}
}