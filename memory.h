DWORD read_memory(DWORD ptr)
{
	DWORD value;
	if (ptr != 0)
	{
		ReadProcessMemory(process.handle, ptr, &value, sizeof(DWORD), NULL);
		return value;
	}
	return 0;
}

VOID get_addresses()
{
	addr.base = read_memory((DWORD)process.client_module + 0x10BAD24);
	addr.player = read_memory(addr.base + 0x6C);

	addr.current_health = addr.player + 0xC;
	addr.current_mana = addr.player + 0x58;
	addr.total_health = addr.player + 0x10;
	addr.total_mana = addr.player + 0x5C;

	addr.haste = NULL;

	addr.heal_cooldown = read_memory((DWORD)process.client_module + 0x010F9D68);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x8);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x0);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x10);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x34);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x44);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x20);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x8);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x44);
	addr.heal_cooldown = read_memory(addr.heal_cooldown + 0x208);
	addr.heal_cooldown = addr.heal_cooldown + 0x18;
}

VOID update_values()
{
	values.current_health = read_memory(addr.current_health);
	values.total_health = read_memory(addr.total_health);
	values.current_mana = read_memory(addr.current_mana);
	values.total_mana = read_memory(addr.total_mana);

	values.heal_cooldown = read_memory(addr.heal_cooldown);

	if (addr.haste != NULL)
	{

		values.haste = read_memory(addr.haste);
	}
}
