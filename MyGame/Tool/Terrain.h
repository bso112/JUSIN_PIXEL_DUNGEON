#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CTexture;
class CVIBuffer;
class CTerrain : public CGameObject
{

public:
	enum STATE { STATE_NORMAL = 0, STATE_UNLOCKED = 0, STATE_LOCKED = 1, STATE_USED = 1, STATE_END };

public:
	typedef struct tagNode
	{
		_int Gcost = INT_MAX; // distance from staring node
		_int Hcost = INT_MAX; // distance from end node
		_int Fcost = INT_MAX;	// Gcost + Hcost

		//인덱스
		_int X = 0;
		_int Y = 0;

		//부모
		CTerrain* pParent = nullptr;

		tagNode() {}
		tagNode(_int _Gcost, _int _Hcost, _int _Fcost, _int _X, _int _Y, CTerrain* _pParent)
		{
			Gcost = _Gcost;
			Hcost = _Hcost;
			Fcost = _Fcost;
			X = _X;
			Y = _Y;
			pParent = _pParent;
		}

		void Clear()
		{
			Gcost = INT_MAX;	// distance from staring node
			Hcost = INT_MAX;	// distance from end node
			Fcost = INT_MAX;	// Gcost + Hcost

			X = 0;
			Y = 0;
			pParent = nullptr;
		}
	}NODE;
public:
	typedef struct tag_SaveData
	{
		_tchar		m_PrototypeTag[MAX_PATH];
		Vector3		m_vPosition;
		Vector3		m_vSize;
		Vector3		m_vRotation;
		_int		m_iCurFrame;
		STATE		m_eState;


	}SAVE_DATA;
protected:
	explicit CTerrain() {};
	explicit CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTerrain(CTerrain& _rhs);
	virtual ~CTerrain() = default;

protected:
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CVIBuffer*		m_pVIBuffer = nullptr;
	Vector3			m_vBasePos = {};

protected:
	STATE			m_eState = STATE_NORMAL;
	bool			m_bHidden = false;
	NODE			m_tNode = {};
	//타일 위에 있는 것들
protected:
	CTransform*		m_pCharacterTranform = nullptr;

protected:
	TERRAIN			m_tInfo = {};
	_tchar			m_PrototypeTag[MAX_PATH];
	// _uint로 하면 음수가 되는순간 4500어쩌구 하는 큰값이 들어가서 최대 텍스쳐 사이즈 -1 이됨.
	_int			m_iCurFrame = 0;

	_int			m_iScrollX = 0;
	_int			m_iScrollY = 0;

	//디버그용
private:
	bool			m_bMarked = false;


public:
	virtual HRESULT	Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pPrototypeTag, _tchar* _pFilePath = nullptr);
	virtual	HRESULT	Initialize();
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render();

public:
	SAVE_DATA	Get_SaveData();
	HRESULT		Load_Data(SAVE_DATA& _eSaveData);
	void		Hide() { m_bHidden = true; }
	void		Reveal() { m_bHidden = false; }
	bool		IsHidden() { return m_bHidden; }
	//원래부터 movable이고, _pTransform 이외의 누군가 서있지 않으면 갈 수 있다.
	bool		IsMovable(CTransform* _pTransform);
	void		Set_Texture(_int index) { m_iCurFrame = index; }

public:
	void		Set_InitialPos(Vector3 _vPos);
	void		Set_ScrollX(_int _iScrollX) { m_iScrollX = _iScrollX; }
	void		Set_ScrollY(_int _iScrollY) { m_iScrollY = _iScrollY; }



public:
	HRESULT		Forward_Frame();
	HRESULT		Backward_Frame();
	void		Set_Node(NODE _tNode) { m_tNode = _tNode; }
	const NODE&	Get_Node() { return m_tNode; }
	void		Clear_Node() { m_tNode.Clear(); }
	void		Set_Mark(bool _bMarked) { m_bMarked = _bMarked; }

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

protected:
	virtual void OnCollisionEnterTerrain(CGameObject* _pOther);
	virtual void OnCollisionStayTerrain(CGameObject* _pOther);
	virtual void OnCollisionExitTerrain(CGameObject* _pOther);


protected:
	//에디터씬에서 Frame이 변할때 하위클래스에 맞는 데이터로 셋팅함.
	virtual	HRESULT	OnMoveFrame();
	//Terrain을 로드할때 하위클래스에 맞는 데이터로 셋팅함.
	virtual HRESULT	OnLoadData();
public:
	static CTerrain*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	virtual CGameObject* Clone(void * _param = nullptr);
	virtual void Free() override;




};
END
