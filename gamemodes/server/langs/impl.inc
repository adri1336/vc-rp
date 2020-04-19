#include <YSI\y_hooks>

hook OnScriptInit()
{
	//langs groups
	for(new i = 0; i != MAX_SERVER_LANGUAGES; i ++)
	{
		g_lang_groups[i] = Group_Create();
	}
	CallRemoteFunction("OnLangGroupsCreated", "");

	//langs
	Langs_Add("ES", "Español");

	//
	new line_str[64], lang_server[64];
	Total_Loaded_Languages = _:Langs_GetLanguageCount();
	for(new i = 0; i != Total_Loaded_Languages; i ++)
	{
		format(line_str, sizeof line_str, "> %s\n", Langs_GetName(Language:i));
		strcat(Lang_Dialog_String, line_str);
		
		format(line_str, sizeof line_str, "%s%s", Langs_GetCode(Language:i), i != Total_Loaded_Languages - 1 ? "-" : "");
		strcat(lang_server, line_str);
	}
	printf("Idiomas cargados (%d): %s", Total_Loaded_Languages, lang_server);
	/*strins(lang_server, "language ", 0);
	SendRconCommand(lang_server);*/
	return 1;
}