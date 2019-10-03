#pragma once

#include "Game/GameLoopFrame.h"

//모든 씬의 클래스를 갖고있고. 조정 가능한 클래스.

class GameLoopManager
{
public:
	typedef ::Derby::Games::GameLoopFrame
		GAMELOOPFRAME;


	GameLoopManager(void);
	~GameLoopManager(void);

public:
	bool Initialize ();
	bool Load();
	bool Startup();
	void Render( IVRender2DInterface *pRI );
	void Process(float fDeltaTime);
	void Release();

	void LoopPushBack ( GAMELOOPFRAME* pLoop );

	void SetSplitCamera(VisContextCamera_cl* pCamera1 , VisContextCamera_cl* pCamera2);

private:
	void MoveNextControl ( void ) ;
	void MoveControl ( ::Derby::Games::GAME_PROCESS_STATE gameState ) ;

private:
	std::vector<GAMELOOPFRAME*>*				m_vAllFlow;
	std::vector<GAMELOOPFRAME*>::iterator		m_vCurrentFlow;

	float										m_fFlowTimer;
	::Derby::Games::GAME_PROCESS_STATE			m_eFlowState;
};
