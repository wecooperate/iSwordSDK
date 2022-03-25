//******************************************************************************
/*++
	FileName:		iSword.h
	Description:

--*/
//******************************************************************************
#ifndef __iSword_h_0b377b1b_3913_42e0_a04f_f570111d093a__
#define __iSword_h_0b377b1b_3913_42e0_a04f_f570111d093a__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <Windows.h>
#include <tchar.h>
#include <atlbase.h>
#include "iSword.h"
//******************************************************************************
interface __declspec(uuid("B49CA9EF-179E-40B9-8F08-463193B761CB")) ISwordAPI : public IUnknown 
{
	virtual HRESULT		SetULONG		(ULONG Index, ULONG Value) = 0;
	virtual HRESULT		SetULONGLONG	(ULONG Index, ULONGLONG Value) = 0;
	virtual HRESULT		SetString		(ULONG Index, LPCWSTR Value) = 0;
	virtual HRESULT		SetPath			(ULONG Index, LPCWSTR Value) = 0;

	virtual HRESULT		Call			(void) = 0;

	virtual ULONG		GetResultULONG	(ULONG Index) = 0;
	virtual ULONGLONG	GetResultULONGLONG(ULONG Index) = 0;
	virtual LPCWSTR		GetResultString	(ULONG Index) = 0;
	virtual LPCWSTR		GetResultPath	(ULONG Index) = 0;
};
//******************************************************************************
interface __declspec(uuid("201359EE-BF5C-466E-9BC4-7147E225AC03")) ISwordManager : public IUnknown 
{
	virtual HRESULT		Start			(void) = 0;
	virtual HRESULT		CreateAPI		(emAPIIndex Index, ISwordAPI** API) = 0;
	virtual HRESULT		Stop			(void) = 0;
};
//******************************************************************************
//
//	helper
//
//******************************************************************************
// clang-format on
//******************************************************************************
#ifdef _M_IX86
#define SWORD_MODULE_NAME _T("iSword.dll")
#else
#define SWORD_MODULE_NAME _T("iSword64.dll")
#endif
//******************************************************************************
class SwordManager
{
public:
	SwordManager(void)
		: m_Module(NULL)
	{
	}

	~SwordManager(void)
	{
		Stop();

		m_Instance = NULL;
	}

	HRESULT Start(LPCTSTR Path = SWORD_MODULE_NAME)
	{
		HRESULT hr = LoadMonitor(Path);

		if (hr != S_OK && hr != S_FALSE)
			return hr;

		if (!m_Instance)
			return E_UNEXPECTED;

		return m_Instance->Start();
	}

	HRESULT Stop(void)
	{
		if (!m_Instance)
			return E_UNEXPECTED;

		return m_Instance->Stop();
	}

public:
	operator ISwordManager*(void)
	{
		return m_Instance;
	}

	CComPtr<ISwordAPI> CreateAPI(emAPIIndex Index)
	{
		if (!m_Instance)
			return NULL;

		CComPtr<ISwordAPI> api;
		m_Instance->CreateAPI(Index, &api);
		return api;
	}

protected:
	HRESULT LoadMonitor(LPCTSTR Path)
	{
		if (m_Instance)
			return S_FALSE;

		if (!Path)
			Path = SWORD_MODULE_NAME;

		if (!m_Module) {
			m_Module = LoadLibraryEx(Path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

			if (!m_Module)
				return HRESULT_FROM_WIN32(GetLastError());
		}

		typedef HRESULT(STDAPICALLTYPE * PFN_DllGetClassObject)(REFCLSID, REFIID, PVOID*);

		PFN_DllGetClassObject pfn = (PFN_DllGetClassObject)GetProcAddress(m_Module, "DllGetClassObject");

		if (!pfn)
			return E_FAIL;

		return pfn(CLSID_NULL, __uuidof(ISwordManager), (PVOID*)&m_Instance);
	}

protected:
	HMODULE m_Module;
	CComPtr<ISwordManager> m_Instance;
};
//******************************************************************************
#endif
