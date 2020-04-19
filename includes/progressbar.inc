#if defined _inc_progressbar
	#endinput
#endif
#define _inc_progressbar

#include <YSI\y_hooks>
#define INVALID_PROGRESS_BAR_ID -1
#define MAX_PROGRESS_BARS 2
#define MAX_PLAYER_PROGRESS_BARS 10

//Global
enum enum_Progress_Bar
{
	Text:progress_bar_BOX,
	Text:progress_bar_BAR,
	Float:progress_bar_X,
	Float:progress_bar_Y,
	Float:progress_bar_SIZE_X,
	Float:progress_bar_SIZE_Y,
	Float:progress_bar_VALUE,
	progress_bar_BOX_COLOR,
	progress_bar_BAR_COLOR,
	progress_bar_DIRECTION
};
new Progress_Bar[MAX_PROGRESS_BARS][enum_Progress_Bar];
new Iterator:Progress_Bar<MAX_PROGRESS_BARS>;

#define IsValidProgressBar(%0) Iter_Contains(Progress_Bar,%0)
#define GetProgressBarPosX(%0) Progress_Bar[%0][progress_bar_X]
#define GetProgressBarPosY(%0) Progress_Bar[%0][progress_bar_Y]
#define GetProgressBarSizeX(%0) Progress_Bar[%0][progress_bar_SIZE_X]
#define GetProgressBarSizeY(%0) Progress_Bar[%0][progress_bar_SIZE_Y]
#define GetProgressBarBoxColor(%0) Progress_Bar[%0][progress_bar_BOX_COLOR]
#define GetProgressBarBarColor(%0) Progress_Bar[%0][progress_bar_BAR_COLOR]
#define GetProgressBarValue(%0) Progress_Bar[%0][progress_bar_VALUE]

stock SetProgressBarBoxColor(slot, color)
{
	if(IsValidProgressBar(slot))
	{
		Progress_Bar[slot][progress_bar_BOX_COLOR] = color;
		TextDrawColor(Progress_Bar[slot][progress_bar_BOX], Progress_Bar[slot][progress_bar_BOX_COLOR]);
		return 1;
	}
	return 0;
}

stock SetProgressBarBarColor(slot, color)
{
	if(IsValidProgressBar(slot))
	{
		Progress_Bar[slot][progress_bar_BAR_COLOR] = color;
		TextDrawColor(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_BAR_COLOR]);
		return 1;
	}
	return 0;
}

stock CreateProgressBar(Float:x, Float:y, Float:size_x, Float:size_y, box_color = 0x000000FF, bar_color = 0xFFFFFFFF, direction = 0)
{
	new slot = Iter_Free(Progress_Bar);
	if(slot != cellmin)
	{
		Progress_Bar[slot][progress_bar_X] = x;
		Progress_Bar[slot][progress_bar_Y] = y;
		Progress_Bar[slot][progress_bar_SIZE_X] = size_x;
		Progress_Bar[slot][progress_bar_SIZE_Y] = size_y;
		Progress_Bar[slot][progress_bar_BOX_COLOR] = box_color;
		Progress_Bar[slot][progress_bar_BAR_COLOR] = bar_color;
		Progress_Bar[slot][progress_bar_VALUE] = 0.0;
		Progress_Bar[slot][progress_bar_DIRECTION] = direction;

		Progress_Bar[slot][progress_bar_BOX] = TextDrawCreate(Progress_Bar[slot][progress_bar_X], Progress_Bar[slot][progress_bar_Y], "LD_SPAC:white");
		TextDrawTextSize(Progress_Bar[slot][progress_bar_BOX], Progress_Bar[slot][progress_bar_SIZE_X], Progress_Bar[slot][progress_bar_SIZE_Y]);
		TextDrawColor(Progress_Bar[slot][progress_bar_BOX], Progress_Bar[slot][progress_bar_BOX_COLOR]);
		TextDrawFont(Progress_Bar[slot][progress_bar_BOX], 4);

		switch(Progress_Bar[slot][progress_bar_DIRECTION])
		{
			case 0: //izq a der
			{
				Progress_Bar[slot][progress_bar_BAR] = TextDrawCreate(Progress_Bar[slot][progress_bar_X], Progress_Bar[slot][progress_bar_Y], "LD_SPAC:white");
				TextDrawTextSize(Progress_Bar[slot][progress_bar_BAR], 0.0, Progress_Bar[slot][progress_bar_SIZE_Y]);
				TextDrawColor(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_BAR_COLOR]);
				TextDrawFont(Progress_Bar[slot][progress_bar_BAR], 4);
			}
			case 1: //der a izq
			{
				Progress_Bar[slot][progress_bar_BAR] = TextDrawCreate(Progress_Bar[slot][progress_bar_X] + Progress_Bar[slot][progress_bar_SIZE_X], Progress_Bar[slot][progress_bar_Y], "LD_SPAC:white");
				TextDrawTextSize(Progress_Bar[slot][progress_bar_BAR], 0.0, Progress_Bar[slot][progress_bar_SIZE_Y]);
				TextDrawColor(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_BAR_COLOR]);
				TextDrawFont(Progress_Bar[slot][progress_bar_BAR], 4);
			}
			case 2: //abajo a arriba
			{
				Progress_Bar[slot][progress_bar_BAR] = TextDrawCreate(Progress_Bar[slot][progress_bar_X], Progress_Bar[slot][progress_bar_Y] + Progress_Bar[slot][progress_bar_SIZE_Y], "LD_SPAC:white");
				TextDrawTextSize(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_SIZE_X], 0.0);
				TextDrawColor(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_BAR_COLOR]);
				TextDrawFont(Progress_Bar[slot][progress_bar_BAR], 4);
			}
			case 3: //arriba a abajo
			{
				Progress_Bar[slot][progress_bar_BAR] = TextDrawCreate(Progress_Bar[slot][progress_bar_X], Progress_Bar[slot][progress_bar_Y], "LD_SPAC:white");
				TextDrawTextSize(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_SIZE_X], 0.0);
				TextDrawColor(Progress_Bar[slot][progress_bar_BAR], Progress_Bar[slot][progress_bar_BAR_COLOR]);
				TextDrawFont(Progress_Bar[slot][progress_bar_BAR], 4);
			}
		}

		Iter_Add(Progress_Bar, slot);
		return slot;
	}
	return INVALID_PROGRESS_BAR_ID;
}

stock DestroyProgressBar(slot)
{
	if(IsValidProgressBar(slot))
	{
		if(Progress_Bar[slot][progress_bar_BOX] != Text:INVALID_TEXT_DRAW)
		{
			TextDrawDestroy(Progress_Bar[slot][progress_bar_BOX]);
			Progress_Bar[slot][progress_bar_BOX] = Text:INVALID_TEXT_DRAW;
		}

		if(Progress_Bar[slot][progress_bar_BAR] != Text:INVALID_TEXT_DRAW)
		{
			TextDrawDestroy(Progress_Bar[slot][progress_bar_BAR]);
			Progress_Bar[slot][progress_bar_BAR] = Text:INVALID_TEXT_DRAW;
		}

		Progress_Bar[slot][progress_bar_X] = 0.0;
		Progress_Bar[slot][progress_bar_Y] = 0.0;
		Progress_Bar[slot][progress_bar_SIZE_X] = 0.0;
		Progress_Bar[slot][progress_bar_SIZE_Y] = 0.0;
		Progress_Bar[slot][progress_bar_BOX_COLOR] = 0;
		Progress_Bar[slot][progress_bar_BAR_COLOR] = 0;
		Progress_Bar[slot][progress_bar_VALUE] = 0.0;

		Iter_Remove(Progress_Bar, slot);
		return 1;
	}
	return 0;
}

stock ShowProgressBarForPlayer(playerid, slot)
{
	if(IsValidProgressBar(slot))
	{
		TextDrawShowForPlayer(playerid, Progress_Bar[slot][progress_bar_BOX]);
		TextDrawShowForPlayer(playerid, Progress_Bar[slot][progress_bar_BAR]);
		return 1;
	}
	return 0;
}

stock HideProgressBarForPlayer(playerid, slot)
{
	if(IsValidProgressBar(slot))
	{
		TextDrawHideForPlayer(playerid, Progress_Bar[slot][progress_bar_BOX]);
		TextDrawHideForPlayer(playerid, Progress_Bar[slot][progress_bar_BAR]);
		return 1;
	}
	return 0;
}

stock ShowProgressBarForAll(slot)
{
	if(IsValidProgressBar(slot))
	{
		TextDrawShowForAll(Progress_Bar[slot][progress_bar_BOX]);
		TextDrawShowForAll(Progress_Bar[slot][progress_bar_BAR]);
		return 1;
	}
	return 0;
}

stock HideProgressBarForAll(slot)
{
	if(IsValidProgressBar(slot))
	{
		TextDrawHideForAll(Progress_Bar[slot][progress_bar_BOX]);
		TextDrawHideForAll(Progress_Bar[slot][progress_bar_BAR]);
		return 1;
	}
	return 0;
}

stock SetProgressBarValue(slot, Float:value)
{
	if(IsValidProgressBar(slot))
	{
		if(value < 0.0) value = 0.0;
		else if(value > 100.0) value = 100.0;

		Progress_Bar[slot][progress_bar_VALUE] = value;

		new Float:size_x = Progress_Bar[slot][progress_bar_SIZE_X], Float:size_y = Progress_Bar[slot][progress_bar_SIZE_Y];
		switch(Progress_Bar[slot][progress_bar_DIRECTION])
		{
			case 0: { size_x = floatmul(floatdiv(Progress_Bar[playerid][slot][progress_bar_SIZE_X], 100.0), Progress_Bar[playerid][slot][progress_bar_VALUE]); }
			case 1: { size_x = -floatmul(floatdiv(Progress_Bar[playerid][slot][progress_bar_SIZE_X], 100.0), Progress_Bar[playerid][slot][progress_bar_VALUE]); }
			case 2: { size_y = -floatmul(floatdiv(Progress_Bar[playerid][slot][progress_bar_SIZE_Y], 100.0), Progress_Bar[playerid][slot][progress_bar_VALUE]); }
			case 3: { size_y = floatmul(floatdiv(Progress_Bar[playerid][slot][progress_bar_SIZE_Y], 100.0), Progress_Bar[playerid][slot][progress_bar_VALUE]); }
		}
		TextDrawTextSize(Progress_Bar[slot][progress_bar_BAR], size_x, size_y);
		return 1;
	}
	return 0;
}
//Global

//Player
enum enum_PlayerProgress_Bar
{
	PlayerText:playerprogress_bar_BOX,
	PlayerText:playerprogress_bar_BAR,
	Float:playerprogress_bar_X,
	Float:playerprogress_bar_Y,
	Float:playerprogress_bar_SIZE_X,
	Float:playerprogress_bar_SIZE_Y,
	Float:playerprogress_bar_VALUE,
	playerprogress_bar_BOX_COLOR,
	playerprogress_bar_BAR_COLOR,
	playerprogress_bar_BAR_DIR
};
new PlayerProgress_Bar[MAX_PLAYERS][MAX_PLAYER_PROGRESS_BARS][enum_PlayerProgress_Bar];
new Iterator:PlayerProgress_Bar[MAX_PLAYERS]<MAX_PLAYER_PROGRESS_BARS>;

hook OnScriptInit()
{
	print("Progress bar include by adri1 loaded");
	Iter_Init(PlayerProgress_Bar);
	return 1;
}

#define IsValidPlayerProgressBar(%0,%1) Iter_Contains(PlayerProgress_Bar[%0],%1)
#define GetPlayerProgressBarPosX(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_X]
#define GetPlayerProgressBarPosY(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_Y]
#define GetPlayerProgressBarSizeX(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_SIZE_X]
#define GetPlayerProgressBarSizeY(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_SIZE_Y]
#define GetPlayerProgressBarBoxColor(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_BOX_COLOR]
#define GetPlayerProgressBarBarColor(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_BAR_COLOR]
#define GetPlayerProgressBarValue(%0,%1) PlayerProgress_Bar[%0][%1][playerprogress_bar_VALUE]

stock SetPlayerProgressBarBoxColor(playerid, slot, color)
{
	if(IsValidPlayerProgressBar(playerid, slot))
	{
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX_COLOR] = color;
		PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX_COLOR]);
		return 1;
	}
	return 0;
}

stock SetPlayerProgressBarBarColor(playerid, slot, color)
{
	if(IsValidPlayerProgressBar(playerid, slot))
	{
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR] = color;
		PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR]);
		return 1;
	}
	return 0;
}

stock CreatePlayerProgressBar(playerid, Float:x, Float:y, Float:size_x, Float:size_y, box_color = 0x000000FF, bar_color = 0xFFFFFFFF, direction = 0)
{
	new slot = Iter_Free(PlayerProgress_Bar[playerid]);
	if(slot != cellmin)
	{
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_X] = x;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y] = y;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X] = size_x;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y] = size_y;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX_COLOR] = box_color;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR] = bar_color;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_DIR] = direction;

		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX] = CreatePlayerTextDraw(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_X], PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y], "LD_SPAC:white");
		PlayerTextDrawTextSize(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX], PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y]);
		PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX_COLOR]);
		PlayerTextDrawFont(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX], 4);

		switch(PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_DIR])
		{
			case 0: //izq a der
			{
				PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] = CreatePlayerTextDraw(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_X], PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y], "LD_SPAC:white");
				PlayerTextDrawTextSize(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], 0.0, PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y]);
				PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR]);
				PlayerTextDrawFont(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], 4);
			}
			case 1: //der a izq
			{
				PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] = CreatePlayerTextDraw(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_X] + PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y], "LD_SPAC:white");
				PlayerTextDrawTextSize(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], 0.0, PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y]);
				PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR]);
				PlayerTextDrawFont(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], 4);
			}
			case 2: //abajo a arriba
			{
				PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] = CreatePlayerTextDraw(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_X], PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y] + PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y], "LD_SPAC:white");
				PlayerTextDrawTextSize(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], 0.0);
				PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR]);
				PlayerTextDrawFont(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], 4);
			}
			case 3: //arriba a abajo
			{
				PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] = CreatePlayerTextDraw(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_X], PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y], "LD_SPAC:white");
				PlayerTextDrawTextSize(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], 0.0);
				PlayerTextDrawColor(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR]);
				PlayerTextDrawFont(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], 4);
			}
		}

		Iter_Add(PlayerProgress_Bar[playerid], slot);
		return slot;
	}
	return INVALID_PROGRESS_BAR_ID;
}

stock DestroyPlayerProgressBar(playerid, slot)
{
	if(IsValidPlayerProgressBar(playerid, slot))
	{
		if(PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX]);
			PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR]);
			PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] = PlayerText:INVALID_TEXT_DRAW;
		}

		PlayerProgress_Bar[playerid][slot][playerprogress_bar_X] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX_COLOR] = 0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR] = 0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE] = 0.0;

		Iter_Remove(PlayerProgress_Bar[playerid], slot);
		return 1;
	}
	return 0;
}

stock DestroyAllPlayerProgressBar(playerid)
{
	foreach(new slot : PlayerProgress_Bar[playerid])
	{
		if(PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX]);
			PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR]);
			PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR] = PlayerText:INVALID_TEXT_DRAW;
		}

		PlayerProgress_Bar[playerid][slot][playerprogress_bar_X] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_Y] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y] = 0.0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX_COLOR] = 0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_COLOR] = 0;
		PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE] = 0.0;
	}

	Iter_Clear(PlayerProgress_Bar[playerid]);
	return 1;
}

stock ShowPlayerProgressBar(playerid, slot)
{
	if(IsValidPlayerProgressBar(playerid, slot))
	{
		PlayerTextDrawShow(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX]);
		PlayerTextDrawShow(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR]);
		return 1;
	}
	return 0;
}

stock HidePlayerProgressBar(playerid, slot)
{
	if(IsValidPlayerProgressBar(playerid, slot))
	{
		PlayerTextDrawHide(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BOX]);
		PlayerTextDrawHide(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR]);
		return 1;
	}
	return 0;
}

stock SetPlayerProgressBarValue(playerid, slot, Float:value)
{
	if(IsValidPlayerProgressBar(playerid, slot))
	{
		if(value < 0.0) value = 0.0;
		else if(value > 100.0) value = 100.0;

		PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE] = value;

		new Float:size_x = PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], Float:size_y = PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y];
		switch(PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR_DIR])
		{
			case 0: { size_x = floatmul(floatdiv(PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], 100.0), PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE]); }
			case 1: { size_x = -floatmul(floatdiv(PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_X], 100.0), PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE]); }
			case 2: { size_y = -floatmul(floatdiv(PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y], 100.0), PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE]); }
			case 3: { size_y = floatmul(floatdiv(PlayerProgress_Bar[playerid][slot][playerprogress_bar_SIZE_Y], 100.0), PlayerProgress_Bar[playerid][slot][playerprogress_bar_VALUE]); }
		}
		PlayerTextDrawTextSize(playerid, PlayerProgress_Bar[playerid][slot][playerprogress_bar_BAR], size_x, size_y);
		return 1;
	}
	return 0;
}
//Player