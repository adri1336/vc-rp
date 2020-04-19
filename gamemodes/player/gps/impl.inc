#include <YSI\y_hooks>

loadtext lang[gps];

hook OnScriptInit()
{
	Iter_Init(Player_Gps_Cats);
	for(new i = 0; i < MAX_PLAYERS; i ++)
	{
		for(new j = 0; j < sizeof GPS_Options_PTD[]; j ++)
		{
			GPS_Options_PTD[i][j][gps_option_ICON] = PlayerText:INVALID_TEXT_DRAW;
			GPS_Options_PTD[i][j][gps_option_TICK] = PlayerText:INVALID_TEXT_DRAW;
			GPS_Options_PTD[i][j][gps_option_TEXT] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;	
}

hook OnPlayerConnect(playerid)
{
	pGps[playerid] = false;
	for(new i = 0; i < sizeof Player_Gps_Cats[]; i ++) Player_Gps_Cats[playerid][i] = false;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerGpsTextdraws(playerid);
	if(pGpsCircle[playerid] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(pGpsCircle[playerid]);
		pGpsCircle[playerid] = INVALID_STREAMER_ID;
	}
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pGps[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			HidePlayerGps(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pGps[playerid])
	{
		if(playertextid == GPS_Body_PTD[playerid][1])
		{
			CancelSelectTextDraw(playerid);
			PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
			return 1;
		}
		else
		{
			if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_MINIMAP][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_MINIMAP] = !PI[playerid][pi_GPS_MINIMAP];
				if(PI[playerid][pi_GPS_MINIMAP])
				{
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					EnablePlayerRadar(playerid);
				}
				else
				{
					PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
					DisablePlayerRadar(playerid);
				}
				CallRemoteFunction("OnPlayerToggleMinimap", "ib", playerid, PI[playerid][pi_GPS_MINIMAP]);
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_LOCATION][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_LOCATION] = !PI[playerid][pi_GPS_LOCATION];
				if(PI[playerid][pi_GPS_LOCATION]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				RecreateGpsMap(playerid);
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_ROUTE][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_ROUTE] = !PI[playerid][pi_GPS_ROUTE];
				if(PI[playerid][pi_GPS_ROUTE]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				RecreateGpsMap(playerid);
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_CANCEL_ROUTE][gps_option_TEXT])
			{
				if(IsPlayerInRoute(playerid))
				{
					if(pInDrivingSchoolVehicleTest[playerid])
					{
						Text_Send(playerid, $MESSAGE_ERROR_DS_ROUTE);
						PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
					}
					else
					{
						Text_Send(playerid, $MESSAGE_INFO_ROUTE_CANCELED);
						DestroyPlayerRoute(playerid);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						RecreateGpsMap(playerid);
					}
				}
				else
				{
					Text_Send(playerid, $MESSAGE_ERROR_NO_ROUTE);
					PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				}
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_OBJECTIVES][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_OBJECTIVES] = !PI[playerid][pi_GPS_OBJECTIVES];
				if(PI[playerid][pi_GPS_OBJECTIVES]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				RecreateGpsMap(playerid);
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_PROPERTIES][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_PROPERTIES] = !PI[playerid][pi_GPS_PROPERTIES];
				if(PI[playerid][pi_GPS_PROPERTIES]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				RecreateGpsMap(playerid);
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_BUSINESS][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_BUSINESS] = !PI[playerid][pi_GPS_BUSINESS];
				if(PI[playerid][pi_GPS_BUSINESS]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				RecreateGpsMap(playerid);
			}
			else if(playertextid == GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_VEHICLES][gps_option_TEXT])
			{
				PI[playerid][pi_GPS_VEHICLES] = !PI[playerid][pi_GPS_VEHICLES];
				if(PI[playerid][pi_GPS_VEHICLES]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
				RecreateGpsMap(playerid);
			}
			else
			{
				//cats
				for(new i = _:GPS_OPTION_CATEGORY_DB; i < sizeof GPS_Options_PTD[]; i ++)
				{
					if(playertextid == GPS_Options_PTD[playerid][i][gps_option_TEXT])
					{
						new cat_index = i - _:GPS_OPTION_CATEGORY_DB;
						Player_Gps_Cats[playerid][cat_index] = !Player_Gps_Cats[playerid][cat_index];
						if(Player_Gps_Cats[playerid][cat_index]) PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						else PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
						RecreateGpsMap(playerid);
						break;
					}
				}
			}
			UpdatePlayerGpsTicks(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pGps[playerid]) CancelSelectTextDraw(playerid);
	return 1;
}

hook OnPlayerLoadScreenFin(playerid)
{
	if(PI[playerid][pi_GPS_MINIMAP] && !pRadarEnabled[playerid]) EnablePlayerRadar(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(PI[playerid][pi_GPS_MINIMAP])
	{
		/*if(newstate == PLAYER_STATE_SPAWNED)
		{
			if(pFirstSpawn_GpsFix[playerid]) pFirstSpawn_GpsFix[playerid] = false;
			else
			{
				if(!pRadarEnabled[playerid]) EnablePlayerRadar(playerid);
			}
		}
		else */
		if(newstate == PLAYER_STATE_SPECTATING || newstate == PLAYER_STATE_WASTED)
		{
			if(pRadarEnabled[playerid]) DisablePlayerRadar(playerid);
			if(pGpsCircle[playerid] != INVALID_STREAMER_ID)
			{
				DestroyDynamicArea(pGpsCircle[playerid]);
				pGpsCircle[playerid] = INVALID_STREAMER_ID;
			}
		}
	}
	return 1;
}

hook OnPlayerLogin(playerid)
{
	new Float:result_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, PLAYER_GPS_ICON_MAP_SIZE, false, result_x, pIconMapSize[playerid]);
	LoadPlayerGpsCats(playerid);
	return 1;
}

YCMD:gps(playerid, params[], help)
{
	if(PlayerInvContainsItemType(playerid, _:INV_ITEM_TYPE_GPS))
	{
		if(pGps[playerid]) CancelSelectTextDraw(playerid);
		else
		{
			if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_SIGNAL);
			else ShowPlayerGps(playerid);
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_NO_GPS);
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(itemid == _:INV_ITEM_GPS)
	{
		if(PI[playerid][pi_GPS_MINIMAP] && pRadarEnabled[playerid]) DisablePlayerRadar(playerid);
		PI[playerid][pi_GPS_MINIMAP] = false;
	}
	return 1;
}

hook OPClickPTdMapPoint(playerid, map_index, point_index, Float:td_x, Float:td_y, Float:x, Float:y, Float:z)
{
	if(IsPlayerInRoute(playerid))
	{
		Text_Send(playerid, $MESSAGE_ERROR_ROUTE_EXISTS);
		PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
	}
	else
	{
		inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
		{
			#pragma unused pid, dialogid, listitem, inputtext
			if(response)
			{
				if(pGpsAutopilotVehicle[playerid] != INVALID_VEHICLE_ID)
				{
					AutoPilotVehicleGoTo(playerid, pGpsAutopilotVehicle[playerid], x, y, z);
					CancelSelectTextDraw(playerid);
				}
				else
				{
					DestroyPlayerRoute(playerid, 1);
					if(CalcRoute(playerid, x, y, z, true))
					{
						Text_Send(playerid, $MESSAGE_INFO_ROUTE);
					}
					else
					{
						Text_Send(playerid, $MESSAGE_ERROR_ROUTE);
						PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
					}
				}
			}
		}
		Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_CREATE_ROUTE_CAPTION, $DIALOG_CREATE_ROUTE_BODY, $DIALOG_CREATE_ROUTE_YES, $DIALOG_CREATE_ROUTE_NO);
	}
	return 1;
}

hook OnPlayerRouteFinish(playerid)
{
	if(!pInDrivingSchoolVehicleTest[playerid])
	{
		if(pGpsCircle[playerid] != INVALID_STREAMER_ID)
		{
			DestroyDynamicArea(pGpsCircle[playerid]);
			pGpsCircle[playerid] = INVALID_STREAMER_ID;
		}
		DestroyPlayerRoute(playerid);
		Text_Send(playerid, $GAMETEXT_INFO_ROUTE_FINISH);
		PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if(pGpsCircle[playerid] != INVALID_STREAMER_ID && pGpsCircle[playerid] == areaid)
	{
		DestroyDynamicArea(pGpsCircle[playerid]);
		pGpsCircle[playerid] = INVALID_STREAMER_ID;
		DestroyPlayerRoute(playerid);
		Text_Send(playerid, $GAMETEXT_INFO_ROUTE_FINISH);
		PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	}
	return 1;
}

public OnPlayerRouteCalculated(Path:pathid, playerid, Float:destX, Float:destY, Float:destZ, bool:gps)
{
	new size, lastAddedIndex = -1, currentIndex = -1, Float:lastAngle;
	GetPathSize(pathid, size);
	for(new i = 0; i < size; i ++)
	{
		new MapNode:currentNode;
		GetPathNode(pathid, i, currentNode);
		currentIndex = GetVcNodeIndexFromNodeId(currentNode);
		if(currentIndex != -1)
		{
			//distancia minima entre cps
			if(lastAddedIndex != -1)
			{
				new Float:distance;
				GetDistanceBetweenMapNodes(VC_Nodes[currentIndex][vcNode_MapNodeID], VC_Nodes[lastAddedIndex][vcNode_MapNodeID], distance);
				if(distance < 100.0)
				{
					continue;
				}
			}

			//obtener angulo entre nodos
			new Float:angle;
			if(size > i + 1)
			{
				new MapNode:nextNode;
				GetPathNode(pathid, i + 1, nextNode);
				GetAngleBetweenMapNodes(VC_Nodes[currentIndex][vcNode_MapNodeID], nextNode, angle);
			}
			else
			{
				new MapNode:prevNode;
				GetPathNode(pathid, i - 1, prevNode);
				GetAngleBetweenMapNodes(VC_Nodes[currentIndex][vcNode_MapNodeID], prevNode, angle);
			}
			if(lastAddedIndex == -1) lastAngle = angle;

			//al lado derecho de la calzada
			if(floatabs(angle - lastAngle) >= 60.0)
			{
				lastAngle = angle;
				continue;
			}
			lastAngle = angle;
			angle -= 180.0;

			//calcular posicion cp
			new Float:cpX, Float:cpY, Float:cpZ;
			cpX = VC_Nodes[currentIndex][vcNode_X];
			cpY = VC_Nodes[currentIndex][vcNode_Y];
			cpZ = VC_Nodes[currentIndex][vcNode_Z];
			cpX += (VC_Nodes[currentIndex][vcNode_Median] + 2.5) * floatsin(-angle, degrees);
			cpY += (VC_Nodes[currentIndex][vcNode_Median] + 2.5) * floatcos(-angle, degrees);
			AddRouteCp(playerid, cpX, cpY, cpZ, 5.0);

			lastAddedIndex = currentIndex;
		}
	}

	///////////////////////////////////////////////////////////
	AddRouteCp(playerid, destX, destY, destZ, 3.0);

	//////cilindro 
	if(gps)
	{
		if(pGpsCircle[playerid] != INVALID_STREAMER_ID)
		{
			DestroyDynamicArea(pGpsCircle[playerid]);
			pGpsCircle[playerid] = INVALID_STREAMER_ID;
		}
		pGpsCircle[playerid] = CreateDynamicCircle(destX, destY, 20.0, .playerid = playerid);
		Streamer_SetIntData(STREAMER_TYPE_AREA, pGpsCircle[playerid], E_STREAMER_EXTRA_ID, _:AREA_TYPE_GPS_CIRCLE);
	}

	StartRoute(playerid);
	if(pGps[playerid])
	{
		HidePlayerRoute(playerid, true);
		RecreateGpsMap(playerid);
	}
	PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	CallRemoteFunction("OnPlayerGpsRouteCalc", "id", playerid, gps);
	DestroyPath(pathid);
	return 1;
}