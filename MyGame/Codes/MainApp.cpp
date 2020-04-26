#include "stdafx.h"
#include "MainApp.h"
#include "SceneMgr.h"
#include "Graphic_Device.h"
#include "TimerMgr.h"
#include "Renderer.h"
#include "ObjMgr.h"
#include "ModuleMgr.h"
#include "KeyMgr.h"
#include "TextureLoader.h"

USING(MyGame)

ID3DXFont* g_pFont = nullptr;
CMainApp::CMainApp()
	:m_pSceneMgr(CSceneMgr::Get_Instance())
{

	Safe_AddRef(m_pSceneMgr);
}

HRESULT CMainApp::Initalize()
{


	if (FAILED(Initalize_Default_Setting()))
		return E_FAIL;

	if (FAILED(Initalize_Module()))
		return E_FAIL;

	if (FAILED(Initalize_Texture()))
		return E_FAIL;

	if (FAILED(Initalize_Scene()))
		return E_FAIL;




	return S_OK;
}

_int CMainApp::Update(_double _timeDelta)
{
#if _DEBUG
	m_dwTimeAcc += _timeDelta;
#endif
	m_pSceneMgr->Update(_timeDelta);

	if (nullptr == m_pSceneMgr)
		return -1;

	return 0;
}



HRESULT CMainApp::Render()
{
#if _DEBUG
	++m_iRenderCnt;
	if (m_dwTimeAcc >= 1.0)
	{
		wsprintf(m_szFPS, L"FPS : %d", m_iRenderCnt);
		SetWindowText(g_hWnd, m_szFPS);
		m_dwTimeAcc = 0.0;
		m_iRenderCnt = 0;
	}
#endif
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pSceneMgr)
		return E_FAIL;

	m_pGraphic_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
	m_pGraphic_Device->BeginScene();
	//그림을 그린다.

	if (FAILED(m_pSceneMgr->Render()))
		return E_FAIL;


	m_pGraphic_Device->EndScene();
	m_pGraphic_Device->Present(nullptr, nullptr, g_hWnd, nullptr);

	//만약 씬이 바뀌었으면 이전씬을 지운다.
	if (FAILED(m_pSceneMgr->Clear_PrvScene()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Initalize_Default_Setting()
{
	CGraphic_Device* pGraphic_Device = CGraphic_Device::Get_Instance();
	if (nullptr == pGraphic_Device)
		return E_FAIL;

	Safe_AddRef(pGraphic_Device);

	if (FAILED(pGraphic_Device->Ready_Graphic_Device(CGraphic_Device::TYPE_WIN, &m_pGraphic_Device)))
		return E_FAIL;


	Safe_Release(pGraphic_Device);

	ALPHATEST;

	D3DXCreateFont(m_pGraphic_Device, 0, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"pixel", &g_pFont);


	return S_OK;
}

HRESULT CMainApp::Initalize_Scene()
{
	if (m_pSceneMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pSceneMgr->Scene_Change(SCENE_MENU, m_pGraphic_Device)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Initalize_Module()
{
	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);

	if (FAILED(pModuleMgr->Add_Module(L"VIBuffer", SCENE_STATIC, CVIBuffer::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(pModuleMgr->Add_Module(L"Texture_Default", SCENE_STATIC, CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Loading.jpg"))))
		return E_FAIL;


	if (FAILED(pModuleMgr->Add_Module(L"Transform", SCENE_STATIC, CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	Safe_Release(pModuleMgr);

	return S_OK;
}

HRESULT CMainApp::Initalize_Texture()
{
	
	//이거 주석풀면 그래픽디바이스 못지움.
	//CTextureLoader* pLoader = CTextureLoader::Get_Instance();

	//if (nullptr == pLoader)
	//	return E_FAIL;

	//Safe_AddRef(pLoader);

	//pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENEID::SCENE_MENU, L"../Bin/Resources/Textures/Static/");

	//Safe_Release(pLoader);
	return S_OK;
}


CMainApp * CMainApp::Create()
{
	CMainApp* instance = new CMainApp;
	if (FAILED(instance->Initalize()))
	{
		MSG_BOX("Fail To Create MainApp");
		Safe_Release(instance);
	}
	return instance;
}

void CMainApp::Free()
{
	Safe_Release(g_pFont);
	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pSceneMgr);


	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		return;


	if (0 != CSceneMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CScneeMgr");

	if (0 != CObjMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CObjMgr");

	if (0 != CModuleMgr::Destroy_Instance())
		MSG_BOX("Fail to Relese CModuleMgr");

	if (0 != CRenderer::Destroy_Instance())
		MSG_BOX("Fail to Release CRenderer");

	if (0 != CTimerMgr::Destroy_Instance())
		MSG_BOX("Fail to Release CTimerMgr");

	if (0 != CTextureLoader::Destroy_Instance())
		MSG_BOX("Fail to Release CTextureLoader");

	if (0 != CGraphic_Device::Destroy_Instance())
		MSG_BOX("Fail to Relese CGraphic_Device");



}
