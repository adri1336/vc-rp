#include <YSI\y_hooks>

loadtext lang[minimap];

hook OnPlayerConnect(playerid)
{
	pRadarArea[playerid] = 0;
	pRadarEnabled[playerid] = false;
	pWasInRoute[playerid] = false;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	DisablePlayerRadar(playerid);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if(GetPlayerInterior(playerid) == 0 && (PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_STREET || PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_OTHER))
	{
		new streamer_info[2];
		Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
		if(streamer_info[0] == _:AREA_TYPE_RADAR)
		{
			if(streamer_info[1])
			{
				pRadarArea[playerid] = streamer_info[1];
				if(pRadarEnabled[playerid])
				{
					new td_str[64];
					format(td_str, sizeof td_str, ""RADAR_TEXTDRAW_CUSTOM_PATH"%d", pRadarArea[playerid]);
					PlayerTextDrawSetString(playerid, pRadarTextdraws[playerid][1], td_str);

					if(pRadarArea[playerid] == 0) PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], 0x95CAFCFF);
					else PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], -1);
					PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][1]);

					RecreatePlayerRadarPoints(playerid);
					RecreatePlayerRadarRoute(playerid);
					RecreatePlayerRadarMapIcons(playerid);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	if(GetPlayerInterior(playerid) == 0 && (PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_STREET || PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_OTHER))
	{
		new streamer_info[2];
		Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
		if(streamer_info[0] == _:AREA_TYPE_RADAR)
		{
			if(streamer_info[1] == 0)
			{
				pRadarArea[playerid] = streamer_info[1];
				if(pRadarEnabled[playerid])
				{
					new td_str[64];
					format(td_str, sizeof td_str, ""RADAR_TEXTDRAW_CUSTOM_PATH"%d", pRadarArea[playerid]);
					PlayerTextDrawSetString(playerid, pRadarTextdraws[playerid][1], td_str);
					
					if(pRadarArea[playerid] == 0) PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], 0x95CAFCFF);
					else PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], -1);
					PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][1]);

					RecreatePlayerRadarPoints(playerid);
					RecreatePlayerRadarRoute(playerid);
					RecreatePlayerRadarMapIcons(playerid);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerZoneChange(playerid, oldzone, newzone)
{
	if(pRadarEnabled[playerid])
	{
		new zone_name[64];
		if(newzone == INVALID_ZONE_ID && pRadarArea[playerid] == 0)
		{
			Text_Format_TD(zone_name, sizeof zone_name, PI[playerid][pi_LANG_ID], $TEXTDRAW_NO_SIGNAL);
			PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], 0x1E1E1EFF);
			PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][1]);
		}
		else
		{
			format(zone_name, sizeof zone_name, "%s", GetZoneName(newzone));
			if(pRadarArea[playerid] == 0) PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], 0x95CAFCFF);
			else PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], -1);
			PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][1]);
		}

		new Float:letter_x = GetTdTextFontX(1, zone_name, true, 0.0, 90.0);
		if(letter_x > 0.241666) letter_x = 0.241666;
		PlayerTextDrawSetString(playerid, pRadarTextdraws[playerid][3], zone_name);
		PlayerTextDrawLetterSize(playerid, pRadarTextdraws[playerid][3], letter_x, RADAR_LSIZE_Y_SITE);
		PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][3]);
	}
	return 1;
}

timer OnPlayerRadarUpdate[RADAR_UPDATE_INTERVAL](playerid)
{
	if(pRadarEnabled[playerid])
	{
		RecreatePlayerRadarPoints(playerid);
		if(IsPlayerInRoute(playerid))
		{
			if(!pWasInRoute[playerid])
			{
				DestroyPlayerRadarMapIcons(playerid);
				RecreatePlayerRadarRoute(playerid);
				RecreatePlayerRadarMapIcons(playerid);
				pWasInRoute[playerid] = true;
			}
			else RecreatePlayerRadarRoute(playerid);
		}
		else
		{
			if(pWasInRoute[playerid])
			{
				DestroyPlayerRadarRoute(playerid);
				pWasInRoute[playerid] = false;
			}
		}
	}
	else DisablePlayerRadar(playerid);
}

hook OnPlayerRouteFinish(playerid)
{
	DestroyPlayerRadarRoute(playerid);
	return 1;
}

hook OnPlayerCloseGps(playerid)
{
	if(pRadarEnabled[playerid])
	{
		RecreatePlayerRadarPoints(playerid);
		RecreatePlayerRadarRoute(playerid);
		RecreatePlayerRadarMapIcons(playerid);
	}
	return 1;
}