#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "TextureLoader.h"
#include "LevelMgr.h"
#include "ObjMgr.h"
#include "Camera.h"
#include "TargetMgr.h"
#include "Light.h"

USING(MyGame)
CLoading::CLoading(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device)
{
}

_uint APIENTRY Theared_Main(void* _pArg)
{
	
	if (nullptr == _pArg)
		return -1;
	CLoading* pLoading = (CLoading*)_pArg;

	HRESULT hr = 0;
	//여기서부터 임계영역
	EnterCriticalSection(&pLoading->Get_CriticalSection());

	//데이터로드
	switch (pLoading->Get_SceneID())
	{
	case SCENE_MENU:
		break;
	case SCENE_STAGE:
		pLoading->Initialize_Stage();
		break;

	}

	//임계영역을 빠져나온다.
	LeaveCriticalSection(&pLoading->Get_CriticalSection());


	pLoading->Set_Finish();
	if (FAILED(hr))
		return -1;

	return 0;

}



HRESULT CLoading::Initialize(SCENEID _eSceneID)
{
	m_eSceneID = _eSceneID;
	/*
	@ 크리티컬 섹션
	임계영역 자체를 말하기도하고, 락을 거는 기법을 의미하기도 한다.
	m_CriticalSection는 임계영역에 들어가기 위한 Key를 의미한다. 이 Key가 있어야 임계영역에 들어갈 수 있다.

	임계영역은 보통 힙과 데이터영역을 의미한다.
	모든 스레드는 이 힙과 데이터영역을 공유하고, 각각 별도의 스택영역을 갖는다.

	주의할 점은 멀티스레드는 멀티프로세스가 아니라는 것이다.
	얼핏보면 멀티스레드는 코드의 흐름이 여러개인 것처럼 보이지만, 
	그것은 하나의 cpu 코어가 여러 스레드를 옮겨가며 연산을 수행하는 시분할방식이기 때문에 그렇게 보이는 것 뿐이다.
	진정으로 코드의 흐름이 여러개인 것은 멀티코어 cpu로 멀티프로세스 프로그램을 돌릴때이다.
	*/
	InitializeCriticalSection(&m_CriticalSection);
	
	/*
	스레드를 만든다.
	unsigned stack_size	: 스레드가 사용할 스택영역의 사이즈. 0을 주면 1바이트로 셋팅된다. (스택영역의 변수는 자동으로 지워지기 때문에 크기가 필요가 없다)
	unsigned ( __clrcall *start_address )( void * ) : 스레드의 진입점(메인함수)
	
	*/
	m_Handle = (HANDLE)_beginthreadex(nullptr, 0, Theared_Main, this, 0, nullptr);
	return S_OK;
}

HRESULT CLoading::Initialize_Stage()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CTextureLoader* pLoader = CTextureLoader::Get_Instance();
	if (nullptr == pLoader)

		return E_FAIL;

	Safe_AddRef(pLoader);

	//텍스쳐생성
	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/Stage/");
	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/icon/");
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Terrain/level_one/");
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Effect/");


	Safe_Release(pLoader);

	CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();

	//레벨에 필요한 프로로타입 생성
	if (FAILED(pLevelMgr->Initialize_Prototypes(m_pGraphic_Device)))
		return E_FAIL;



	//카메라 프로로타입 생성
	pObjMgr->Add_Prototype(L"MainCamera", SCENE_STAGE, CCamera::Create(m_pGraphic_Device));

	pObjMgr->Add_Prototype(L"Light", SCENE_STAGE, CLight::Create(m_pGraphic_Device));
	
	//렌더타겟 생성
	CTargetMgr* pTargetMgr = CTargetMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pTargetMgr);
	pTargetMgr->Add_RenderTarget(m_pGraphic_Device, L"Portrait", 100.f, 100.f, D3DFMT_A8R8G8B8);
	pTargetMgr->Add_RenderTarget(m_pGraphic_Device, L"Fog", g_iWinCX, g_iWinCY, D3DFMT_A8R8G8B8);


	return S_OK;

}



CLoading * CLoading::Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID)
{
	CLoading* pInstance = new CLoading(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_eSceneID)))
	{
		MSG_BOX("Fail to create Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoading::Free()
{
	//스레드의 실행도중에 스레드를 닫으면 메모리릭이 날 수 있다. 따라서 끝날때까지 기다린다.
	WaitForSingleObject(m_Handle, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_Handle);

	Safe_Release(m_pGraphic_Device);
}
