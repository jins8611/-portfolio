#include "DerbyStandAloneAppPCH.h"
#include "SplitScreenRenderLoop.h"

#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/Rendering/RendererNode/VRendererNodeCommon.hpp>

SplitScreenRenderLoop::SplitScreenRenderLoop(void)
{
}

SplitScreenRenderLoop::~SplitScreenRenderLoop(void)
{
}


SplitScreenRenderLoop::SplitScreenRenderLoop(VTextureObject *pTarget1, VTextureObject *pTarget2)
{
	m_bFirstRun = true ; 
	m_spSplitTexture[0] = pTarget1 ; 
	m_spSplitTexture[1] = pTarget2 ; 

	return;
}


void SplitScreenRenderLoop::OnDoRenderLoop(void *pUserData)
{

	// since we have a border, the screen should be cleared once at beginning
	Vision::RenderLoopHelper.ClearScreen() ; 

	const float fBorder = 1.f;
	const float x0 = 0.f;
	const float x1 = static_cast<float>(Vision::Video.GetXRes());
	const float y0 = 0.f;
	const float y2 = static_cast<float>(Vision::Video.GetYRes());
	const float y1 = y2 * 0.5f;

	const float u0 = fBorder/(float)m_spSplitTexture[0]->GetTextureWidth();
	const float v0 = fBorder/(float)m_spSplitTexture[0]->GetTextureHeight();
	const float u1 = 1.0f - u0;
	const float v1 = 1.0f - v0;

	//VSimpleRenderState_t iState(VIS_TRANSP_NONE,RENDERSTATEFLAG_FRONTFACE|RENDERSTATEFLAG_USEFOG|RENDERSTATEFLAG_NOWIREFRAME);
	VSimpleRenderState_t iState(VIS_TRANSP_NONE,RENDERSTATEFLAG_FRONTFACE|RENDERSTATEFLAG_ALWAYSVISIBLE|RENDERSTATEFLAG_NOWIREFRAME|RENDERSTATEFLAG_NOMULTISAMPLING);
	VSimpleRenderState_t iFontState = VisFont_cl::DEFAULT_STATE;

	IVRender2DInterface *pRI = Vision::RenderLoopHelper.BeginOverlayRendering();

	// render the two target textures as screen overlays
	// if two texture are used:
	if (m_spSplitTexture[0] != NULL && m_spSplitTexture[1] != NULL)
	{

		if( cSetup()->GetStatus() == EST_None )
		{
			//  [1/14/2016 ChangJin_Win7]
			// 3D 화면 랜더.
			pRI->DrawTexturedQuad(hkvVec2( x0 + fBorder , y0 + fBorder ) , hkvVec2( x1 -fBorder , y1 - fBorder ) ,m_spSplitTexture[0],hkvVec2(u0,v0), hkvVec2(u1,v1), V_RGBA_WHITE, iState);
			pRI->DrawTexturedQuad(hkvVec2( x0 + fBorder , y1 + fBorder ) , hkvVec2( x1 -fBorder , y2 - fBorder ) ,m_spSplitTexture[1],hkvVec2(u0,v0), hkvVec2(u1,v1), V_RGBA_WHITE, iState);
		}

		iState = VGUIManager::DefaultGUIRenderState();

		//이 부분이 UI인데.
		this->m_pMainFrame->Render(pRI);


	}
	//otherwise: only one texture that occupies the full space
	else if (m_spSplitTexture[0] != NULL)
	{
		//pRI->DrawTexturedQuad(hkvVec2(x0,y0),hkvVec2(x2,y1),m_spSplitTexture[0],hkvVec2(0.0f,0.0f), hkvVec2(1.0f,1.0f), V_RGBA_WHITE, iState);
	}

	Vision::RenderLoopHelper.EndOverlayRendering();

	// Render 2D and 3D overlaid geometry
	VRendererNodeCommon::RenderOverlays(false , false ) ; 
}

void SplitScreenRenderLoop::SetMainFrame(DerbyMainManager* pMainFrame)
{
	this->m_pMainFrame = pMainFrame ; 
}