#pragma once

//화면 절반 나눈 다음 화면 랜더 안쪽 루프 따로따로 돌림.
#include <Vision/Runtime/Engine/System/Vision.hpp>
#include <Vision/Runtime/Framework/VisionApp/VAppModule.hpp>

#include "../DerbyMain/DerbyMainManager.h"

class SplitScreenRenderLoop : public VisionRenderLoop_cl
{
public:
	SplitScreenRenderLoop(void);
	virtual ~SplitScreenRenderLoop(void);


	void SetMainFrame ( DerbyMainManager*	pMainFrame ) ; 

public:
	// the constructor takes the two render target textures
	SplitScreenRenderLoop(VTextureObject *pTarget1, VTextureObject *pTarget2);

	virtual void OnDoRenderLoop(void *pUserData) HKV_OVERRIDE ; 

private:
	bool m_bFirstRun;
	//화면
	VTextureObjectPtr m_spSplitTexture[2];


	VisScreenMask_cl*	m_pScreenMask;


	DerbyMainManager*	m_pMainFrame;
};

