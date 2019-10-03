#include "DerbyStandAloneAppPCH.h"
#include "GameLoopFrame.h"

namespace Derby { namespace Games {
	GameLoopFrame::GameLoopFrame(void)
		:
		m_pTopCamera(NULL) , 
		m_pBottomCamera(NULL)
	{
		this->m_eState = GAME_PROCESS_STATE_NONE;

		this->m_fDeltaTime=0.f;

		this->testSprite=0;

	}


	GameLoopFrame::~GameLoopFrame(void)
	{
		this->testSprite=0;
	}

	bool GameLoopFrame::Initialize(void)
	{


		return true;
	}

	bool GameLoopFrame::Load(void)
	{

		return true;
	}

	GAME_PROCESS_STATE GameLoopFrame::Process(float fPassedTime)
	{


		return GAME_PROCESS_STATE_MAX  ; 
	}



	void GameLoopFrame::Render(IVRender2DInterface *pRI)
	{

	}


	void GameLoopFrame::StartUp(void)
	{

	}

	void GameLoopFrame::Release()
	{

	}

	void GameLoopFrame::SetSplitCamera(VisContextCamera_cl* pCamera1 , VisContextCamera_cl* pCamera2)
	{

	}

} /*Games*/ } /*Derby*/
