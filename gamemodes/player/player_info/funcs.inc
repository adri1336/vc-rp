SetPlayerWorldState(playerid, PLAYER_WORLD_STATES:worldstate, index = -1, extra_index = -1)
{
	new PLAYER_WORLD_STATES:old_worldstate = PI[playerid][pi_WORLD_STATE];
	PI[playerid][pi_WORLD_STATE] = worldstate;
	PI[playerid][pi_WORLD_STATE_INDEX] = index;
	PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] = extra_index;
	PI[playerid][pi_WORLD_STATE_ID] = 0;
	PI[playerid][pi_WORLD_STATE_EXTRA_ID] = 0;

	//id
	switch(worldstate)
	{
		case PLAYER_WORLD_STATE_STREET: StopAudioStreamForPlayer(playerid);
		case PLAYER_WORLD_STATE_ENTRANCE:
		{
			PI[playerid][pi_WORLD_STATE_ID] = Entrances[index][entrance_ID];
			if(Entrances[index][entrance_RADIO] > 0) PlayAudioStreamForPlayer(playerid, Radios[ Entrances[index][entrance_RADIO] ][radio_URL]);
			else if(Entrances[index][entrance_AUDIO])
			{
				if(!(old_worldstate == PLAYER_WORLD_STATE_BUSINESS && Entrances[index][entrance_ID_ENTRANCE] == 7))
				PlayAudioStreamForPlayer(playerid, Entrances[index][entrance_AUDIO]);
			}
		}
		case PLAYER_WORLD_STATE_PROPERTY:
		{
			PI[playerid][pi_WORLD_STATE_ID] = PropertyInfo[index][property_ID];
			PI[playerid][pi_WORLD_STATE_EXTRA_ID] = PropertyDoor[index][extra_index][prop_door_ID];
		}
		case PLAYER_WORLD_STATE_BUSINESS:
		{
			PI[playerid][pi_WORLD_STATE_ID] = BusinessData[index][bdata_ID];
			PI[playerid][pi_WORLD_STATE_EXTRA_ID] = BusinessDoors[index][extra_index][bdoor_ID];
			if(BusinessData[index][bdata_RADIO] > 0)
			PlayAudioStreamForPlayer(playerid, Radios[ BusinessData[index][bdata_RADIO] ][radio_URL]);
		}
	}

	//call
	CallRemoteFunction("OnPlayerWStateChange", "iddd", playerid, _:worldstate, index, extra_index);
	return 1;
}