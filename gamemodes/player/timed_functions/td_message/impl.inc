#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	PTD_Info_Message[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 390.000000, "_");
	PlayerTextDrawLetterSize(playerid, PTD_Info_Message[playerid], 0.257333, 1.272296);
	PlayerTextDrawTextSize(playerid, PTD_Info_Message[playerid], 0.000000, 260.000000);
	PlayerTextDrawAlignment(playerid, PTD_Info_Message[playerid], 2);
	PlayerTextDrawColor(playerid, PTD_Info_Message[playerid], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Info_Message[playerid], 0);
	PlayerTextDrawSetOutline(playerid, PTD_Info_Message[playerid], 1);
	PlayerTextDrawFont(playerid, PTD_Info_Message[playerid], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Info_Message[playerid], LAYER_MESSAGES);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	PlayerTextDrawDestroy(playerid, PTD_Info_Message[playerid]);
	if(PTD_Aux_Message[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_Aux_Message[playerid]);
		PTD_Aux_Message[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(ptdinfomsgtimer[playerid] != Timer:-1)
	{
		stop ptdinfomsgtimer[playerid];
		ptdinfomsgtimer[playerid] = Timer:-1;
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	HidePlayerInfoMessage(playerid);
	return 1;
}

hook OnPlayerOpenGps(playerid)
{
	if(PTD_Aux_Message[playerid] != PlayerText:INVALID_TEXT_DRAW)
	PlayerTextDrawHide(playerid, PTD_Aux_Message[playerid]);
	return 1;
}

hook OnPlayerCloseGps(playerid)
{
	if(PTD_Aux_Message[playerid] != PlayerText:INVALID_TEXT_DRAW)
	PlayerTextDrawShow(playerid, PTD_Aux_Message[playerid]);
	return 1;
}

timer HidePlayerInfoMessage_Timer[5000](playerid)
{
	ptdinfomsgtimer[playerid] = Timer:-1;
	HidePlayerInfoMessage(playerid);
}