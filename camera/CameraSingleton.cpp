#include "DerbyStandAloneAppPCH.h"
#include "CameraSingleton.h"

namespace Derby { namespace Game {

CameraSingleton::CameraSingleton(void)
{
	//카메라.
	this->m_pBottomCamera			= 0 ; 
	this->m_pTopCamera				= 0 ;

	//랜더 콘텍스트. 
	this->m_pTopRenderContext		= 0;
	this->m_pBottomRenderContext	= 0;

	this->m_fTopFovX = 90.f;
	this->m_fTopFovY = 0.f;

	this->m_fBottomFovX = 90.f;
	this->m_fBottomFovY = 0.f;

	//카메라 시나리오
	this->m_nCameraScenario = 0 ;

	//상단 카메라 엔티티.
	this->m_pTopCameraEntity	= new struct TOP_CAMERA;
	this->m_pOriginalTopCamera_Entity	= new struct TOP_CAMERA;

	//저장해둘 엔티티는 생성해놔야 함. 
	for ( int i = 0 ; i < MAX_UPPER_CAMERA_ENTITY ; i++)
	{
		this->m_pOriginalTopCamera_Entity->Upper_camera[i] = 0 ; 
		this->m_pOriginalTopCamera_Entity->Upper_camera[i] = new VisBaseEntity_cl;
	}

	//하단 카메라 엔티티. 

	for ( int i = 0 ; i < MAX_BOTTOM_SCENARIO_TYPE ; i++ )
	{
		this->m_pBottom_Scenario[i]				= 0 ;
		this->m_pBottom_Scenario[i]				= new struct BOTTOM_CAMERA ; 
		this->m_pBottom_Original_Scenario[i]	= new struct BOTTOM_CAMERA;
	}

	//하단 오리지널 카메라.
	for ( int i= 0 ; i < MAX_BOTTOM_SCENARIO_1_ENTITY ; i++)
	{
		this->m_pBottom_Original_Scenario[0]->Bottom_camera[i] = 0;
		this->m_pBottom_Original_Scenario[0]->Bottom_camera[i] = new VisBaseEntity_cl;
	}
	//하단 2번째 시나리오 오리지널 카메라. 
	for ( int i= 0 ; i < MAX_BOTTOM_SCENARIO_2_ENTITY ; i++)
	{
		this->m_pBottom_Original_Scenario[1]->Bottom_camera[i] = 0;
		this->m_pBottom_Original_Scenario[1]->Bottom_camera[i] = new VisBaseEntity_cl;
	}

	//예시장.

	this->m_pBetCamera_Entity			= 0 ; 
	this->m_pOriginalBetCamera_Entity	= 0 ; 

	this->m_pBetCamera_Entity			= new struct BET_CAMERA;
	this->m_pOriginalBetCamera_Entity	= new struct BET_CAMERA;

	for ( int i = 0 ; i < MAX_BET_CAMERA_ENTITY ; i++ )
	{
		this->m_pOriginalBetCamera_Entity->Bet_Camera[i] = new VisBaseEntity_cl;
	}

	//화면준비
	this->m_pRaceGuideCamera_Entity		= 0 ;
	this->m_pRaceGuideCamera_Original	= 0 ;

	this->m_pRaceGuideCamera_Entity		= new struct RACE_GUIDE_CAMERA;
	this->m_pRaceGuideCamera_Original	= new struct RACE_GUIDE_CAMERA;

	for ( int i = 0 ; i < 2; i++ )
	{
		this->m_pRaceGuideCamera_Original->RaceGuideCamera[i] = new VisBaseEntity_cl;
	}
	this->InstallSingleton();
}


CameraSingleton::~CameraSingleton(void)
{
	this->m_pBottomCamera	= 0 ; 
	this->m_pTopCamera		= 0 ;

	//상단.
	if(this->m_pOriginalTopCamera_Entity)
	{
		//오리지널 구조체 안에 생성한것부터 삭제한 후에 오리지널 구조체 삭제. 
		for ( int i = 0 ; i < MAX_UPPER_CAMERA_ENTITY  ; i++)
		{
			if(this->m_pOriginalTopCamera_Entity->Upper_camera[i])
			{
				delete this->m_pOriginalTopCamera_Entity->Upper_camera[i];
				this->m_pOriginalTopCamera_Entity->Upper_camera[i] = 0 ; 
			}
		}

		delete this->m_pOriginalTopCamera_Entity ; 
		this->m_pOriginalTopCamera_Entity = 0 ; 
	}

	if(this->m_pTopCameraEntity)
	{
		delete this->m_pTopCameraEntity;
		this->m_pTopCameraEntity = 0 ; 
	}

	//하단. 
	for ( int i = 0 ; i < MAX_BOTTOM_SCENARIO_TYPE ; i++)
	{
		if(m_pBottom_Scenario[i])
		{
			int nIterator = 0 ; 

			// 시나리오 변경되면 아래 조건 추가하거나 삭제.
			if( 0 == i)
			{
				nIterator = MAX_BOTTOM_SCENARIO_1_ENTITY;
			}
			else if( 1 == i )
			{
				nIterator = MAX_BOTTOM_SCENARIO_2_ENTITY;
			}

			for ( int j = 0 ; j < nIterator ; j++ )
			{
				//오리지널 엔티티 안 삭제,
				if(this->m_pBottom_Original_Scenario[i]->Bottom_camera[j])
				{
					delete this->m_pBottom_Original_Scenario[i]->Bottom_camera[j];
					this->m_pBottom_Original_Scenario[i]->Bottom_camera[j] = 0;
				}
			}
			//오리지널 삭제.
			delete this->m_pBottom_Original_Scenario[i] ; 
			this->m_pBottom_Original_Scenario[i] = 0 ;

			//쓰던거 삭제. 
			delete m_pBottom_Scenario[i];
			this->m_pBottom_Scenario[i] = 0 ; 
		}
	}

	//예시장. 
	if(this->m_pOriginalBetCamera_Entity)
	{
		for ( int i = 0 ; i < MAX_BET_CAMERA_ENTITY ; i++ )
		{
			if(this->m_pOriginalBetCamera_Entity->Bet_Camera[i])
			{
				delete this->m_pOriginalBetCamera_Entity->Bet_Camera[i];
				this->m_pOriginalBetCamera_Entity->Bet_Camera[i] = 0 ; 
			}
		}
		delete this->m_pOriginalBetCamera_Entity;
		this->m_pOriginalBetCamera_Entity = 0 ;
	}

	//화면준비. 
	for ( int i = 0 ; i < 2 ; i++)
	{
		delete this->m_pRaceGuideCamera_Original->RaceGuideCamera[i];
		this->m_pRaceGuideCamera_Original->RaceGuideCamera[i] = 0 ; 
	}
	delete this->m_pRaceGuideCamera_Original;
	this->m_pRaceGuideCamera_Original = 0 ; 

	delete this->m_pRaceGuideCamera_Entity ; 
	this->m_pRaceGuideCamera_Entity  = 0 ;

	this->UninstallSingleton();
}


//---------------------------------------------------------------------------------------------------------------------
void CameraSingleton::SetContextCamera(VisContextCamera_cl* TopCamera , VisContextCamera_cl* BottomCamera)
{
	this->m_pTopCamera		= TopCamera ; 
	this->m_pBottomCamera	= BottomCamera; 
}
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//씬 카메라 로드 .
void CameraSingleton::LoadSceneCamera()
{
	//상단 로드. 
	this->LoadUpperCameraEntity();

	//하단 로드. 
	this->LoadBottomCameraEntity();
	
	//예시장 로드 . 
	this->LoadBetCameraEntity();

	//경기준비 로드. 
	this->LoadRaceGuideCameraEntity();

	//리플레이는 카메라 1개에 움직이지 않으니 오리지널 뭐 이런거 필요없음. 바로 복사. 
	this->m_pReplayCamera = Vision::Game.SearchEntity("Replay_CameraPosition_Finish");

	int a = 0 ; 
}

void CameraSingleton::LoadUpperCameraEntity()
{
	//상단. 
	this->m_pTopCameraEntity->Upper_camera[0] = Vision::Game.SearchEntity("Upper_CameraPosition_01");
	//오리지널에 바로 복사해둠. 
	memcpy(this->m_pOriginalTopCamera_Entity->Upper_camera[0] , this->m_pTopCameraEntity->Upper_camera[0] , sizeof(VisBaseEntity_cl) ); 

	this->m_pTopCameraEntity->Upper_camera[1] = Vision::Game.SearchEntity("Upper_CameraPosition_02");
	memcpy(this->m_pOriginalTopCamera_Entity->Upper_camera[1] , this->m_pTopCameraEntity->Upper_camera[1] , sizeof(VisBaseEntity_cl) ); 
}

void CameraSingleton::LoadBottomCameraEntity()
{
	//하단. 

	//여기 좌표 확인해봐야됨.

	//시나리오1.
	this->m_pBottom_Scenario[0]->Bottom_camera[0] = Vision::Game.SearchEntity("1nd_Bottom_CameraPosition_01");
	memcpy( this->m_pBottom_Original_Scenario[0]->Bottom_camera[0] ,this->m_pBottom_Scenario[0]->Bottom_camera[0] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[0]->Bottom_camera[1] = Vision::Game.SearchEntity("1nd_Bottom_CameraPosition_02");
	memcpy( this->m_pBottom_Original_Scenario[0]->Bottom_camera[1] ,this->m_pBottom_Scenario[0]->Bottom_camera[1] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[0]->Bottom_camera[2] = Vision::Game.SearchEntity("1nd_Bottom_CameraPosition_03");
	memcpy( this->m_pBottom_Original_Scenario[0]->Bottom_camera[2] ,this->m_pBottom_Scenario[0]->Bottom_camera[2] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[0]->Bottom_camera[3] = Vision::Game.SearchEntity("1nd_Bottom_CameraPosition_04");
	memcpy( this->m_pBottom_Original_Scenario[0]->Bottom_camera[3] ,this->m_pBottom_Scenario[0]->Bottom_camera[3] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[0]->Bottom_camera[4] = Vision::Game.SearchEntity("1nd_Bottom_CameraPosition_05");
	memcpy( this->m_pBottom_Original_Scenario[0]->Bottom_camera[4] ,this->m_pBottom_Scenario[0]->Bottom_camera[4] , sizeof(VisBaseEntity_cl));



	//시나리오2.
	this->m_pBottom_Scenario[1]->Bottom_camera[0] = Vision::Game.SearchEntity("2nd_Bottom_CameraPosition_01");
	memcpy( this->m_pBottom_Original_Scenario[1]->Bottom_camera[0] ,this->m_pBottom_Scenario[1]->Bottom_camera[0] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[1]->Bottom_camera[1] = Vision::Game.SearchEntity("2nd_Bottom_CameraPosition_02");
	memcpy( this->m_pBottom_Original_Scenario[1]->Bottom_camera[1] ,this->m_pBottom_Scenario[1]->Bottom_camera[1] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[1]->Bottom_camera[2] = Vision::Game.SearchEntity("2nd_Bottom_CameraPosition_03");
	memcpy( this->m_pBottom_Original_Scenario[1]->Bottom_camera[2] ,this->m_pBottom_Scenario[1]->Bottom_camera[2] , sizeof(VisBaseEntity_cl));
	
	this->m_pBottom_Scenario[1]->Bottom_camera[3] = Vision::Game.SearchEntity("2nd_Bottom_CameraPosition_04");
	memcpy( this->m_pBottom_Original_Scenario[1]->Bottom_camera[3] ,this->m_pBottom_Scenario[1]->Bottom_camera[3] , sizeof(VisBaseEntity_cl));
	
	this->m_pBottom_Scenario[1]->Bottom_camera[4] = Vision::Game.SearchEntity("2nd_Bottom_CameraPosition_04.5");
	memcpy( this->m_pBottom_Original_Scenario[1]->Bottom_camera[4] ,this->m_pBottom_Scenario[1]->Bottom_camera[4] , sizeof(VisBaseEntity_cl));

	this->m_pBottom_Scenario[1]->Bottom_camera[5] = Vision::Game.SearchEntity("2nd_Bottom_CameraPosition_05");
	memcpy( this->m_pBottom_Original_Scenario[1]->Bottom_camera[5] ,this->m_pBottom_Scenario[1]->Bottom_camera[5] , sizeof(VisBaseEntity_cl));

}

void CameraSingleton::LoadBetCameraEntity()
{
	//예시장.
	this->m_pBetCamera_Entity->Bet_Camera[0] = Vision::Game.SearchEntity("ex_camera_01");
	memcpy( this->m_pOriginalBetCamera_Entity->Bet_Camera[0] , this->m_pBetCamera_Entity->Bet_Camera[0] , sizeof(VisBaseEntity_cl));

	this->m_pBetCamera_Entity->Bet_Camera[1] = Vision::Game.SearchEntity("ex_camera_02");
	memcpy( this->m_pOriginalBetCamera_Entity->Bet_Camera[1] , this->m_pBetCamera_Entity->Bet_Camera[1] , sizeof(VisBaseEntity_cl));

	this->m_pBetCamera_Entity->Bet_Camera[2] = Vision::Game.SearchEntity("ex_camera_03");
	memcpy( this->m_pOriginalBetCamera_Entity->Bet_Camera[2] , this->m_pBetCamera_Entity->Bet_Camera[2] , sizeof(VisBaseEntity_cl));
	
	this->m_pBetCamera_Entity->Bet_Camera[3] = Vision::Game.SearchEntity("ex_camera_04");
	memcpy( this->m_pOriginalBetCamera_Entity->Bet_Camera[3] , this->m_pBetCamera_Entity->Bet_Camera[3] , sizeof(VisBaseEntity_cl));

}


void CameraSingleton::LoadRaceGuideCameraEntity()
{
	//화면준비
	this->m_pRaceGuideCamera_Entity->RaceGuideCamera[0] = Vision::Game.SearchEntity("1nd_Bottom_start_CameraPosition");
	memcpy(this->m_pRaceGuideCamera_Original->RaceGuideCamera[0] , this->m_pRaceGuideCamera_Entity->RaceGuideCamera[0] , sizeof(VisBaseEntity_cl));

	this->m_pRaceGuideCamera_Entity->RaceGuideCamera[1] = Vision::Game.SearchEntity("2nd_Bottom_start_CameraPosition");
	memcpy(this->m_pRaceGuideCamera_Original->RaceGuideCamera[1] , this->m_pRaceGuideCamera_Entity->RaceGuideCamera[1] , sizeof(VisBaseEntity_cl));
}

//---------------------------------------------------------------------------------------------------------------------
bool CameraSingleton::AttachCamera(const enum CameraLocation eCameraLocation , VisBaseEntity_cl* pSceneCamera , hkvVec3 SpawnPos /*= hkvVec3(0,0,0) */)
{
	if( CameraLocation_TOP == eCameraLocation )
	{
		this->m_pTopCamera->AttachToEntity(pSceneCamera , SpawnPos );//hkvVec3::ZeroVector());
		this->m_pTopCamera->SetPosition(pSceneCamera->GetPosition());

		return true; 
	}
	else if( CameraLocation_BOTTOM == eCameraLocation )
	{
		this->m_pBottomCamera->AttachToEntity(pSceneCamera ,SpawnPos);// hkvVec3::ZeroVector());
		this->m_pBottomCamera->SetPosition(pSceneCamera->GetPosition());
		return true; 
	}
	return false;
}

void CameraSingleton::ResetCamera()
{
	//상단. 
	this->ResetTopCameraEntity();

	//하단
	this->ResetBottomCameraEntity();

	//예시장
	this->ResetBottomCameraEntity();

	//화면준비
	this->ResetRaceGuideCameraEntity();
	
}


void CameraSingleton::ResetRaceGuideCameraEntity()
{
	for ( int i = 0 ; i < 2 ; i++)
	{
		memcpy(this->m_pRaceGuideCamera_Entity->RaceGuideCamera[i] , this->m_pRaceGuideCamera_Original->RaceGuideCamera[i] , sizeof(VisBaseEntity_cl));
	}
}

void CameraSingleton::ResetTopCameraEntity()
{
	for ( int i = 0 ; i < MAX_UPPER_CAMERA_ENTITY ; i++ )
	{
		memcpy(this->m_pTopCameraEntity->Upper_camera[i] ,this->m_pOriginalTopCamera_Entity->Upper_camera[i] ,  sizeof(VisBaseEntity_cl) ); 
	}
}

void CameraSingleton::ResetBottomCameraEntity()
{
	for ( int i = 0 ; i < MAX_BOTTOM_SCENARIO_TYPE; i++ )
	{
		int nIterator = 0 ; 

		// 시나리오 변경되면 아래 조건 추가하거나 삭제.
		if( 0 == i)
		{
			nIterator = MAX_BOTTOM_SCENARIO_1_ENTITY;
		}
		else if( 1 == i )
		{
			nIterator = MAX_BOTTOM_SCENARIO_2_ENTITY;
		}

		for ( int j = 0 ; j < nIterator ; j++ )
		{
			memcpy( this->m_pBottom_Scenario[i]->Bottom_camera[j] ,this->m_pBottom_Original_Scenario[i]->Bottom_camera[j] , sizeof(VisBaseEntity_cl));
		}
	}

}

void CameraSingleton::ResetBetCamera()
{
	for ( int i = 0 ; i < MAX_BET_CAMERA_ENTITY ; i++ )
	{
		memcpy( this->m_pBetCamera_Entity->Bet_Camera[i] , this->m_pOriginalBetCamera_Entity->Bet_Camera[i] , sizeof(VisBaseEntity_cl));
	}
}

void CameraSingleton::SetRenderContext( VisRenderContext_cl* TopRenderContext, VisRenderContext_cl* BottomRenderContext )
{
	this->m_pTopRenderContext		= TopRenderContext;
	this->m_pBottomRenderContext	= BottomRenderContext;
}

void CameraSingleton::SetTopFov( float fFov /*= 90.f*/ )
{
	long int iSizeX = Vision::Video.GetXRes();
	long int iSizeY = Vision::Video.GetYRes()/2;

	this->m_fTopFovX = fFov ; 
	this->m_fTopFovY = hkvMathHelpers::getFovY( this->m_fTopFovX , float(iSizeX) / float(iSizeY)  ) ; 

	this->m_pTopRenderContext->SetFOV(this->m_fTopFovX , this->m_fTopFovY);
}

void CameraSingleton::SetBottomFov( float fFov )
{
	if( fFov < 0.f )
	{
		fFov += 180.f;
	}

	if ( fFov > 180.f )
	{
		fFov -= 180.f;
	}

	long int iSizeX = Vision::Video.GetXRes();
	long int iSizeY = Vision::Video.GetYRes()/2;

	this->m_fBottomFovX = fFov ; 
	this->m_fBottomFovY = hkvMathHelpers::getFovY( this->m_fBottomFovX , float(iSizeX) / float(iSizeY)  ) ; 

	this->m_pBottomRenderContext->SetFOV(this->m_fBottomFovX , this->m_fBottomFovY);
}

void CameraSingleton::ResetTopFov()
{
	long int iSizeX = Vision::Video.GetXRes();
	long int iSizeY = Vision::Video.GetYRes()/2;

	this->m_fTopFovX = 90.f ; 
	this->m_fTopFovY = hkvMathHelpers::getFovY( this->m_fTopFovX , float(iSizeX) / float(iSizeY)  ) ; 

	this->m_pTopRenderContext->SetFOV(this->m_fTopFovX , this->m_fTopFovY);
}

void CameraSingleton::ResetBottomFov()
{
	long int iSizeX = Vision::Video.GetXRes();
	long int iSizeY = Vision::Video.GetYRes()/2;

	this->m_fBottomFovX = 90.f; 
	this->m_fBottomFovY = hkvMathHelpers::getFovY( this->m_fBottomFovX , float(iSizeX) / float(iSizeY)  ) ; 

	this->m_pBottomRenderContext->SetFOV(this->m_fBottomFovX , this->m_fBottomFovY);
}



//
//bool CameraSingleton::AttachCamera( const enum CameraLocation eCameraLocation , VisBaseEntity_cl* pSceneCamera )
//{
//
//}

} /*Game*/ } /*Derby*/