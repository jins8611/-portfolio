#pragma once

//#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
//#include <Vision/Runtime/Base/Graphics/Textures/VTextureObject.hpp>


#include <Vision/Runtime/Engine/System/Vision.hpp>
#include <Vision/Runtime/Engine/Animation/VisApiAnimNormalizeMixerNode.hpp>

//�н� 
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Components/VFollowPathComponent.hpp>
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Components/VOrbitCamera.hpp>
//���̴�
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
	//�̵� , ȸ��.
	void SetPos ( hkvVec3 NextPos ) ; 
	void SetORIENTATION ( hkvVec3 Orientation ) ;
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//�ִϸ��̼�.
	void SetAnimation(enum AnimationEnum eAnimation)
	void SetAnimationSpeed ( float fSpeed = 1.f) ; 
	void BlendAnimation ( AnimationEnum eCurrentAnim , AnimationEnum eNextAnim ) ; 

	//���̷��� �ִϸ��̼� ��Ʈ�� Ŭ���� �����͸� ����.
	VisSkeletalAnimControl_cl *GetSingleAnimControl() const { return m_spSingleAnimControl; }

	void StopAnimation( float fPassedTime );

	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//�н�
	void SetPath ( PathElement pElement ) ; 

	void ChangePathSpeed ( float fCurrentTime ) ; 

	void ResetPath ( void ) ; 

	VisPath_cl*					GetPath ( void ) { return m_Path ; }
	VFollowPathComponent*		GetFollowPath (void) { return m_FollowPath ; }
	float						GetLintTime (void) ;

	PathElement*				GetPathElement ( void ) { return &m_pathElement ;  } 

	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//���� ���� �Ǿ��ִ� Orbitī�޶�. 
	void SetOrbitCamera ( void ) ; 

	void EnableOrbitCamera ( bool bEnable ) ; 
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//Debug Print
	float ReturnCurrentSpeed ( void );
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//�� ������.
	float GetModelSize ( void ) ; 
	//------------------------------------------------------------------

	//�ӵ� ����
	void ChangeHorseSpeed ( float fSpeed ) ; 

	//------------------------------------------------------------------
	//���̴�
	void SetCustomShader ( void ) ; 
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//�ڱ� �ڽ� ����. 
	VisBaseEntity_cl*	GetHorse ( void ) { return (VisBaseEntity_cl*)this ; }

	VOrbitCamera*		GetOrbitCamera ( void ) { return m_OrbitCamera ; } 
	//------------------------------------------------------------------

	//���׸��� 
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

	//��ֶ����� �ͼ����. ������ �ʿ��� Ŭ���� ������. 
	VSmartPtr<VisAnimNormalizeMixerNode_cl> m_spNormalizeMixerNode;
	//���� �Է� ����
	int m_iMixerInputStay, m_iMixerInputGallop;

	//���� �������� �ִϸ��̼�.
	AnimationEnum				m_eCurrentAnim;

	//�н�
	VFollowPathComponent*		m_FollowPath;
	VisPath_cl*					m_Path;
	//�н���
	PathElement					m_pathElement;

	float						m_RandomPi ; 


	//OrbitCamera
	VOrbitCamera*				m_OrbitCamera;

	//�ִϸ��̼� ����. 
	//VisSkeletalAnimSequence_cl*		m_spRun;
	//VisSkeletalAnimSequence_cl*			pAnimSequenceGallop;


	//�޸��� �ִϸ��̼� ��Ʈ�ѷ�.
	VSmartPtr<VisSkeletalAnimControl_cl> spGallopAnimComtrol ; 

	
	
};

