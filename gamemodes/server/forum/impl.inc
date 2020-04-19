#include <YSI\y_hooks>

hook OnScriptInit()
{
	print("[MySQL] Conectando con la base de datos (forum)...");
	vc_forum_db = mysql_connect_file("forum_db.ini");
	if(mysql_errno(vc_forum_db) == 0) printf("[MySQL] Base de datos conectada (%d)", _:vc_forum_db);
	else
	{
		printf("[MySQL] No se pudo conectar con la base de datos (forum) (%d)", mysql_errno(vc_forum_db));
		SendRconCommand("exit");
	}
	return 1;
}

hook OnScriptExit()
{
	mysql_close(vc_forum_db);
	return 1;
}