#ifndef __iSwordProtocol_4a950266_3a3d_45e9_b057_b268e76f0925__
#define __iSwordProtocol_4a950266_3a3d_45e9_b057_b268e76f0925__
//******************************************************************************
class cxAPIBase
{
	cxAPIBase(const cxAPIBase&);
	cxAPIBase& operator=(const cxAPIBase&);

public:
	typedef LPCWSTR Path;
	typedef LPCWSTR String;

public:
	explicit cxAPIBase(ISwordManager* Manager, emAPIIndex Index)
	{
		if (!Manager)
			return;

		Manager->CreateAPI(Index, &m_API);
	}

	~cxAPIBase()
	{
		if (m_API) {
			m_API->Release();
		}
	}

	operator bool(void)
	{
		return m_API != NULL;
	}

	HRESULT Call(void)
	{
		if (!m_API)
			return E_UNEXPECTED;

		return m_API->Call();
	}

protected:
	ISwordAPI* m_API = NULL;
};

class cxAPITerminateProcess : public cxAPIBase
{
	enum {
		emFieldProcessId,
	};

public:
	cxAPITerminateProcess(ISwordManager* Manager)
		: cxAPIBase(Manager, emAPITerminateProcess)
	{
	}

public:
	HRESULT SetProcessId(ULONG Value)
	{
		return m_API->SetULONG(emFieldProcessId, Value);
	}

public:
	__declspec(property(put = SetProcessId)) ULONG ProcessId;
};

class cxAPIDeleteFile : public cxAPIBase
{
	enum {
		emFieldPath,
		emFieldCloseAllHandles,
	};

public:
	cxAPIDeleteFile(ISwordManager* Manager)
		: cxAPIBase(Manager, emAPIDeleteFile)
	{
	}

public:
	HRESULT SetPath(String Value)
	{
		return m_API->SetString(emFieldPath, Value);
	}

	HRESULT SetCloseAllHandles(ULONG Value)
	{
		return m_API->SetULONG(emFieldCloseAllHandles, Value);
	}

public:
	__declspec(property(put = SetPath)) String Path;
	__declspec(property(put = SetCloseAllHandles)) ULONG CloseAllHandles;
};

//******************************************************************************
#endif
