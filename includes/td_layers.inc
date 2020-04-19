#if defined _inc_td_layers
	#endinput
#endif
#define _inc_td_layers

#include <YSI\y_hooks>
#include <YSI\y_iterate>

#define DEFAULT_TD_LAYER 0
#define MAX_TEXTDRAWS_LAYERS 20

#if !defined MAX_TEXTDRAWS
    #define MAX_TEXTDRAWS 2048
#endif

#if !defined MAX_PLAYER_TEXTDRAWS
    #define MAX_PLAYER_TEXTDRAWS 256
#endif

new Global_TextDraws_Layer[MAX_TEXTDRAWS],
    Iterator:Global_TextDraws<MAX_TEXTDRAWS>;

new Player_TextDraws_Layer[MAX_PLAYERS][MAX_PLAYER_TEXTDRAWS],
    Iterator:Player_TextDraws[MAX_PLAYERS]<MAX_PLAYER_TEXTDRAWS>,
    PlayerText:reverse_PTDS[MAX_PLAYERS][MAX_PLAYER_TEXT_DRAWS];

new Iterator:PActive_TextDraws[MAX_PLAYERS]<MAX_TEXTDRAWS>,
    Iterator:PActive_PTextDraws[MAX_PLAYERS]<MAX_PLAYER_TEXTDRAWS>;

new bool:PActive_Layers[MAX_PLAYERS][MAX_TEXTDRAWS_LAYERS] = {{true, ...}, ...};

enum E_TextDrawsLayers_Options
{
    bool:td_layer_DISABLE_LABELS,
    bool:td_layer_ALWAYS_ON
};
new TextDrawsLayers_Options[MAX_TEXTDRAWS_LAYERS][E_TextDrawsLayers_Options];

hook OnScriptInit()
{
    Iter_Init(Player_TextDraws);
    Iter_Init(PActive_TextDraws);
    Iter_Init(PActive_PTextDraws);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    for(new i = 0; i < MAX_TEXTDRAWS_LAYERS; i ++)
    PActive_Layers[playerid][i] = true;

    for(new i = 0; i < MAX_PLAYER_TEXT_DRAWS; i ++)
    reverse_PTDS[playerid][i] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "");
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    for(new i = 0; i < MAX_PLAYER_TEXT_DRAWS; i ++)
    PlayerTextDrawDestroy(playerid, reverse_PTDS[playerid][i]);
    return 1;
}

stock Text:td_layers_TextDrawCreate(Float:x, Float:y, text[])
{
	new Text:textdraw = Text:INVALID_TEXT_DRAW;
    convert_encoding(text);
    textdraw = TextDrawCreate(x, y, text);
    if(textdraw != Text:INVALID_TEXT_DRAW)
    {
        Global_TextDraws_Layer[_:textdraw] = DEFAULT_TD_LAYER;
        Iter_Add(Global_TextDraws, _:textdraw);
    }
	return textdraw;
}

stock GetHighestPlayerTextDrawFreeId(playerid)
{
    for(new i = MAX_PLAYER_TEXT_DRAWS - 1; i != 0; i --)
    {
        if(!Iter_Contains(Player_TextDraws[playerid], i))
        return i;
    }
    return cellmin;
}

stock PlayerText:td_layers_CreatePlayerTextDraw(playerid, Float:x, Float:y, text[], bool:reverse = false)
{
    if(playerid >= 0 && playerid < MAX_PLAYERS)
    {
        new ptd_index = cellmin;
        if(reverse) ptd_index = GetHighestPlayerTextDrawFreeId(playerid);
        else ptd_index = Iter_Free(Player_TextDraws[playerid]);

        if(ptd_index != cellmin)
        {
            PlayerTextDrawDestroy(playerid, reverse_PTDS[playerid][ptd_index]);
            convert_encoding(text);
            reverse_PTDS[playerid][ptd_index] = CreatePlayerTextDraw(playerid, x, y, text);
            if(_:reverse_PTDS[playerid][ptd_index] == ptd_index)
            {
                Player_TextDraws_Layer[playerid][ptd_index] = DEFAULT_TD_LAYER;
                Iter_Add(Player_TextDraws[playerid], ptd_index);

                //info
                //printf("Creating ptdindex:%d, ptdid: %d", ptd_index, _:reverse_PTDS[playerid][ptd_index]);
                return reverse_PTDS[playerid][ptd_index];
            }
        }
    }
    return PlayerText:INVALID_TEXT_DRAW;
}

stock td_layers_TextDrawDestroy(Text:textdraw)
{
    if(Iter_Contains(Global_TextDraws, _:textdraw))
    {
        Global_TextDraws_Layer[_:textdraw] = DEFAULT_TD_LAYER;
        Iter_Remove(Global_TextDraws, _:textdraw);
        foreach(new i : Player)
        {
            Iter_Remove(PActive_TextDraws[i], _:textdraw);
        }
    }
    TextDrawDestroy(textdraw);
	return 1;
}

stock td_layers_PlayerTextDrawDestroy(playerid, PlayerText:textdraw)
{
    if(playerid >= 0 && playerid < MAX_PLAYERS)
    {
        if(Iter_Contains(Player_TextDraws[playerid], _:textdraw))
        {
            new ptd_index = _:textdraw;
            PlayerTextDrawDestroy(playerid, reverse_PTDS[playerid][ptd_index]);
            reverse_PTDS[playerid][ptd_index] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "");

            Player_TextDraws_Layer[playerid][_:textdraw] = DEFAULT_TD_LAYER;
            Iter_Remove(Player_TextDraws[playerid], _:textdraw);
            Iter_Remove(PActive_PTextDraws[playerid], _:textdraw);
        }
	    return 1;
    }
    return 0;
}

stock td_layers_TextDrawShowForAll(Text:textdraw)
{
    if(Iter_Contains(Global_TextDraws, _:textdraw))
    {
        foreach(new i : Player)
        {
            Iter_Add(PActive_TextDraws[i], _:textdraw);
            
            if(PActive_Layers[playerid][Global_TextDraws_Layer[_:textdraw]])
            TextDrawShowForPlayer(i, textdraw, true);
        }
        return 1;
    }
    return 0;
}

stock td_layers_TextDrawHideForAll(Text:textdraw)
{
    if(Iter_Contains(Global_TextDraws, _:textdraw))
    {
        foreach(new i : Player)
        Iter_Remove(PActive_TextDraws[i], _:textdraw);
    }
    TextDrawHideForAll(textdraw);
    return 1;
}

stock td_layers_TextDrawShowForPlayer(playerid, Text:textdraw)
{
    if(IsPlayerConnected(playerid))
    {
        if(Iter_Contains(Global_TextDraws, _:textdraw))
        {
            Iter_Add(PActive_TextDraws[playerid], _:textdraw);

            if(PActive_Layers[playerid][Global_TextDraws_Layer[_:textdraw]])
            TextDrawShowForPlayer(playerid, textdraw);
            return 1;
        }
    }
	return 0;
}

stock td_layers_PlayerTextDrawShow(playerid, PlayerText:textdraw)
{
    if(IsPlayerConnected(playerid))
    {
        if(Iter_Contains(Player_TextDraws[playerid], _:textdraw))
        {
            Iter_Add(PActive_PTextDraws[playerid], _:textdraw);

            if(PActive_Layers[playerid][Player_TextDraws_Layer[playerid][_:textdraw]])
            PlayerTextDrawShow(playerid, textdraw);
            return 1;
        }
    }
    return 0;
}

stock td_layers_TextDrawHideForPlayer(playerid, Text:textdraw)
{
    if(IsPlayerConnected(playerid))
    {
        if(Iter_Contains(Global_TextDraws, _:textdraw))
        {
            Iter_Remove(PActive_TextDraws[playerid], _:textdraw);
        }
        TextDrawHideForPlayer(playerid, textdraw);
        return 1;
    }
	return 0;
}

stock td_layers_PlayerTextDrawHide(playerid, PlayerText:textdraw)
{
    if(IsPlayerConnected(playerid))
    {
        if(Iter_Contains(Player_TextDraws[playerid], _:textdraw))
        {
            Iter_Remove(PActive_PTextDraws[playerid], _:textdraw);
        }
        PlayerTextDrawHide(playerid, textdraw);
        return 1;
    }
	return 0;
}

stock SetTextDrawLayer(Text:textdraw, layer)
{
    if(layer >= 0 && layer < MAX_TEXTDRAWS_LAYERS)
    {
        if(Iter_Contains(Global_TextDraws, _:textdraw))
        {
            Global_TextDraws_Layer[_:textdraw] = layer;
            return 1;
        }
    }
    return 0;
}

stock SetPlayerTextDrawLayer(playerid, PlayerText:textdraw, layer)
{
    if(playerid >= 0 && playerid < MAX_PLAYERS)
    {
        if(layer >= 0 && layer < MAX_TEXTDRAWS_LAYERS)
        {
            if(Iter_Contains(Player_TextDraws[playerid], _:textdraw))
            {
                Player_TextDraws_Layer[playerid][_:textdraw] = layer;
                return 1;
            }
        }
    }
    return 0;
}

stock EnablePlayerLayers(playerid, bool:plabel = true)
{
    if(IsPlayerConnected(playerid))
    {
        for(new i = 0; i < MAX_TEXTDRAWS_LAYERS; i ++)
        PActive_Layers[playerid][i] = true;
        
        foreach(new i : PActive_TextDraws[playerid])
        TextDrawShowForPlayer(playerid, Text:i);
        
        foreach(new i : PActive_PTextDraws[playerid])
        PlayerTextDrawShow(playerid, PlayerText:i);
        
        if(!plabel) Streamer_ToggleAllItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL, true);
        else
        {
            new Text3D:playerLabel;
            playerLabel = Text3D:GetPVarInt(playerid, "playerLabel");

            if(playerLabel != Text3D:INVALID_STREAMER_ID)
            Streamer_ToggleItem(playerid, STREAMER_TYPE_3D_TEXT_LABEL, playerLabel, true);
        }
        Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
        return 1;
    }
    return 0;
}

stock EnablePlayerLayer(playerid, layer)
{
    if(IsPlayerConnected(playerid) && layer >= 0 && layer < MAX_TEXTDRAWS_LAYERS)
    {
        PActive_Layers[playerid][layer] = true;
        
        foreach(new i : PActive_TextDraws[playerid])
        {
            if(Global_TextDraws_Layer[i] == layer)
            TextDrawShowForPlayer(playerid, Text:i, true);
        }
        
        foreach(new i : PActive_PTextDraws[playerid])
        {
            if(Player_TextDraws_Layer[playerid][i] == layer)
            PlayerTextDrawShow(playerid, PlayerText:i, true);
        }
        return 1;
    }
    return 0;
}

stock DisablePlayerLayers(playerid, except = -1, bool:plabel = true, except2 = -1)
{
    if(IsPlayerConnected(playerid))
    {
        for(new i = 0; i < MAX_TEXTDRAWS_LAYERS; i ++)
        {
            if(TextDrawsLayers_Options[i][td_layer_ALWAYS_ON]) PActive_Layers[playerid][i] = true;
            else PActive_Layers[playerid][i] = false;
        }

        if(except >= 0 && except < MAX_TEXTDRAWS_LAYERS)
        {
            PActive_Layers[playerid][except] = true;
            if(TextDrawsLayers_Options[except][td_layer_DISABLE_LABELS])
            {
                if(!plabel) Streamer_ToggleAllItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL, false);
                else
                {
                    new Text3D:playerLabel;
                    playerLabel = Text3D:GetPVarInt(playerid, "playerLabel");
                    
                    if(playerLabel != Text3D:INVALID_STREAMER_ID)
                    Streamer_ToggleItem(playerid, STREAMER_TYPE_3D_TEXT_LABEL, playerLabel, false);
                }
                Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
            }
        }
        
        if(except2 >= 0 && except2 < MAX_TEXTDRAWS_LAYERS)
        PActive_Layers[playerid][except2] = true;

        foreach(new i : PActive_TextDraws[playerid])
        {
            if(TextDrawsLayers_Options[ Global_TextDraws_Layer[i] ][td_layer_ALWAYS_ON]) continue;

            if((except >= 0 && except < MAX_TEXTDRAWS_LAYERS) && except == Global_TextDraws_Layer[i]) TextDrawShowForPlayer(playerid, Text:i);
            else if((except2 >= 0 && except2 < MAX_TEXTDRAWS_LAYERS) && except2 == Global_TextDraws_Layer[i]) TextDrawShowForPlayer(playerid, Text:i);
            else TextDrawHideForPlayer(playerid, Text:i);
        }
        
        foreach(new i : PActive_PTextDraws[playerid])
        {
            if(TextDrawsLayers_Options[ Player_TextDraws_Layer[playerid][i] ][td_layer_ALWAYS_ON]) continue;

            if((except >= 0 && except < MAX_TEXTDRAWS_LAYERS) && except == Player_TextDraws_Layer[playerid][i]) PlayerTextDrawShow(playerid, PlayerText:i);
            else if((except2 >= 0 && except2 < MAX_TEXTDRAWS_LAYERS) && except2 == Player_TextDraws_Layer[playerid][i]) PlayerTextDrawShow(playerid, PlayerText:i);
            else PlayerTextDrawHide(playerid, PlayerText:i);
        }
        return 1;
    }
    return 0;
}

stock DisablePlayerLayer(playerid, layer)
{
    if(IsPlayerConnected(playerid) && layer >= 0 && layer < MAX_TEXTDRAWS_LAYERS)
    {
        PActive_Layers[playerid][layer] = false;
        
        foreach(new i : PActive_TextDraws[playerid])
        {
            if(Global_TextDraws_Layer[i] == layer)
            TextDrawHideForPlayer(playerid, Text:i);
        }
        
        foreach(new i : PActive_PTextDraws[playerid])
        {
            if(Player_TextDraws_Layer[playerid][i] == layer)
            PlayerTextDrawHide(playerid, PlayerText:i);
        }
        return 1;
    }
    return 0;
}

stock ToggleTextDrawLayerLabels(layer, bool:toggle)
{
    if(layer >= 0 && layer < MAX_TEXTDRAWS_LAYERS)
    {
        TextDrawsLayers_Options[layer][td_layer_DISABLE_LABELS] = !toggle;
        return 1;
    }
    return 0;
}

stock SetTextdrawLayerAlwaysOn(layer, bool:toggle)
{
    if(layer >= 0 && layer < MAX_TEXTDRAWS_LAYERS)
    {
        TextDrawsLayers_Options[layer][td_layer_ALWAYS_ON] = toggle;
        return 1;
    }
    return 0;
}

stock td_layers_TextDrawSetString(Text:text, string[])
{
    convert_encoding(string);
    return TextDrawSetString(text, string);
}

stock td_layers_PlayerTextDrawSetStr(playerid, PlayerText:text, string[])
{
    if(IsPlayerConnected(playerid))
    {
        convert_encoding(string);
        return PlayerTextDrawSetString(playerid, text, string);
    }
	return 0;
}

stock td_layers_GameTextForAll(string[], time, style)
{
    convert_encoding(string);
    return GameTextForAll(string, time, style);
}

stock td_layers_GameTextForPlayer(playerid, string[], time, style)
{
    if(IsPlayerConnected(playerid))
    {
        convert_encoding(string);
        return GameTextForPlayer(playerid, string, time, style);
    }
    return 0;
}


/*  hooks   */
#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif
#define TextDrawCreate td_layers_TextDrawCreate

#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw td_layers_CreatePlayerTextDraw

#if defined _ALS_TextDrawDestroy
	#undef TextDrawDestroy
#else
	#define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy td_layers_TextDrawDestroy

#if defined _ALS_PlayerTextDrawDestroy
	#undef PlayerTextDrawDestroy
#else
	#define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy td_layers_PlayerTextDrawDestroy

#if defined _ALS_TextDrawShowForAll
	#undef TextDrawShowForAll
#else
	#define _ALS_TextDrawShowForAll
#endif
#define TextDrawShowForAll td_layers_TextDrawShowForAll

#if defined _ALS_TextDrawHideForAll
	#undef TextDrawHideForAll
#else
	#define _ALS_TextDrawHideForAll
#endif
#define TextDrawHideForAll td_layers_TextDrawHideForAll

#if defined _ALS_TextDrawShowForPlayer
	#undef TextDrawShowForPlayer
#else
	#define _ALS_TextDrawShowForPlayer
#endif
#define TextDrawShowForPlayer td_layers_TextDrawShowForPlayer

#if defined _ALS_PlayerTextDrawShow
	#undef PlayerTextDrawShow
#else
	#define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow td_layers_PlayerTextDrawShow

#if defined _ALS_TextDrawHideForPlayer
	#undef TextDrawHideForPlayer
#else
	#define _ALS_TextDrawHideForPlayer
#endif
#define TextDrawHideForPlayer td_layers_TextDrawHideForPlayer

#if defined _ALS_PlayerTextDrawHide
	#undef PlayerTextDrawHide
#else
	#define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide td_layers_PlayerTextDrawHide

#if defined _ALS_TextDrawSetString
	#undef TextDrawSetString
#else
	#define _ALS_TextDrawSetString
#endif
#define TextDrawSetString td_layers_TextDrawSetString

#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString td_layers_PlayerTextDrawSetStr

#if defined _ALS_GameTextForAll
	#undef GameTextForAll
#else
	#define _ALS_GameTextForAll
#endif
#define GameTextForAll td_layers_GameTextForAll

#if defined _ALS_GameTextForPlayer
	#undef GameTextForPlayer
#else
	#define _ALS_GameTextForPlayer
#endif
#define GameTextForPlayer td_layers_GameTextForPlayer

//by mooman (https://forum.sa-mp.com/showthread.php?t=397515)
stock convert_encoding(string[])
{
	new original[50] = {192,193,194,196,198,199,200,201,202,203,204,205,206,207,210,211,212,214,217,218,219,220,223,224,225,226,228,230,231,232,233,234,235,236,237,238,239,242,243,244,246,249,250,251,252,209,241,191,161,176};
	new fixed[50] = {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,94,124};
	new len = strlen(string);
	for (new i; i < len; i++) {
		for(new j;j < 50;j++) {
			if(string[i] == original[j]) {
				string[i] = fixed[j];
				break;
			}
		}
	}
}