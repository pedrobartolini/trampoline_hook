FLOAT percentage(DWORD value, DWORD percentage)
{
	return ((FLOAT)value / 100) * (FLOAT)percentage;
}

VOID auto_waste_mana(WPARAM waste_mana_htk, DWORD minimum_percentage)
{
	if (values.current_mana >= percentage(values.total_mana, minimum_percentage))
	{
		send_key(waste_mana_htk);
	}
}

VOID auto_haste(WPARAM cure_paralyze_htk, WPARAM haste_htk, DWORD cure_paralyze_mana, DWORD haste_mana)
{
	DWORD wasted_mana;
	DWORD tmp_addr;
	if (values.haste == 2 && values.current_mana > cure_paralyze_mana)
	{
		send_key(cure_paralyze_htk);
	}

	if (values.haste != 2 && values.current_mana > haste_mana)
	{
		send_key(haste_htk);

		while (true)
		{
			tmp_addr = read_memory((DWORD)process.qtQuick_module + 0x2CB734);
			if (read_memory(tmp_addr) == 2)
			{
				addr.haste = tmp_addr;
				break;
			}
		}
	}
}

VOID auto_mana(WPARAM restore_mana_htk, DWORD mana_percentage, DWORD health_percentage)
{
	if (values.current_mana < percentage(values.total_mana, mana_percentage))
	{
		if (values.current_health > percentage(values.total_health, health_percentage))
		{
			send_key(restore_mana_htk);
		}
	}
}

VOID auto_heal(struct str_heal low_heal, struct str_heal med_heal, struct str_heal high_heal)
{
	heal_conditions(high_heal);
	heal_conditions(med_heal);
	heal_conditions(low_heal);
}

VOID heal_conditions(struct str_heal heal)
{
	if (heal.is_spell && values.heal_cooldown > 0)
	{
		return;
	}

	if (values.current_health >= percentage(values.total_health, heal.life_percentage))
	{
		return;
	}

	if (values.current_mana < heal.required_mana)
	{
		return;
	}

	send_key(heal.key);
}