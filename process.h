VOID send_key(WPARAM key)
{
	SendMessage(process.hwnd, WM_KEYDOWN, key, 0);
	SendMessage(process.hwnd, WM_KEYUP, key, 0);
}

HMODULE get_module(const HANDLE process_handle, const char *module_name)
{
	HMODULE module_handles[1024];
	DWORD num_modules;
	if (!EnumProcessModulesEx(process_handle, module_handles, sizeof(module_handles), &num_modules, LIST_MODULES_ALL))
	{
		return NULL;
	}
	num_modules /= sizeof(HMODULE);
	for (DWORD i = 0; i < num_modules; ++i)
	{
		char module_name_buffer[256];
		DWORD module_name_size = sizeof(module_name_buffer);
		if (!GetModuleBaseNameA(process_handle, module_handles[i], module_name_buffer, module_name_size))
		{
			continue;
		}
		if (strcmp(module_name_buffer, module_name) == 0)
		{
			return module_handles[i];
		}
	}
	return NULL;
}

DWORD get_pid(const wchar_t *process_name)
{
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	while (Process32NextW(snapshot_handle, &entry))
	{
		if (wcscmp(entry.szExeFile, process_name) == 0)
		{
			return entry.th32ProcessID;
		}
	}
	return NULL;
}

HANDLE get_thread_handle(DWORD thread_id)
{
	HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, thread_id);

	if (hThread == NULL)
	{
		return NULL;
	}

	return hThread;
}
