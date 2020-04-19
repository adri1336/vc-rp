loadtext lang[minimap];

DestroyPlayerRadarTds(playerid)
{
	for(new i, j = sizeof pRadarTextdraws[]; i != j; i ++)
	{
		if(pRadarTextdraws[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pRadarTextdraws[playerid][i]);
			pRadarTextdraws[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	DestroyPlayerRadarMapIcons(playerid);
	DestroyPlayerRadarRoute(playerid);
	DestroyPlayerRadarVehicles(playerid);
	DestroyPlayerRadarObjectives(playerid);
	return 1;
}

CreatePlayerRadarTds(playerid)
{
	new Float:result_x, Float:result_size_x, Float:result_x2, Float:result_size_x2;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], RADAR_POS_X, RADAR_SIZE_X, true, result_x, result_size_x);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, RADAR_SEPARATION, false, result_x2, result_size_x2);
	pRadarTextdraws[playerid][0] = CreatePlayerTextDraw(playerid, result_x, RADAR_POS_Y, "LD_SPAC:white");

	PlayerTextDrawTextSize(playerid, pRadarTextdraws[playerid][0], result_size_x, RADAR_SIZE_Y_SITE + RADAR_SIZE_Y + (result_size_x2 * 2));
	PlayerTextDrawAlignment(playerid, pRadarTextdraws[playerid][0], 1);
	PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, pRadarTextdraws[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, pRadarTextdraws[playerid][0], 255);
	PlayerTextDrawFont(playerid, pRadarTextdraws[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, pRadarTextdraws[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, pRadarTextdraws[playerid][0], LAYER_RADAR);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], RADAR_POS_X, RADAR_SIZE_X - (result_size_x2 * 2), true, result_x, result_size_x);	
	pRadarPosInfo[playerid][0] = result_x;
	pRadarPosInfo[playerid][1] = RADAR_POS_Y + RADAR_SIZE_Y_SITE + result_size_x2;
	pRadarPosInfo[playerid][2] = result_size_x;
	pRadarPosInfo[playerid][3] = RADAR_SIZE_Y;

	new td_str[64];
	format(td_str, sizeof td_str, ""RADAR_TEXTDRAW_CUSTOM_PATH"%d", pRadarArea[playerid]);
	pRadarTextdraws[playerid][1] = CreatePlayerTextDraw(playerid, pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], td_str);
	PlayerTextDrawTextSize(playerid, pRadarTextdraws[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3]);
	PlayerTextDrawAlignment(playerid, pRadarTextdraws[playerid][1], 1);

	if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0) PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], 0x1E1E1EFF);
	else
	{
		if(pRadarArea[playerid] == 0) PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], 0x95CAFCFF);
		else PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][1], -1);
	}

	PlayerTextDrawSetShadow(playerid, pRadarTextdraws[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, pRadarTextdraws[playerid][1], 255);
	PlayerTextDrawFont(playerid, pRadarTextdraws[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, pRadarTextdraws[playerid][1], 0);
	SetPlayerTextDrawLayer(playerid, pRadarTextdraws[playerid][1], LAYER_RADAR);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, RADAR_POINT_SIZE, false, result_x, pRadarPosInfo[playerid][4]);	
	pRadarTextdraws[playerid][2] = CreatePlayerTextDraw(playerid, pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], ""TEXTDRAW_CUSTOM_PATH"location_icon", true);
	PlayerTextDrawTextSize(playerid, pRadarTextdraws[playerid][2], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
	PlayerTextDrawFont(playerid, pRadarTextdraws[playerid][2], 4);
	SetPlayerTextDrawLayer(playerid, pRadarTextdraws[playerid][2], LAYER_RADAR);

	new Float:result_y = RADAR_POS_Y + ((RADAR_SIZE_Y_SITE + result_size_x2) / 2) - ((RADAR_LSIZE_Y_SITE * 10.0) / 2);
	pRadarTextdraws[playerid][3] = CreatePlayerTextDraw(playerid, 70.000000, result_y, "_");

	if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0) { PlayerTD_Text(playerid, pRadarTextdraws[playerid][3], $TEXTDRAW_NO_SIGNAL); }
	else PlayerTextDrawSetString(playerid, pRadarTextdraws[playerid][3], GetPlayerZoneName(playerid));

	PlayerTextDrawLetterSize(playerid, pRadarTextdraws[playerid][3], 0.241666, RADAR_LSIZE_Y_SITE);
	PlayerTextDrawTextSize(playerid, pRadarTextdraws[playerid][3], 0.000000, 90.0);
	PlayerTextDrawAlignment(playerid, pRadarTextdraws[playerid][3], 2);
	PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, pRadarTextdraws[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, pRadarTextdraws[playerid][3], 255);
	PlayerTextDrawFont(playerid, pRadarTextdraws[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, pRadarTextdraws[playerid][3], 1);
	SetPlayerTextDrawLayer(playerid, pRadarTextdraws[playerid][3], LAYER_RADAR);
	return 1;
}

ShowPlayerRadarTds(playerid)
{
	for(new i, j = sizeof pRadarTextdraws[]; i != j; i ++)
	{
		if(pRadarTextdraws[playerid][i] != PlayerText:INVALID_TEXT_DRAW)	
		PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][i]);
	}
	return 1;
}

EnablePlayerRadar(playerid)
{
	CreatePlayerRadarTds(playerid);
	ShowPlayerRadarTds(playerid);
	RecreatePlayerRadarPoints(playerid);
	RecreatePlayerRadarRoute(playerid);
	RecreatePlayerRadarMapIcons(playerid);
	pRadarTimer[playerid] = repeat OnPlayerRadarUpdate(playerid);
	pRadarEnabled[playerid] = true;
	pWasInRoute[playerid] = false;
	return 1;
}

DisablePlayerRadar(playerid)
{
	pRadarEnabled[playerid] = false;
	DestroyPlayerRadarTds(playerid);
	if(pRadarTimer[playerid] != Timer:-1)
	{
		stop pRadarTimer[playerid];
		pRadarTimer[playerid] = Timer:-1;
	}
	return 1;
}

IsValidRadarArea(area)
{
	if(area >= 0 && area < sizeof radarAreas) return true;
	else return false;
}

RecreatePlayerRadarPoints(playerid)
{
	new area = pRadarArea[playerid] - 1,
		valid_area = IsValidRadarArea(area);
	if(PI[playerid][pi_GPS_LOCATION])
	{
		if(pRadarTextdraws[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pRadarTextdraws[playerid][2]);
			pRadarTextdraws[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(valid_area)
		{
			new Float:td_x, Float:td_y, Float:pos[3], Float:angle, interiorid, worldid;
			if(pInDrivingSchoolVehicleTest[playerid]) GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			else GetPlayerExteriorPos(playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid, .radar = true);
			Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], pos[0], pos[1], pos[2], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

			new Float:xangle;
			if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), xangle);
			else GetPlayerFacingAngle(playerid, xangle);
			pRadarTextdraws[playerid][2] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 2.0), td_y - (RADAR_POINT_SIZE / 2.0), GetIconNameByAngle(xangle), true);
			PlayerTextDrawTextSize(playerid, pRadarTextdraws[playerid][2], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
			PlayerTextDrawFont(playerid, pRadarTextdraws[playerid][2], 4);
			PlayerTextDrawColor(playerid, pRadarTextdraws[playerid][2], 0xCCCCCCFF);
			SetPlayerTextDrawLayer(playerid, pRadarTextdraws[playerid][2], LAYER_RADAR);
			PlayerTextDrawShow(playerid, pRadarTextdraws[playerid][2]);
		}
	}
	if(PI[playerid][pi_GPS_VEHICLES])
	{
		new td_count;
		DestroyPlayerRadarVehicles(playerid);
		if(valid_area)
		{
			foreach(new i : PlayerVehicles[playerid])
			{
				if(VehicleInfo[i][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID && GetPlayerVehicleID(playerid) != VehicleInfo[i][vinfo_VEHICLE_ID])
				{
					if(VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_JOB && pLastVehicleIndex[playerid] != i)
					continue;
				
					new Float:pos[3];
					GetVehiclePos(VehicleInfo[i][vinfo_VEHICLE_ID], pos[0], pos[1], pos[2]);
					if(IsPointInDynamicArea(radarAreas[area], pos[0], pos[1], pos[2]))
					{
						if(td_count >= MAX_PLAYER_VEHICLES) break;
						new Float:td_x, Float:td_y;
						Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], pos[0], pos[1], pos[2], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

						pRadarVehicles_PTD[playerid][td_count] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 2.0), td_y - (RADAR_POINT_SIZE / 2.0), GetVehicleModelIcon(VehicleInfo[i][vinfo_MODELID]), true);
						PlayerTextDrawTextSize(playerid, pRadarVehicles_PTD[playerid][td_count], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
						PlayerTextDrawColor(playerid, pRadarVehicles_PTD[playerid][td_count], GetPlayerVehicleIconColor(playerid, i));
						PlayerTextDrawFont(playerid, pRadarVehicles_PTD[playerid][td_count], 4);
						SetPlayerTextDrawLayer(playerid, pRadarVehicles_PTD[playerid][td_count], LAYER_RADAR);
						PlayerTextDrawShow(playerid, pRadarVehicles_PTD[playerid][td_count]);
						td_count ++;
					}
				}
			}
		}
	}
	if(PI[playerid][pi_GPS_OBJECTIVES])
	{
		new td_count, objective_color = GetPlayerObjectiveColor(playerid);
		switch(GetPlayerJobId(playerid))
		{
			case JOB_TAXI:
			{
				DestroyPlayerRadarObjectives(playerid);
				if(valid_area)
				{
					foreach(new i : Player)
					{
						if(pTaxiRequested[i])
						{
							new Float:pos[3], Float:angle, interiorid, worldid;
							GetPlayerExteriorPos(i, pos[0], pos[1], pos[2], angle, interiorid, worldid, .radar = true);
							if(IsPointInDynamicArea(radarAreas[area], pos[0], pos[1], pos[2]))
							{
								if(td_count >= MAX_OBJECTIVES_IN_RADAR) break;
								new Float:td_x, Float:td_y;
								Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], pos[0], pos[1], pos[2], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

								pRadarObjectives_PTD[playerid][td_count] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 4.0), td_y - (RADAR_POINT_SIZE / 4.0), ""TEXTDRAW_CUSTOM_PATH"icon_pos", true);
								PlayerTextDrawTextSize(playerid, pRadarObjectives_PTD[playerid][td_count], pRadarPosInfo[playerid][4] / 2.0, RADAR_POINT_SIZE / 2.0);
								PlayerTextDrawFont(playerid, pRadarObjectives_PTD[playerid][td_count], 4);
								PlayerTextDrawColor(playerid, pRadarObjectives_PTD[playerid][td_count], objective_color);
								SetPlayerTextDrawLayer(playerid, pRadarObjectives_PTD[playerid][td_count], LAYER_RADAR);
								PlayerTextDrawShow(playerid, pRadarObjectives_PTD[playerid][td_count]);
								td_count ++;
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

DestroyPlayerRadarMapIcons(playerid)
{
	for(new i = 0; i < sizeof pRadarMapIcons_PTD[]; i ++)
	{
		if(pRadarMapIcons_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pRadarMapIcons_PTD[playerid][i]);
			pRadarMapIcons_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

DestroyPlayerRadarVehicles(playerid)
{
	for(new i = 0; i < sizeof pRadarVehicles_PTD[]; i ++)
	{
		if(pRadarVehicles_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pRadarVehicles_PTD[playerid][i]);
			pRadarVehicles_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

DestroyPlayerRadarObjectives(playerid)
{
	for(new i = 0; i < sizeof pRadarObjectives_PTD[]; i ++)
	{
		if(pRadarObjectives_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pRadarObjectives_PTD[playerid][i]);
			pRadarObjectives_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

RecreatePlayerRadarMapIcons(playerid)
{
	new area = pRadarArea[playerid] - 1,
		valid_area = IsValidRadarArea(area);
	DestroyPlayerRadarMapIcons(playerid);
	if(valid_area)
	{
		new td_count;
		//properties
		if(PI[playerid][pi_GPS_PROPERTIES])
		{
			foreach(new i : PlayerProperties<playerid>)
			{
				if(Iter_Contains(PropertyDoor[i], 0))
				{
					if(IsPointInDynamicArea(radarAreas[area], PropertyDoor[i][0][prop_door_EXT_X], PropertyDoor[i][0][prop_door_EXT_Y], PropertyDoor[i][0][prop_door_EXT_Z]))
					{
						if(td_count >= MAX_RADAR_MAPICONS) break;
						new Float:td_x, Float:td_y;
						Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], PropertyDoor[i][0][prop_door_EXT_X], PropertyDoor[i][0][prop_door_EXT_Y], PropertyDoor[i][0][prop_door_EXT_Z], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

						pRadarMapIcons_PTD[playerid][td_count] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 2.0), td_y - (RADAR_POINT_SIZE / 2.0), "hud:radar_propertyg", true);
						PlayerTextDrawTextSize(playerid, pRadarMapIcons_PTD[playerid][td_count], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
						PlayerTextDrawFont(playerid, pRadarMapIcons_PTD[playerid][td_count], 4);
						SetPlayerTextDrawLayer(playerid, pRadarMapIcons_PTD[playerid][td_count], LAYER_RADAR);
						PlayerTextDrawShow(playerid, pRadarMapIcons_PTD[playerid][td_count]);
						td_count ++;
					}
				}
			}
		}
		//business
		if(PI[playerid][pi_GPS_BUSINESS])
		{
			foreach(new i : PlayerBusiness<playerid>)
			{
				if(Iter_Contains(BusinessDoors[i], 0))
				{
					if(IsPointInDynamicArea(radarAreas[area], BusinessDoors[i][0][bdoor_EXT_X], BusinessDoors[i][0][bdoor_EXT_Y], BusinessDoors[i][0][bdoor_EXT_Z]))
					{
						if(td_count >= MAX_RADAR_MAPICONS) break;
						new Float:td_x, Float:td_y;
						Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], BusinessDoors[i][0][bdoor_EXT_X], BusinessDoors[i][0][bdoor_EXT_Y], BusinessDoors[i][0][bdoor_EXT_Z], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

						pRadarMapIcons_PTD[playerid][td_count] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 2.0), td_y - (RADAR_POINT_SIZE / 2.0), ""TEXTDRAW_CUSTOM_PATH"radar_propertyb", true);
						PlayerTextDrawTextSize(playerid, pRadarMapIcons_PTD[playerid][td_count], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
						PlayerTextDrawFont(playerid, pRadarMapIcons_PTD[playerid][td_count], 4);
						SetPlayerTextDrawLayer(playerid, pRadarMapIcons_PTD[playerid][td_count], LAYER_RADAR);
						PlayerTextDrawShow(playerid, pRadarMapIcons_PTD[playerid][td_count]);
						td_count ++;
					}
				}
			}
		}
		//cats
		foreach(new i : GPS_Cat)
		{
			if(Player_Gps_Cats[playerid][i])
			{
				foreach(new j : GPS_Sites[i])
				{
					if(IsPointInDynamicArea(radarAreas[area], GPS_Sites[i][j][gps_site_X], GPS_Sites[i][j][gps_site_Y], GPS_Sites[i][j][gps_site_Z]))
					{
						if(td_count >= MAX_RADAR_MAPICONS) break;
						new Float:td_x, Float:td_y;
						Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], GPS_Sites[i][j][gps_site_X], GPS_Sites[i][j][gps_site_Y], GPS_Sites[i][j][gps_site_Z], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

						new icon[32];
						if(isnull(GPS_Sites[i][j][gps_site_ICON])) format(icon, 32, "%s", GPS_Cat[i][gps_cat_ICON]);
						else format(icon, 32, "%s", GPS_Sites[i][j][gps_site_ICON]);
						pRadarMapIcons_PTD[playerid][td_count] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 2.0), td_y - (RADAR_POINT_SIZE / 2.0), icon, true);
						PlayerTextDrawTextSize(playerid, pRadarMapIcons_PTD[playerid][td_count], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
						PlayerTextDrawFont(playerid, pRadarMapIcons_PTD[playerid][td_count], 4);
						SetPlayerTextDrawLayer(playerid, pRadarMapIcons_PTD[playerid][td_count], LAYER_RADAR);
						PlayerTextDrawShow(playerid, pRadarMapIcons_PTD[playerid][td_count]);
						td_count ++;
					}
				}
			}
		}
	}
	return 1;
}

DestroyPlayerRadarRoute(playerid)
{
	for(new i = 0; i < sizeof pRadarRoute_PTD[]; i ++)
	{
		if(pRadarRoute_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pRadarRoute_PTD[playerid][i]);
			pRadarRoute_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

RecreatePlayerRadarRoute(playerid)
{
	new area = pRadarArea[playerid] - 1,
		valid_area = IsValidRadarArea(area);
	DestroyPlayerRadarRoute(playerid);
	if(valid_area)
	{
		if(pInRoute[playerid] && PI[playerid][pi_GPS_ROUTE])
		{
			new td_count, cp;
			if(GetPlayerRouteCP(playerid) == -1) cp = Iter_First(RouteCps[playerid]);
			else cp = Iter_Next(RouteCps[playerid], GetPlayerRouteCP(playerid));
			//for(new i = cp; i <= Iter_Last(RouteCps[playerid]); i = Iter_Next(RouteCps[playerid], i))
			for(new i = cp; i != Iter_End(RouteCps[playerid]); i = Iter_Next(RouteCps[playerid], i))
			{
				if(IsPointInDynamicArea(radarAreas[area], RouteCps[playerid][i][routecp_X], RouteCps[playerid][i][routecp_Y], RouteCps[playerid][i][routecp_Z]))
				{
					if(td_count >= MAX_RADAR_MAPICONS) break;
					new Float:td_x, Float:td_y;
					Vc3dTo2d(pRadarPosInfo[playerid][0], pRadarPosInfo[playerid][1], pRadarPosInfo[playerid][2], pRadarPosInfo[playerid][3], RouteCps[playerid][i][routecp_X], RouteCps[playerid][i][routecp_Y], RouteCps[playerid][i][routecp_Z], td_x, td_y, radarAreas_Coords[area][0], radarAreas_Coords[area][2], radarAreas_Coords[area][3], radarAreas_Coords[area][1]);

					pRadarRoute_PTD[playerid][td_count] = CreatePlayerTextDraw(playerid, td_x - (pRadarPosInfo[playerid][4] / 2.0), td_y - (RADAR_POINT_SIZE / 2.0), i == Iter_Last(RouteCps[playerid]) ? "hud:radar_flag" : GetRouteIconNameByAngle(RouteCps[playerid][i][routecp_ANGLE]), true);
					PlayerTextDrawTextSize(playerid, pRadarRoute_PTD[playerid][td_count], pRadarPosInfo[playerid][4], RADAR_POINT_SIZE);
					PlayerTextDrawFont(playerid, pRadarRoute_PTD[playerid][td_count], 4);
					SetPlayerTextDrawLayer(playerid, pRadarRoute_PTD[playerid][td_count], LAYER_RADAR);
					PlayerTextDrawShow(playerid, pRadarRoute_PTD[playerid][td_count]);
					td_count ++;
				}
			}
		}
	}
	return 1;
}

GetIconNameByAngle(Float:angle)
{
	new icon[32], compass = GetCompassByAngle(angle);
	switch(compass)
	{
		case 0: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_n");
		case 1: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_nw");
		case 2: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_w");
		case 3: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_sw");
		case 4: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_s");
		case 5: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_se");
		case 6: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_e");
		case 7: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon_ne");
		default: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"location_icon");
	}
	return icon;
}