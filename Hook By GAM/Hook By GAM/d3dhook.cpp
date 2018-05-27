//Hook By GAM

#include "main.h"

HRESULT __stdcall Hooked_Present(IDirect3DDevice9 *pDevice, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion)
{
	if (!pDevice)
		return pD3DHook->Orginal_Present(pDevice, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);

	if (pD3DHook->bD3DRenderInit == false)
	{
		pD3DHook->pRender->Initialize(pDevice);
		pD3DHook->pD3DFont->Initialize(pDevice);

		pD3DHook->bD3DRenderInit = true;
	}

	if (!pSAMP->isInited)
		pD3DHook->pD3DFont->Print(1, 1, D3DCOLOR_ARGB(255, rand() % 255, rand() % 255, rand() % 255), "", true);
	
	return pD3DHook->Orginal_Present(pDevice, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);
}

HRESULT __stdcall Hooked_Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentParams)
{
	if (!pDevice)
		return pD3DHook->Orginal_Reset(pDevice, pPresentParams);

	if (pD3DHook->bD3DRenderInit == true)
	{
		pD3DHook->pD3DFont->Invalidate();
		pD3DHook->pRender->Invalidate();

		pD3DHook->bD3DRenderInit = false;
	}

	HRESULT ret = pD3DHook->Orginal_Reset(pDevice, pPresentParams);

	if (ret == D3D_OK)
	{
		pD3DHook->pRender->Initialize(pDevice);
		pD3DHook->pD3DFont->Initialize(pDevice);
		pD3DHook->pPresentParam = *pPresentParams;

		pD3DHook->bD3DRenderInit = true;
	}

	return ret;
}