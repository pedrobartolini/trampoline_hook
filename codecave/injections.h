VOID inject_total_health(DWORD module_address, SIZE_T module_size)
{
	BYTE total_health_signature[] = {0x89, 0x41, 0x10, 0x83, 0xB9, 0x9C, 0x01, 0x00, 0x00, 0x00};
	addr.total_health = VirtualAllocEx(process.handle, NULL, sizeof(int), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// HEALTH ADDRESS BYTES
	BYTE total_health_bytes[4];
	get_byte_arr(&total_health_bytes, addr.total_health);

	// BUILD INJECT CODE
	BYTE new_code[] = {0xA3, 0x00, 0x00, 0x00, 0x00};
	memcpy(new_code + 1, total_health_bytes, sizeof(total_health_bytes));

	// INJECT CODE
	code_inject(module_address, module_size, total_health_signature, sizeof(total_health_signature), new_code, sizeof(new_code));
}

VOID inject_current_health(DWORD module_address, SIZE_T module_size)
{
	BYTE current_health_signature[] = {0x89, 0x46, 0x0C, 0x83, 0xBE, 0x9C, 0x01, 0x00, 0x00, 0x00};
	addr.current_health = VirtualAllocEx(process.handle, NULL, sizeof(int), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// HEALTH ADDRESS BYTES
	BYTE current_health_bytes[4];
	get_byte_arr(&current_health_bytes, addr.current_health);

	// BUILD INJECT CODE
	BYTE new_code[] = {0xA3, 0x00, 0x00, 0x00, 0x00};
	memcpy(new_code + 1, current_health_bytes, sizeof(current_health_bytes));

	// INJECT CODE
	code_inject(module_address, module_size, current_health_signature, sizeof(current_health_signature), new_code, sizeof(new_code));
}

VOID inject_total_mana(DWORD module_address, SIZE_T module_size)
{
	BYTE total_mana_signature[] = {0x89, 0x41, 0x5C, 0x83, 0xB9, 0x9C, 0x01, 0x00, 0x00, 0x00};
	addr.total_mana = VirtualAllocEx(process.handle, NULL, sizeof(int), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// MANA ADDRESS BYTES
	BYTE total_mana_bytes[4];
	get_byte_arr(&total_mana_bytes, addr.total_mana);

	// BUILD INJECT CODE
	BYTE new_code[] = {0xA3, 0x00, 0x00, 0x00, 0x00}; // mov [xxx], eax
	memcpy(new_code + 1, total_mana_bytes, sizeof(total_mana_bytes));

	// INJECT CODE
	code_inject(module_address, module_size, total_mana_signature, sizeof(total_mana_signature), new_code, sizeof(new_code));
}

VOID inject_current_mana(DWORD module_address, SIZE_T module_size)
{
	BYTE current_mana_signature[] = {0x89, 0x41, 0x58, 0x83, 0xB9, 0x9C, 0x01, 0x00, 0x00, 0x00};
	addr.current_mana = VirtualAllocEx(process.handle, NULL, sizeof(int), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// MANA ADDRESS BYTES
	BYTE current_mana_bytes[4];
	get_byte_arr(&current_mana_bytes, addr.current_mana);

	// BUILD INJECT CODE
	BYTE new_code[] = {0xA3, 0x00, 0x00, 0x00, 0x00}; // mov [xxx], eax
	memcpy(new_code + 1, current_mana_bytes, sizeof(current_mana_bytes));

	// INJECT CODE
	code_inject(module_address, module_size, current_mana_signature, sizeof(current_mana_signature), new_code, sizeof(new_code));
}
