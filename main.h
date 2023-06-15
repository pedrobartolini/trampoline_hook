struct str_addr addr;
struct str_values values;
struct str_process process;

struct str_addr
{
	DWORD base;
	DWORD player;
	DWORD current_health;
	DWORD total_health;
	DWORD current_mana;
	DWORD total_mana;
	DWORD haste;
	DWORD support_cooldown;
	DWORD heal_cooldown;
};

struct str_values
{
	DWORD current_mana;
	DWORD total_mana;
	DWORD current_health;
	DWORD total_health;
	DWORD haste;
	DWORD support_cooldown;
	DWORD heal_cooldown;
};

struct str_process
{
	HWND hwnd;
	DWORD id;
	HANDLE handle;
	HMODULE client_module;
	HMODULE qtGui_module;
	HMODULE qtQml_module;
	HMODULE qtQuick_module;
};

struct str_heal
{
	DWORD life_percentage;
	DWORD required_mana;
	WPARAM key;
	BOOL is_spell;
};

struct str_heal low_heal;
struct str_heal med_heal;
struct str_heal high_heal;
