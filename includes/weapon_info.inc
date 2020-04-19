#if defined _inc_weapon_info
	#endinput
#endif
#define _inc_weapon_info

#define WEAPON_NONE 0
enum E_weaponInfo
{
	bool:weaponinfo_AMMO,
	weaponinfo_TYPE,
	weaponinfo_SLOT,
	weaponinfo_SHOT_TIME,
}
new weaponInfo[][E_weaponInfo] = 
{
	{false, WEAPON_NONE, 0, 250}, //puño
	{false, WEAPON_BRASSKNUCKLE, 0, 250}, //Manopla
	{false, WEAPON_GOLFCLUB, 1, 250}, //Palo de golf
	{false, WEAPON_NITESTICK, 1, 250}, //Porra
	{false, WEAPON_KNIFE, 1, 250}, //Cuchillo
	{false, WEAPON_BAT, 1, 250}, //Bate
	{false, WEAPON_SHOVEL, 1, 250}, //Pala
	{false, WEAPON_POOLSTICK, 1, 250}, //Taco
	{false, WEAPON_KATANA, 1, 250}, //Katana
	{false, WEAPON_CHAINSAW, 1, 30}, //Motosierra
	{false, WEAPON_DILDO, 10, 250}, //Dildo morado
	{false, WEAPON_DILDO2, 10, 250}, //Dildo
	{false, WEAPON_VIBRATOR, 10, 250}, //Vibrador
	{false, WEAPON_VIBRATOR2, 10, 250}, //Vibrador plateado
	{false, WEAPON_FLOWER, 10, 250}, //Flores
	{false, WEAPON_CANE, 10, 250}, //Bastón
	{true, WEAPON_GRENADE, 8, 500}, //Granada
	{true, WEAPON_TEARGAS, 8, 500}, //Gas lacrimógeno
	{true, WEAPON_MOLTOV, 8, 500}, //Cocktail Molotov
	{false, WEAPON_NONE, 0, 0},
	{false, WEAPON_NONE, 0, 0},
	{false, WEAPON_NONE, 0, 0},
	{true, WEAPON_COLT45, 2, 160}, //9mm
	{true, WEAPON_SILENCED, 2, 120}, //9mm silenciada
	{true, WEAPON_DEAGLE, 2, 950}, //Desert Eagle
	{true, WEAPON_SHOTGUN, 3, 800}, //Escopeta
	{true, WEAPON_SAWEDOFF, 3, 120}, //Escopeta recortada
	{true, WEAPON_SHOTGSPA, 3, 120}, //Escopeta de combate
	{true, WEAPON_UZI, 4, 70}, //Micro UZI
	{true, WEAPON_MP5, 4, 70}, //MP5
	{true, WEAPON_AK47, 5, 80}, //Ak-47
	{true, WEAPON_M4, 5, 80}, //M4
	{true, WEAPON_TEC9, 4, 70}, //TEC-9
	{true, WEAPON_RIFLE, 6, 1000}, //Rifle
	{true, WEAPON_SNIPER, 6, 1000}, //Sniper
	{true, WEAPON_ROCKETLAUNCHER, 7, 1000}, //Lanzacohetes RPG
	{true, WEAPON_HEATSEEKER, 7, 1000}, //Lanzacohetes HS
	{true, WEAPON_FLAMETHROWER, 7, 500}, //Lanzallamas
	{true, WEAPON_MINIGUN, 7, 0}, //Minigun
	{true, WEAPON_SATCHEL, 8, 500}, //Bomba detonadora
	{false, WEAPON_BOMB, 12, 500}, //Detonador
	{true, WEAPON_SPRAYCAN, 9, 10}, //Bote de spray
	{true, WEAPON_FIREEXTINGUISHER, 9, 10}, //Extintor
	{false, WEAPON_CAMERA, 9, 500}, //Cámara
	{false, WEAPON_NONE, 11, 0}, //Gafas de visión nocturna
	{false, WEAPON_NONE, 11, 0}, //Gafas térmicas
	{false, WEAPON_PARACHUTE, 11, 0} //Paracaídas
};

#define GetWeaponSlot(%0) weaponInfo[%0][weaponinfo_SLOT]
#define GetWeaponShotTime(%0) weaponInfo[%0][weaponinfo_SHOT_TIME]
#define HasWeaponAmmo(%0) weaponInfo[%0][weaponinfo_AMMO]