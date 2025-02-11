#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CLayer;
class CHero;
class CObjMgr final : public CBase
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CObjMgr();
	virtual ~CObjMgr();

private:
	map<const _tchar*, CGameObject*>	m_mapPrototype[SCENE_END];
	map<const _tchar*, CLayer*>			m_mapLayer[SCENE_END];

public:
	_int Update(_double _timeDelta);
	
public:
	/*
	프로토타입 패턴
	몬스터를 만들때, 그 몬스터를 구성하는 체력, 힘 같은 정보는 따로 파일이나 데이터베이스에서 가져오는게 보통이다.
	하지만 몬스터를 만들때마다 외부파일에 접근하는 것은 시간이 많이 든다.
	따라서 미리 다 만들어 놓은 다음, 필요할때 그 원본을 복사해서 사용한다.
	*/
	//프로토타입 맵에 원형객체를 넣는다.
	HRESULT			Add_Prototype(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID, CGameObject* _pGO);
	//프로토타입을 복사해 객체를 생성한다. 생성한 객체는 레이어맵에 넣는다. 만약 해당 레이어가 없으면 새로 만든다.
	CGameObject*	Add_GO_To_Layer(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID, const _tchar* _eLayerID, SCENEID _eLayerSceneID, void* _pArg = nullptr);
	//오브젝트를 레이어에 등록한다.
	CGameObject*	Add_GO_To_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID, CGameObject* _pObj);
	//레이어를 만들어둔다.
	HRESULT			Make_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID);
	CGameObject*	Find_Prototype(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID);
	CLayer*			Find_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID);
	CGameObject*	Get_Player(SCENEID _eLayerSceneID);
	CGameObject*	Get_ObjectOnFront(const _tchar* _pLayerID, SCENEID _eLayerSceneID);
	//씬이 포함하는 프로토타입들과 레이어들을 클리어한다.
	HRESULT			Clear_Scene(SCENEID _eSceneID);
	HRESULT			Clear_DeadObjects();

	
public:
	map<const _tchar*, CLayer*>* Get_Layers() { return m_mapLayer; }

private:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END
