#ifndef __DERBY_GAME_FLOW_LOGO_H__
#define __DERBY_GAME_FLOW_LOGO_H__

#include "GameLoopFrame.h"

#include "../../Sprite/uiManager.h"

//게임 씬중 일부 예제. 

namespace Derby { namespace Games {

	class Logo : public GameLoopFrame
	{
		public:

			virtual bool Initialize ( void ) ; 
			virtual bool Load ( void ) ; 
			virtual void StartUp ( void ) ; 
			virtual GAME_PROCESS_STATE Process ( float fDeltaTime) ; 
			virtual void Render ( IVRender2DInterface *pRI ) ; 
			virtual void Release ();

		public:
			Logo(void);
			Logo(const Logo&){}
			virtual ~Logo(void);

		private:
			::Derby::Sprite::Font				*fontDebug;

			::Derby::Sprite::UserBar *userBar;
	};


} /*Games*/ } /*Derby*/

#endif	//__DERBY_GAME_FLOW_LOGO_H__