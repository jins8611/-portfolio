#pragma once

//#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
//#include <Vision/Runtime/Base/Graphics/Textures/VTextureObject.hpp>


#include <Vision/Runtime/Engine/System/Vision.hpp>
#include <Vision/Runtime/Engine/Animation/VisApiAnimNormalizeMixerNode.hpp>

//패스 
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Components/VFollowPathComponent.hpp>
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Components/VOrbitCamera.hpp>
//쉐이더
#include <Vision/Runtime/Engine/Renderer/Shader/VisApiShaderSet.hpp>

enum AnimationEnum
{
	Anim_NONE = 0 ,
	Anim_Stay , 
	Anim_Walk1 , 
	Anim_Walk2 , 
	Anim_Run1 , 
	Anim_Run2 , 
	Anim_Run3 , 
	Anim_Trot1 , 
	Anim_Trot2 , 
	Anim_Trot3 , 
	Anim_Gallop , 
	Anim_Cheer1 , 
	Anim_Cheer2 , 

	Anim_End
};

struct PathElement
{
	char*			pPathName;
	float			fTime;
	hkvVec3			vec3Orientation;
	hkvVec3			vec3Position;
	float			HorseSpeed;

};


class DerbyHorse : public VisBaseEntity_cl
{
public:

	//------------------------------------------------------------------
	//이동 , 회전.
	void SetPos ( hkvVec3 NextPos ) ; 
	void SetORIENTATION ( hkvVec3 Orientation ) ;
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//애니메이션.
	void SetAnimation(enum AnimationEnum eAnimation)
	void SetAnimationSpeed ( float fSpeed = 1.f) ; 
	void BlendAnimation ( AnimationEnum eCurrentAnim , AnimationEnum eNextAnim ) ; 

	//스켈레톤 애니메이션 컨트롤 클래스 포인터를 리턴.
	VisSkeletalAnimControl_cl *GetSingleAnimControl() const { return m_spSingleAnimControl; }

	void StopAnimation( float fPassedTime );

	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//패스
	void SetPath ( PathElement pElement ) ; 

	void ChangePathSpeed ( float fCurrentTime ) ; 

	void ResetPath ( void ) ; 

	VisPath_cl*					GetPath ( void ) { return m_Path ; }
	VFollowPathComponent*		GetFollowPath (void) { return m_FollowPath ; }
	float						GetLintTime (void) ;

	PathElement*				GetPathElement ( void ) { return &m_pathElement ;  } 

	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//말에 종속 되어있는 Orbit카메라. 
	void SetOrbitCamera ( void ) ; 

	void EnableOrbitCamera ( bool bEnable ) ; 
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//Debug Print
	float ReturnCurrentSpeed ( void );
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//말 사이즈.
	float GetModelSize ( void ) ; 
	//------------------------------------------------------------------

	//속도 변경
	void ChangeHorseSpeed ( float fSpeed ) ; 

	//------------------------------------------------------------------
	//쉐이더
	void SetCustomShader ( void ) ; 
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//자기 자신 뱉어내기. 
	VisBaseEntity_cl*	GetHorse ( void ) { return (VisBaseEntity_cl*)this ; }

	VOrbitCamera*		GetOrbitCamera ( void ) { return m_OrbitCamera ; } 
	//------------------------------------------------------------------

	//메테리얼 
	void ReplaceEntityBaseTexture(VisBaseEntity_cl *pEntity, const char *szSurfacename, const char *szNewTexture);

public:
	V_DECLARE_SERIAL( DerbyHorse, )
		V_DECLARE_VARTABLE_NO_EXPORT(DerbyHorse);

	
public:
	DerbyHorse(void);
	DerbyHorse(VisBaseEntity_cl* p);

	~DerbyHorse(void);

public:
	// VisBaseEntity_cl overrides
	virtual void InitFunction() HKV_OVERRIDE;
	virtual void DeInitFunction() HKV_OVERRIDE;
	virtual void ThinkFunction() HKV_OVERRIDE;
	virtual void MessageFunction(int iID, INT_PTR iParamA, INT_PTR iParamB) HKV_OVERRIDE;



private:

	//VisVertexAnimControl
	//VisSkeletalAnimControl
	VSmartPtr<VisSkeletalAnimControl_cl> m_spSingleAnimControl;

	//노멀라이즈 믹서노드. 블렌딩에 필요한 클래스 포인터. 
	VSmartPtr<VisAnimNormalizeMixerNode_cl> m_spNormalizeMixerNode;
	//블렌딩 입력 변수
	int m_iMixerInputStay, m_iMixerInputGallop;

	//현재 실행중인 애니메이션.
	AnimationEnum				m_eCurrentAnim;

	//패스
	VFollowPathComponent*		m_FollowPath;
	VisPath_cl*					m_Path;
	//패스값
	PathElement					m_pathElement;

	float						m_RandomPi ; 


	//OrbitCamera
	VOrbitCamera*				m_OrbitCamera;

	//애니메이션 제어. 
	//VisSkeletalAnimSequence_cl*		m_spRun;
	//VisSkeletalAnimSequence_cl*			pAnimSequenceGallop;


	//달리는 애니메이션 컨트롤러.
	VSmartPtr<VisSkeletalAnimControl_cl> spGallopAnimComtrol ; 

	
	
};

