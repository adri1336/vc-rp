#define DEFAULT_WEAPON_AMMO 100
#define MAX_PLAYER_WEAPONS 5
#define MAX_PLAYER_WEAPONS_CARRIED 2

enum E_pWeapons
{
	pweapon_ID,
	pweapon_CARRIED,
	pweapon_WEAPONID,
	pweapon_AMMO
};
new pWeapons[MAX_PLAYERS][MAX_PLAYER_WEAPONS][E_pWeapons],
	Iterator:pWeapons[MAX_PLAYERS]<MAX_PLAYER_WEAPONS>;