#include "stdafx.h"
#include "..\Headers\SceneMgr.h"
#include "Menu.h"
#include "CharacterSelect.h"
#include "Stage.h"
#include "Editor.h"
#include "Scene_Loading.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CSceneMgr)


HRESULT CSceneMgr::Scene_Change(SCENEID _eID, PDIRECT3DDEVICE9 _pGraphic_Device)
{

	m_pPrvScene = m_pCurrScene;
	m_eCurrSceneID = _eID;


	switch (_eID)
	{
	case MyGame::SCENE_STATIC:
		break;
	case MyGame::SCENE_MENU:
	{
		m_pCurrScene = CMenu::Create(_pGraphic_Device);
		break;
	}
	case MyGame::SCENE_EDITOR:
	{
		m_pCurrScene = CEditor::Create(_pGraphic_Device);
		break;
	}
	case MyGame::SCENE_STAGE:
	{
		m_pCurrScene = CStage::Create(_pGraphic_Device);
		break;
	}
	case MyGame::SCENE_LOADING:
	{
		m_pCurrScene = CScene_Loading::Create(_pGraphic_Device);
		break;
	}
	default:
		break;
	}

	if (nullptr == m_pCurrScene)
		goto exception;

	return S_OK;
exception:
	MSG_BOX("Failed To Replacement Scene");
	return E_FAIL;
}

_int CSceneMgr::Update(_double _timeDelta)
{
	if (nullptr == m_pCurrScene)
		return -1;


	return m_pCurrScene->Update(_timeDelta);
}

HRESULT CSceneMgr::Render()
{
	if (nullptr == m_pCurrScene)
		return E_FAIL;

	m_pCurrScene->Render();
	return S_OK;
}

HRESULT CSceneMgr::Clear_PrvScene()
{
	if (0 != Safe_Release(m_pPrvScene))
		return E_FAIL;
	return S_OK;

}



void CSceneMgr::Free()
{
	if (0 != Safe_Release(m_pCurrScene))
		MSG_BOX("Fail to Release Current Scene");
}
