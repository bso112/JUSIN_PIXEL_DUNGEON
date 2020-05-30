#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "ParticleSystem.h"
BEGIN(MyGame)
class CClock_Delay;
class CEffect abstract : public CGameObject
{
protected:
	explicit CEffect(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CEffect(CEffect& _rhs);
	virtual ~CEffect() = default;


protected:
	CParticleSystem*	m_pParticleSystem = nullptr;
	CTransform*			m_pTransform = nullptr;
	//�i�ƴٴ� Ÿ��
	CTransform*			m_pTarget = nullptr;

	//����Ʈ�� ���ӽð� (��ƼŬ�ý����� �ƴ�)
	_int				m_iDuration = 0;
	//���ݱ��� �� ��
	_int				m_iTurnCnt = 0;
public:
	virtual _int Act();
	virtual _int Update(_double _timeDelta);
	virtual void Play() = 0;
	
public:
	void	Set_Target(CTransform* _pTarget) { if (nullptr == _pTarget) return; m_pTarget = _pTarget; }


	virtual void Free() override;
};
END

