VOID code_inject(DWORD module_address, SIZE_T module_size, BYTE *signature, SIZE_T signature_size, BYTE *new_code, SIZE_T new_code_size)
{
	// JMP DEFAULTS
	BYTE jmp_placeholder[] = {0xE9, 0x00, 0x00, 0x00, 0x00};
	SIZE_T jmp_placeholder_size = sizeof(jmp_placeholder);

	// SIGNATURE SCAN
	DWORD address = find_signature_address(module_address, module_size, signature, signature_size);
	printf("Signature address: %p\n", address);

	// NEW ALLOC FOR NEW CODE
	BYTE code_to_alloc[signature_size + new_code_size + 5];
	LPVOID allocation = VirtualAllocEx(process.handle, NULL, sizeof(code_to_alloc), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (allocation == NULL)
	{
		printf("Failed to allocate memory\n");
		return;
	}

	// WRITING NEW CODE TO NEW ALLOC
	BYTE jmp_back[4];
	get_byte_arr(&jmp_back, (DWORD)address - (DWORD)allocation - signature_size);
	memcpy(code_to_alloc, signature, signature_size);
	memcpy(code_to_alloc + signature_size, new_code, new_code_size);
	memcpy(code_to_alloc + signature_size + new_code_size, jmp_placeholder, jmp_placeholder_size);
	memcpy(code_to_alloc + signature_size + new_code_size + 1, jmp_back, sizeof(jmp_back));
	WriteProcessMemory(process.handle, allocation, code_to_alloc, sizeof(code_to_alloc), NULL);

	// REPLACING OLD CODE
	BYTE replace_code[signature_size];
	BYTE jmp_to[4];
	get_byte_arr(&jmp_to, (DWORD)allocation - (DWORD)address - 5);
	memcpy(replace_code, jmp_placeholder, jmp_placeholder_size);
	memcpy(replace_code + 1, jmp_to, 4);
	for (int i = 5; i < signature_size; i++)
	{
		replace_code[i] = 0x90;
	}
	WriteProcessMemory(process.handle, address, replace_code, signature_size, NULL);
}