#define IsPlayerInRoute(%0) pInRoute[%0]

StartRoute(playerid)
{
	if(GetPlayerRouteTotalCP(playerid) > 0)
	{
		pInRoute[playerid] = true;
		if(GetPlayerRouteTotalCP(playerid) > 1)
		{
			if(pRoute_ProgressBar[playerid] == INVALID_PROGRESS_BAR_ID)
			{
				pRoute_ProgressBar[playerid] = CreatePlayerProgressBar(playerid, 280.0, 420.0, 80.0, 4.0, -1966081, -545062913);
			}
			if(pRoute_Percentage_TD[playerid] == PlayerText:INVALID_TEXT_DRAW)
			{
				pRoute_Percentage_TD[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 408.000000, "0%");
				PlayerTextDrawLetterSize(playerid, pRoute_Percentage_TD[playerid], 0.207666, 0.977778);
				PlayerTextDrawAlignment(playerid, pRoute_Percentage_TD[playerid], 2);
				PlayerTextDrawColor(playerid, pRoute_Percentage_TD[playerid], -1);
				PlayerTextDrawSetShadow(playerid, pRoute_Percentage_TD[playerid], 0);
				PlayerTextDrawBackgroundColor(playerid, pRoute_Percentage_TD[playerid], 255);
				PlayerTextDrawFont(playerid, pRoute_Percentage_TD[playerid], 1);
				PlayerTextDrawSetProportional(playerid, pRoute_Percentage_TD[playerid], 1);
			}
			PlayerTextDrawShow(playerid, pRoute_Percentage_TD[playerid]);
			ShowPlayerProgressBar(playerid, pRoute_ProgressBar[playerid]);
		}
		if(pRoute_Timer[playerid] == Timer:-1)
		{
			pRoute_Timer[playerid] = repeat OnPlayerRouteUpdate(playerid);
		}
		SetPlayerRouteCps(playerid);
		return 1;
	}
	return 0;
}

DestroyPlayerRoute(playerid, type = 0)
{
	pInRoute[playerid] = false;
	if(pRoute_Timer[playerid] != Timer:-1)
	{
		stop pRoute_Timer[playerid];
		pRoute_Timer[playerid] = Timer:-1;
	}
	if(pRoute_ProgressBar[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, pRoute_ProgressBar[playerid]);
		pRoute_ProgressBar[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	if(pRoute_Percentage_TD[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pRoute_Percentage_TD[playerid]);
		pRoute_Percentage_TD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	ResetPlayerRoute(playerid, type);
	return 1;
}

ShowPlayerRoute(playerid)
{
	if(pInRoute[playerid])
	{
		if(pRoute_ProgressBar[playerid] != INVALID_PROGRESS_BAR_ID) ShowPlayerProgressBar(playerid, pRoute_ProgressBar[playerid]);
		if(pRoute_Percentage_TD[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, pRoute_Percentage_TD[playerid]);
		SetPlayerRouteCps(playerid);

		if(pRoute_Timer[playerid] == Timer:-1)
		{
			pRoute_Timer[playerid] = repeat OnPlayerRouteUpdate(playerid);
		}
		return 1;
	}
	return 0;
}

HidePlayerRoute(playerid, bool:only_tds = false)
{
	if(pInRoute[playerid])
	{
		if(pRoute_ProgressBar[playerid] != INVALID_PROGRESS_BAR_ID) HidePlayerProgressBar(playerid, pRoute_ProgressBar[playerid]);
		if(pRoute_Percentage_TD[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, pRoute_Percentage_TD[playerid]);
		if(!only_tds) DestroyPlayerRouteCps(playerid);

		if(pRoute_Timer[playerid] != Timer:-1)
		{
			stop pRoute_Timer[playerid];
			pRoute_Timer[playerid] = Timer:-1;
		}
		return 1;
	}
	return 0;
}

CalcRoute(playerid, Float:x, Float:y, Float:z, bool:gps = false)
{
	new	MapNode:from_node, MapNode:to_node,
		Float:pos[3], Float:angle, interiorid, worldid;

	GetPlayerExteriorPos(playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid);
	GetClosestMapNodeToPoint(pos[0], pos[1], pos[2], from_node);
	GetClosestMapNodeToPoint(x, y, z, to_node);
	if(IsValidMapNode(from_node) && IsValidMapNode(to_node))
	{
		FindPathThreaded(from_node, to_node, "OnPlayerRouteCalculated", "ifffd", playerid, x, y, z, gps);
		return 1;
	}
	return 0;
}