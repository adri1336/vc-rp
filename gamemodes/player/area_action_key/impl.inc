#include <YSI\y_hooks>

loadtext lang[area_action_key];

hook OnPlayerDisconnect(playerid, reason)
{
	pLastAreaId[playerid] = INVALID_STREAMER_ID;
	pLastActionAreaId[playerid] = INVALID_STREAMER_ID;
	pLastSecondaryActionAreaId[playerid] = INVALID_STREAMER_ID;
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	pLastAreaId[playerid] = areaid;

	new streamer_info[3];
	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
	switch(streamer_info[0])
	{
		case
			AREA_TYPE_ENTRANCE, AREA_TYPE_INT_ENTRANCE, AREA_TYPE_HOSPITAL_BED, AREA_TYPE_ATM, AREA_TYPE_BANK,
			AREA_TYPE_SALE_VEHS, AREA_TYPE_GAS_STATION, AREA_TYPE_DRIVING_SCHOOL, AREA_TYPE_EXT_PROPERTY_DOOR,
			AREA_TYPE_INT_PROPERTY_DOOR, AREA_TYPE_BDOOR_EXT, AREA_TYPE_BDOOR_INT, AREA_TYPE_BSALE_POINT,
			AREA_TYPE_JOB_POINT, AREA_TYPE_INTEREST_POINT, AREA_TYPE_GUNSMITH, AREA_TYPE_GUN_LICENSE,
			AREA_TYPE_REAL_ESTATE:
		{
			pLastActionAreaId[playerid] = areaid;
		}
		case AREA_TYPE_CARWORKSHOP:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			pLastActionAreaId[playerid] = areaid;
		}
		case AREA_TYPE_BOOMBOX:
		{
			if(Boombox[streamer_info[1]][boombox_ACCOUNT_ID] == PI[playerid][pi_ID])
			pLastActionAreaId[playerid] = areaid;
		}
		case AREA_TYPE_VINV:
		{
			if(HasPlayerAccessToVehicle(playerid, streamer_info[1]))
			{
				if(Vehicle_Speed(VehicleInfo[streamer_info[1]][vinfo_VEHICLE_ID]) <= 1.0)
				pLastActionAreaId[playerid] = areaid;
			}
		}
		case AREA_TYPE_ENV_AREA, AREA_TYPE_PLAY_BOOMBOX: pLastSecondaryActionAreaId[playerid] = areaid;
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED)
	{
		if(PRESSED(ACTION_KEY) && pLastActionAreaId[playerid] != INVALID_STREAMER_ID)
		{
			if(IsPlayerInDynamicArea(playerid, pLastActionAreaId[playerid]))
			{
				new streamer_info[3];
				Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastActionAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
				switch(streamer_info[0])
				{
					case AREA_TYPE_ENTRANCE:
					{
						if(Entrances[streamer_info[1]][entrance_TIME_OPEN] != 0 && Entrances[streamer_info[1]][entrance_TIME_CLOSE] != 0)
						{
							if(is_open(SERVER_TIME[0], Entrances[streamer_info[1]][entrance_TIME_OPEN], Entrances[streamer_info[1]][entrance_TIME_CLOSE]))
							{
								SetPlayerPosEx
								(
									playerid,
									Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_X],
									Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_Y],
									Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_Z],
									Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_ANGLE],
									Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_INTERIORID],
									Entrances[streamer_info[1]][entrance_ID_ENTRANCE],
									false,
									true,
									true
								);
								SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, streamer_info[1]);
								LoadScreenTimed(playerid);
							}
							else Text_Send(playerid, $GAMETEXT_INFO_CLOSED);
						}
						else
						{
							SetPlayerPosEx
							(
								playerid,
								Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_X],
								Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_Y],
								Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_Z],
								Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_ANGLE],
								Interiors[Entrances[streamer_info[1]][entrance_INTERIOR_INDEX]][interior_INTERIORID],
								Entrances[streamer_info[1]][entrance_ID_ENTRANCE],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, streamer_info[1]);
							LoadScreenTimed(playerid);
						}
					}
					case AREA_TYPE_INT_ENTRANCE:
					{
						if(Entrances[streamer_info[1]][entrance_SUB_ID_INDEX] == -1)
						{
							SetPlayerPosEx
							(
								playerid,
								Entrances[streamer_info[1]][entrance_X],
								Entrances[streamer_info[1]][entrance_Y],
								Entrances[streamer_info[1]][entrance_Z],
								Entrances[streamer_info[1]][entrance_ANGLE],
								0,
								VC_WORLD,
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
						}
						else
						{
							SetPlayerPosEx
							(
								playerid,
								Entrances[streamer_info[1]][entrance_X],
								Entrances[streamer_info[1]][entrance_Y],
								Entrances[streamer_info[1]][entrance_Z],
								Entrances[streamer_info[1]][entrance_ANGLE],
								Interiors[Entrances[ Entrances[streamer_info[1]][entrance_SUB_ID_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
								Entrances[ Entrances[streamer_info[1]][entrance_SUB_ID_INDEX] ][entrance_ID_ENTRANCE],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, Entrances[streamer_info[1]][entrance_SUB_ID_INDEX]);
						}
						LoadScreenTimed(playerid);
					}
					case AREA_TYPE_HOSPITAL_BED: CallRemoteFunction("OnPlayerRequestHospitalBed", "id", playerid, streamer_info[1]);
					case AREA_TYPE_ATM: CallRemoteFunction("OnPlayerRequestAtm", "i", playerid);
					case AREA_TYPE_BANK: CallRemoteFunction("OnPlayerRequestBankPoint", "i", playerid);
					case AREA_TYPE_SALE_VEHS: CallRemoteFunction("OnPlayerRequestSalesVehMenu", "i", playerid);
					case AREA_TYPE_GAS_STATION:
					{
						if(GetPlayerVehicleIndex(playerid) != INVALID_VEHICLE_INDEX && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
						{
							if(VehicleModelHasEngine(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_MODELID])) CallRemoteFunction("OnPlayerRequestGasStation", "id", playerid, GetPlayerVehicleIndex(playerid));
						}
					}
					case AREA_TYPE_DRIVING_SCHOOL: CallRemoteFunction("OnPlayerRequestDrivingSchool", "i", playerid);
					case AREA_TYPE_EXT_PROPERTY_DOOR:
					{
						if(IsPropertyOccupied(streamer_info[1]))
						{
							new params[24];
							format(params, sizeof params, "%d", PropertyInfo[streamer_info[1]][property_ID]);
							if(PlayerInvContainsItemEx(playerid, _:INV_ITEM_PROPERTY_MASTER_KEY, _:INV_ITEM_PROPERTY_KEY, _:INV_ITEM_PROPERTY_RENT_KEY, params))
							{
								new PLAYER_WORLD_STATES:oldstate = PI[playerid][pi_WORLD_STATE];
								SetPlayerPosEx
								(
									playerid,
									Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_X],
									Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_Y],
									Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_Z],
									Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_ANGLE],
									Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID],
									PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_PROPERTY],
									false,
									true,
									true
								);
								SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_PROPERTY, streamer_info[1], streamer_info[2]);
								LoadScreenTimed(playerid);
								if(oldstate != PLAYER_WORLD_STATE_PROPERTY) CallRemoteFunction("OnPlayerEnterProperty", "i", playerid);
							}
							else
							{
								if(IsPropertyDoorClosed(streamer_info[1], streamer_info[2])) Text_Send(playerid, $GAMETEXT_INFO_CLOSED);
								else
								{
									new PLAYER_WORLD_STATES:oldstate = PI[playerid][pi_WORLD_STATE];
									SetPlayerPosEx
									(
										playerid,
										Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_X],
										Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_Y],
										Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_Z],
										Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_ANGLE],
										Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID],
										PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_PROPERTY],
										false,
										true,
										true
									);
									SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_PROPERTY, streamer_info[1], streamer_info[2]);
									LoadScreenTimed(playerid);
									if(oldstate != PLAYER_WORLD_STATE_PROPERTY) CallRemoteFunction("OnPlayerEnterProperty", "i", playerid);
								}
							}
						}
						else
						{
							new PLAYER_WORLD_STATES:oldstate = PI[playerid][pi_WORLD_STATE];
							if(oldstate != PLAYER_WORLD_STATE_PROPERTY)
							{
								if(gettime() - pLastPropertyTour[playerid] < MIN_TIME_BETWEEN_PROPERTY_TOUR)
								{
									new time_sec, days, hours, minutes, seconds;
									time_sec = MIN_TIME_BETWEEN_PROPERTY_TOUR - (gettime() - pLastPropertyTour[playerid]);
									TimeConvert(time_sec, days, hours, minutes, seconds);

									if(minutes) Text_Send(playerid, $MESSAGE_ERROR_PROPERTY_LT_MINUTES, minutes, seconds);
									else Text_Send(playerid, $MESSAGE_ERROR_PROPERTY_LT_SECONDS, time_sec);
									return Y_HOOKS_BREAK_RETURN_1;
								}
							}

							SetPlayerPosEx
							(
								playerid,
								Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_X],
								Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_Y],
								Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_Z],
								Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_ANGLE],
								Interiors[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID_PROPERTY],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_PROPERTY, streamer_info[1], streamer_info[2]);
							LoadScreenTimed(playerid);
							if(oldstate != PLAYER_WORLD_STATE_PROPERTY) CallRemoteFunction("OnPlayerEnterProperty", "i", playerid);
						}
					}
					case AREA_TYPE_INT_PROPERTY_DOOR:
					{
						if(PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ENTR_DOOR_INDEX] != -1)
						{
							SetPlayerPosEx
							(
								playerid,
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_X],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_Y],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_Z],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ANGLE],
								Interiors[Entrances[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
								Entrances[ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ENTR_DOOR_INDEX]);
							CallRemoteFunction("OnPlayerExitProperty", "i", playerid);
						}
						else if(PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_SUB_INDEX] != -1)
						{
							SetPlayerPosEx
							(
								playerid,
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_X],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_Y],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_Z],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ANGLE],
								Interiors[ PropertyDoor[streamer_info[1]][ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID],
								PropertyDoor[streamer_info[1]][ PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_SUB_INDEX] ][prop_door_ID_PROPERTY],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_PROPERTY, streamer_info[1], PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_SUB_INDEX]);
						}
						else
						{
							SetPlayerPosEx
							(
								playerid,
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_X],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_Y],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_Z],
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_EXT_ANGLE],
								0,
								VC_WORLD,
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
							CallRemoteFunction("OnPlayerExitProperty", "i", playerid);
						}
						LoadScreenTimed(playerid);
					}
					case AREA_TYPE_BDOOR_EXT:
					{
						new params[24],
							int_worldid = BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_ID_BUSINESS],
							int_interior_index = BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_INDEX_INTERIOR];

						format(params, sizeof params, "%d", BusinessData[streamer_info[1]][bdata_ID]);
						if(PlayerInvContainsItemEx(playerid, _:INV_ITEM_BUSINESS_MASTER_KEY, _:INV_ITEM_BUSINESS_KEY, _:INV_ITEM_BUSINESS_KEY, params))
						{
							//jugador tiene la llave
							SetPlayerPosEx
							(
								playerid,
								Interiors[int_interior_index][interior_X],
								Interiors[int_interior_index][interior_Y],
								Interiors[int_interior_index][interior_Z],
								Interiors[int_interior_index][interior_ANGLE],
								Interiors[int_interior_index][interior_INTERIORID],
								int_worldid,
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_BUSINESS, streamer_info[1], streamer_info[2]);
							LoadScreenTimed(playerid);
						}
						else
						{
							if(IsBusinessOccupied(streamer_info[1]) && BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED])
							{
								//puerta cerrada
								Text_Send(playerid, $GAMETEXT_INFO_CLOSED);	
							}
							else
							{
								if(BusinessData[streamer_info[1]][bdata_HOUR_OPEN] != 0 && BusinessData[streamer_info[1]][bdata_HOUR_CLOSE] != 0) //tiene horario
								{
									if(is_open(SERVER_TIME[0], BusinessData[streamer_info[1]][bdata_HOUR_OPEN], BusinessData[streamer_info[1]][bdata_HOUR_CLOSE]))
									{
										//abierto
										SetPlayerPosEx
										(
											playerid,
											Interiors[int_interior_index][interior_X],
											Interiors[int_interior_index][interior_Y],
											Interiors[int_interior_index][interior_Z],
											Interiors[int_interior_index][interior_ANGLE],
											Interiors[int_interior_index][interior_INTERIORID],
											int_worldid,
											false,
											true,
											true
										);
										SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_BUSINESS, streamer_info[1], streamer_info[2]);
										LoadScreenTimed(playerid);
									}
									else
									{
										//cerrado
										Text_Send(playerid, $GAMETEXT_INFO_CLOSED);
									}
								}
								else //no tiene horario
								{
									//abierto
									SetPlayerPosEx
									(
										playerid,
										Interiors[int_interior_index][interior_X],
										Interiors[int_interior_index][interior_Y],
										Interiors[int_interior_index][interior_Z],
										Interiors[int_interior_index][interior_ANGLE],
										Interiors[int_interior_index][interior_INTERIORID],
										int_worldid,
										false,
										true,
										true
									);
									SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_BUSINESS, streamer_info[1], streamer_info[2]);
									LoadScreenTimed(playerid);
								}
							}
						}
					}
					case AREA_TYPE_BDOOR_INT:
					{
						if(BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ENTRANCE_DOOR_INDEX] != -1)
						{
							SetPlayerPosEx
							(
								playerid,
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_X],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_Y],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_Z],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ANGLE],
								Interiors[Entrances[ BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
								Entrances[ BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_ID_ENTRANCE],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ENTRANCE_DOOR_INDEX]);
						}
						else if(BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_SUB_INDEX] != -1)
						{
							SetPlayerPosEx
							(
								playerid,
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_X],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_Y],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_Z],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ANGLE],
								Interiors[ BusinessDoors[streamer_info[1]][ BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_SUB_INDEX] ][bdoor_INDEX_INTERIOR] ][interior_INTERIORID],
								BusinessDoors[streamer_info[1]][ BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_SUB_INDEX] ][bdoor_ID_BUSINESS],
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_BUSINESS, streamer_info[1], BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_SUB_INDEX]);
						}
						else
						{
							SetPlayerPosEx
							(
								playerid,
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_X],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_Y],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_Z],
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_EXT_ANGLE],
								0,
								VC_WORLD,
								false,
								true,
								true
							);
							SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
						}
						LoadScreenTimed(playerid);
					}
					case AREA_TYPE_BSALE_POINT:
					{
						if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
						CallRemoteFunction("OnPlayerRequestBSPoint", "idd", playerid, BSales_Points[streamer_info[1]][bsale_point_ID_TYPE], PI[playerid][pi_WORLD_STATE_INDEX]);
					}
					case AREA_TYPE_JOB_POINT: CallRemoteFunction("OnPlayerRequestJob", "idd", playerid, streamer_info[1], streamer_info[2]);
					case AREA_TYPE_INTEREST_POINT: CallRemoteFunction("OnPlayerRequestInterestPoint", "i", playerid);
					case AREA_TYPE_GUNSMITH: CallRemoteFunction("OnPlayerRequestGsPoint", "id", playerid, streamer_info[1]);
					case AREA_TYPE_GUN_LICENSE: CallRemoteFunction("OnPlayerRequestGunLicense", "i", playerid);
					case AREA_TYPE_REAL_ESTATE: CallRemoteFunction("OnPlayerRequestRealEstate", "i", playerid);
					case AREA_TYPE_CARWORKSHOP: CallRemoteFunction("OnPlayerRequestCarWorkShop", "i", playerid);
					case AREA_TYPE_BOOMBOX:
					{
						if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && Boombox[streamer_info[1]][boombox_ACCOUNT_ID] == PI[playerid][pi_ID])
						CallRemoteFunction("OnPlayerRequestBoomboxConfig", "id", playerid, streamer_info[1]);
					}
					case AREA_TYPE_VINV:
					{
						if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
						{
							if(Vehicle_Speed(VehicleInfo[streamer_info[1]][vinfo_VEHICLE_ID]) <= 1.0)
							{
								if(vInvInUse[streamer_info[1]]) Text_Send(playerid, $MESSAGE_ERROR_VINV_IN_USE);
								else ShowVehicleInventoryForPlayer(streamer_info[1], playerid, pLastActionAreaId[playerid]);
							}
						}
					}
					default: return Y_HOOKS_CONTINUE_RETURN_1;
				}
				return Y_HOOKS_BREAK_RETURN_1;
			}
		}
		else if(PRESSED(SECONDARY_ACTION_KEY) && pLastSecondaryActionAreaId[playerid] != INVALID_STREAMER_ID && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(IsPlayerInDynamicArea(playerid, pLastSecondaryActionAreaId[playerid]))
			{
				new streamer_info[3];
				Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastSecondaryActionAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
				switch(streamer_info[0])
				{
					case AREA_TYPE_ENV_AREA: CallRemoteFunction("OnPlayerRequestEnvArea", "id", playerid, streamer_info[1]);
					case AREA_TYPE_PLAY_BOOMBOX:
					{
						if(!isnull(Boombox[streamer_info[1]][boombox_URL]))
						CallRemoteFunction("OnPlayerRequestEnvArea", "id", playerid, ENV_AREA_TYPE_DANCE);
					}
					default: return Y_HOOKS_CONTINUE_RETURN_1;
				}
				return Y_HOOKS_BREAK_RETURN_1;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}