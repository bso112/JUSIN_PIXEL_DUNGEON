#pragma once
#include "Base.h"

BEGIN(MyGame)
class CLayer;
class CCharacter;
/*
턴을 종료한다는 개념과 State를 변경한다는 개념을 분리했다.
애초에 그걸 셋트로 생각하는게 잘못이었음.
*/
class CTurnMgr : public CBase
{
	DECLARE_SINGLETON(CTurnMgr)
private:
	explicit CTurnMgr();
	explicit CTurnMgr(CTurnMgr& _rhs);
	virtual ~CTurnMgr() = default;

private:
	SCENEID	m_eCurrScene = SCENE_END;
	size_t	m_iLayerIndex = 0;
	size_t	m_iObjIndex = 0;
	_int	m_iCurrTurn = 0;
	_int	m_iMaxTurn = 0;


private:
	CLayer*	m_pActorLayers[2];

	

private:
	CCharacter*				m_pCurrActor = nullptr;

public:
	HRESULT		Initialize();
	_int		Update_sequentially();
	_int		Update_Simultaneously();
	_int		Get_TurnCnt() {return m_iMaxTurn;}

public:
	HRESULT	MoveTurn_sequentially(_int _iTurnCnt);
	HRESULT	MoveTurn_Simultaneously(_int _iTurnCnt);




	

private:
	_int	Get_NextActor(CCharacter** _pOutCharacter);
public:
	virtual void Free() override;
};
END
