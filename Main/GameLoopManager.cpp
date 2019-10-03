#include "DerbyStandAloneAppPCH.h"
#include "GameLoopManager.h"

#include "../CameraSingleton/CameraSingleton.h"
#include "../Entity/Horse/HorseManager.h"

GameLoopManager::GameLoopManager(void)
	:
	m_eFlowState(::Derby::Games::GAME_PROCESS_STATE_INITAILIZE)
{
	this->m_vAllFlow = new std::vector<GAMELOOPFRAME*>;
}


GameLoopManager::~GameLoopManager(void)
{

}


void GameLoopManager::LoopPushBack(GAMELOOPFRAME* pLoop)
{
	this->m_vAllFlow->push_back(pLoop) ;
}


bool GameLoopManager::Initialize()
{
	std::vector<GAMELOOPFRAME*>::iterator i = m_vAllFlow->begin();

	for ( i ; i != m_vAllFlow->end() ; ++i )
	{
		GAMELOOPFRAME* TempFrame = *i;

		if ( TempFrame )
		{
			TempFrame->Initialize();
		}
	}

	return true;
}

bool GameLoopManager::Load()
{
	std::vector<GAMELOOPFRAME*>::iterator i = m_vAllFlow->begin();

	for ( i ; i != m_vAllFlow->end() ; ++i )
	{
		GAMELOOPFRAME* TempFrame = *i;

		if ( TempFrame )
		{
			TempFrame->Load();
		}
	}
	return true;
}

bool GameLoopManager::Startup()
{
	std::vector<GAMELOOPFRAME*>::iterator i = m_vAllFlow->begin();

	for ( i ; i != m_vAllFlow->end() ; ++i )
	{
		GAMELOOPFRAME* TempFrame = *i;

		if ( TempFrame )
		{
			TempFrame->StartUp();
		}
	}

	this->m_vCurrentFlow = m_vAllFlow->begin();

	return true;
}

void GameLoopManager::Render( IVRender2DInterface *pRI )
{
	GAMELOOPFRAME*	TempFrame = *this->m_vCurrentFlow ; 

	TempFrame->Render(pRI);
}

void GameLoopManager::Process(float fDeltaTime)
{
	
	::Derby::Games::GAME_PROCESS_STATE Ret = ::Derby::Games::GAME_PROCESS_STATE_NONE ; 

	if ( this->m_vAllFlow )
	{
		GAMELOOPFRAME*	TempFrame = *this->m_vCurrentFlow;

		if ( TempFrame )
		{
			Ret = TempFrame->Process(fDeltaTime);//this->m_pTimer->GetTime());
		}

		if ( Ret != m_eFlowState )
		{
			this->m_eFlowState = Ret ; 

			//this->MoveNextControl();
			this->MoveControl(Ret);
			//this->m_pTimer->SetTime(0);
		}
	}


}

void GameLoopManager::Release()
{
	std::vector<GAMELOOPFRAME*>::iterator i = m_vAllFlow->begin();

	for ( i ; i != m_vAllFlow->end() ; ++i )
	{
		GAMELOOPFRAME* TempFrame = *i;

		if ( TempFrame )
		{
			TempFrame->Release();
		}
	}
}

void GameLoopManager::MoveNextControl(void)
{
	this->m_vCurrentFlow ++;

	if ( this->m_vCurrentFlow == this->m_vAllFlow->end() )
	{
		this->m_vCurrentFlow = this->m_vAllFlow->begin() ; 

		//카메라 다시. 
		::Derby::Game::CameraSingleton::GetInstance()->ResetCamera();

		::HorseManager::GetInstance()->ResetHorse();	

		this->Startup();
	}

	

}

void GameLoopManager::MoveControl ( ::Derby::Games::GAME_PROCESS_STATE gameState )
{
	this->m_vCurrentFlow=this->m_vAllFlow->end();

	for(std::vector<GAMELOOPFRAME*>::iterator i=this->m_vAllFlow->begin(); i!=this->m_vAllFlow->end(); i++)
	{
		GAMELOOPFRAME *tempGameLoop=*i;
		if(tempGameLoop)
		{
			if(tempGameLoop->GetState()==gameState)
			{
				this->m_vCurrentFlow=i;
				break;
			}
		}
	}

	if ( (*this->m_vCurrentFlow)->GetState() == ::Derby::Games::GAME_PROCESS_STATE_INITAILIZE )
	{
		//this->m_vCurrentFlow = this->m_vAllFlow->begin() ; 

		//카메라 다시. 
		::Derby::Game::CameraSingleton::GetInstance()->ResetCamera();

		::HorseManager::GetInstance()->ResetHorse();	

		this->Startup();
	}
}

void GameLoopManager::SetSplitCamera(VisContextCamera_cl* pCamera1 , VisContextCamera_cl* pCamera2)
{
	std::vector<GAMELOOPFRAME*>::iterator i = m_vAllFlow->begin();

	for ( i ; i != m_vAllFlow->end() ; ++i )
	{
		GAMELOOPFRAME* TempFrame = *i;

		if ( TempFrame )
		{
			TempFrame->SetSplitCamera(pCamera1 , pCamera2);//Release();
		}
	}
}
