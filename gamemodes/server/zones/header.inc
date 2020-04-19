#define INVALID_ZONE_ID -1

enum e_ZONEINFO
{
	eZone_AREAID,
	eZone_NAME[32],
	Float:eZone_MINX,
	Float:eZone_MINY,
	Float:eZone_MINZ,
	Float:eZone_MAXX,
	Float:eZone_MAXY,
	Float:eZone_MAXZ
};

new g_Zones[][e_ZONEINFO] =
{
	{INVALID_STREAMER_ID, "Downtown", -1613.03, 413.128, 0.0, -213.73, 1677.32, 300.0},
	{INVALID_STREAMER_ID, "Vice Point", 163.656, -351.153, 0.0, 1246.03, 1398.85, 300.0},
	{INVALID_STREAMER_ID, "Washington Beach", -103.97, -930.526, 0.0, 1246.03, -351.153, 300.0},
	{INVALID_STREAMER_ID, "Ocean Beach", -253.206, -1805.37, 0.0, 1254.9, -930.526, 300.0},
	{INVALID_STREAMER_ID, "Starfish Island", -748.206, -818.266, 0.0, -104.505, -241.467, 300.0},
	{INVALID_STREAMER_ID, "Prawn Island", -213.73, 797.605, 0.0, 163.656, 1243.47, 300.0},
	{INVALID_STREAMER_ID, "Leaf Links", -213.73, -241.429, 0.0, 163.656, 797.605, 300.0},
	{INVALID_STREAMER_ID, "Little Haiti", -1396.76, -42.9113, 0.0, -1208.21, 230.39, 300.0}, //vetedero
	{INVALID_STREAMER_ID, "Escobar International", -1888.21, -1779.61, 0.0, -1208.21, 230.39, 300.0},
	{INVALID_STREAMER_ID, "Viceport", -1208.21, -1779.61, 0.0, -253.206, -898.738, 300.0},
	{INVALID_STREAMER_ID, "Little Havana", -1208.21, -898.738, 0.0, -748.206, -241.467, 300.0},
	{INVALID_STREAMER_ID, "Little Haiti", -1208.21, -241.467, 0.0, -578.289, 412.66, 300.0}
};