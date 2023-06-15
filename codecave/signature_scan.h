DWORD find_signature_address(LPVOID module_address, SIZE_T module_size, BYTE *signature, SIZE_T signature_size)
{
	SIZE_T bytesRead = 0;
	BYTE buffer[4096];
	DWORD oldProtect = 0;
	DWORD newProtect = PAGE_READWRITE;
	SIZE_T i, j, k;

	for (i = 0; i < module_size; i += bytesRead)
	{
		if (!ReadProcessMemory(process.handle, (LPCVOID)((DWORD_PTR)module_address + i), buffer, sizeof(buffer), &bytesRead))
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
					return (DWORD)module_address + i + j;
				}
			}
		}
	}
}