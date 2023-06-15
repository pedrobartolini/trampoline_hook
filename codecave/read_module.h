
VOID read_main_module(HANDLE handle, DWORD *output_base_addr, DWORD *output_module_size)
{
	HMODULE module_handles[1024];
	DWORD num_modules;
	MODULEINFO module_info;
	if (!EnumProcessModulesEx(handle, module_handles, sizeof(module_handles), &num_modules, LIST_MODULES_ALL))
	{
		return;
	}
	for (DWORD i = 0; i < (num_modules / sizeof(HMODULE)); i++)
	{
		if (GetModuleInformation(handle, module_handles[i], &module_info, sizeof(module_info)))
		{
			if (module_info.lpBaseOfDll == module_info.lpBaseOfDll)
			{
				*output_base_addr = (DWORD)module_info.lpBaseOfDll;
				*output_module_size = (DWORD)module_info.SizeOfImage;
				return;
			}
		}
	}
}

VOID read_module(HANDLE handle, const char *target_module_name, DWORD *output_base_addr, DWORD *output_module_size)
{
	HMODULE module_handles[1024];
	DWORD num_modules;
	MODULEINFO module_info;
	if (!EnumProcessModulesEx(handle, module_handles, sizeof(module_handles), &num_modules, LIST_MODULES_ALL))
	{
		return;
	}
	for (DWORD i = 0; i < (num_modules / sizeof(HMODULE)); i++)
	{
		char this_module_name[MAX_PATH];
		if (!GetModuleBaseNameA(handle, module_handles[i], this_module_name, sizeof(this_module_name)))
		{
			continue;
		}

		if (strcmp(this_module_name, target_module_name) != 0)
		{
			continue;
		}
		printf("%s -- %s\n", this_module_name, target_module_name);

		if (GetModuleInformation(handle, module_handles[i], &module_info, sizeof(module_info)))
		{
			if (module_info.lpBaseOfDll == module_info.lpBaseOfDll)
			{
				*output_base_addr = (DWORD)module_info.lpBaseOfDll;
				*output_module_size = (DWORD)module_info.SizeOfImage;
				return;
			}
		}
	}
}

VOID print_bytes(BYTE *buffer, SIZE_T size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%02X ", buffer[i]);
	}
	printf("\n");
}

VOID get_byte_arr(BYTE *target, DWORD src)
{
	target[0] = (BYTE)(src & 0xFF);
	target[1] = (BYTE)((src >> 8) & 0xFF);
	target[2] = (BYTE)((src >> 16) & 0xFF);
	target[3] = (BYTE)((src >> 24) & 0xFF);
}