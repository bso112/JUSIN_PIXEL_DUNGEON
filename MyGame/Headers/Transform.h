#pragma once
#include "Module.h"

BEGIN(MyGame)
class CTerrain;
class CTexture;
class CVIBuffer;
class CTransform final : public CModule
{
public:
	typedef struct tagStateDesc
	{
		_double speedPerSec;
		_double	radianPerSec;
		//한턴에 몇 타일 움직이는가
		_uint	movePerTurn;
		tagStateDesc() {}
		tagStateDesc
		(
			_double _speedPerSec,
			_double	_radianPerSec,
			_uint	_movePerTurn = 1
		)
		{
			speedPerSec = _speedPerSec;
			radianPerSec = _radianPerSec;
			movePerTurn = _movePerTurn;
		}
	}STATEDESC;

private:
	explicit CTransform(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTransform(CTransform& _module);
	virtual ~CTransform() = default;


private:
	STATEDESC	m_tStateDesc;
	_matrix		m_StateMatrix;
	_matrix		m_ParentMatrix;

	Vector3		m_vPosition;
	Vector3		m_vSize;
	Vector3		m_vRotation;
	Vector3		m_vRevolveAngle;
	//회전이 기준이될 x축방향
	Vector3		m_vLook;

	//콜라이더 렌더를 위함
	CTexture*	m_pTexture = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;

	//for Update_Route
private:
	//목표 트랜스폼
	CTransform*			m_pTarget = nullptr;
	//목표 위치
	Vector3				m_vDst;
	//이동할 방향
	Vector3				m_vDir;
	//목표까지의 루트(지형)
	vector<CTerrain*>	m_Route;
	_double				m_StopDistance;
	//멈춰 있냐?
	_bool				m_bStop = true;
	//콜라이더 사이즈
	Vector3				m_vColliderSize;
	//이동력만큼 이동했나?
	_bool				m_bTurnEnd = false;
	
	//for Update_Noaml
private:
	//이동할 방향
	Vector3				m_vDir_Normal;

private:
	static _int m_iTurnCnt;


private:
	//현재 이동할 경로의 인덱스
	_int				m_iCurrRouteIndex = 0;
	//이동력만큼 이동했는지 알아보기 위한 카운트변수
	_int				m_iCntForTurn = 0;
	//총 몇개의 타일을 이동했는가
	_int				m_iTotalMoveCnt = 0;
public:
	 HRESULT Initialize_Prototype();
	 HRESULT Initialize(void* _pArg);
	 HRESULT Update_Route(_double _timeDelta);
	 HRESULT Update_Normal(_double _timeDelta);
	//state martix를 업데이트한다.
	_int	Update_Transform();
	HRESULT	Render_Collider();



public:
	HRESULT	Set_Position(Vector3 _vPosition);
	HRESULT	Set_Size(Vector3 _vSize);
	HRESULT	Set_ColliderSize(Vector3 _vSize) { m_vColliderSize = _vSize; return S_OK; }
	HRESULT	Set_Rotation(Vector3 _vRotation);

public:
	_matrix		Get_Matrix() { return m_StateMatrix; }
	Vector3		Get_Position() { return m_vPosition; }
	Vector3		Get_Size() { return m_vSize; }
	Vector3		Get_Rotation() { return m_vRotation; }
	RECT		Get_Collider();
	RECT		Get_RECT();
	STATEDESC	Get_Desc() { return m_tStateDesc; }
	Vector3		Get_Dir() { return m_vDir; }


private:
	//이동하는 방향을 바라본다.
	void		FaceDir();

public:
	//저절로 움직이고 있나?
	_bool	Is_Auto() { return !m_bStop; }
	_bool	Is_Moving() { return !m_bStop; }
	_bool	Is_TurnEnd() { return m_bTurnEnd; }
	void	NextTurn() { m_bTurnEnd = false; }


public:
	HRESULT LookAt(CTransform* pTargetTransform);
	HRESULT	RevolveAround(CTransform* pTargetTransform);
public:
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance);
	HRESULT MoveToTarget(CTransform * _pTransform, _double _timeDelta, _double _StopDistance, _double _Speed);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta);
	HRESULT MoveToDir(Vector3 _vDir, _double _timeDelta, _double _Speed);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance);
	HRESULT	MoveToDst(Vector3 _vDst, _double _timeDelta, _double _fStopDistance, _double _Speed);

public:
	HRESULT Add_Froce(Vector3 _vDir, _float _fForce, _double _timeDelta);


public:
	HRESULT	Go_Route(vector<CTerrain*> _route, _double _fStopDistance, _int _iTurnCnt);
	HRESULT	Go_Target(CTransform* _pTarget, _double _fStopDistance);




public:
	void	Stop() { m_bStop = true; }


public:
	static CTransform*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	// CModule을(를) 통해 상속됨
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END
