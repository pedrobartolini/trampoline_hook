DWORD main_base_addr;
DWORD main_module_size;

VOID read_main_module(HANDLE handle)
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
				main_base_addr = (DWORD)module_info.lpBaseOfDll;
				main_module_size = (DWORD)module_info.SizeOfImage;
				return;
			}
		}
	}
}

DWORD find_signature(HANDLE handle, LPVOID base_addr, SIZE_T module_size, BYTE *signature, SIZE_T signature_size)
{
	SIZE_T bytesRead = 0;
	BYTE buffer[4096];
	DWORD oldProtect = 0;
	DWORD newProtect = PAGE_READWRITE;
	SIZE_T i, j, k;

	for (i = 0; i < module_size; i += bytesRead)
	{
		if (!ReadProcessMemory(handle, (LPCVOID)((DWORD_PTR)base_addr + i), buffer, sizeof(buffer), &bytesRead))
		{
			printf("ReadProcessMemory failed: %d\n", GetLastError());
			break;
		}
		for (j = 0; j < bytesRead; j++)
		{
			if (buffer[j] == signature[0])
			{
				for (k = 1; k < signature_size; k++)
				{
					if (buffer[j + k] != signature[k])
						break;
				}
				if (k == signature_size)
				{
					return (DWORD)base_addr + i + j;
				}
			}
		}
	}
}


void print_dword_bytes(unsigned char *buffer, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%02X ", buffer[i]);
	}
	printf("\n");
}

VOID aob_scan(HANDLE handle)
{
	read_main_module(handle);

	BYTE heal_start[] = {0x89, 0x41, 0x58, 0x83, 0xB9, 0x9C, 0x01};
	DWORD heal_start_address = find_signature(handle, main_base_addr, main_module_size, heal_start, sizeof(heal_start));
	heal_start_address = 0xAD60AB;

	printf("target address: %p\n", heal_start_address);

	unsigned char originalCode[10];
	if (!ReadProcessMemory(handle, heal_start_address, originalCode, sizeof(originalCode), NULL))
	{
		printf("Failed to read process memory\n");
		return 1;
	}

	unsigned char newCode[] = {originalCode[0], originalCode[1], originalCode[2],
							   originalCode[3], originalCode[4], originalCode[5], originalCode[6], originalCode[7], originalCode[8], originalCode[9],
							   0xA3, 0x64, 0x21, 0xC1, 0x05,
							   0xE9, 0x00, 0x00, 0x00, 0x00};

	LPVOID new_code_alloc = VirtualAllocEx(handle, NULL, sizeof(newCode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (new_code_alloc == NULL)
	{
		printf("Failed to allocate memory\n");
		return;
	}

	*(DWORD *)(newCode + (sizeof(newCode) - 4)) = (DWORD)heal_start_address - (DWORD)new_code_alloc - sizeof(originalCode);

	if (!WriteProcessMemory(handle, new_code_alloc, newCode, sizeof(newCode), NULL))
	{
		printf("Failed to write new code\n");
		return 1;
	}

	printf("new allocated code: %p\n", new_code_alloc);

	unsigned char jmpInstruction[10] = {0xE9, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90};
	*(DWORD *)(jmpInstruction + 1) = (DWORD)new_code_alloc - (DWORD)heal_start_address - 5;
	print_dword_bytes(jmpInstruction, 10);

	if (!WriteProcessMemory(handle, heal_start_address, jmpInstruction, sizeof(jmpInstruction), NULL))
	{
		printf("Failed to write JMP instruction\n");
		return 1;
	}
}
