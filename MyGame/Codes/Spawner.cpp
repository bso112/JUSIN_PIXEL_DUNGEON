#include "stdafx.h"
#include "..\Headers\Spawner.h"
#include "LevelMgr.h"
#include "ObjMgr.h"
#include "Rat.h"
#include "Gnoll.h"
#include "Crab.h"
#include "Food.h"
#include "Cheese.h"
#include "Texture.h"
#include "ModuleMgr.h"
#include "StageUIMgr.h"
#include "Image.h"
#include "Pipline.h"
#include "Fire.h"

#include "TextureLoader.h"
#include "Key.h"
#include "ItemFactory.h"
#include "Smoke.h"
#include "Ghost.h"
#include "Goo.h"
#include "InventoryUIMgr.h"
#include "Tengu.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CSpawner)

CSpawner::CSpawner()
{
}

HRESULT CSpawner::Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, _uint level)
{

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;
	Safe_AddRef(pObjMgr);

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;
	Safe_AddRef(pModuleMgr);

	//몬스터 프로토타입을 만든다.
	pObjMgr->Add_Prototype(L"Rat", SCENE_STAGE, CRat::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Gnoll", SCENE_STAGE, CGnoll::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Crab", SCENE_STAGE, CCrab::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Ghost", SCENE_STAGE, CGhost::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Goo", SCENE_STAGE, CGoo::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Tengu", SCENE_STAGE, CTengu::Create(_pGraphic_Device));



	//레벨에 필요한 텍스쳐를 생성한다.
	if (FAILED(pModuleMgr->Add_Module(L"Texture_Food", SCENE_STAGE, CTexture::Create(_pGraphic_Device, L"../Bin/Resources/Textures/Item/Food/%d.png", 1))))
		return E_FAIL;



	CItemFactory::Make_Prototpyes(_pGraphic_Device);



	//이펙트 프로토타입
	pObjMgr->Add_Prototype(L"Effect_Fire", SCENE_STAGE, CFire::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Effect_Smoke", SCENE_STAGE, CSmoke::Create(_pGraphic_Device));



	Safe_Release(pObjMgr);
	Safe_Release(pModuleMgr);
	return S_OK;
}

HRESULT CSpawner::Spawn(_uint _iLevel)
{

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CLevel* pWorld = CLevelMgr::Get_Instance()->Get_Level(_iLevel);
	if (nullptr == pWorld)
		return E_FAIL;



	m_listCharacter[_iLevel].push_back(pObjMgr->Get_Player(SCENE_STAGE));


	//레벨마다 액티브 제어하기 위해 분리
	if (0 == _iLevel)
	{

		Vector3 ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Rat", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());

		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"FireFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"IceFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"ShieldFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Key", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));


		////아이템 만들기
		ranPos = pWorld->Get_RandomPos();
		CItem* pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_SHORTSWORD);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_BATTLEAXE);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LONGSWORD);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LETHERARMOR);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_POSIONPOTION);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_PARALYZEPOTION);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_FIREPOTION);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
	

		for (auto& GO : m_listGO[_iLevel])
		{
			Safe_AddRef(GO);
		}
		for (auto& GO : m_listCharacter[_iLevel])
		{
			Safe_AddRef(GO);
		}
	}

	if (1 == _iLevel)
	{

		Vector3 ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Rat", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Ghost", SCENE_STAGE, L"Monster", SCENE_STAGE, &Vector3(4787.f, 5137.f, 1.f)));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Goo", SCENE_STAGE, L"Monster", SCENE_STAGE, &Vector3(5484.f, 5159.f, 1.f)));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();

		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"FireFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"IceFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"ShieldFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Key", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));


		////아이템 만들기
		ranPos = pWorld->Get_RandomPos();
		CItem* pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_SHORTSWORD);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_BATTLEAXE);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LONGSWORD);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();



		for (auto& GO : m_listGO[_iLevel])
		{
			Safe_AddRef(GO);
		}
		for (auto& GO : m_listCharacter[_iLevel])
		{
			Safe_AddRef(GO);
		}
	}
	else if (2 == _iLevel)
	{
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Tengu", SCENE_STAGE, L"Monster", SCENE_STAGE, &Vector2(4436.f, 5191.f)));
		m_listCharacter[_iLevel].push_back(m_listGO[2].back());

		for (auto& GO : m_listGO[_iLevel])
		{
			Safe_AddRef(GO);
		}
		for (auto& GO : m_listCharacter[_iLevel])
		{
			Safe_AddRef(GO);
		}
	}
	return S_OK;
}

HRESULT CSpawner::Add_Interact(CGameObject * _pInteractor, _uint _iDepth)
{
	if (nullptr == _pInteractor ||
		MAX_DEPTH <= _iDepth)
		return E_FAIL;

	//중복 불허용
	for (auto& go : m_listGO[_iDepth])
	{
		if (_pInteractor == go)
			return E_FAIL;
	}
	m_listGO[_iDepth].push_back(_pInteractor);
	//맞지?
	Safe_AddRef(_pInteractor);
	return S_OK;
}

HRESULT CSpawner::Set_Visuable(Vector3 _vPlayerPos, _int _iRange, _int _iDepth)
{
	if (MAX_DEPTH <= _iDepth)
		return E_FAIL;

	for (int i = 0; i < MAX_DEPTH; ++i)
	{
		for (auto& GO : m_listGO[i])
		{
			//액티브가 안되있으면 무시
			if (!GO->Get_Active())
				continue;

			RECT rc = Make_Rect(_vPlayerPos, Vector2(TILECX * ((_iRange << 1) + 1), TILECY * ((_iRange << 1) + 1)));
			CTransform* pTransform = (CTransform*)GO->Get_Module(L"Transform");
			if (nullptr == pTransform)
				continue;
			POINT pt;
			pt.x = pTransform->Get_Position().x;
			pt.y = pTransform->Get_Position().y;

			if (PtInRect(&rc, pt))
			{
				GO->Set_Visuable(true);
				GO->Set_Visited(true);
			}

		}


	}
	return S_OK;
}

HRESULT CSpawner::Ready_BasicItem(CInventory* _pInventory)
{
	if (nullptr == _pInventory)
		return E_FAIL;

	CItem* pItem = nullptr;
	CGameObject* pPlayer = CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE);
	CTransform* pPlayerTransform = (CTransform*)pPlayer->Get_Module(L"Transform");
	RETURN_FAIL_IF_NULL(pPlayer);

	for (int i = 0; i < 10; ++i)
	{
		//기본템 생성
		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_POSIONPOTION));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);


		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_PARALYZEPOTION));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);
	}

	for (int i = 0; i < 10; ++i)
	{
		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);

		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_FIREPOTION));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);

	}



	for (int i = 0; i < 10; ++i)
	{
		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);
	}

	for (int i = 0; i < 5; ++i)
	{
		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_CHEESE));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);
	}

	for (int i = 0; i < 5; ++i)
	{
		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_SHIELDSEED));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);

		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_FIRESEED));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);

		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_ICESEED));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);

	}

	for (int i = 0; i < 2; ++i)
	{
		m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_KEY));
		pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
		Safe_AddRef(m_listGO[0].back());
		_pInventory->Put_Item(pItem);
		_pInventory->Put_Key((CKey*)pItem);
	}

	m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_RINGOFPARALYSIS));
	pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
	Safe_AddRef(m_listGO[0].back());
	_pInventory->Put_Item(pItem);

	m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_LETHERARMOR));
	pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
	Safe_AddRef(m_listGO[0].back());
	_pInventory->Put_Item(pItem);

	m_listGO[0].push_back(CItemFactory::Make_Item(BASEDESC(Vector2(), Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND));
	pItem = dynamic_cast<CItem*>(m_listGO[0].back()); RETURN_FAIL_IF_NULL(pItem);
	Safe_AddRef(m_listGO[0].back());
	_pInventory->Put_Item(pItem);

	



	return S_OK;
}

list<CGameObject*>* CSpawner::Get_Actors()
{
	return &m_listCharacter[CLevelMgr::Get_Instance()->Get_CurrDepth()];
}

CGameObject* CSpawner::PickObject(POINT& _pt, _uint _iLevel)
{
	if (MAX_DEPTH <= _iLevel)
		return nullptr;

	vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
	for (auto& rc : UIRect)
	{
		//만약 마우스 포인트가 UI위에 있으면 무시
		if (PtInRect(&rc, _pt))
		{
			return nullptr;
		}
	}

	//마우스 좌표 변환
	Vector4 dst = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&dst, &dst, &CPipline::Get_Instance()->Get_CameraMatrix_inverse());
	POINT pt;
	pt.x = (LONG)dst.x;
	pt.y = (LONG)dst.y;

	for (int i = 0; i < MAX_DEPTH; ++i)
	{
		auto& iter = m_listGO[i].begin();
		while (iter != m_listGO[i].end())
		{
			//만약 지워진 오브젝트면 리스트에 지운다.
			if (nullptr == *iter)
			{
				Safe_Release(*iter);
				iter = m_listGO[i].erase(iter);
			}
			else
			{
				//액티브 안된거면 피킹안함
				if (!(*iter)->Get_Active())
				{
					++iter;
					continue;
				}

				//오브젝트를 피킹한다.
				CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
				if (nullptr != pTransform)
				{
					if (PtInRect(&pTransform->Get_Collider(), pt))
						return *iter;
				}

				++iter;
			}


		}

	}


	return nullptr;
}

CGameObject * CSpawner::PickCharacter(Vector3 _vPos, _uint _iLevel, CTransform * pSelfTransform)
{

	if (MAX_DEPTH <= _iLevel)
		return nullptr;


	POINT pt;
	pt.x = (LONG)_vPos.x;
	pt.y = (LONG)_vPos.y;


	auto& iter = m_listCharacter[_iLevel].begin();
	while (iter != m_listCharacter[_iLevel].end())
	{
		//죽은 몬스터는 피킹안함
		CMonster* pMonster = dynamic_cast<CMonster*>(*iter);
		if (nullptr != pMonster)
		{
			if (pMonster->Get_Dying() || pMonster->Get_Dead())
				return nullptr;
		}

		//만약 지워진 오브젝트면 리스트에 지운다.
		if (nullptr == *iter)
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
		{
			//오브젝트를 피킹한다.
			CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
			if (nullptr != pTransform && pSelfTransform != pTransform)
			{

				if (PtInRect(&pTransform->Get_Collider(), pt))
				{
					return *iter;
				}
			}

			++iter;
		}

	}

	return nullptr;

}

CGameObject * CSpawner::PickCharacter(POINT& _pt, _uint _iLevel, CTransform * pSelfTransform)
{

	if (MAX_DEPTH <= _iLevel)
		return nullptr;


	//마우스 좌표 변환
	Vector4 dst = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&dst, &dst, &CPipline::Get_Instance()->Get_CameraMatrix_inverse());
	POINT pt;
	pt.x = (LONG)dst.x;
	pt.y = (LONG)dst.y;

	auto& iter = m_listCharacter[_iLevel].begin();
	while (iter != m_listCharacter[_iLevel].end())
	{
		//죽은 몬스터는 피킹안함
		CMonster* pMonster = dynamic_cast<CMonster*>(*iter);
		if (nullptr != pMonster)
		{
			if (pMonster->Get_Dying() || pMonster->Get_Dead())
				return nullptr;
		}
		//만약 지워진 오브젝트면 리스트에 지운다.
		if (nullptr == *iter)
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
		{
			//오브젝트를 피킹한다.
			CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
			if (nullptr != pTransform && pSelfTransform != pTransform)
			{
				if (PtInRect(&pTransform->Get_Collider(), pt))
				{
					return *iter;
				}
			}

			++iter;
		}

	}

	return nullptr;

}



vector<pair<int, int>> CSpawner::Get_CharacterTileIndexs()
{
	vector<pair<int, int>> indexs;
	for (auto& character : m_listCharacter[CLevelMgr::Get_Instance()->Get_CurrDepth()])
	{
		CMonster* pMonster = dynamic_cast<CMonster*>(character);
		if (nullptr != pMonster)
		{
			if (pMonster->Get_Dying() || pMonster->Get_Dead())
				continue;
		}
		CTransform* pTransform = (CTransform*)character->Get_Module(L"Transform");
		if (nullptr != pTransform)
		{
			Vector2 vPos = pTransform->Get_Position();
			pair<int, int> index = pair<int, int>((int)vPos.x / TILECX, (int)vPos.y / TILECY);
			indexs.push_back(index);
		}
	}
	return indexs;
}

void CSpawner::SetActive(_bool _bActive, _uint _iLevel)
{
	for (auto& GO : m_listGO[_iLevel])
	{
		//인벤토리에 들어간 아이템은 영향받지 않음.
		CItem* pItem = dynamic_cast<CItem*>(GO);
		if (nullptr != pItem)
		{
			if (!pItem->IsDrop())
				continue;
		}

		GO->Set_Active(_bActive);
	}
}

_int CSpawner::Clear_DeadObjects(_uint _iLevel)
{
	if (MAX_DEPTH <= _iLevel)
		return -1;

	for (int i = 0; i < MAX_DEPTH; ++i)
	{
		auto& iter = m_listGO[i].begin();
		while (iter != m_listGO[i].end())
		{
			if ((*iter)->Get_Dead())
			{
				Safe_Release(*iter);
				iter = m_listGO[i].erase(iter);
			}
			else
				++iter;
		}


		auto& iter2 = m_listCharacter[i].begin();
		while (iter2 != m_listCharacter[i].end())
		{
			if ((*iter2)->Get_Dead())
			{
				Safe_Release(*iter2);
				iter2 = m_listCharacter[i].erase(iter2);
			}
			else
				++iter2;
		}

	}

	return 0;
}



void CSpawner::Free()
{

	for (auto& list : m_listCharacter)
	{
		for (auto& GO : list)
		{
			Safe_Release(GO);
		}
	}
	for (auto& list : m_listGO)
	{
		for (auto& GO : list)
		{
			Safe_Release(GO);
		}
	}
}
