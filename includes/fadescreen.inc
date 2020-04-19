/*
	By RIDE2DAY
*/

#if defined _inc_fadescreen
	#endinput
#endif
#define _inc_fadescreen

#include <YSI\y_hooks>

#define INVALID_FADE_ID -1
forward OnFadeComplete(playerid, bool:in, color, fadeid);
new screen_fade_alpha[MAX_PLAYERS];
new Timer:screen_fade_timer[MAX_PLAYERS] = {Timer:-1, ...};
new PlayerText:screen_fade_ptd[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

hook OnPlayerLogin(playerid)
{
	screen_fade_ptd[playerid] = CreatePlayerTextDraw(playerid, -30.000000, -40.000000, "LD_SPAC:white");
	PlayerTextDrawFont(playerid, screen_fade_ptd[playerid], 4);
	PlayerTextDrawColor(playerid, screen_fade_ptd[playerid], 255);
	PlayerTextDrawTextSize(playerid, screen_fade_ptd[playerid], 670.000000, 720.000000);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(screen_fade_timer[playerid] != Timer:-1)
	{
		stop screen_fade_timer[playerid];
		screen_fade_timer[playerid] = Timer:-1;
	}
	
	if(screen_fade_ptd[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, screen_fade_ptd[playerid]);
		screen_fade_ptd[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

timer UpdateScreenFadePTD[70](playerid, bool:in, color, to_alpha, fadeid)
{
	if(in)
	{
		screen_fade_alpha[playerid] += 0x11;
		if(screen_fade_alpha[playerid] >= to_alpha)
		{
			screen_fade_alpha[playerid] = to_alpha;
			stop screen_fade_timer[playerid];
			screen_fade_timer[playerid] = Timer:-1;
		}
	}
	else
	{
		screen_fade_alpha[playerid] -= 0x11;

		if(screen_fade_alpha[playerid] <= to_alpha)
		{
			screen_fade_alpha[playerid] = to_alpha;
			stop screen_fade_timer[playerid];
			screen_fade_timer[playerid] = Timer:-1;
		}
	}

	PlayerTextDrawColor(playerid, screen_fade_ptd[playerid], color | screen_fade_alpha[playerid]);
	PlayerTextDrawShow(playerid, screen_fade_ptd[playerid]);

	if(screen_fade_timer[playerid] == Timer:-1)
	{
		if(to_alpha == 0x00) PlayerTextDrawHide(playerid, screen_fade_ptd[playerid]);
		CallRemoteFunction("OnFadeComplete", "ibdd", playerid, in, color, fadeid);
	}
}

stock ShowPlayerScreenTD(playerid, color = 0x000000FF)
{
	if(screen_fade_timer[playerid] != Timer:-1)
	{
		stop screen_fade_timer[playerid];
		screen_fade_timer[playerid] = Timer:-1;
	}

	PlayerTextDrawColor(playerid, screen_fade_ptd[playerid], color);
	PlayerTextDrawShow(playerid, screen_fade_ptd[playerid]);
	return 1;
}

stock HidePlayerScreenTD(playerid)
{
	if(screen_fade_timer[playerid] != Timer:-1)
	{
		stop screen_fade_timer[playerid];
		screen_fade_timer[playerid] = Timer:-1;
	}

	PlayerTextDrawColor(playerid, screen_fade_ptd[playerid], 0x00000000);
	PlayerTextDrawHide(playerid, screen_fade_ptd[playerid]);
	return 1;
}

FadePlayerScreen(playerid, color = 0x000000, init_alpha = 0xAA, to_alpha = 0xFF, fadeid = INVALID_FADE_ID)
{
	if(init_alpha == to_alpha) return 0;

	color = (color << 8) + 0x00;
	if(screen_fade_timer[playerid] != Timer:-1)
	{
		stop screen_fade_timer[playerid];
		screen_fade_timer[playerid] = Timer:-1;
	}

	new bool:in;
	if(to_alpha > init_alpha) in = true;
	else in = false;

	PlayerTextDrawColor(playerid, screen_fade_ptd[playerid], color | init_alpha);
	PlayerTextDrawShow(playerid, screen_fade_ptd[playerid]);

	screen_fade_alpha[playerid] = init_alpha;
	screen_fade_timer[playerid] = repeat UpdateScreenFadePTD(playerid, in, color, to_alpha, fadeid);
	return 1;
}