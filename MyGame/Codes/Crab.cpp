#include "stdafx.h"
#include "Crab.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"

USING(MyGame)

CCrab::CCrab(CCrab & _rhs)
	:CMonster(_rhs)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CCrab::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Crab/");
	return S_OK;
}

HRESULT CCrab::Initialize(void * _param)
{
	m_pName = L"게";
#pragma region 스텟셋팅

	//스텟셋팅
	m_tStat.m_fExp = 20.f;
	m_tStat.m_fMaxHp = CStat::Create(30.f);
	m_tStat.m_fAtt = CStat::Create(2.f, 6.f);
	m_tStat.m_iGold = 15;
	m_tStat.m_fArmor = CStat::Create(0.f);
	m_tStat.m_fHP = 20.f;
#pragma endregion

#pragma region 모듈셋팅
	//모듈셋팅
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	_uint movePerturn = 3;
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr, &CTransform::STATEDESC(CalulateSpeed(movePerturn), 100.0, movePerturn))))
		return E_FAIL;
	if (FAILED(Set_Module(L"AIStateCon", SCENE_STATIC, (CModule**)&m_pStateCon)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	//위치 셋팅
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));


	m_pTransform->Set_Size(Vector2(25.f, 25.f));
	m_pTransform->Set_ColliderSize(Vector2(30.f, 30.f));

#pragma endregion

#pragma region 상태셋팅
	CAIStateCon* pStateCon = dynamic_cast<CAIStateCon*>(m_pStateCon);
	pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting(this));
	pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	pStateCon->Set_State(CAIState::STATE_WADERING, new CAIWandering(this));
	if (nullptr == m_pFocus)
		return E_FAIL;
	pStateCon->Set_Default_State(CAIState::STATE_SLEEP, IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"crab_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"crab_sleep", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pSleepAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"sleep", pSleepAnim);

	Set_Module(L"crab_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	Set_Module(L"crab_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	Set_Module(L"crab_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pWalkAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator->Add_Animation(L"walk", pWalkAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

#pragma endregion

	CMonster::Initialize(_param);



	return S_OK;
}

void CCrab::OnDead()
{
	CMonster::OnDead();
	if (nullptr == m_pAnimator)
		return;
	m_pAnimator->Play(L"dead");
}



CCrab * CCrab::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CCrab* pInstance = new CCrab(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CCrab");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CCrab::Clone(void * _param)
{
	CCrab* pInstance = new CCrab(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CCrab");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CCrab::Free()
{

	CMonster::Free();
}
