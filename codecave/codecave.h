#include "read_module.h"
#include "signature_scan.h"
#include "injector.h"
#include "injections.h"

VOID codecave()
{
	DWORD module_address;
	SIZE_T module_size;

	// read_module(process.handle, "client.exe", &module_address, &module_size);
	// inject_current_health(module_address, module_size);
	// inject_total_health(module_address, module_size);
	// inject_current_mana(module_address, module_size);
	// inject_total_mana(module_address, module_size);

	// inject_heal_spell_cooldown(module_address, module_size);
	// read_module(process.handle, "Qt5Qml.dll", &module_address, &module_size);
	// printf("%p", module_address);
}
