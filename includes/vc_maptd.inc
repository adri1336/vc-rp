#if defined _inc_vc_maptd
	#endinput
#endif
#define _inc_vc_maptd

#include <YSI\y_hooks>

#define VC_TDMAP_PATH "mdl-1000:vc_map"
#define INVALID_VC_TDMAP_ID -1

#define vc_limit_X_WEST 4130.0
#define vc_limit_X_EAST 6975.0
#define vc_limit_Y_NORTH 2665.0
#define vc_limit_Y_SOUTH -930.0

//Global
#define MAX_VC_TDMAPS 10
#define MAX_VC_TDMAPS_POINTS 300

enum enum_Vc_TdMaps
{
	Text:vc_tdmap_TD,
	Float:vc_tdmap_X,
	Float:vc_tdmap_Y,
	Float:vc_tdmap_SIZE_X,
	Float:vc_tdmap_SIZE_Y,
	bool:vc_tdmap_BIG
};
new Vc_TdMaps[MAX_VC_TDMAPS][enum_Vc_TdMaps],
	Iterator:Vc_TdMaps<MAX_VC_TDMAPS>;

enum enum_Vc_TdMaps_Points
{
	Text:vc_tdmap_point_TD,
	Text:vc_tdmap_point_TD_DESCRIPTION,
	vc_tdmap_point_ICON[64],
	Float:vc_tdmap_point_ICON_SIZE_X,
	Float:vc_tdmap_point_ICON_SIZE_Y,
	vc_tdmap_point_DESCRIPTION[128],
	Float:vc_tdmap_point_DESCR_LS_X,
	Float:vc_tdmap_point_DESCR_LS_Y,
	vc_tdmap_point_DESCR_OUTLINE,
	vc_tdmap_point_DESCR_COLOR,
	Float:vc_tdmap_point_X,
	Float:vc_tdmap_point_Y,
	Float:vc_tdmap_point_Z,
	Float:vc_tdmap_point_TD_X,
	Float:vc_tdmap_point_TD_Y,
	vc_tdmap_point_COLOR
};
new Vc_TdMaps_Points[MAX_VC_TDMAPS][MAX_VC_TDMAPS_POINTS][enum_Vc_TdMaps_Points],
	Iterator:Vc_TdMaps_Points[MAX_VC_TDMAPS]<MAX_VC_TDMAPS_POINTS>;

#define GetFreeVcTdMapSlot() Iter_Free(Vc_TdMaps)
#define GetFreeVcTdMapPointSlot(%0) Iter_Free(Vc_TdMaps_Points[%0])
#define CountVcTdMaps() Iter_Count(Vc_TdMaps)
#define CountVcTdMapPoints(%0) Iter_Count(Vc_TdMaps_Points[%0])
#define IsValidVcTdMap(%0) Iter_Contains(Vc_TdMaps,%0)
#define IsValidVcTdMapPoint(%0,%1) Iter_Contains(Vc_TdMaps_Points[%0],%1)

stock CreateVcTdMap(Float:x, Float:y, Float:size_x, Float:size_y, bool:big = false)
{
	new index = GetFreeVcTdMapSlot();
	if(index != cellmin)
	{
		Vc_TdMaps[index][vc_tdmap_X] = x;
		Vc_TdMaps[index][vc_tdmap_Y] = y;
		Vc_TdMaps[index][vc_tdmap_SIZE_X] = size_x;
		Vc_TdMaps[index][vc_tdmap_SIZE_Y] = size_y;
		Vc_TdMaps[index][vc_tdmap_BIG] = big;
		Vc_TdMaps[index][vc_tdmap_TD] = TextDrawCreate(Vc_TdMaps[index][vc_tdmap_X], Vc_TdMaps[index][vc_tdmap_Y], VC_TDMAP_PATH);
		TextDrawTextSize(Vc_TdMaps[index][vc_tdmap_TD], Vc_TdMaps[index][vc_tdmap_SIZE_X], Vc_TdMaps[index][vc_tdmap_SIZE_Y]);
		TextDrawFont(Vc_TdMaps[index][vc_tdmap_TD], 4);

		Iter_Add(Vc_TdMaps, index);
		return index;
	}
	return INVALID_VC_TDMAP_ID;
}

stock DestroyVcTdMaps()
{
	foreach(new i : Vc_TdMaps)
	{
		DestroyVcTdMapPoints(i);
		Vc_TdMaps[i][vc_tdmap_X] = 0.0;
		Vc_TdMaps[i][vc_tdmap_Y] = 0.0;
		Vc_TdMaps[i][vc_tdmap_SIZE_X] = 0.0;
		Vc_TdMaps[i][vc_tdmap_SIZE_Y] = 0.0;
		TextDrawDestroy(Vc_TdMaps[i][vc_tdmap_TD]);
	}
	Iter_Clear(Vc_TdMaps);
	return 1;
}

stock DestroyVcTdMap(index)
{
	if(IsValidVcTdMap(index))
	{
		DestroyVcTdMapPoints(index);
		Vc_TdMaps[index][vc_tdmap_X] = 0.0;
		Vc_TdMaps[index][vc_tdmap_Y] = 0.0;
		Vc_TdMaps[index][vc_tdmap_SIZE_X] = 0.0;
		Vc_TdMaps[index][vc_tdmap_SIZE_Y] = 0.0;
		TextDrawDestroy(Vc_TdMaps[index][vc_tdmap_TD]);
		Iter_Remove(Vc_TdMaps, index);
		return 1;
	}
	return 0;
}

stock DestroyVcTdMapPoints(index)
{
	if(IsValidVcTdMap(index))
	{
		foreach(new i : Vc_TdMaps_Points[index])
		{
			if(Vc_TdMaps_Points[index][i][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawDestroy(Vc_TdMaps_Points[index][i][vc_tdmap_point_TD_DESCRIPTION]);
			TextDrawDestroy(Vc_TdMaps_Points[index][i][vc_tdmap_point_TD]);
			Vc_TdMaps_Points[index][i][vc_tdmap_point_ICON][0] = EOS;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_ICON_SIZE_X] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_ICON_SIZE_Y] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_DESCRIPTION][0] = EOS;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_X] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_Y] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_Z] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_TD_X] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_TD_Y] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_DESCR_LS_X] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_DESCR_LS_Y] = 0.0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_DESCR_OUTLINE] = 0;
			Vc_TdMaps_Points[index][i][vc_tdmap_point_DESCR_COLOR] = 0;
		}
		Iter_Clear(Vc_TdMaps_Points[index]);
		return 1;
	}
	return 0;
}

stock DestroyVcTdMapPoint(index, point_index)
{
	if(IsValidVcTdMapPoint(index, point_index))
	{
		if(Vc_TdMaps_Points[index][point_index][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawDestroy(Vc_TdMaps_Points[index][point_index][vc_tdmap_point_TD_DESCRIPTION]);
		TextDrawDestroy(Vc_TdMaps_Points[index][point_index][vc_tdmap_point_TD]);
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_ICON][0] = EOS;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_ICON_SIZE_X] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_ICON_SIZE_Y] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_DESCRIPTION][0] = EOS;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_X] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_Y] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_Z] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_TD_X] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_TD_Y] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_DESCR_LS_X] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_DESCR_LS_Y] = 0.0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_DESCR_OUTLINE] = 0;
		Vc_TdMaps_Points[index][point_index][vc_tdmap_point_DESCR_COLOR] = 0;
		Iter_Remove(Vc_TdMaps_Points[index], point_index);
		return 1;
	}
	return 0;
}

stock AddPointToVcTdMap(map_index, icon[], Float:x, Float:y, Float:z, Float:icon_size_x = 5.0, Float:icon_size_y = 5.0, description[] = "", Float:description_ls_x = 0.149333, Float:description_ls_y = 0.766222, description_outline = 0, description_color = -1, color = -1)
{
	if(IsValidVcTdMap(map_index))
	{
		new index = GetFreeVcTdMapPointSlot(map_index);
		if(index != cellmin)
		{
			format(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON], 64, "%s", icon);
			format(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCRIPTION], 128, "%s", description);
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_X] = icon_size_x;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_Y] = icon_size_y;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION] = Text:INVALID_TEXT_DRAW;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_X] = x;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_Y] = y;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_Z] = z;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_LS_X] = description_ls_x;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_LS_Y] = description_ls_y;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_OUTLINE] = description_outline;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_COLOR] = description_color;
			Vc_TdMaps_Points[map_index][index][vc_tdmap_point_COLOR] = color;


			Vc3dTo2d(Vc_TdMaps[map_index][vc_tdmap_X], Vc_TdMaps[map_index][vc_tdmap_Y], Vc_TdMaps[map_index][vc_tdmap_SIZE_X], Vc_TdMaps[map_index][vc_tdmap_SIZE_Y], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_X], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_Y], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_Z], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_X], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_Y]);

			if(!Vc_TdMaps[map_index][vc_tdmap_BIG])
			{
				Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD] = TextDrawCreate(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_X] - floatdiv(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_X], 2), Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_Y] - floatdiv(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_Y], 2), Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON]);
				TextDrawTextSize(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_X], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_Y]);
				TextDrawColor(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_COLOR]);
				TextDrawFont(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], 4);
			}
			else
			{
				Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD] = TextDrawCreate(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_X] - floatdiv(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_X], 2), Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_Y] - floatdiv(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_Y], 2) - 5.5, ".");
				TextDrawLetterSize(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], 0.262333, 1.110517);
				TextDrawColor(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], 0xFFFF00FF);
				TextDrawSetShadow(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], 0);
				TextDrawFont(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD], 1);
			}

			if(!isnull(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCRIPTION]))
			{
				Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION] = TextDrawCreate(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_X] + floatdiv(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_X], 2) - 2.0, Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_Y] + floatdiv(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_ICON_SIZE_Y], 2) - 2.0, Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCRIPTION]);
				TextDrawLetterSize(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_LS_X], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_LS_Y]);
				TextDrawSetShadow(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION], 0);
				TextDrawSetOutline(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_OUTLINE]);
				TextDrawColor(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION], Vc_TdMaps_Points[map_index][index][vc_tdmap_point_DESCR_COLOR]);
				TextDrawFont(Vc_TdMaps_Points[map_index][index][vc_tdmap_point_TD_DESCRIPTION], 1);
			}

			Iter_Add(Vc_TdMaps_Points[map_index], index);
			return index;
		}
		return INVALID_VC_TDMAP_ID;
	}
	return INVALID_VC_TDMAP_ID;
}

stock ShowVcTdMapForPlayer(playerid, map_index, bool:only_points = false)
{
	if(IsValidVcTdMap(map_index))
	{
		foreach(new i : Vc_TdMaps_Points[map_index])
		{
			TextDrawShowForPlayer(playerid, Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD]);
			if(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawShowForPlayer(playerid, Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION]);
		}
		if(!only_points) TextDrawShowForPlayer(playerid, Vc_TdMaps[map_index][vc_tdmap_TD]);
		return 1;
	}
	return 0;
}

stock HideVcTdMapForPlayer(playerid, map_index)
{
	if(IsValidVcTdMap(map_index))
	{
		foreach(new i : Vc_TdMaps_Points[map_index])
		{
			TextDrawHideForPlayer(playerid, Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD]);
			if(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawHideForPlayer(playerid, Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION]);
		}
		TextDrawHideForPlayer(playerid, Vc_TdMaps[map_index][vc_tdmap_TD]);
		return 1;
	}
	return 0;
}

stock ShowVcTdMapForAll(map_index, bool:only_points = false)
{
	if(IsValidVcTdMap(map_index))
	{
		foreach(new i : Vc_TdMaps_Points[map_index])
		{
			TextDrawShowForAll(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD]);
			if(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawShowForAll(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION]);
		}
		if(!only_points) TextDrawShowForAll(Vc_TdMaps[map_index][vc_tdmap_TD]);
		return 1;
	}
	return 0;
}

stock HideVcTdMapForAll(map_index)
{
	if(IsValidVcTdMap(map_index))
	{
		foreach(new i : Vc_TdMaps_Points[map_index])
		{
			TextDrawHideForAll(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD]);
			if(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawHideForAll(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION]);
		}
		TextDrawHideForAll(Vc_TdMaps[map_index][vc_tdmap_TD]);
		return 1;
	}
	return 0;
}

stock UpdateVcMapPointsForPlayer(playerid, map_index)
{
	if(IsValidVcTdMap(map_index))
	{
		foreach(new i : Vc_TdMaps_Points[map_index])
		{
			TextDrawShowForPlayer(playerid, Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD]);
			if(Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION] != Text:INVALID_TEXT_DRAW) TextDrawShowForPlayer(playerid, Vc_TdMaps_Points[map_index][i][vc_tdmap_point_TD_DESCRIPTION]);
		}
		return 1;
	}
	return 0;
}

//Player
#define MAX_VC_PTDMAPS 10
#define MAX_VC_PTDMAPS_POINTS 300

enum enum_Vc_PTdMaps
{
	PlayerText:vc_ptdmap_TD,
	Float:vc_ptdmap_X,
	Float:vc_ptdmap_Y,
	Float:vc_ptdmap_SIZE_X,
	Float:vc_ptdmap_SIZE_Y,
	bool:vc_ptdmap_BIG
};
new Vc_PTdMaps[MAX_PLAYERS][MAX_VC_PTDMAPS][enum_Vc_PTdMaps],
	Iterator:Vc_PTdMaps[MAX_PLAYERS]<MAX_VC_PTDMAPS>,
	pLastPtdMapShown[MAX_PLAYERS] = {INVALID_VC_TDMAP_ID, ...};

forward OPClickPTdMapPoint(playerid, map_index, point_index, Float:td_x, Float:td_y, Float:x, Float:y, Float:z);

enum enum_Vc_PTdMaps_Points
{
	bool:vc_ptdmap_point_VALID,
	PlayerText:vc_ptdmap_point_TD,
	PlayerText:vc_ptdmap_point_TD_DESCRIPTION,
	vc_ptdmap_point_ICON[64],
	Float:vc_ptdmap_point_ICON_SIZE_X,
	Float:vc_ptdmap_point_ICON_SIZE_Y,
	vc_ptdmap_point_DESCRIPTION[128],
	Float:vc_ptdmap_point_DESCR_LS_X,
	Float:vc_ptdmap_point_DESCR_LS_Y,
	vc_ptdmap_point_DESCR_OUTLINE,
	vc_ptdmap_point_DESCR_COLOR,
	Float:vc_ptdmap_point_X,
	Float:vc_ptdmap_point_Y,
	Float:vc_ptdmap_point_Z,
	Float:vc_ptdmap_point_TD_X,
	Float:vc_ptdmap_point_TD_Y,
	bool:vc_ptdmap_point_SELECTABLE,
	vc_ptdmap_point_COLOR
};
new Vc_PTdMaps_Points[MAX_PLAYERS][MAX_VC_PTDMAPS][MAX_VC_PTDMAPS_POINTS][enum_Vc_PTdMaps_Points];

#define GetFreeVcPTdMapSlot(%0) Iter_Free(Vc_PTdMaps[%0])
#define CountVcPTdMaps(%0) Iter_Count(Vc_PTdMaps[%0])
#define IsValidVcPTdMap(%0,%1) Iter_Contains(Vc_PTdMaps[%0],%1)
#define IsValidVcPTdMapPoint(%0,%1,%2) Vc_PTdMaps_Points[%0][%1][%2][vc_ptdmap_point_VALID]

stock GetFreeVcPTdMapPointSlot(playerid, map_index)
{
	for(new i = 0; i < MAX_VC_PTDMAPS_POINTS; i ++)
	{
		if(!Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_VALID])
		{
			return i;
		}
	}
	return cellmin;
}

stock CountVcPTdMapPoints(playerid, map_index)
{
	new c;
	for(new i = 0; i < MAX_VC_PTDMAPS; i ++)
	{
		if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_VALID]) c ++;
	}
	return c;
}

stock CreateVcPTdMap(playerid, Float:x, Float:y, Float:size_x, Float:size_y, bool:big = false)
{
	new index = GetFreeVcPTdMapSlot(playerid);
	if(index != cellmin)
	{
		Vc_PTdMaps[playerid][index][vc_ptdmap_X] = x;
		Vc_PTdMaps[playerid][index][vc_ptdmap_Y] = y;
		Vc_PTdMaps[playerid][index][vc_ptdmap_SIZE_X] = size_x;
		Vc_PTdMaps[playerid][index][vc_ptdmap_SIZE_Y] = size_y;
		Vc_PTdMaps[playerid][index][vc_ptdmap_BIG] = big;
		Vc_PTdMaps[playerid][index][vc_ptdmap_TD] = CreatePlayerTextDraw(playerid, Vc_PTdMaps[playerid][index][vc_ptdmap_X], Vc_PTdMaps[playerid][index][vc_ptdmap_Y], VC_TDMAP_PATH);
		PlayerTextDrawTextSize(playerid, Vc_PTdMaps[playerid][index][vc_ptdmap_TD], Vc_PTdMaps[playerid][index][vc_ptdmap_SIZE_X], Vc_PTdMaps[playerid][index][vc_ptdmap_SIZE_Y]);
		PlayerTextDrawFont(playerid, Vc_PTdMaps[playerid][index][vc_ptdmap_TD], 4);
		Iter_Add(Vc_PTdMaps[playerid], index);
		return index;
	}
	return INVALID_VC_TDMAP_ID;
}

stock DestroyVcPTdMaps(playerid)
{
	foreach(new i : Vc_PTdMaps[playerid])
	{
		DestroyVcPTdMapPoints(playerid, i);
		Vc_PTdMaps[playerid][i][vc_ptdmap_X] = 0.0;
		Vc_PTdMaps[playerid][i][vc_ptdmap_Y] = 0.0;
		Vc_PTdMaps[playerid][i][vc_ptdmap_SIZE_X] = 0.0;
		Vc_PTdMaps[playerid][i][vc_ptdmap_SIZE_Y] = 0.0;
		PlayerTextDrawDestroy(playerid, Vc_PTdMaps[playerid][i][vc_ptdmap_TD]);
	}
	Iter_Clear(Vc_PTdMaps[playerid]);
	return 1;
}

stock DestroyVcPTdMap(playerid, index)
{
	if(IsValidVcPTdMap(playerid, index))
	{
		DestroyVcPTdMapPoints(playerid, index);
		Vc_PTdMaps[playerid][index][vc_ptdmap_X] = 0.0;
		Vc_PTdMaps[playerid][index][vc_ptdmap_Y] = 0.0;
		Vc_PTdMaps[playerid][index][vc_ptdmap_SIZE_X] = 0.0;
		Vc_PTdMaps[playerid][index][vc_ptdmap_SIZE_Y] = 0.0;
		PlayerTextDrawDestroy(playerid, Vc_PTdMaps[playerid][index][vc_ptdmap_TD]);
		Iter_Remove(Vc_PTdMaps[playerid], index);
		return 1;
	}
	return 0;
}

stock DestroyVcPTdMapPoints(playerid, index)
{
	if(IsValidVcPTdMap(playerid, index))
	{
		for(new i = 0; i < MAX_VC_PTDMAPS_POINTS; i ++)
		{
			if(Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_VALID])
			{
				if(Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_TD_DESCRIPTION] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_TD_DESCRIPTION]);
				PlayerTextDrawDestroy(playerid, Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_TD]);
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_ICON][0] = EOS;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_ICON_SIZE_X] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_ICON_SIZE_Y] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_DESCRIPTION][0] = EOS;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_X] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_Y] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_Z] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_TD_X] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_TD_Y] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_DESCR_LS_X] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_DESCR_LS_Y] = 0.0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_DESCR_OUTLINE] = 0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_DESCR_COLOR] = 0;
				Vc_PTdMaps_Points[playerid][index][i][vc_ptdmap_point_VALID] = false;
			}
		}
		return 1;
	}
	return 0;
}

stock DestroyVcPTdMapPoint(playerid, index, point_index)
{
	if(IsValidVcPTdMap(playerid, index))
	{
		if(Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_VALID])
		{
			if(Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_TD_DESCRIPTION] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_TD_DESCRIPTION]);
			PlayerTextDrawDestroy(playerid, Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_TD]);
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_ICON][0] = EOS;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_ICON_SIZE_X] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_ICON_SIZE_Y] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_DESCRIPTION][0] = EOS;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_X] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_Y] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_Z] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_TD_X] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_TD_Y] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_DESCR_LS_X] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_DESCR_LS_Y] = 0.0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_DESCR_OUTLINE] = 0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_DESCR_COLOR] = 0;
			Vc_PTdMaps_Points[playerid][index][point_index][vc_ptdmap_point_VALID] = false;
			return 1;
		}
	}
	return 0;
}

stock AddPointToVcPTdMap(playerid, map_index, icon[], Float:x, Float:y, Float:z, Float:icon_size_x = 5.0, Float:icon_size_y = 5.0, description[] = "", Float:description_ls_x = 0.149333, Float:description_ls_y = 0.766222, description_outline = 0, description_color = -1, bool:selectable = false, bool:big = false, color = -1, bool:description_selectable = false)
{
	if(IsValidVcPTdMap(playerid, map_index))
	{
		new index = GetFreeVcPTdMapPointSlot(playerid, map_index);
		if(index != cellmin)
		{
			format(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON], 64, "%s", icon);
			format(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCRIPTION], 128, "%s", description);
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X] = icon_size_x;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y] = icon_size_y;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION] = PlayerText:INVALID_TEXT_DRAW;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_X] = x;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_Y] = y;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_Z] = z;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_LS_X] = description_ls_x;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_LS_Y] = description_ls_y;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_OUTLINE] = description_outline;
			if(description_selectable) Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_COLOR] = 0x00000000; //invisible
			else Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_COLOR] = description_color;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_SELECTABLE] = selectable;
			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_COLOR] = color;
			Vc3dTo2d(Vc_PTdMaps[playerid][map_index][vc_ptdmap_X], Vc_PTdMaps[playerid][map_index][vc_ptdmap_Y], Vc_PTdMaps[playerid][map_index][vc_ptdmap_SIZE_X], Vc_PTdMaps[playerid][map_index][vc_ptdmap_SIZE_Y], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_X], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_Y], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_Z], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_X], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_Y]);

			if(!Vc_PTdMaps[playerid][map_index][vc_ptdmap_BIG] && !big)
			{
				Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD] = CreatePlayerTextDraw(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_X] - floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], 2), Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_Y] - floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y], 2), Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON]);
				PlayerTextDrawTextSize(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y]);
				PlayerTextDrawColor(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_COLOR]);
				PlayerTextDrawFont(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], 4);
				PlayerTextDrawSetSelectable(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_SELECTABLE]);
			}
			else
			{
				Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD] = CreatePlayerTextDraw(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_X] - floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], 2), Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_Y] - floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y], 2) - 5.5, ".");
				PlayerTextDrawLetterSize(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], 0.262333, 1.110517);
				PlayerTextDrawColor(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], 0xFFFF00FF);
				PlayerTextDrawSetShadow(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], 0);
				PlayerTextDrawFont(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD], 1);				
			}

			if(!isnull(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCRIPTION]))
			{
				if(description_selectable)
				{
					new string_description[128];
					format(string_description, sizeof string_description, "_~n~____%s", Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCRIPTION]);
					Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION] = CreatePlayerTextDraw(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_X] - floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], 2), Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_Y] - (floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y], 2) - 1.0), string_description);
					PlayerTextDrawTextSize(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], (Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_X] - floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], 2)) + Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y] - 1.5);
					PlayerTextDrawSetSelectable(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], true);
				}
				else Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION] = CreatePlayerTextDraw(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_X] + floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_X], 2) - 2.0, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_Y] + floatdiv(Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_ICON_SIZE_Y], 2) - 2.0, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCRIPTION]);
				PlayerTextDrawLetterSize(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_LS_X], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_LS_Y]);
				PlayerTextDrawSetShadow(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], 0);
				PlayerTextDrawSetOutline(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_OUTLINE]);
				PlayerTextDrawColor(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_DESCR_COLOR]);
				PlayerTextDrawFont(playerid, Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_TD_DESCRIPTION], 1);
			}

			Vc_PTdMaps_Points[playerid][map_index][index][vc_ptdmap_point_VALID] = true;
			return index;
		}
	}
	return INVALID_VC_TDMAP_ID;
}

stock ShowVcPtdPointForPlayer(playerid, map_index, point_index)
{
	if(IsValidVcPTdMap(playerid, map_index))
	{
		if(IsValidVcPTdMapPoint(playerid, map_index, point_index))
		{
			PlayerTextDrawShow(playerid, Vc_PTdMaps_Points[playerid][map_index][point_index][vc_ptdmap_point_TD]);
			if(Vc_PTdMaps_Points[playerid][map_index][point_index][vc_ptdmap_point_TD_DESCRIPTION] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, Vc_PTdMaps_Points[playerid][map_index][point_index][vc_ptdmap_point_TD_DESCRIPTION]);
		}
	}
	return 0;
}

stock ShowVcPTdMapForPlayer(playerid, map_index, bool:only_points = false)
{
	if(IsValidVcPTdMap(playerid, map_index))
	{
		for(new i = 0; i < MAX_VC_PTDMAPS_POINTS; i ++)
		{
			if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_VALID])
			{
				PlayerTextDrawShow(playerid, Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD]);
				if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD_DESCRIPTION] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD_DESCRIPTION]);
			}
		}
		if(!only_points) PlayerTextDrawShow(playerid, Vc_PTdMaps[playerid][map_index][vc_ptdmap_TD]);
		pLastPtdMapShown[playerid] = map_index;
		return 1;
	}
	return 0;
}

stock HideVcPTdMapForPlayer(playerid, map_index)
{
	if(IsValidVcPTdMap(playerid, map_index))
	{
		for(new i = 0; i < MAX_VC_PTDMAPS_POINTS; i ++)
		{
			if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_VALID])
			{
				PlayerTextDrawHide(playerid, Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD]);
				if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD_DESCRIPTION] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD_DESCRIPTION]);
			}
		}
		PlayerTextDrawHide(playerid, Vc_PTdMaps[playerid][map_index][vc_ptdmap_TD]);
		return 1;
	}
	return 0;
}

stock UpdateVcPMapPointsForPlayer(playerid, map_index)
{
	if(IsValidVcPTdMap(playerid, map_index))
	{
		for(new i = 0; i < MAX_VC_PTDMAPS_POINTS; i ++)
		{
			if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_VALID])
			{
				PlayerTextDrawShow(playerid, Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD]);
				if(Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD_DESCRIPTION] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, Vc_PTdMaps_Points[playerid][map_index][i][vc_ptdmap_point_TD_DESCRIPTION]);
			}
		}
		return 1;
	}
	return 0;
}

hook OnPlayerConnect(playerid)
{
	pLastPtdMapShown[playerid] = INVALID_VC_TDMAP_ID;
	return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(IsValidVcPTdMap(playerid, pLastPtdMapShown[playerid]))
	{
		for(new i = 0; i < MAX_VC_PTDMAPS_POINTS; i ++)
		{
			if(Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_VALID])
			{
				if(Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_SELECTABLE])
				{
					if(playertextid == Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_TD])
					{
						CallRemoteFunction("OPClickPTdMapPoint", "iddfffff",
							playerid, pLastPtdMapShown[playerid], i,
							Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_TD_X], Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_TD_Y],
							Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_X], Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_Y],
							Vc_PTdMaps_Points[playerid][pLastPtdMapShown[playerid]][i][vc_ptdmap_point_Z]
						);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

//

hook OnScriptInit()
{
	print("--- vc_maptd include by adri1 loaded!");
	Iter_Init(Vc_TdMaps_Points);
	Iter_Init(Vc_PTdMaps);
	return 1;
}

stock Vc3dTo2d(Float:map_x, Float:map_y, Float:map_size_x, Float:map_size_y, Float:x, Float:y, Float:z, &Float:td_x, &Float:td_y, Float:limit_X_WEST = vc_limit_X_WEST, Float:limit_X_EAST = vc_limit_X_EAST, Float:limit_Y_NORTH = vc_limit_Y_NORTH, Float:limit_Y_SOUTH = vc_limit_Y_SOUTH)
{
	#pragma unused z

	/* Map limits */
	if(x > limit_X_EAST) x = limit_X_EAST;
	else if(x < limit_X_WEST) x = limit_X_WEST;

	if(y > limit_Y_NORTH) y = limit_Y_NORTH;
	else if(y < limit_Y_SOUTH) y = limit_Y_SOUTH;

	/* Calculations */
	new Float:map_width = floatsub(limit_X_EAST, limit_X_WEST),
		Float:prop_X = floatdiv(map_size_x, map_width),
		Float:mv_X = floatsub(map_width, limit_X_EAST);

	new Float:map_height = floatsub(limit_Y_SOUTH, limit_Y_NORTH),
		Float:prop_Y = floatdiv(map_size_y, map_height),
		Float:mv_Y = floatsub(map_height, limit_Y_SOUTH);
	
	/* Conversion */
	x += mv_X;
	y += mv_Y;

	/* Result */
	td_x = map_x + floatmul(prop_X, x),
	td_y = map_y + floatmul(prop_Y, y);
	return 1;
}

stock Vc2dTo3d(Float:map_size_x, Float:map_size_y, Float:x, Float:y, &Float:pos_x, &Float:pos_y)
{
	/* Map limits */
	if(x > map_size_x) x = map_size_x;
	else if(x < 0) x = 0;

	if(y > map_size_y) y = map_size_y;
	else if(y < 0) y = 0;

	/* Calculations */
	new Float:map_width = floatsub(vc_limit_X_EAST, vc_limit_X_WEST);
	pos_x = vc_limit_X_WEST + ((map_width / map_size_x) * x);

	new Float:map_height = floatsub(vc_limit_Y_SOUTH, vc_limit_Y_NORTH);
	pos_y = vc_limit_Y_NORTH + ((map_height / map_size_y) * y);
	return 1;
}