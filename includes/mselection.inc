#if defined _inc_mselection
	#endinput
#endif
#define _inc_mselection

#define AR_VERSION true

#include <YSI\y_hooks>
#define MAX_MENU_PREVIEWS_PAGES 50
#define MAX_MENU_MODELS MAX_MENU_PREVIEWS_PAGES*6
#define MAX_MENU_PREVIEWS 50
#define INVALID_MENU_ID -1
#define TDLAYER_MSELECTION 1
#define CountPreviewMenus() Iter_Count(MENU_PREVIEWS)
#define CountModelsFromMenu(%0) Iter_Count(MENU_MODELS[%0])
#define CountMenuPages(%0) MENU_PREVIEWS[%0][menu_preview_PAGES]
#define IsPlayerUsingMenu(%0) Player_Menu_Current_Index[%0]!=INVALID_MENU_ID

forward OnPreviewMenuResponse(playerid, menu_id, menu_model_id, response, modelid, price);

new Player_Menu_Page[MAX_PLAYERS],
	Player_Menu_Current_Index[MAX_PLAYERS],
	Player_Menu_Models_Index[MAX_PLAYERS][6],
	PlayerText:PTD_Menu[MAX_PLAYERS][5] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:PTD_Menu_Models[MAX_PLAYERS][6] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:PTD_Menu_Models_Price[MAX_PLAYERS][6] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};

enum ENUM_MENU_PREVIEWS
{
	menu_preview_TITLE[32],
	menu_preview_BG_COLOR,
	menu_preview_TEXT_COLOR,
	menu_preview_BUTTONS_BG_COLOR,
	menu_preview_PAGES
};
new MENU_PREVIEWS[MAX_MENU_PREVIEWS][ENUM_MENU_PREVIEWS];
new Iterator:MENU_PREVIEWS<MAX_MENU_PREVIEWS>;

enum ENUM_MENU_PREVIEWS_MODELS
{
	menu_preview_MODELID,
	menu_preview_PRICE,
	Float:menu_preview_ROT_X,
	Float:menu_preview_ROT_Y,
	Float:menu_preview_ROT_Z,
	Float:menu_preview_ZOOM
};
new MENU_PREVIEWS_MODELS[MAX_MENU_PREVIEWS][MAX_MENU_MODELS][ENUM_MENU_PREVIEWS_MODELS];
new Iterator:MENU_MODELS[MAX_MENU_PREVIEWS]<MAX_MENU_MODELS>,
	pMenuPreviewIndex[MAX_PLAYERS][MAX_MENU_MODELS],
	pMenuPreviewTitle[MAX_PLAYERS][32];

stock CreatePreviewMenu(title[])
{
	new menu_index = Iter_Free(MENU_PREVIEWS);
	if(menu_index == cellmin) return INVALID_MENU_ID;

	format(MENU_PREVIEWS[menu_index][menu_preview_TITLE], 32, "%s", title);
	MENU_PREVIEWS[menu_index][menu_preview_BG_COLOR] = 220;
	MENU_PREVIEWS[menu_index][menu_preview_TEXT_COLOR] = -1;
	MENU_PREVIEWS[menu_index][menu_preview_BUTTONS_BG_COLOR] = 1179010815;
	MENU_PREVIEWS[menu_index][menu_preview_PAGES] = 1;
	Iter_Add(MENU_PREVIEWS, menu_index);
	return menu_index;
}

stock DeletePreviewMenu(menu_index)
{
	if(menu_index == INVALID_MENU_ID) return 0;

	new tmp_MENU_PREVIEWS[ENUM_MENU_PREVIEWS];
	MENU_PREVIEWS[menu_index] = tmp_MENU_PREVIEWS;

	new tmp_MENU_PREVIEWS_MODELS[ENUM_MENU_PREVIEWS_MODELS];
	foreach(new i : MENU_MODELS[menu_index])
	{
		MENU_PREVIEWS_MODELS[menu_index][i] = tmp_MENU_PREVIEWS_MODELS;
	}

	Iter_Remove(MENU_PREVIEWS, menu_index);
	Iter_Clear(MENU_MODELS[menu_index]);
	return 1;
}

stock AddModelToPreviewMenu(menu_index, modelid, price = 0, Float:rot_x = 0.0, Float:rot_y = 0.0, Float:rot_z = 0.0, Float:zoom = 1.0)
{
	if(menu_index == INVALID_MENU_ID) return INVALID_MENU_ID;
	new model_index = Iter_Free(MENU_MODELS[menu_index]);
	if(model_index == cellmin) return INVALID_MENU_ID;

	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_MODELID] = modelid;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_PRICE] = price;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ROT_X] = rot_x;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ROT_Y] = rot_y;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ROT_Z] = rot_z;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ZOOM] = zoom;
	Iter_Add(MENU_MODELS[menu_index], model_index);

	new menu_models = CountModelsFromMenu(menu_index);
	new Float:pages = floatdiv(float(menu_models), float(6));
	MENU_PREVIEWS[menu_index][menu_preview_PAGES] = floatround(pages, floatround_ceil);
	return model_index;
}

stock SetPreviewMenuModel(menu_index, model_index, modelid)
{
	if(menu_index == INVALID_MENU_ID) return 0;
	if(!Iter_Contains(MENU_MODELS[menu_index], model_index)) return 0;

	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_MODELID] = modelid;
	return 1;
}

stock SetPreviewMenuPrice(menu_index, model_index, price)
{
	if(menu_index == INVALID_MENU_ID) return 0;
	if(!Iter_Contains(MENU_MODELS[menu_index], model_index)) return 0;

	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_PRICE] = price;
	return 1;
}

stock RemovePreviewMenuModel(menu_index, model_index)
{
	if(menu_index == INVALID_MENU_ID) return 0;
	if(!Iter_Contains(MENU_MODELS[menu_index], model_index)) return 0;

	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_MODELID] = 0;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_PRICE] = 0;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ROT_X] = 0.0;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ROT_Y] = 0.0;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ROT_Z] = 0.0;
	MENU_PREVIEWS_MODELS[menu_index][model_index][menu_preview_ZOOM] = 0.0;
	Iter_Remove(MENU_MODELS[menu_index], model_index);

	new menu_models = CountModelsFromMenu(menu_index);
	new Float:pages = floatdiv(float(menu_models), float(6));
	MENU_PREVIEWS[menu_index][menu_preview_PAGES] = floatround(pages, floatround_ceil);
	return 1;
}

stock ShowPreviewMenuForPlayer(playerid, menu_index, select_color = -1, title[] = "")
{
	if(menu_index == INVALID_MENU_ID) return 0;

	for(new i = 0; i != MAX_MENU_MODELS; i ++)
	{
		pMenuPreviewIndex[playerid][i] = -1;
	}

	new count;
	foreach(new i : MENU_MODELS[menu_index])
	{
		pMenuPreviewIndex[playerid][count] = i;
		count ++;
	}

	Player_Menu_Page[playerid] = 1;
	Player_Menu_Current_Index[playerid] = menu_index;
	if(isnull(title)) format(pMenuPreviewTitle[playerid], 32, "%s", MENU_PREVIEWS[menu_index][menu_preview_TITLE]);
	else format(pMenuPreviewTitle[playerid], 32, "%s", title);
	UpdatePreviewMenuForPlayer(playerid);
	SelectTextDraw(playerid, select_color);
	DisablePlayerLayers(playerid, TDLAYER_MSELECTION);
	return 1;
}

HidePreviewMenuForPlayer(playerid)
{
	if(Player_Menu_Current_Index[playerid] == INVALID_MENU_ID) return 0;

	for(new i = 0; i != 5; i ++) PlayerTextDrawHide(playerid, PTD_Menu[playerid][i]);
	for(new i = 0; i != 6; i ++)
	{
		PlayerTextDrawHide(playerid, PTD_Menu_Models[playerid][i]);
		PlayerTextDrawHide(playerid, PTD_Menu_Models_Price[playerid][i]);
	}

	Player_Menu_Current_Index[playerid] = INVALID_MENU_ID;
	CancelSelectTextDraw(playerid);
	EnablePlayerLayers(playerid);
	return 1;
}

UpdatePreviewMenuForPlayer(playerid)
{
	for(new i = 0; i != 5; i ++) PlayerTextDrawHide(playerid, PTD_Menu[playerid][i]);
	for(new i = 0; i != 6; i ++)
	{
		Player_Menu_Models_Index[playerid][i] = -1;
		PlayerTextDrawHide(playerid, PTD_Menu_Models[playerid][i]);
		PlayerTextDrawHide(playerid, PTD_Menu_Models_Price[playerid][i]);
	}

	new menu_index = Player_Menu_Current_Index[playerid],
		menu_pages = CountMenuPages(menu_index),
		td_model_index,
		start_index = (Player_Menu_Page[playerid] - 1) * 6;

	new td_str[45];
	for(new i = start_index; i != start_index + 6; i ++)
	{
		if(pMenuPreviewIndex[playerid][i] != -1)
		{
			PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][td_model_index], MENU_PREVIEWS[menu_index][menu_preview_BUTTONS_BG_COLOR]);
			PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][td_model_index], MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_MODELID]);

			new Float:rot[3];
			rot[0] = MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_ROT_X];
			rot[1] = MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_ROT_Y];
			rot[2] = MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_ROT_Z];
			if(rot[0] == -1.0 && rot[1] == -1.0 && rot[2] == -1.0)
			{
				rot[0] = float(random(15));
				rot[1] = float(random(5));
				rot[2] = float(random(360));
			}

			PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][td_model_index], rot[0], rot[1], rot[2], MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_ZOOM]);
			PlayerTextDrawShow(playerid, PTD_Menu_Models[playerid][td_model_index]);

			if(MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_PRICE] > 0)
			{
				format(td_str, sizeof td_str, "%d$", MENU_PREVIEWS_MODELS[menu_index][ pMenuPreviewIndex[playerid][i] ][menu_preview_PRICE]);
				PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][td_model_index], MENU_PREVIEWS[menu_index][menu_preview_TEXT_COLOR]);
				PlayerTextDrawSetString(playerid, PTD_Menu_Models_Price[playerid][td_model_index], td_str);
				PlayerTextDrawShow(playerid, PTD_Menu_Models_Price[playerid][td_model_index]);
			}

			Player_Menu_Models_Index[playerid][td_model_index] = pMenuPreviewIndex[playerid][i];
			td_model_index ++;
		}
	}
	
	format(td_str, sizeof td_str, "%s", pMenuPreviewTitle[playerid]);
	PlayerTextDrawColor(playerid, PTD_Menu[playerid][1], MENU_PREVIEWS[menu_index][menu_preview_TEXT_COLOR]);
	PlayerTextDrawSetString(playerid, PTD_Menu[playerid][1], td_str);
	PlayerTextDrawShow(playerid, PTD_Menu[playerid][1]);

	if(menu_pages == 1) PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][0], 0.000000, 18.633342);
	else
	{
		PlayerTextDrawColor(playerid, PTD_Menu[playerid][2], MENU_PREVIEWS[menu_index][menu_preview_TEXT_COLOR]);
		PlayerTextDrawColor(playerid, PTD_Menu[playerid][3], MENU_PREVIEWS[menu_index][menu_preview_TEXT_COLOR]);
		PlayerTextDrawColor(playerid, PTD_Menu[playerid][4], MENU_PREVIEWS[menu_index][menu_preview_TEXT_COLOR]);

		PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][0], 0.000000, 20.666687);
		PlayerTextDrawShow(playerid, PTD_Menu[playerid][2]);
		PlayerTextDrawShow(playerid, PTD_Menu[playerid][3]);

		format(td_str, sizeof td_str, "%d/%d", Player_Menu_Page[playerid], menu_pages);
		PlayerTextDrawSetString(playerid, PTD_Menu[playerid][4], td_str);
		PlayerTextDrawShow(playerid, PTD_Menu[playerid][4]);
	}

	
	PlayerTextDrawBoxColor(playerid, PTD_Menu[playerid][0], MENU_PREVIEWS[menu_index][menu_preview_BG_COLOR]);
	PlayerTextDrawShow(playerid, PTD_Menu[playerid][0]);
	return 1;
}

hook OnScriptInit()
{
	Iter_Init(MENU_MODELS);
	return 1;
}

hook OnPlayerARLoad(playerid, width, height)
{
	Player_Menu_Current_Index[playerid] = INVALID_MENU_ID;

	new Float:result_x, Float:result_size_x, Float:result_size_x_total;
	AR_Calc(width, height, 0.0, 263.8, false, result_x, result_size_x_total);
	PTD_Menu[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 128.000000, "bg");
	PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][0], 0.000000, 18.633342);
	PlayerTextDrawTextSize(playerid, PTD_Menu[playerid][0], 0.000000, result_size_x_total);
	PlayerTextDrawAlignment(playerid, PTD_Menu[playerid][0], 2);
	PlayerTextDrawColor(playerid, PTD_Menu[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, PTD_Menu[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, PTD_Menu[playerid][0], 220);
	PlayerTextDrawSetShadow(playerid, PTD_Menu[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu[playerid][0], 255);
	PlayerTextDrawFont(playerid, PTD_Menu[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu[playerid][0], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu[playerid][0], TDLAYER_MSELECTION);

	PTD_Menu[playerid][1] = CreatePlayerTextDraw(playerid, 320.000000, 132.000000, "title");
	PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][1], 0.227332, 1.110519);
	PlayerTextDrawAlignment(playerid, PTD_Menu[playerid][1], 2);
	PlayerTextDrawColor(playerid, PTD_Menu[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu[playerid][1], 255);
	PlayerTextDrawFont(playerid, PTD_Menu[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu[playerid][1], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu[playerid][1], TDLAYER_MSELECTION);

	AR_Calc(width, height, 0.0, 56.0, false, result_x, result_size_x);
	PTD_Menu[playerid][2] = CreatePlayerTextDraw(playerid, 399.000000, 298.000000, ">>");
	PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][2], 0.227332, 1.110519);
	PlayerTextDrawTextSize(playerid, PTD_Menu[playerid][2], 10.000000, result_size_x);
	PlayerTextDrawAlignment(playerid, PTD_Menu[playerid][2], 2);
	PlayerTextDrawColor(playerid, PTD_Menu[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, PTD_Menu[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, PTD_Menu[playerid][2], 1179010815);
	PlayerTextDrawSetShadow(playerid, PTD_Menu[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu[playerid][2], 255);
	PlayerTextDrawFont(playerid, PTD_Menu[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu[playerid][2], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu[playerid][2], TDLAYER_MSELECTION);

	PTD_Menu[playerid][3] = CreatePlayerTextDraw(playerid, 241.000000, 298.000000, "<<");
	PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][3], 0.227332, 1.110519);
	PlayerTextDrawTextSize(playerid, PTD_Menu[playerid][3], 10.000000, result_size_x);
	PlayerTextDrawAlignment(playerid, PTD_Menu[playerid][3], 2);
	PlayerTextDrawColor(playerid, PTD_Menu[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, PTD_Menu[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, PTD_Menu[playerid][3], 1179010815);
	PlayerTextDrawSetShadow(playerid, PTD_Menu[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu[playerid][3], 255);
	PlayerTextDrawFont(playerid, PTD_Menu[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu[playerid][3], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu[playerid][3], TDLAYER_MSELECTION);

	PTD_Menu[playerid][4] = CreatePlayerTextDraw(playerid, 320.000000, 298.000000, "Pagina_0/0");
	PlayerTextDrawLetterSize(playerid, PTD_Menu[playerid][4], 0.227332, 1.110519);
	PlayerTextDrawAlignment(playerid, PTD_Menu[playerid][4], 2);
	PlayerTextDrawColor(playerid, PTD_Menu[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu[playerid][4], 255);
	PlayerTextDrawFont(playerid, PTD_Menu[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu[playerid][4], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu[playerid][4], TDLAYER_MSELECTION);

	new Float:separation, Float:start_x;
	AR_Calc(width, height, 0.0, 3.0, false, result_x, separation);
	start_x = 320.0 - (result_size_x_total / 2) + separation;
	AR_Calc(width, height, 0.0, 5.0, false, result_x, separation);
	AR_Calc(width, height, 0.0, 82.0, false, result_x, result_size_x);
	PTD_Menu_Models[playerid][0] = CreatePlayerTextDraw(playerid, start_x, 150.000000, ""); //0
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models[playerid][0], result_size_x, 68.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models[playerid][0], 1);
	PlayerTextDrawColor(playerid, PTD_Menu_Models[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][0], 1179010815);
	PlayerTextDrawFont(playerid, PTD_Menu_Models[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][0], 0);
	PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][0], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu_Models[playerid][0], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models[playerid][0], TDLAYER_MSELECTION);

	PTD_Menu_Models[playerid][1] = CreatePlayerTextDraw(playerid, start_x + ((result_size_x + separation) * 1), 150.000000, ""); //1
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models[playerid][1], result_size_x, 68.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models[playerid][1], 1);
	PlayerTextDrawColor(playerid, PTD_Menu_Models[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][1], 1179010815);
	PlayerTextDrawFont(playerid, PTD_Menu_Models[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][1], 12);
	PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][1], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu_Models[playerid][1], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models[playerid][1], TDLAYER_MSELECTION);

	PTD_Menu_Models[playerid][2] = CreatePlayerTextDraw(playerid, start_x + ((result_size_x + separation) * 2), 150.000000, ""); //2
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models[playerid][2], result_size_x, 68.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models[playerid][2], 1);
	PlayerTextDrawColor(playerid, PTD_Menu_Models[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][2], 1179010815);
	PlayerTextDrawFont(playerid, PTD_Menu_Models[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][2], 12);
	PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][2], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu_Models[playerid][2], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models[playerid][2], TDLAYER_MSELECTION);

	PTD_Menu_Models[playerid][3] = CreatePlayerTextDraw(playerid, start_x, 223.000000, ""); //3
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models[playerid][3], result_size_x, 68.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models[playerid][3], 1);
	PlayerTextDrawColor(playerid, PTD_Menu_Models[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][3], 1179010815);
	PlayerTextDrawFont(playerid, PTD_Menu_Models[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models[playerid][3], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][3], 12);
	PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][3], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu_Models[playerid][3], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models[playerid][3], TDLAYER_MSELECTION);

	PTD_Menu_Models[playerid][4] = CreatePlayerTextDraw(playerid, start_x + ((result_size_x + separation) * 1), 223.000000, ""); //4
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models[playerid][4], result_size_x, 68.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models[playerid][4], 1);
	PlayerTextDrawColor(playerid, PTD_Menu_Models[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][4], 1179010815);
	PlayerTextDrawFont(playerid, PTD_Menu_Models[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][4], 12);
	PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][4], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu_Models[playerid][4], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models[playerid][4], TDLAYER_MSELECTION);

	PTD_Menu_Models[playerid][5] = CreatePlayerTextDraw(playerid, start_x + ((result_size_x + separation) * 2), 223.000000, ""); //5
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models[playerid][5], result_size_x, 68.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models[playerid][5], 1);
	PlayerTextDrawColor(playerid, PTD_Menu_Models[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models[playerid][5], 1179010815);
	PlayerTextDrawFont(playerid, PTD_Menu_Models[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_Menu_Models[playerid][5], 12);
	PlayerTextDrawSetPreviewRot(playerid, PTD_Menu_Models[playerid][5], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PTD_Menu_Models[playerid][5], true);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models[playerid][5], TDLAYER_MSELECTION);

//x + 65, y + 59
	new Float:offset;
	AR_Calc(width, height, 0.0, 80.8, false, result_x, offset);
	PTD_Menu_Models_Price[playerid][0] = CreatePlayerTextDraw(playerid, start_x + offset, 209.000000, "0$$");
	PlayerTextDrawLetterSize(playerid, PTD_Menu_Models_Price[playerid][0], 0.162333, 0.828444);
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models_Price[playerid][0], result_size_x, 0.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models_Price[playerid][0], 3);
	PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][0], -36);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models_Price[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models_Price[playerid][0], 255);
	PlayerTextDrawFont(playerid, PTD_Menu_Models_Price[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models_Price[playerid][0], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models_Price[playerid][0], TDLAYER_MSELECTION);

	PTD_Menu_Models_Price[playerid][1] = CreatePlayerTextDraw(playerid, start_x + offset + ((result_size_x + separation) * 1), 209.000000, "0$$");
	PlayerTextDrawLetterSize(playerid, PTD_Menu_Models_Price[playerid][1], 0.162333, 0.828444);
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models_Price[playerid][1], result_size_x, 0.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models_Price[playerid][1], 3);
	PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][1], -36);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models_Price[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models_Price[playerid][1], 255);
	PlayerTextDrawFont(playerid, PTD_Menu_Models_Price[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models_Price[playerid][1], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models_Price[playerid][1], TDLAYER_MSELECTION);

	PTD_Menu_Models_Price[playerid][2] = CreatePlayerTextDraw(playerid, start_x + offset + ((result_size_x + separation) * 2), 209.000000, "0$$");
	PlayerTextDrawLetterSize(playerid, PTD_Menu_Models_Price[playerid][2], 0.162333, 0.828444);
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models_Price[playerid][2], result_size_x, 0.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models_Price[playerid][2], 3);
	PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][2], -36);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models_Price[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models_Price[playerid][2], 255);
	PlayerTextDrawFont(playerid, PTD_Menu_Models_Price[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models_Price[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models_Price[playerid][2], TDLAYER_MSELECTION);

	PTD_Menu_Models_Price[playerid][3] = CreatePlayerTextDraw(playerid, start_x + offset, 282.000000, "0$$");
	PlayerTextDrawLetterSize(playerid, PTD_Menu_Models_Price[playerid][3], 0.162333, 0.828444);
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models_Price[playerid][3], result_size_x, 0.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models_Price[playerid][3], 3);
	PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][3], -36);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models_Price[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models_Price[playerid][3], 255);
	PlayerTextDrawFont(playerid, PTD_Menu_Models_Price[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models_Price[playerid][3], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models_Price[playerid][3], TDLAYER_MSELECTION);

	PTD_Menu_Models_Price[playerid][4] = CreatePlayerTextDraw(playerid, start_x + offset + ((result_size_x + separation) * 1), 282.000000, "0$$");
	PlayerTextDrawLetterSize(playerid, PTD_Menu_Models_Price[playerid][4], 0.162333, 0.828444);
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models_Price[playerid][4], result_size_x, 0.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models_Price[playerid][4], 3);
	PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][4], -36);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models_Price[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models_Price[playerid][4], 255);
	PlayerTextDrawFont(playerid, PTD_Menu_Models_Price[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models_Price[playerid][4], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models_Price[playerid][4], TDLAYER_MSELECTION);

	PTD_Menu_Models_Price[playerid][5] = CreatePlayerTextDraw(playerid, start_x + offset + ((result_size_x + separation) * 2), 282.000000, "0$$");
	PlayerTextDrawLetterSize(playerid, PTD_Menu_Models_Price[playerid][5], 0.162333, 0.828444);
	PlayerTextDrawTextSize(playerid, PTD_Menu_Models_Price[playerid][5], result_size_x, 0.000000);
	PlayerTextDrawAlignment(playerid, PTD_Menu_Models_Price[playerid][5], 3);
	PlayerTextDrawColor(playerid, PTD_Menu_Models_Price[playerid][5], -36);
	PlayerTextDrawSetShadow(playerid, PTD_Menu_Models_Price[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Menu_Models_Price[playerid][5], 255);
	PlayerTextDrawFont(playerid, PTD_Menu_Models_Price[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Menu_Models_Price[playerid][5], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Menu_Models_Price[playerid][5], TDLAYER_MSELECTION);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	Player_Menu_Page[playerid] = 0;
	Player_Menu_Current_Index[playerid] = INVALID_MENU_ID;

	for(new i = 0; i != 5; i ++)
	{
		if(PTD_Menu[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_Menu[playerid][i]);
			PTD_Menu[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	for(new i = 0; i != 6; i ++)
	{
		if(PTD_Menu_Models[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_Menu_Models[playerid][i]);
			PTD_Menu_Models[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(PTD_Menu_Models_Price[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_Menu_Models_Price[playerid][i]);
			PTD_Menu_Models_Price[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == Text:INVALID_TEXT_DRAW)
	{
		if(Player_Menu_Current_Index[playerid] != INVALID_MENU_ID)
		{
			CallRemoteFunction("OnPreviewMenuResponse", "iddddd", playerid, Player_Menu_Current_Index[playerid], -1, false, 0, 0);
			HidePreviewMenuForPlayer(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(Player_Menu_Current_Index[playerid] != INVALID_MENU_ID)
	{
		if(playertextid == PTD_Menu[playerid][2]) //siguiente
		{
			new menu_pages = CountMenuPages(Player_Menu_Current_Index[playerid]);
			if(Player_Menu_Page[playerid] >= menu_pages) Player_Menu_Page[playerid] = 1;
			else Player_Menu_Page[playerid] ++;

			UpdatePreviewMenuForPlayer(playerid);
		}
		else if(playertextid == PTD_Menu[playerid][3]) //anterior
		{
			if(Player_Menu_Page[playerid] <= 1)	Player_Menu_Page[playerid] = CountMenuPages(Player_Menu_Current_Index[playerid]);
			else Player_Menu_Page[playerid] --;

			UpdatePreviewMenuForPlayer(playerid);
		}
		else
		{
			for(new i = 0; i != 6; i ++)
			{
				if(playertextid == PTD_Menu_Models[playerid][i])
				{
					CallRemoteFunction("OnPreviewMenuResponse", "iddddd", playerid, Player_Menu_Current_Index[playerid], Player_Menu_Models_Index[playerid][i], true, MENU_PREVIEWS_MODELS[ Player_Menu_Current_Index[playerid] ][ Player_Menu_Models_Index[playerid][i] ][menu_preview_MODELID], MENU_PREVIEWS_MODELS[ Player_Menu_Current_Index[playerid] ][ Player_Menu_Models_Index[playerid][i] ][menu_preview_PRICE]);
					return 1;
				}
			}
		}
	}
	return 0;
}