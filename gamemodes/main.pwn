/*PAWN DEBUG MODE*/
#pragma option -d2
/*PAWN DEBUG MODE*/

#include <a_samp>

//---------------------------------------------------------------------//
#undef MAX_PLAYERS

#define MAX_PLAYERS 50
#define Y_TEXT_MAX_SETS 64 //contar con find ]\r
//#define _DEBUG 4
#define USE_ARTWORK 1
#define SAVE_ACCOUNTS_TIME 300000 //5 minutos

#define LOCAL_HOST
#if defined LOCAL_HOST

#define REDIRECT_DOWNLOAD 0
#define LOAD_TIME 0
#define IMPL_FORUM 0
#define IMPL_DEV 1

#else

#define REDIRECT_DOWNLOAD 1
#define LOAD_TIME 60000
#define IMPL_FORUM 1
#define IMPL_DEV 0

#endif

//---------------------------------------------------------------------//
#define SERVER_WEBSITE		"vc-rp.es"
#define SERVER_HOSTNAME		"[0.3.DL] Vice City Roleplay ("SERVER_WEBSITE")"
#define SERVER_MAPNAME		"Vice City"
#define SERVER_LANGUAGE		"Español"
#define SERVER_NAME			"Vice City Roleplay"
#define SERVER_NAME_SHORT	"VC-RP"
#define SERVER_VERSION		"0.07"
#define RELEASE_VERSION		"R1"
#define VERSION_DATE		"22/08/19"
#define SERVER_MODE			"VC-RP "SERVER_VERSION" "RELEASE_VERSION" (BETA)(Roleplay)"
//---------------------------------------------------------------------//

new QUERY_BUFFER[2048],
	TEXTDRAW_STR[1024];
DEFINE_HOOK_REPLACEMENT(Downloading, DL);

#define PlayerTD_Text(%0,%1,%2) Text_Format_TD(TEXTDRAW_STR,sizeof(TEXTDRAW_STR),PI[%0][pi_LANG_ID],%2);PlayerTextDrawSetString(%0,%1,TEXTDRAW_STR)

//---------------------------------------------------------------------//

//---------------------------------------------------------------------//
#include <YSI\y_dialog>
#include <YSI\y_text>
#include <YSI\y_languages>
#include <YSI\y_inline>
#include <YSI\y_iterate>
#include <YSI\y_commands>
#include <YSI\y_groups>
#include <YSI\y_timers>
#include <YSI\y_colours>
#include <YSI\y_vehicledata>
#include <a_mysql>
#include <a_mysql_yinline>
#include <streamer>
#include <sscanf2>
#include <Pawn.Regex>
#include <td_layers>
#include <progressbar>
#include <fadescreen>
#include <mselection>
#include <vc_maptd>
#include <GPS>
#include <opvc>
#include <afk>
#include <gradient_color>
#include <route>
#include <aspect_ratio>
#include <tdlines>
#include <weapon_info>
#include <clothing>
#include <anticheat>
#include <components>
//---------------------------------------------------------------------//

//---------------------------------------------------------------------//

//--- HEADERS ---//
#include "streamer/config/header"
#include "streamer/types/header"

#include "utils/defines/header"

#include "server/db/header"
#include "server/langs/header"
#include "server/peds_styles/header"
#include "server/models/header"
#include "server/inv/header"
#include "server/interiors/header"
#include "server/entrances/header"
#include "server/hospital/header"
#include "server/bank/header"
#include "server/atm/header"
#include "server/vehicles/header"
#include "server/veh_shop_sunshine/header"
#include "server/worldtime/header"
#include "server/connection_td/header"
#include "server/radios/header"
#include "server/vehicle_pound/header"
#include "server/gas_station/header"
#include "server/variables/header"
#include "server/vehicle_prices/header"
#include "server/driving_school/header"
#include "server/properties/header"
#include "server/rent_vehicles/header"
#include "server/achievements/header"
#include "server/radar/header"
#include "server/zones/header"
#include "server/gps_cat/header"
#include "server/business/header"
#include "server/clothing/header"
#include "server/jobs/header"
#include "server/actors/header"
#include "server/interest_points/header"
#include "server/gun_license/header"
#include "server/real_estates/header"
#include "server/intro/header"
#include "server/car_workshop/header"
#if IMPL_FORUM == 1
#include "server/forum/header"
#endif
#include "server/env_areas/header"
#include "server/layers/header"
#include "server/autopilot/header"
#include "server/vehicle_inventory/header"

#include "admin/levels/header"
#include "admin/properties_editor/header"
#include "admin/vcmap_editor/header"
#include "admin/entrances_editor/header"
#include "admin/interiors_editor/header"
#include "admin/vehicles_editor/header"
#include "admin/business_editor/header"
#include "admin/player/header"

#include "player/timed_functions/loadscreen/header"
#include "player/timed_functions/timedkick/header"
#include "player/timed_functions/freezeplayer/header"
#include "player/timed_functions/fadescreen/header"
#include "player/timed_functions/td_message/header"
#include "player/pstates/header"
#include "player/tutorial/header"
#include "player/player_info/header"
#include "player/connection/header"
#include "player/register/header"
#include "player/login/header"
#include "player/player_spawn/header"
#include "player/pstats/header"
#include "player/ptask/header"
#include "player/label_system/header"
#include "player/area_action_key/header"
#include "player/nears_players/header"
#include "player/inv/header"
#include "player/hospital/header"
#include "player/preloadanims/header"
#include "player/bank/header"
#include "player/atm/header"
#include "player/dialog_pagination/header"
#include "player/veh_shop_sunshine/header"
#include "player/pvehicles/header"
#include "player/vehicle_funcs/header"
#include "player/gas_station/header"
#if REDIRECT_DOWNLOAD == 1
#include "player/redirect_download/header"
#endif
#include "player/driving_school/header"
#include "player/actions/header"
#include "player/menu/header"
#include "player/achievements/header"
#include "player/properties/header"
#include "player/radar/header"
#include "player/zones/header"
#include "player/route/header"
#include "player/gps/header"
#include "player/anim_env/header"
#include "player/phone/header"
#include "player/toys/header"
#include "player/weapons/header"
#include "player/business/header"
#include "player/clothing/header"
#include "player/jobs/header"
#include "player/interest_points/header"
#include "player/gun_license/header"
#include "player/real_estates/header"
#include "player/intro/header"
#include "player/help_dialog/header"
#include "player/help_channel/header"
#include "player/car_workshop/header"
#include "player/env_areas/header"
#include "player/admin_messages/header"
#include "player/autopilot/header"
#include "player/melee/header"
#include "player/boombox/header"
#include "player/anims_cmd/header"
#include "player/vehicle_inventory/header"

#include "vc_map/db/header"
#include "vc_map/models_types/header"
#include "vc_map/models/header"
#include "vc_map/objects/header"
#include "vc_map/nodes/header"

#if IMPL_DEV == 1
#include "dev/flymode/header"
#include "dev/debug/header"
#include "dev/vc_mdlpreview/header"
#endif


//--- FUNCS ---//
#include "utils/functions/funcs"

#include "server/peds_styles/funcs"
#include "server/inv/funcs"
#include "server/interiors/funcs"
#include "server/entrances/funcs"
#include "server/vehicles/funcs"
#include "server/veh_shop_sunshine/funcs"
#include "server/worldtime/funcs"
#include "server/connection_td/funcs"
#include "server/vehicle_pound/funcs"
#include "server/vehicle_prices/funcs"
#include "server/properties/funcs"
#include "server/zones/funcs"
#include "server/business/funcs"
#include "server/jobs/funcs"
#include "server/autopilot/funcs"
#include "server/vehicle_inventory/funcs"

#include "admin/levels/funcs"
#include "admin/chat/funcs"
#include "admin/properties_editor/funcs"
#include "admin/entrances_editor/funcs"
#include "admin/interiors_editor/funcs"
#include "admin/vehicles_editor/funcs"
#include "admin/gps_cat_editor/funcs"
#include "admin/business_editor/funcs"

#include "player/timed_functions/loadscreen/funcs"
#include "player/timed_functions/timedkick/funcs"
#include "player/timed_functions/freezeplayer/funcs"
#include "player/timed_functions/fadescreen/funcs"
#include "player/timed_functions/td_message/funcs"
#include "player/pstates/funcs"
#include "player/tutorial/funcs"
#include "player/player_info/funcs"
#include "player/register/funcs"
#include "player/disconnect_message/funcs"
#include "player/funcs/funcs"
#include "player/pstats/funcs"
#include "player/ptask/funcs"
#include "player/label_system/funcs"
#include "player/nears_players/funcs"
#include "player/label_render/funcs"
#include "player/infomsg_render/funcs"
#include "player/inv/funcs"
#include "player/hospital/funcs"
#include "player/bank/funcs"
#include "player/atm/funcs"
#include "player/dialog_pagination/funcs"
#include "player/pvehicles/funcs"
#include "player/vehicle_funcs/funcs"
#include "player/gas_station/funcs"
#include "player/driving_school/funcs"
#include "player/menu/funcs"
#include "player/achievements/funcs"
#include "player/properties/funcs"
#include "player/radar/funcs"
#include "player/zones/funcs"
#include "player/route/funcs"
#include "player/gps/funcs"
#include "player/anim_env/funcs"
#include "player/phone/funcs"
#include "player/toys/funcs"
#include "player/weapons/funcs"
#include "player/business/funcs"
#include "player/clothing/funcs"
#include "player/jobs/funcs"
#include "player/gun_license/funcs"
#include "player/real_estates/funcs"
#include "player/car_workshop/funcs"
#include "player/autopilot/funcs"
#include "player/intro/funcs"
#include "player/boombox/funcs"
#include "player/vehicle_inventory/funcs"

#include "vc_map/models_types/funcs"
#include "vc_map/models/funcs"
#include "vc_map/objects/funcs"
#include "vc_map/nodes/funcs"

#if IMPL_DEV == 1
#include "dev/flymode/funcs"
#include "dev/vc_mdlpreview/funcs"
#endif


//--- IMPLS ---//
#include "streamer/config/impl"

#include "server/db/impl"
#include "server/langs/impl"
#include "server/models/impl"
#include "server/inv/impl"
#include "server/interiors/impl"
#include "server/entrances/impl"
#include "server/hospital/impl"
#include "server/bank/impl"
#include "server/atm/impl"
#include "server/vehicles/impl"
#include "server/veh_shop_sunshine/impl"
#include "server/worldtime/impl"
#include "server/connection_td/impl"
#include "server/gas_station/impl"
#include "server/variables/impl"
#include "server/vehicle_prices/impl"
#include "server/driving_school/impl"
#include "server/properties/impl"
#include "server/rent_vehicles/impl"
#include "server/radar/impl"
#include "server/zones/impl"
#include "server/gps_cat/impl"
#include "server/business/impl"
#include "server/clothing/impl"
#include "server/jobs/impl"
#include "server/actors/impl"
#include "server/interest_points/impl"
#include "server/gun_license/impl"
#include "server/real_estates/impl"
#include "server/car_workshop/impl"
#if IMPL_FORUM == 1
#include "server/forum/impl"
#endif
#include "server/env_areas/impl"
#include "server/layers/impl"
#include "server/autopilot/impl"
#include "server/vehicle_inventory/impl"

#include "admin/levels/impl"
#include "admin/getadmin/impl"
#include "admin/chat/impl"
#include "admin/properties_editor/impl"
#include "admin/vcmap_editor/impl"
#include "admin/entrances_editor/impl"
#include "admin/veh_shop_editor/impl"
#include "admin/variables_editor/impl"
#include "admin/interiors_editor/impl"
#include "admin/vehicles_editor/impl"
#include "admin/gps_cat_editor/impl"
#include "admin/business_editor/impl"
#include "admin/player/impl"
#include "admin/ac_editor/impl"
#include "admin/boombox_editor/impl"

#include "player/phone/impl"
#include "player/timed_functions/loadscreen/impl"
#include "player/timed_functions/timedkick/impl"
#include "player/timed_functions/freezeplayer/impl"
#include "player/timed_functions/fadescreen/impl"
#include "player/timed_functions/td_message/impl"
#include "player/pstates/impl"
#include "player/afk_message/impl"
#include "player/commands_control/impl"
#include "player/tutorial/impl"
#include "player/player_info/impl"
#include "player/chat/impl"
#include "player/connection/impl"
#include "player/register/impl"
#include "player/login/impl"
#include "player/antif4/impl"
#include "player/player_spawn/impl"
#include "player/pstats/impl"
#include "player/ptask/impl"
#include "player/label_system/impl"
#include "player/label_render/impl"
#include "player/infomsg_render/impl"
#include "player/area_action_key/impl"
#include "player/inv/impl"
#include "player/hospital/impl"
#include "player/preloadanims/impl"
#include "player/bank/impl"
#include "player/atm/impl"
#include "player/dialog_pagination/impl"
#include "player/veh_shop_sunshine/impl"
#include "player/pvehicles/impl"
#include "player/vehicle_funcs/impl"
#include "player/gas_station/impl"
#if REDIRECT_DOWNLOAD == 1
#include "player/redirect_download/impl"
#endif
#include "player/driving_school/impl"
#include "player/actions/impl"
#include "player/menu/impl"
#include "player/rent_vehicles/impl"
#include "player/achievements/impl"
#include "player/properties/impl"
#include "player/shared_commands/impl"
#include "player/radar/impl"
#include "player/zones/impl"
#include "player/route/impl"
#include "player/gps/impl"
#include "player/anim_env/impl"
#include "player/toys/impl"
#include "player/weapons/impl"
#include "player/business/impl"
#include "player/clothing/impl"
#include "player/jobs/impl"
#include "player/interest_points/impl"
#include "player/gun_license/impl"
#include "player/real_estates/impl"
#include "player/intro/impl"
#include "player/help_dialog/impl"
#include "player/help_channel/impl"
#include "player/car_workshop/impl"
#if IMPL_FORUM == 1
#include "player/forum/impl"
#endif
#include "player/anticheat/impl"
#include "player/env_areas/impl"
#include "player/admin_messages/impl"
#include "player/autopilot/impl"
#include "player/melee/impl"
#include "player/boombox/impl"
#include "player/anims_cmd/impl"
#include "player/vehicle_inventory/impl"

#include "vc_map/db/impl"
#include "vc_map/models_types/impl"
#include "vc_map/models/impl"
#include "vc_map/objects/impl"
#include "vc_map/nodes/impl"

#if IMPL_DEV == 1
#include "dev/flymode/impl"
#include "dev/commands/impl"
#include "dev/debug/impl"
#include "dev/vc_mdlpreview/impl"
#endif

//COMMANDS
#include "server/commands/admin"
#include "server/commands/player"

//---------------------------------------------------------------------//

main()
{
	print("\n----------------------------------");
	print(" "SERVER_NAME"");
	print("----------------------------------\n");
}

#if LOAD_TIME > 0
timer OnServerLoad[LOAD_TIME]()
{
	SendRconCommand("hostname "SERVER_HOSTNAME"");
	SendRconCommand("password 0");
}
#endif

#if SAVE_ACCOUNTS_TIME > 0
task OnServerPlayerAccountsSave[SAVE_ACCOUNTS_TIME]()
{
	foreach(new i : Player)
	{
		if(PI[i][pi_ID])
		{
			if(GetPlayerGameState(i) == GAME_STATE_SPAWNED || GetPlayerGameState(i) == GAME_STATE_DEAD)
			{
				SavePlayerWorldInfo(i);
			}
			orm_update(PI[i][pi_ORM]);
		}
	}
}
#endif

/* YSI Fix */
loadtext lang[connection];

public OnGameModeInit()
{
	//info
	//SendRconCommand("password OnFilterScriptInit");
	#if LOAD_TIME == 0
		SendRconCommand("hostname "SERVER_HOSTNAME"");
	#else
		SendRconCommand("hostname "SERVER_WEBSITE" (loading...)");
		SendRconCommand("password "SERVER_WEBSITE""SERVER_VERSION"");
		defer OnServerLoad();
	#endif

	SetGameModeText(SERVER_MODE);
	SendRconCommand("weburl "SERVER_WEBSITE"");
	SendRconCommand("mapname "SERVER_MAPNAME"");
	SendRconCommand("language "SERVER_LANGUAGE"");
	SendRconCommand("announce 1");
	SendRconCommand("query 1");
	SendRconCommand("sleep 1");
	SendRconCommand("minconnectiontime 1000");
    SendRconCommand("conncookies 1");
	SendRconCommand("cookielogging 0");
	SendRconCommand("chatlogging 0");
	SendRconCommand("ackslimit 5000");

	//colors
	SetColour("ERROR", 0xFF4040FF);
	SetColour("SUCCESS", 0xFFCCFFFF);
	SetColour("WARNING", X11_YELLOW);
	SetColour("INFO", X11_LIGHT_BLUE);
	SetColour("NORMAL", X11_WHITE);
	SetColour("ACTION", 0xC2A2DAFF);
	SetColour("CHAT", 0xE6E6E6E6);
	SetColour("PHONE", 0xE6E6E6E6);
	SetColour("ADMIN", X11_RED);

	//
	DisableInteriorEnterExits();
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	EnableStuntBonusForAll(false);
	ManualVehicleEngineAndLights();

	/* YSI Fix */
	Text_Format_TD(TEXTDRAW_STR, sizeof TEXTDRAW_STR, Language:0, $MESSAGE_ERROR_INDEX);

	//---------------------------------------------------------------------//
	print("---> Init: main");
	//---------------------------------------------------------------------//
	return 1;
}

public OnGameModeExit()
{
	//---------------------------------------------------------------------//
	print("---> Exit: main");
	//---------------------------------------------------------------------//
	return 1;
}

/* YSI Fix */
public OnPlayerFinishedDownloading(playerid, virtualworld)
{
	return 1;
}