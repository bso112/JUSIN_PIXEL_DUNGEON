#include "stdafx.h"
#include "..\Headers\Paralyze.h"
#include "Character.h"
USING(MyGame)


HRESULT CParalyze::Initialize(void* _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tStateDesc, _pArg, sizeof(STATEDESC));
	return S_OK;
}

void CParalyze::OnAct(CCharacter* _pTarget)
{
	if (nullptr == _pTarget)
		return;

	_pTarget->Set_Paralyze(true);

}

CParalyze * CParalyze::Create(void* _pArg)
{
	CParalyze* pInstance = new CParalyze();
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create CParalyze");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CParalyze::Free()
{
	CBuff::Free();
}
