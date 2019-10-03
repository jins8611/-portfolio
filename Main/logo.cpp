#include "DerbyStandAloneAppPCH.h"
#include "logo.h"

namespace Derby { namespace Games {

	Logo::Logo(void)
	{
		//this->m_eState = GAME_PROCESS_STATE_LOGO
	}


	Logo::~Logo(void)
	{
	}

	bool Logo::Initialize(void)
	{
		int a= 0 ; 
		return true;
	}

	bool Logo::Load(void)
	{

		return true;
	}

	GAME_PROCESS_STATE Logo::Process(float fPassedTime)
	{
		this->m_fDeltaTime += fPassedTime;

		if ( this->m_fDeltaTime > 5.0f)
		{
			this->m_fDeltaTime=0.f;

			return GAME_PROCESS_STATE_TITLE ; 
		}

		return this->m_eState;
	}


	void Logo::Render(IVRender2DInterface *pRI)
	{
		VSimpleRenderState_t iState = VGUIManager::DefaultGUIRenderState();

	}

	void Logo::StartUp(void)
	{

	}

	void Logo::Release()
	{

	}

} /*Games*/ } /*Games*/
