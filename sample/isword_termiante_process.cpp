#include "isword_common.h"

int main()
{
	SwordManager manager;

	HRESULT hr = manager.Start();

	CheckSignError(hr);

	while (true) {
		printf("input process id to terminate: ");

		ULONG process_id = 0;
		scanf("%d", &process_id);

		if (process_id <= 8)
			break;

		cxAPITerminateProcess api(manager);
		api.ProcessId = process_id;
		HRESULT hr = api.Call();

		if (hr != S_OK) {
			printf("termiante process failed = %08X\n", hr);
			break;
		}
	}

	return 0;
}
