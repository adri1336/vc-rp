StopFueling(playerid)
{
	if(pGasStation_Timer[playerid] != Timer:-1)
	{
		stop pGasStation_Timer[playerid];
		pGasStation_Timer[playerid] = Timer:-1;
	}
	pGasStation[playerid] = false;
	return 1;
}

StartFueling(playerid, vehicle_index)
{
	if(pGasStation_Timer[playerid] != Timer:-1)
	{
		stop pGasStation_Timer[playerid];
		pGasStation_Timer[playerid] = Timer:-1;
	}
	pGasStation[playerid] = true;
	pGasStation_Timer[playerid] = repeat OnFuelingUp(playerid, vehicle_index);
	return 1;
}