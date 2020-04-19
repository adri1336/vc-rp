#define MIN_PASSWD_LENGHT 6
#define MAX_PASSWD_LENGHT 32

new PlayerText:PTD_VCRP_REGISTER[MAX_PLAYERS][7] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};

new register_player_passwd[MAX_PLAYERS][MAX_PASSWD_LENGHT + 1],
	bool:pNewUser[MAX_PLAYERS],
	pSelectedCharacter[MAX_PLAYERS];

new Intro_Characters[][] =
{
	{1, 2, 3, 4, 5, 6}, //hombre
	{7, 8, 9, 10, 11, 12} //mujer
};

forward OnPlayerRequestRegister(playerid);
forward OnPlayerRegisterDialog(playerid, dialogid, response, listitem, inputtext[]);
forward OnPlayerEmailRegister(playerid, dialogid, response, listitem, inputtext[]);
forward OnPlayerRegister(playerid);