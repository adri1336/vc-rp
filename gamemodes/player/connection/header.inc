forward OnPlayerLogin(playerid);
forward OnPlayerARLoad(playerid, width, height);

#define PLAYER_COLOR 0xFFFFFF00

new Float:Intro_Cameras[][] =
{
	{6217.098632, 1433.547973, 52.145801, 6216.370117, 1432.955932, 51.801494, 6217.098632, 1433.547973, 52.145801, 6216.370117, 1432.955932, 51.801494},
	{5246.989257, 535.516235, 17.597894, 5247.903808, 535.880493, 17.422311, 5246.989257, 535.516235, 17.597894, 5247.903808, 535.880493, 17.422311}
};

new Intro_Audios[][] =
{
	"https://www.dropbox.com/s/3otdltn99zdq3yt/vcrptheme.mp3?dl=1"
};

new bool:pClassed[MAX_PLAYERS];