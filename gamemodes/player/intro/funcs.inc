loadtext lang[intro];

StartPlayerIntro(playerid)
{
	//ptds
	if(pIntro_PTD[playerid][0] == PlayerText:INVALID_TEXT_DRAW && pIntro_PTD[playerid][1] == PlayerText:INVALID_TEXT_DRAW && pIntro_PTD[playerid][2] == PlayerText:INVALID_TEXT_DRAW)
	{
		pIntro_PTD[playerid][0] = CreatePlayerTextDraw(playerid, -5.000000, -5.000000, "LD_SPAC:white");
		PlayerTextDrawTextSize(playerid, pIntro_PTD[playerid][0], 650.000000, 50.000000);
		PlayerTextDrawAlignment(playerid, pIntro_PTD[playerid][0], 1);
		PlayerTextDrawColor(playerid, pIntro_PTD[playerid][0], 255);
		PlayerTextDrawSetShadow(playerid, pIntro_PTD[playerid][0], 0);
		PlayerTextDrawBackgroundColor(playerid, pIntro_PTD[playerid][0], 255);
		PlayerTextDrawFont(playerid, pIntro_PTD[playerid][0], 4);
		PlayerTextDrawSetProportional(playerid, pIntro_PTD[playerid][0], 0);

		pIntro_PTD[playerid][1] = CreatePlayerTextDraw(playerid, -5.000000, 403.000000, "LD_SPAC:white");
		PlayerTextDrawTextSize(playerid, pIntro_PTD[playerid][1], 650.000000, 50.000000);
		PlayerTextDrawAlignment(playerid, pIntro_PTD[playerid][1], 1);
		PlayerTextDrawColor(playerid, pIntro_PTD[playerid][1], 255);
		PlayerTextDrawSetShadow(playerid, pIntro_PTD[playerid][1], 0);
		PlayerTextDrawBackgroundColor(playerid, pIntro_PTD[playerid][1], 255);
		PlayerTextDrawFont(playerid, pIntro_PTD[playerid][1], 4);
		PlayerTextDrawSetProportional(playerid, pIntro_PTD[playerid][1], 0);

		pIntro_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 635.000000, 436.000000, "_");
		PlayerTextDrawLetterSize(playerid, pIntro_PTD[playerid][2], 0.187333, 0.957037);
		PlayerTextDrawAlignment(playerid, pIntro_PTD[playerid][2], 3);
		PlayerTextDrawColor(playerid, pIntro_PTD[playerid][2], -1);
		PlayerTextDrawSetShadow(playerid, pIntro_PTD[playerid][2], 0);
		PlayerTextDrawBackgroundColor(playerid, pIntro_PTD[playerid][2], 255);
		PlayerTextDrawFont(playerid, pIntro_PTD[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, pIntro_PTD[playerid][2], 1);
	}
	PlayerTextDrawShow(playerid, pIntro_PTD[playerid][0]);
	PlayerTextDrawShow(playerid, pIntro_PTD[playerid][1]);
	FormatExitIntoPtd(playerid, pIntro_PTD[playerid][2]);
	PlayerTextDrawShow(playerid, pIntro_PTD[playerid][2]);

	//
	SetPlayerVirtualWorld(playerid, VC_WORLD);
	StopAudioStreamForPlayer(playerid);
	SetPlayerTime(playerid, 12, 0);
	SetPlayerWeather(playerid, 0);
	pInIntro[playerid] = true;
	pIntroExiting[playerid] = false;
	pIntroFinished[playerid] = false;
	pIntroStep[playerid] = 0;
	SetPlayerIntroStep(playerid);
	return 1;
}

SetPlayerIntroStep(playerid)
{
	new params[256],
		time, audio[128];
	switch(pIntroStep[playerid])
	{
		case 0: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_0_AUDIO);
		case 1: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_1_AUDIO);
		case 2: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_2_AUDIO);
		case 3: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_3_AUDIO);
		case 4: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_4_AUDIO);
		case 5: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_5_AUDIO);
		case 6: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_6_AUDIO);
		case 7: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_7_AUDIO);
		case 8: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_8_AUDIO);
		case 9: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_9_AUDIO);
		case 10: Text_Format_Dialog(params, sizeof params, PI[playerid][pi_LANG_ID], $INTRO_10_AUDIO);
	}
	sscanf(params, "ds[128]", time, audio);

	time += 5000;
	InterpolateCameraPos(playerid, Intro_Info[pIntroStep[playerid]][intro_CAM_POS][0], Intro_Info[pIntroStep[playerid]][intro_CAM_POS][1], Intro_Info[pIntroStep[playerid]][intro_CAM_POS][2], Intro_Info[pIntroStep[playerid]][intro_CAM_MOVE_TO][0], Intro_Info[pIntroStep[playerid]][intro_CAM_MOVE_TO][1], Intro_Info[pIntroStep[playerid]][intro_CAM_MOVE_TO][2], time + 4500, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, Intro_Info[pIntroStep[playerid]][intro_CAM_POS][3], Intro_Info[pIntroStep[playerid]][intro_CAM_POS][4], Intro_Info[pIntroStep[playerid]][intro_CAM_POS][5], Intro_Info[pIntroStep[playerid]][intro_CAM_MOVE_TO][3], Intro_Info[pIntroStep[playerid]][intro_CAM_MOVE_TO][4], Intro_Info[pIntroStep[playerid]][intro_CAM_MOVE_TO][5], time + 4500, CAMERA_MOVE);
	PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	PlayAudioStreamForPlayer(playerid, audio);
	if(pIntro_Timer[playerid] != Timer:-1)
	{
		stop pIntro_Timer[playerid];
		pIntro_Timer[playerid] = Timer:-1;
	}
	pIntro_Timer[playerid] = defer OnPlayerRequestIntroNext[time - 1000](playerid, false);
	CleanPlayerChat(playerid);
	return 1;
}

DestroyPlayerIntro(playerid)
{
	if(pIntro_Timer[playerid] != Timer:-1)
	{
		stop pIntro_Timer[playerid];
		pIntro_Timer[playerid] = Timer:-1;
	}
	if(pIntro_PTD[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pIntro_PTD[playerid][0]);
		pIntro_PTD[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(pIntro_PTD[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pIntro_PTD[playerid][1]);
		pIntro_PTD[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(pIntro_PTD[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pIntro_PTD[playerid][1]);
		pIntro_PTD[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
	}
	pInIntro[playerid] = false;
	pIntroStep[playerid] = 0;
	DestroyPlayerCreditsObjects(playerid);
	return 1;
}

DestroyPlayerCreditsObjects(playerid)
{
	foreach(new i : pCreditsObjects[playerid])
	{
		DestroyDynamicObject(pCreditsObjects[playerid][i]);
		pCreditsObjects[playerid][i] = INVALID_STREAMER_ID;
	}
	Iter_Clear(pCreditsObjects[playerid]);
	return 1;
}

FormatExitIntoPtd(playerid, PlayerText:td)
{
	new str[128];
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_EXIT, "~k~~PED_SPRINT~");
	PlayerTextDrawSetString(playerid, td, str);
	return 1;
}

CreatePlayerCreditsObjects(playerid, index)
{
	new str[64], count,
		Float:fPX, Float:fPY, Float:fPZ,
		Float:fVX, Float:fVY, Float:fVZ,
		Float:camAngle, Float:fScale, Float:mSpeed = 0.125,
		Float:object_x, Float:object_y, Float:object_z, Float:object_mz;
	fPX = Intro_Info[index][intro_CAM_POS][0];
	fPY = Intro_Info[index][intro_CAM_POS][1];
	fPZ = Intro_Info[index][intro_CAM_POS][2];
	fVX = Intro_Info[index][intro_CAM_POS][3] - Intro_Info[index][intro_CAM_POS][0];
	fVY = Intro_Info[index][intro_CAM_POS][4] - Intro_Info[index][intro_CAM_POS][1];
	fVZ = Intro_Info[index][intro_CAM_POS][5] - Intro_Info[index][intro_CAM_POS][2];
	camAngle = GetCameraFacingAngle(fVX, fVY);

	//calc
	fScale = 3.0;
	object_x = fPX + floatmul(fVX, fScale);
	object_y = fPY + floatmul(fVY, fScale);
	object_z = (fPZ - 2.0) + floatmul(fVZ, fScale);
	object_mz = (fPZ + 20.0) + floatmul(fVZ, fScale);

	//logo
	pCreditsObjects[playerid][count] = CreateDynamicObject(-1002, object_x, object_y, object_z, 90.0, 0.0, camAngle, .playerid = playerid, .priority = 10);
	MoveDynamicObject(pCreditsObjects[playerid][count], object_x, object_y, object_mz, mSpeed);
	Iter_Add(pCreditsObjects[playerid], count);
	object_z -= 1.5;
	count ++;

	//Programación
	pCreditsObjects[playerid][count] = CreateDynamicObject(19362, object_x, object_y, object_z, 0.0, 0.0, camAngle + 90.0, .playerid = playerid, .priority = 10);
	Text_Format_Dialog(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXT_CODING);
	SetDynamicObjectMaterialText(pCreditsObjects[playerid][count], 0, str, OBJECT_MATERIAL_SIZE_512x512, "Arial", 30, 1, 0xFF000000, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	MoveDynamicObject(pCreditsObjects[playerid][count], object_x, object_y, object_mz, mSpeed);
	Iter_Add(pCreditsObjects[playerid], count);
	object_z -= 0.20;
	count ++;

	pCreditsObjects[playerid][count] = CreateDynamicObject(19362, object_x, object_y, object_z, 0.0, 0.0, camAngle + 90.0, .playerid = playerid, .priority = 10);
	SetDynamicObjectMaterialText(pCreditsObjects[playerid][count], 0,
		"adri1",
	OBJECT_MATERIAL_SIZE_512x512, "Arial", 26, 1, 0xFF000000, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	MoveDynamicObject(pCreditsObjects[playerid][count], object_x, object_y, object_mz, mSpeed);
	Iter_Add(pCreditsObjects[playerid], count);
	object_z -= 0.5;
	count ++;

	//Otros
	pCreditsObjects[playerid][count] = CreateDynamicObject(19362, object_x, object_y, object_z, 0.0, 0.0, camAngle + 90.0, .playerid = playerid, .priority = 10);
	Text_Format_Dialog(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXT_OTHERS);
	SetDynamicObjectMaterialText(pCreditsObjects[playerid][count], 0, str, OBJECT_MATERIAL_SIZE_512x512, "Arial", 30, 1, 0xFF000000, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	MoveDynamicObject(pCreditsObjects[playerid][count], object_x, object_y, object_mz, mSpeed);
	Iter_Add(pCreditsObjects[playerid], count);
	object_z -= 1.27;
	count ++;

	pCreditsObjects[playerid][count] = CreateDynamicObject(19362, object_x, object_y, object_z, 0.0, 0.0, camAngle + 90.0, .playerid = playerid, .priority = 10);
	SetDynamicObjectMaterialText(pCreditsObjects[playerid][count], 0,
		"BlueG (a_mysql)\ncsgames (Spanish Voice Over)\nGTA United 1.2 (vc2sa)\nGraber (vc2samp)\nIncognito (streamer)\nkristo (GPS)\n\
		Muphy (webmaster)\nRIDE2DAY (fadescreen)\nRockstar Games\nSA-MP Team\nSA-MP Wiki\nY_Less (YSI, sscanf2)\nYourShadow (Pawn.Regex)",
	OBJECT_MATERIAL_SIZE_512x512, "Arial", 26, 1, 0xFF000000, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	MoveDynamicObject(pCreditsObjects[playerid][count], object_x, object_y, object_mz, mSpeed);
	Iter_Add(pCreditsObjects[playerid], count);
	object_z -= 2.5;
	count ++;

	//Otros
	pCreditsObjects[playerid][count] = CreateDynamicObject(19362, object_x, object_y, object_z, 0.0, 0.0, camAngle + 90.0, .playerid = playerid, .priority = 10);
	SetDynamicObjectMaterialText(pCreditsObjects[playerid][count], 0, SERVER_WEBSITE, OBJECT_MATERIAL_SIZE_512x512, "Arial", 30, 1, 0xFF000000, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	MoveDynamicObject(pCreditsObjects[playerid][count], object_x, object_y, object_mz, mSpeed);
	Iter_Add(pCreditsObjects[playerid], count);
	count ++;
	return 1;
}