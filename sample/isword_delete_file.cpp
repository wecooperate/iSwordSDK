#include "isword_common.h"

int wmain(int argc, LPCWSTR args[])
{
	if (argc != 2) {
		printf("usage: %S FilePath\n", args[0]);
		return -1;
	}

	SwordManager manager;

	HRESULT hr = manager.Start();

	CheckSignError(hr);

	cxAPIDeleteFile api(manager);

	if (!api) {
		return -1;
	}

	api.Path = args[1];
	api.CloseAllHandles = TRUE;
	api.Call();

	return 0;
}
