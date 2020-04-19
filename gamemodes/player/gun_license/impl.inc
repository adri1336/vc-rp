#include <YSI\y_hooks>

loadtext lang[gun_license];

public OnPlayerRequestGunLicense(playerid)
{
	if(PlayerInvContainsItem(playerid, _:INV_ITEM_GUN_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_ALREADY_LICENSE);
	else
	{
		if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);
		else if(PlayerInvContainsItem(playerid, _:INV_ITEM_GUN_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_ALREADY_LICENSE);
		else if(GUN_LICENSE_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
		else
		{
			SavePlayerWorldInfo_DB(playerid);
			SetPlayerGameState(playerid, GAME_STATE_SPECTATING);
			PlayAudioStreamForPlayer(playerid, ""RADIO_URL"/vcrp.ogg");
			HidePlayerInfoMessage(playerid);
			SetPlayerVirtualWorld(playerid, playerid + 1);
			TogglePlayerSpectating(playerid, true);
			SetPlayerInterior(playerid, 3);
			InterpolateCameraPos(playerid, Gunlicense_Camera_Pos[0], Gunlicense_Camera_Pos[1], Gunlicense_Camera_Pos[2], Gunlicense_Camera_Pos[0], Gunlicense_Camera_Pos[1], Gunlicense_Camera_Pos[2], 5000, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, Gunlicense_Camera_Pos[3], Gunlicense_Camera_Pos[4], Gunlicense_Camera_Pos[5], Gunlicense_Camera_Pos[3], Gunlicense_Camera_Pos[4], Gunlicense_Camera_Pos[5], 5000, CAMERA_MOVE);
			pGunLicensePoints[playerid] = 0;
			pGunLicenseQuestion[playerid] = 0;

			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, listitem, inputtext
				if(response)
				{
					GivePlayerMoneyEx(playerid, -GUN_LICENSE_PRICE, true);
					ShowPlayerGunLicenseTestDlg(playerid);
				}
				else
				{
					LoadScreenTimed(playerid);
					TogglePlayerSpectating(playerid, false);
				}
			}
			Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_LICENSE_INFO_CAPTION, $DIALOG_LICENSE_INFO_BODY, $DIALOG_LICENSE_INFO_YES, $DIALOG_LICENSE_INFO_NO, GUN_LICENSE_PRICE);
		}
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pGunLicenseTimer[playerid] != Timer:-1)
	{
		stop pGunLicenseTimer[playerid];
		pGunLicenseTimer[playerid] = Timer:-1;
	}
	return 1;
}

public OnPlayerGunLicenseTestDialog(playerid, dialogid, response, listitem, inputtext[])
{
	if(listitem == pGunLicenseValidQuestion[playerid] - 1) pGunLicensePoints[playerid] ++;
	pGunLicenseQuestion[playerid] ++;

	if(pGunLicenseQuestion[playerid] >= 3)
	{
		if(pGunLicensePoints[playerid] == 3)
		{
			new date[24];
			getDateTime(date);
			if(AddPlayerInventoryItem(playerid, _:INV_ITEM_GUN_LICENSE, date))
			{
				Text_Send(playerid, $GAMETEXT_INFO_LICENSE_PASSED);
				CallRemoteFunction("OnPlayerGetGunLicen", "i", playerid);
			}
			else Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);
			
			if(pGunLicenseTimer[playerid] != Timer:-1)
			{
				stop pGunLicenseTimer[playerid];
				pGunLicenseTimer[playerid] = Timer:-1;
			}
			pGunLicenseTimer[playerid] = defer PlayerGunLicenseTest_End(playerid);
		}
		else
		{
			Text_Send(playerid, $MESSAGE_ERROR_LICENSE_TEST);
			LoadScreenTimed(playerid);
			TogglePlayerSpectating(playerid, false);
		}
	}
	else ShowPlayerGunLicenseTestDlg(playerid);
	return 1;
}

timer PlayerGunLicenseTest_End[5000](playerid)
{
	pGunLicenseTimer[playerid] = Timer:-1;
	LoadScreenTimed(playerid);
	TogglePlayerSpectating(playerid, false);
}