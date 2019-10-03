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

		//���÷��� ī�޶�
		struct REPLAY_CAMERA
		{
			VisBaseEntity_cl*	ReplayCamera;
		};


	public:
		CameraSingleton(void);
		~CameraSingleton(void);

		//ī�޶� �ּ� ������ �Լ�. 
		void SetContextCamera(VisContextCamera_cl* TopCamera , VisContextCamera_cl* BottomCamera);
		void SetRenderContext(VisRenderContext_cl* TopRenderContext, VisRenderContext_cl* BottomRenderContext) ; 

		//������ ī�޶� �ε�.
		void LoadSceneCamera();

		//ī�޶� ���̱�. 
		bool AttachCamera( const enum CameraLocation eCameraLocation , VisBaseEntity_cl* pSceneCamera , hkvVec3 SpawnPos = hkvVec3(0,0,0) );

		//ī�޶� ����.
		void ResetCamera();

		//������ ����.
		void ResetBetCamera();
		void ResetTopCameraEntity();
		void ResetBottomCameraEntity();
		void ResetRaceGuideCameraEntity();

		//fov�� ����.
		inline VisRenderContext_cl* GetTopRenderContext()		{ return this->m_pTopRenderContext ; }
		inline VisRenderContext_cl* GetBottomRenderContext()	{ return this->m_pBottomRenderContext ; }

		void SetTopFov( float fFov );
		void ResetTopFov() ; 

		void SetBottomFov( float fFov );
		void ResetBottomFov() ; 

		//ī�޶� ����. 
		inline VisContextCamera_cl* GetTopCamera()		{ return this->m_pTopCamera ; }
		inline VisContextCamera_cl* GetBottomCamera()	{ return this->m_pBottomCamera ; }
		//������ ī�޶� ����. 
		inline struct BET_CAMERA*	GetBetCamera() { return this->m_pBetCamera_Entity ; }

		inline struct RACE_GUIDE_CAMERA* GetRaceGuideCamera() { return this->m_pRaceGuideCamera_Entity;}

		//���÷��� ī�޶� ����. 
		inline VisBaseEntity_cl* GetReplayCamera() { return this->m_pReplayCamera ; }

		//���� �ٸ���. �̰� ����ü �ȿ� ������.
		inline struct TOP_CAMERA*		GetTopCameraEntity() { return this->m_pTopCameraEntity ; }
		inline struct BOTTOM_CAMERA*	GetBottomCameraEntity(int nScenarioIndex ) { return this->m_pBottom_Scenario[nScenarioIndex] ; }

		inline float GetTopFov() { return this->m_fTopFovX ; }
		inline float GetBottomFov() { return this->m_fBottomFovX ; }

		//ī�޶� �ó�����
		inline long int GetCameraScenario() { return this->m_nCameraScenario;}
		inline void SetCameraScenario(long int nScenario) { this->m_nCameraScenario = nScenario ;}

		//float		m_fTopFov;
		//float		m_fBottomFov;

	private:
		//��� ī�޶� �ε�.
		void LoadUpperCameraEntity();
		//�ϴ� ī�޶� �ε�.
		void LoadBottomCameraEntity();
		//������ ī�޶� �ε�.
		void LoadBetCameraEntity();
		//ȭ���غ� ī�޶� �ε�
		void LoadRaceGuideCameraEntity();



	private:

		//ī�޶�.
		VisContextCamera_cl*			m_pTopCamera;
		VisContextCamera_cl*			m_pBottomCamera;

		//���� ���ؽ�Ʈ. 
		VisRenderContext_cl*			m_pTopRenderContext;//GetRenderContext() { return m_pContext1 ;}
		VisRenderContext_cl*			m_pBottomRenderContext;

		//FOV ���� ����. 
		float							m_fTopFovX;
		float							m_fTopFovY;
		float							m_fBottomFovX;
		float							m_fBottomFovY;

		//��� ī�޶� ��ƼƼ. 
		struct TOP_CAMERA*				m_pTopCameraEntity;
		struct TOP_CAMERA*				m_pOriginalTopCamera_Entity;

		//�ϴ� ī�޶� ��ƼƼ. 
		struct BOTTOM_CAMERA*			m_pBottom_Scenario[2];
		struct BOTTOM_CAMERA*			m_pBottom_Original_Scenario[2];

		//������ ī�޶�. 
		struct BET_CAMERA*				m_pBetCamera_Entity;
		struct BET_CAMERA*				m_pOriginalBetCamera_Entity;

		//ȭ���غ� ī�޶� 
		struct RACE_GUIDE_CAMERA*		m_pRaceGuideCamera_Entity;
		struct RACE_GUIDE_CAMERA*		m_pRaceGuideCamera_Original;

		//���÷��� ī�޶�.
		VisBaseEntity_cl*				m_pReplayCamera;

	};

} /*Game*/ } /*Derby*/