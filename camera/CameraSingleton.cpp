#include "DerbyStandAloneAppPCH.h"
#include "CameraSingleton.h"

namespace Derby { namespace Game {

CameraSingleton::CameraSingleton(void)
{
	//ī�޶�.
	this->m_pBottomCamera			= 0 ; 
	this->m_pTopCamera				= 0 ;

	//���� ���ؽ�Ʈ. 
	this->m_pTopRenderContext		= 0;
	this->m_pBottomRenderContext	= 0;

	this->m_fTopFovX = 90.f;
	this->m_fTopFovY = 0.f;

	this->m_fBottomFovX = 90.f;
	this->m_fBottomFovY = 0.f;

	//ī�޶� �ó�����
	this->m_nCameraScenario = 0 ;

	//��� ī�޶� ��ƼƼ.
	this->m_pTopCameraEntity	= new struct TOP_CAMERA;
	this->m_pOriginalTopCamera_Entity	= new struct TOP_CAMERA;

	//�����ص� ��ƼƼ�� �����س��� ��. 
	for ( int i = 0 ; i < MAX_UPPER_CAMERA_ENTITY ; i++)
	{
		this->m_pOriginalTopCamera_Entity->Upper_camera[i] = 0 ; 
		this->m_pOriginalTopCamera_Entity->Upper_camera[i] = new VisBaseEntity_cl;
	}

	//�ϴ� ī�޶� ��ƼƼ. 

	for ( int i = 0 ; i < MAX_BOTTOM_SCENARIO_TYPE ; i++ )
	{
		this->m_pBottom_Scenario[i]				= 0 ;
		this->m_pBottom_Scenario[i]				= new struct BOTTOM_CAMERA ; 
		this->m_pBottom_Original_Scenario[i]	= new struct BOTTOM_CAMERA;
	}

	//�ϴ� �������� ī�޶�.
	for ( int i= 0 ; i < MAX_BOTTOM_SCENARIO_1_ENTITY ; i++)
	{
		this->m_pBottom_Original_Scenario[0]->Bottom_camera[i] = 0;
		this->m_pBottom_Original_Scenario[0]->Bottom_camera[i] = new VisBaseEntity_cl;
	}
	//�ϴ� 2��° �ó����� �������� ī�޶�. 
	for ( int i= 0 ; i < MAX_BOTTOM_SCENARIO_2_ENTITY ; i++)
	{
		this->m_pBottom_Original_Scenario[1]->Bottom_camera[i] = 0;
		this->m_pBottom_Original_Scenario[1]->Bottom_camera[i] = new VisBaseEntity_cl;
	}

	//������.

	this->m_pBetCamera_Entity			= 0 ; 
	this->m_pOriginalBetCamera_Entity	= 0 ; 

	this->m_pBetCamera_Entity			= new struct BET_CAMERA;
	this->m_pOriginalBetCamera_Entity	= new struct BET_CAMERA;

	for ( int i = 0 ; i < MAX_BET_CAMERA_ENTITY ; i++ )
	{
		this->m_pOriginalBetCamera_Entity->Bet_Camera[i] = new VisBaseEntity_cl;
	}

	//ȭ���غ�
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

	//���.
	if(this->m_pOriginalTopCamera_Entity)
	{
		//�������� ����ü �ȿ� �����Ѱͺ��� ������ �Ŀ� �������� ����ü ����. 
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

	//�ϴ�. 
	for ( int i = 0 ; i < MAX_BOTTOM_SCENARIO_TYPE ; i++)
	{
		if(m_pBottom_Scenario[i])
		{
			int nIterator = 0 ; 

			// �ó����� ����Ǹ� �Ʒ� ���� �߰��ϰų� ����.
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
				//�������� ��ƼƼ �� ����,
				if(this->m_pBottom_Original_Scenario[i]->Bottom_camera[j])
				{
					delete this->m_pBottom_Original_Scenario[i]->Bottom_camera[j];
					this->m_pBottom_Original_Scenario[i]->Bottom_camera[j] = 0;
				}
			}
			//�������� ����.
			delete this->m_pBottom_Original_Scenario[i] ; 
			this->m_pBottom_Original_Scenario[i] = 0 ;

			//������ ����. 
			delete m_pBottom_Scenario[i];
			this->m_pBottom_Scenario[i] = 0 ; 
		}
	}

	//������. 
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

	//ȭ���غ�. 
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
//�� ī�޶� �ε� .
void CameraSingleton::LoadSceneCamera()
{
	//��� �ε�. 
	this->LoadUpperCameraEntity();

	//�ϴ� �ε�. 
	this->LoadBottomCameraEntity();
	
	//������ �ε� . 
	this->LoadBetCameraEntity();

	//����غ� �ε�. 
	this->LoadRaceGuideCameraEntity();

	//���÷��̴� ī�޶� 1���� �������� ������ �������� �� �̷��� �ʿ����. �ٷ� ����. 
	this->m_pReplayCamera = Vision::Game.SearchEntity("Replay_CameraPosition_Finish");

	int a = 0 ; 
}

void CameraSingleton::LoadUpperCameraEntity()
{
	//���. 
	this->m_pTopCameraEntity->Upper_camera[0] = Vision::Game.SearchEntity("Upper_CameraPosition_01");
	//�������ο� �ٷ� �����ص�. 
	memcpy(this->m_pOriginalTopCamera_Entity->Upper_camera[0] , this->m_pTopCameraEntity->Upper_camera[0] , sizeof(VisBaseEntity_cl) ); 

	this->m_pTopCameraEntity->Upper_camera[1] = Vision::Game.SearchEntity("Upper_CameraPosition_02");
	memcpy(this->m_pOriginalTopCamera_Entity->Upper_camera[1] , this->m_pTopCameraEntity->Upper_camera[1] , sizeof(VisBaseEntity_cl) ); 
}

void CameraSingleton::LoadBottomCameraEntity()
{
	//�ϴ�. 

	//���� ��ǥ Ȯ���غ��ߵ�.

	//�ó�����1.
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



	//�ó�����2.
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
	//������.
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
	//ȭ���غ�
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
	//���. 
	this->ResetTopCameraEntity();

	//�ϴ�
	this->ResetBottomCameraEntity();

	//������
	this->ResetBottomCameraEntity();

	//ȭ���غ�
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

		// �ó����� ����Ǹ� �Ʒ� ���� �߰��ϰų� ����.
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