#include <YSI\y_hooks>

hook OnScriptInit()
{
	print("[MySQL] Conectando con la base de datos...");
	vcrp_db = mysql_connect_file("vc_rp_db.ini");
	if(mysql_errno(vcrp_db) == 0)
	{
		mysql_tquery(vcrp_db, "UPDATE player SET connected = 0, playerid = 0;");
		mysql_tquery(vcrp_db, "UPDATE vehicles SET created = 0;");
		printf("[MySQL] Base de datos conectada (vcrp) (%d)", _:vcrp_db);
	}
	else
	{
		printf("[MySQL] No se pudo conectar con la base de datos (vcrp) (%d)", mysql_errno(vcrp_db));
		SendRconCommand("exit");
	}
	return 1;
}

hook OnScriptExit()
{
	mysql_close(vcrp_db);
	return 1;
}

hook OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) 
	{
		case CR_SERVER_GONE_ERROR: printf("[MySQL] [ERROR]: Se ha perdido la conexión con el servidor (%d)", _:handle);
		case ER_SYNTAX_ERROR: printf("[MySQL] [ERROR]: Syntax error, query: %s (%d)", query, _:handle);
		default: printf("[MySQL] [ERROR] errorid: %d, error: %s, callback: %s, query: %s, handle: %d", errorid, error, callback, query, _:handle);
	}
	return 1;
}