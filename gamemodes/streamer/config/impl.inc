#include <YSI\y_hooks>

hook OnScriptInit()
{
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 2000);
	return 1;
}