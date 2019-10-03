#pragma once
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
#include <utility/utility.h>

namespace Derby { namespace Game {

	class CameraSingleton : public ::Common::Utility::Singleton<CameraSingleton>
	{
	public:

		enum CameraLocation
		{
			CameraLocation_NONE = 0 , 
			CameraLocation_TOP  , 
			CameraLocation_BOTTOM  , 
		};

		struct TOP_CAMERA
		{
			VisBaseEntity_cl*	Upper_camera[2];
		};

		struct BOTTOM_CAMERA
		{
			VisBaseEntity_cl*	Bottom_camera[6];
		};

		struct BET_CAMERA
		{
			VisBaseEntity_cl*	Bet_Camera[4];
		};

		//RaceGuideCamera
		struct RACE_GUIDE_CAMERA
		{
			VisBaseEntity_cl*	RaceGuideCamera[2];
		};

		//리플레이 카메라
		struct REPLAY_CAMERA
		{
			VisBaseEntity_cl*	ReplayCamera;
		};


	public:
		CameraSingleton(void);
		~CameraSingleton(void);

		//카메라 주소 얻어오는 함수. 
		void SetContextCamera(VisContextCamera_cl* TopCamera , VisContextCamera_cl* BottomCamera);
		void SetRenderContext(VisRenderContext_cl* TopRenderContext, VisRenderContext_cl* BottomRenderContext) ; 

		//씬에서 카메라 로드.
		void LoadSceneCamera();

		//카메라 붙이기. 
		bool AttachCamera( const enum CameraLocation eCameraLocation , VisBaseEntity_cl* pSceneCamera , hkvVec3 SpawnPos = hkvVec3(0,0,0) );

		//카메라 리셋.
		void ResetCamera();

		//예시장 리셋.
		void ResetBetCamera();
		void ResetTopCameraEntity();
		void ResetBottomCameraEntity();
		void ResetRaceGuideCameraEntity();

		//fov값 세팅.
		inline VisRenderContext_cl* GetTopRenderContext()		{ return this->m_pTopRenderContext ; }
		inline VisRenderContext_cl* GetBottomRenderContext()	{ return this->m_pBottomRenderContext ; }

		void SetTopFov( float fFov );
		void ResetTopFov() ; 

		void SetBottomFov( float fFov );
		void ResetBottomFov() ; 

		//카메라 리턴. 
		inline VisContextCamera_cl* GetTopCamera()		{ return this->m_pTopCamera ; }
		inline VisContextCamera_cl* GetBottomCamera()	{ return this->m_pBottomCamera ; }
		//예시장 카메라 리턴. 
		inline struct BET_CAMERA*	GetBetCamera() { return this->m_pBetCamera_Entity ; }

		inline struct RACE_GUIDE_CAMERA* GetRaceGuideCamera() { return this->m_pRaceGuideCamera_Entity;}

		//리플레이 카메라 리턴. 
		inline VisBaseEntity_cl* GetReplayCamera() { return this->m_pReplayCamera ; }

		//위랑 다르다. 이건 구조체 안에 리턴임.
		inline struct TOP_CAMERA*		GetTopCameraEntity() { return this->m_pTopCameraEntity ; }
		inline struct BOTTOM_CAMERA*	GetBottomCameraEntity(int nScenarioIndex ) { return this->m_pBottom_Scenario[nScenarioIndex] ; }

		inline float GetTopFov() { return this->m_fTopFovX ; }
		inline float GetBottomFov() { return this->m_fBottomFovX ; }

		//카메라 시나리오
		inline long int GetCameraScenario() { return this->m_nCameraScenario;}
		inline void SetCameraScenario(long int nScenario) { this->m_nCameraScenario = nScenario ;}

		//float		m_fTopFov;
		//float		m_fBottomFov;

	private:
		//상단 카메라 로드.
		void LoadUpperCameraEntity();
		//하단 카메라 로드.
		void LoadBottomCameraEntity();
		//예시장 카메라 로드.
		void LoadBetCameraEntity();
		//화면준비 카메라 로드
		void LoadRaceGuideCameraEntity();



	private:

		//카메라.
		VisContextCamera_cl*			m_pTopCamera;
		VisContextCamera_cl*			m_pBottomCamera;

		//랜더 콘텍스트. 
		VisRenderContext_cl*			m_pTopRenderContext;//GetRenderContext() { return m_pContext1 ;}
		VisRenderContext_cl*			m_pBottomRenderContext;

		//FOV 관련 변수. 
		float							m_fTopFovX;
		float							m_fTopFovY;
		float							m_fBottomFovX;
		float							m_fBottomFovY;

		//상단 카메라 엔티티. 
		struct TOP_CAMERA*				m_pTopCameraEntity;
		struct TOP_CAMERA*				m_pOriginalTopCamera_Entity;

		//하단 카메라 엔티티. 
		struct BOTTOM_CAMERA*			m_pBottom_Scenario[2];
		struct BOTTOM_CAMERA*			m_pBottom_Original_Scenario[2];

		//예시장 카메라. 
		struct BET_CAMERA*				m_pBetCamera_Entity;
		struct BET_CAMERA*				m_pOriginalBetCamera_Entity;

		//화면준비 카메라 
		struct RACE_GUIDE_CAMERA*		m_pRaceGuideCamera_Entity;
		struct RACE_GUIDE_CAMERA*		m_pRaceGuideCamera_Original;

		//리플레이 카메라.
		VisBaseEntity_cl*				m_pReplayCamera;

	};

} /*Game*/ } /*Derby*/