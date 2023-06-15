#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <stdlib.h>

#include "main.h"
#include "memory.h"
#include "process.h"
#include "bot.h"
// #include "codecave.h"
#include "codecave/codecave.h"

VOID main()
{
	const wchar_t *process_name = L"client.exe";

	process.hwnd = FindWindow(NULL, "Tibia - Threadstack");

	process.id = get_pid(process_name);
	if (process.id == NULL)
	{
		printf("Could not find PID.\n");
		return;
	}

	process.handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process.id);
	if (process.handle == NULL)
	{
		printf("Could not attach to process.\n");
		return;
	}

	process.client_module = get_module(process.handle, "client.exe");
	if (process.client_module == NULL)
	{
		printf("Could not find client.exe module.\n");
		CloseHandle(process.handle);
		return;
	}

	process.qtGui_module = get_module(process.handle, "Qt5Gui.dll");
	if (process.qtGui_module == NULL)
	{
		printf("Could not find Qt5Gui module.\n");
		CloseHandle(process.handle);
		return;
	}

	process.qtQml_module = get_module(process.handle, "Qt5Qml.dll");
	if (process.qtGui_module == NULL)
	{
		printf("Could not find Qt5Qml module.\n");
		CloseHandle(process.handle);
		return;
	}

	process.qtQuick_module = get_module(process.handle, "Qt5Quick.dll");
	if (process.qtGui_module == NULL)
	{
		printf("Could not find Qt5Quick module.\n");
		CloseHandle(process.handle);
		return;
	}

	get_addresses();
	codecave();

	low_heal.key = VK_F1;
	low_heal.required_mana = 40;
	low_heal.life_percentage = 80;
	low_heal.is_spell = true;

	med_heal.key = VK_F11;
	med_heal.required_mana = 0;
	med_heal.life_percentage = 65;
	med_heal.is_spell = false;

	high_heal.key = VK_F12;
	high_heal.required_mana = 0;
	high_heal.life_percentage = 40;
	high_heal.is_spell = false;

	BOOL debug = true;
	INT debug_refresh = 0;
	while (true)
	{
		Sleep(50);
		debug_refresh++;
		update_values();

		// auto_waste_mana(VK_F5, 100);
		auto_haste(VK_F1, VK_F6, 40, 100);
		// auto_heal(low_heal, med_heal, high_heal);
		// auto_mana(VK_F2, 30, 10);

		if (debug && debug_refresh > 10)
		{
			debug_refresh = 0;
			system("cls");
			printf("Addresses debugging\n");
			printf("Vida(%p): %u - Vida cheia(%p): %u\n", addr.current_health, values.current_health, addr.total_health, values.total_health);
			printf("Mana(%p): %u - Mana cheia(%p): %u\n", addr.current_mana, values.current_mana, addr.total_mana, values.total_mana);
			printf("Auto haste(%p): %u\n", addr.haste, values.haste);
			printf("Heal cooldown(%p): %u\n", addr.heal_cooldown, values.heal_cooldown);
		}
	}
}
