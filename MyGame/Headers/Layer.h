#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CLayer final : public CBase
{
private:
	explicit CLayer() {};
	virtual ~CLayer() = default;

private:
	list<CGameObject*>		m_listGO;
	
public:
	HRESULT Initialize();
	_int	Update(_double _timeDelta);
	_int	Late_Update(_double _timeDelta);
	HRESULT Add_GameObject(CGameObject* _pGO);

public:
	CGameObject*				Get_Front() { if (m_listGO.size() <= 0) return nullptr; return m_listGO.front(); }
	const list<CGameObject*>&	Get_List() { return  m_listGO; }
	//죽은 게임오브젝트 클리어
	_int						Clear_DeadObjects();
public:
	static CLayer* Create();
private:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
