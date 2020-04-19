HidePlayerInfoMessage(playerid)
{
	if(ptdinfomsgtimer[playerid] != Timer:-1)
	{
		stop ptdinfomsgtimer[playerid];
		ptdinfomsgtimer[playerid] = Timer:-1;
	}
	
	PlayerTextDrawHide(playerid, PTD_Info_Message[playerid]);
	return 1;
}

ShowPlayerInfoMessage(playerid, text[], seconds = 5, bool:sound = true)
{
	if(ptdinfomsgtimer[playerid] != Timer:-1)
	{
		stop ptdinfomsgtimer[playerid];
		ptdinfomsgtimer[playerid] = Timer:-1;
	}

	PlayerTextDrawSetString(playerid, PTD_Info_Message[playerid], text);
	PlayerTextDrawShow(playerid, PTD_Info_Message[playerid]);
	
	if(sound) PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
	if(seconds) ptdinfomsgtimer[playerid] = defer HidePlayerInfoMessage_Timer[seconds*1000](playerid);
	return 1;
}

ShowPlayerAuxTextDraw(playerid, text[])
{
	if(!pGps[playerid])
	{
		if(PTD_Aux_Message[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawSetString(playerid, PTD_Aux_Message[playerid], text);	
		else
		{
			PTD_Aux_Message[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 360.000000, text);
			PlayerTextDrawLetterSize(playerid, PTD_Aux_Message[playerid], 0.267500, 1.382222);
			PlayerTextDrawTextSize(playerid, PTD_Aux_Message[playerid], 0.000000, 260.000000);
			PlayerTextDrawAlignment(playerid, PTD_Aux_Message[playerid], 2);
			PlayerTextDrawColor(playerid, PTD_Aux_Message[playerid], -1);
			PlayerTextDrawSetShadow(playerid, PTD_Aux_Message[playerid], 0);
			PlayerTextDrawSetOutline(playerid, PTD_Aux_Message[playerid], 1);
			PlayerTextDrawBackgroundColor(playerid, PTD_Aux_Message[playerid], 255);
			PlayerTextDrawFont(playerid, PTD_Aux_Message[playerid], 1);
			PlayerTextDrawSetProportional(playerid, PTD_Aux_Message[playerid], 1);
			SetPlayerTextDrawLayer(playerid, PTD_Aux_Message[playerid], LAYER_MESSAGES);
		}
		PlayerTextDrawShow(playerid, PTD_Aux_Message[playerid]);
		return 1;
	}
	return 0;
}

HidePlayerAuxTextDraw(playerid)
{
	if(PTD_Aux_Message[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_Aux_Message[playerid]);
		PTD_Aux_Message[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	return 1;
}