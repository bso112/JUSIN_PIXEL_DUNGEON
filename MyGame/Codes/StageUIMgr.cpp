#include "stdafx.h"
#include "..\Headers\StageUIMgr.h"
#include "ObjMgr.h"
#include "Image.h"
#include "MyButton.h"
#include "Hero.h"
#include "InventoryUIMgr.h"
#include "DialogMgr.h"
#include "StatsPanel.h"
#include "Texture.h"
#include "TargetMgr.h"
#include "HpBar.h"
#include "DialogPanel.h"
#include "TurnMgr.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CStageUIMgr)

CStageUIMgr::CStageUIMgr()
	:m_pObjMgr(CObjMgr::Get_Instance())
{
	Safe_AddRef(m_pObjMgr);
}

HRESULT CStageUIMgr::Initialize_Prototype(LPDIRECT3DDEVICE9 _pGraphic_Device, CHero* _pHero)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	Safe_AddRef(_pGraphic_Device);
	Safe_AddRef(_pHero);

	vector<CGameObject*>  vecUI;
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(_pGraphic_Device, Vector4(float(g_iWinCX>>1), 50.f, 0.f, 1.f), Vector2((float)g_iWinCX, 100.f), L"status_pane", SCENE_STAGE));
	
	int iBtnCX = 60;
	int iBtnCY = 70;
	CMyButton* pBtn = nullptr;


	//스텟판넬
	m_pStatsPanel = dynamic_cast<CStatsPanel*>( m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CStatsPanel::Create(_pGraphic_Device)));
	if (m_pStatsPanel == nullptr)
		return E_FAIL;
	Safe_AddRef(m_pStatsPanel);

	CTargetMgr* pTargetMgr = CTargetMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pTargetMgr);
	LPDIRECT3DTEXTURE9 pPortrait = pTargetMgr->Get_Texture(L"Portrait");
	RETURN_FAIL_IF_NULL(pPortrait);

	//초상화버튼
	pBtn = CMyButton::Create(_pGraphic_Device, Vector2(40.f, 40.f), Vector2(80.f, 80.f), CTexture::Create(_pGraphic_Device, pPortrait));
	pBtn->Add_Listener([&] {m_pStatsPanel->Set_Active(!m_pStatsPanel->Get_Active()); m_pStatsPanel->Set_Player();});
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	
	vecUI.push_back(pBtn);



	//인벤토리버튼
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1), g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"inventoryBtn", SCENE_STAGE);
	//누르면 인벤토리 켜기
	pBtn->Add_Listener([&] {m_pInventoryUIMgr->Active_Inventory();});
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	


	//탐사버튼
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1) + iBtnCX * 1, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"searchBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	pBtn->Add_Listener([] 
	{
		CObjMgr* pObjMgr = CObjMgr::Get_Instance(); 
		if (pObjMgr) 
		{ 
			CHero* pHero = dynamic_cast<CHero*> (pObjMgr->Get_Player(SCENE_STAGE));
			if (nullptr != pHero)
			{
				pHero->Explore();
			}
			
		}
	
	});
	vecUI.push_back(pBtn);
	//조사버튼
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1) + iBtnCX * 2, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"checkBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	//대기버튼
	pBtn = CMyButton::Create(_pGraphic_Device, Vector4((g_iWinCX >> 1) + float(iBtnCX >> 1) + iBtnCX * 3, g_iWinCY - float(iBtnCY >> 1), 0.f, 1.f), Vector2((float)iBtnCX, (float)iBtnCY), L"waitBtn", SCENE_STAGE);
	m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, pBtn);
	vecUI.push_back(pBtn);
	pBtn->Add_Listener([&]
	{
		
		CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(1);
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		if (pObjMgr)
		{
			CHero* pHero = dynamic_cast<CHero*> (pObjMgr->Get_Player(SCENE_STAGE));
			if (nullptr != pHero)
			{
				pHero->ShowText(L"....", 0xffffffff);
			}
		}
	});


	
	//다이어로그판넬
	m_pDialogPanel = (CDialogPanel*)m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CDialogPanel::Create(_pGraphic_Device));
	RETURN_FAIL_IF_NULL(m_pDialogPanel);
	m_pDialogPanel->Set_Active(false);
	Safe_AddRef(m_pDialogPanel);

	//스크롤 표시
	//pBtn = CMyButton::Create(_pGraphic_Device, Vector4((float)(g_iWinCX >> 1), (float)(g_iWinCY >> 1), 0.f, 1.f), Vector2(g_iWinCX - 100.f, 200.f), L"scroll", SCENE_STAGE);
	//m_pObjMgr->Add_GO_To_Layer(CObjMgr::LAYER_UI, SCENE_STAGE, pBtn);

	
	
	for (auto& ui : vecUI)
	{
		CTransform* pTransform = (CTransform*)ui->Get_Module(L"Transform");
		if (nullptr != pTransform)
			m_vecUIRect.push_back(pTransform->Get_RECT());
	}

	CImage::STATEDESC bossBannerDesc;
	bossBannerDesc.m_dLifeTime = 10.f;
	bossBannerDesc.m_eTextureSceneID = SCENE_STAGE;
	bossBannerDesc.m_pTextureTag = L"BossBanner";
	bossBannerDesc.m_iTextureID = 0;
	bossBannerDesc.m_fSpeed = 100.f;
	bossBannerDesc.m_tBaseDesc = BASEDESC(Vector3(_float(g_iWinCX >> 1), 150.f), Vector3(400.f, 150.f, 1.f));
	m_pBossSlainBanner = (CImage*)m_pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(_pGraphic_Device, &bossBannerDesc));
	RETURN_FAIL_IF_NULL(m_pBossSlainBanner);
	Safe_AddRef(m_pBossSlainBanner);
	m_pBossSlainBanner->Set_UI(true);
	m_pBossSlainBanner->Set_Active(false);
	m_pBossSlainBanner->Set_Depth(5);


	Safe_Release(_pHero);
	Safe_Release(_pGraphic_Device);
	return S_OK;
}

HRESULT CStageUIMgr::Initialize(LPDIRECT3DDEVICE9 _pGraphic_Device, CHero* _pHero)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	Safe_AddRef(_pGraphic_Device);

	if (FAILED(Initialize_Prototype(_pGraphic_Device, _pHero)))
	{
		Safe_Release(_pGraphic_Device);
		return E_FAIL;
	}

	m_pInventoryUIMgr = CInventoryUIMgr::Get_Instance();
	if (nullptr == m_pInventoryUIMgr)
		return E_FAIL;
	
	m_pInventoryUIMgr->Initialize(_pGraphic_Device);
	Safe_AddRef(m_pInventoryUIMgr);

	CDialogMgr* pDialogMgr = CDialogMgr::Get_Instance();
	if (nullptr == pDialogMgr)
		return E_FAIL;

	pDialogMgr->Initialize(_pGraphic_Device);


	Safe_Release(_pGraphic_Device);
	return S_OK;
}

vector<RECT> CStageUIMgr::GetUIRect()
{
	if (nullptr == m_pStatsPanel ||
		nullptr == m_pDialogPanel)
		return vector<RECT>();

	vector<RECT> rc = m_pInventoryUIMgr->GetUIRect();
	for (auto& uiRect : m_vecUIRect)
	{
		rc.push_back(uiRect);
	}
	//활성화상태면
	if (m_pStatsPanel->Get_Active())
	{
		CTransform* pTrasform = (CTransform*)m_pStatsPanel->Get_Module(L"Transform");
		rc.push_back(pTrasform->Get_RECT());
	}
	//활성화상태면
	if (m_pDialogPanel->Get_Active())
	{
		rc.push_back(m_pDialogPanel->Get_Rect());
	}
	return rc;
}

HRESULT CStageUIMgr::SetActiveDialogPanel()
{
	RETURN_FAIL_IF_NULL(m_pDialogPanel);
	m_pDialogPanel->Set_Active(!m_pDialogPanel->Get_Active());
	return S_OK;
}

HRESULT CStageUIMgr::SetDialogInfo(const _tchar * _pIconTextureTag, SCENEID _eTextureSceneID, const _tchar * _pSpeakerName, const _tchar * _pDialog)
{
	if (nullptr == m_pDialogPanel)
		return E_FAIL;

	return m_pDialogPanel->Set_Speacker(_pIconTextureTag, _eTextureSceneID, _pSpeakerName, _pDialog);
}

HRESULT CStageUIMgr::SetActiveBossSlainBanner()
{
	RETURN_FAIL_IF_NULL(m_pBossSlainBanner);
	m_pBossSlainBanner->Set_Active(true);
	CTransform* pTransform = (CTransform*)m_pBossSlainBanner->Get_Module(L"Transform");
	RETURN_FAIL_IF_NULL(pTransform);
	pTransform->Fadein(Vector2(1200.f, 450.f));

	return S_OK;
}

void CStageUIMgr::Free()
{
	Safe_Release(m_pBossSlainBanner);
	Safe_Release(m_pStatsPanel);
	Safe_Release(m_pObjMgr);
	Safe_Release(m_pInventoryUIMgr);
	Safe_Release(m_pDialogPanel);
	//다른 씬에서도 쓰려나?
	if (0 != CInventoryUIMgr::Destroy_Instance())
	{
		m_pInventoryUIMgr = nullptr;
		MSG_BOX("Fail to release InventoryUIMgr");
	}

	if (0 != CDialogMgr::Destroy_Instance())
		MSG_BOX("Fail to release CDialogMgr");

		
}
