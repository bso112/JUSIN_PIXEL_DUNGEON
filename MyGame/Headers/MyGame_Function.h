#pragma once

BEGIN(MyGame)

class CFinder_Tag
{
public:
	explicit CFinder_Tag(const wchar_t* pTag) : m_pTag(pTag) {}
	virtual ~CFinder_Tag() = default;
public:
	template <typename T>
	bool operator () (T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}
private:
	const wchar_t*		m_pTag = nullptr;
};

template <typename T>
void Safe_Delete_Array(T* pPointer)
{
	if (nullptr != pPointer)
	{
		delete[] pPointer;
		pPointer = nullptr;
	}
}

template <typename T>
void Safe_Delete(T* pPointer)
{
	if (nullptr != pPointer)
	{
		delete pPointer;
		pPointer = nullptr;
	}
}

template <typename T>
unsigned long Safe_AddRef(T& pInstance)
{
	unsigned long dwRefCnt = 0;

	if (nullptr != pInstance)
		dwRefCnt = pInstance->AddRef();

	return dwRefCnt;
}


template <typename T>
unsigned long Safe_Release(T& pInstance)
{
	unsigned long dwRefCnt = 0;

	if (nullptr != pInstance)
	{
		dwRefCnt = pInstance->Release();
		//if (0 == dwRefCnt)
		pInstance = nullptr;
	}

	return dwRefCnt;
}




END