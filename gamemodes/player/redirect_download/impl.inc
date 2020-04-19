#include <YSI\y_hooks>

hook OnPlayerRequestDownload(playerid, type, crc)
{
	if(!IsPlayerConnected(playerid)) return 0;

	new fullurl[256 + 1],
		dlfilename[64 + 1],
		foundfilename;


	if(type == DOWNLOAD_REQUEST_TEXTURE_FILE) foundfilename = FindTextureFileNameFromCRC(crc, dlfilename, 64);
	else if(type == DOWNLOAD_REQUEST_MODEL_FILE) foundfilename = FindModelFileNameFromCRC(crc, dlfilename, 64);

	if(foundfilename)
	{
		format(fullurl, 256, ""REDIRECT_DOWNLOAD_URL"%s", dlfilename);
		RedirectDownload(playerid, fullurl);
	}
	return 0;
}