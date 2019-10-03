#ifndef __DERBY_GAME_GAME_LOOPE_FRAME_H__
#define __DERBY_GAME_GAME_LOOPE_FRAME_H__

#include <vector>
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>

#include "../../Sprite/uiManager.h"

#include "../../CameraSingleton/CameraSingleton.h"

//게임 상태를 상속시킬 부모 클래스. 

namespace Derby { namespace Games {

	enum GAME_PROCESS_STATE
	{
		GAME_PROCESS_STATE_NONE				= 0 , 
		//..
	};

	class GameLoopFrame
	{
		public:
			inline ::Derby::Games::GAME_PROCESS_STATE GetState(){	return this->m_eState;	}

			virtual bool Initialize ( void ) ; 
			virtual bool Load ( void ) ; 
			virtual void StartUp ( void ) ; 
			virtual GAME_PROCESS_STATE Process ( float fDeltaTime) ; 
			virtual void Render ( IVRender2DInterface *pRI ) ; 
			virtual void Release ();

			virtual void SetSplitCamera(VisContextCamera_cl* pCamera1 , VisContextCamera_cl* pCamera2);

		public:
			GameLoopFrame(void);
			GameLoopFrame(const GameLoopFrame& ) {}
			virtual ~GameLoopFrame(void);

		protected:
			::Derby::Games::GAME_PROCESS_STATE	m_eState;

			double								loopFrameTime;
			float								m_fDeltaTime;

			::Derby::Sprite::SpriteBase			*testSprite;

			VisContextCamera_cl*				m_pTopCamera;
			VisContextCamera_cl*				m_pBottomCamera;

	};

} /*Games*/ } /*Derby*/

#endif	//__DERBY_GAME_GAME_LOOPE_FRAME_H__