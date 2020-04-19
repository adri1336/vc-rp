#include <YSI\y_hooks>

loadtext lang[commands_control];

hook OnScriptInit()
{
	Command_SetDeniedReturn(true); //No aparece 'SERVER: Unknown command.' en OnPlayerCommandReceived COMMAND_DENIED
	Group_SetGlobalCommandDefault(false); //Desactivar todos los comandos, habra que darle permiso manualmente
	return 1;
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
	#if IMPL_DEV == 0
	if(GetPlayerGameState(playerid) != GAME_STATE_SPAWNED)
	{
		Text_Send(playerid, $MESSAGE_ERROR_NOT_SPAWNED);
		return COMMAND_DENIED;
	}

	switch(success)
	{
		case COMMAND_DENIED:
		{
			Text_Send(playerid, $MESSAGE_ERROR_NOT_ALLOWED);
			return COMMAND_DENIED;
		}
		case COMMAND_UNDEFINED:
		{
			Text_Send(playerid, $MESSAGE_ERROR_UNDEFINED_COMMAND, cmdtext);
			return COMMAND_OK;
		}
	}
	#endif
	return success;
}