#include "stdafx.h"
#include "FireFlower.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Terrain.h"
USING(MyGame)
CFireFlower::CFireFlower(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CSeed(_pGrahic_Device)
{
}

CFireFlower::CFireFlower(CFireFlower & _rhs)
	: CSeed(_rhs)
{
}

HRESULT CFireFlower::Initialize(void * _param)
{
	CSeed::Initialize(_param);



	if (nullptr != _param)
		m_pTransform->Set_Position((*(Vector3*)_param));


	m_pDescription = L"ȭ������ �����̴�. �߰ſ� ����� ��������.";
	m_iTextureID = 1;
	m_pItemName = L"ȭ������ ����";

	return S_OK;
}


void CFireFlower::OnCollisionEnter(CGameObject * _pOther)
{
	//������ �ε�ģ�� �ƴϰ�, �� ���¶��
	if (nullptr == dynamic_cast<CTerrain*>(_pOther) && m_bFlower)
	{
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();

		if (m_pTransform == nullptr)
			return;

		CEffect*  pEffect = nullptr;
		BASEDESC tBsseDesc = BASEDESC(m_pTransform->Get_Position(), m_pTransform->Get_Size());
		CEffect::STATEDESC desc;
		desc.m_tBaseDesc = tBsseDesc;
		desc.m_tBuffType = CBuff::TYPE_BURN;
		//����Ʈ ����
		pEffect = dynamic_cast<CEffect*>(pObjMgr->Add_GO_To_Layer(L"Effect_Fire", SCENE_STAGE, L"Effect", SCENE_STAGE, &desc));
		pEffect->Set_CollidableEffect(true);
		//����Ʈ ���
		if (pEffect)
			pEffect->Play();

		//����
		m_bDead = true;

	}
}

void CFireFlower::Free()
{
	CSeed::Free();
}
