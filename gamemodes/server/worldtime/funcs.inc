SetMyWorldTime(minutes_for_day) // SetMyWorldTime(180); // 3 horas reales = 24 horas en juego
{
	worldtime_timer_interval = floatround(floatmul(float(minutes_for_day), floatdiv(125, 3)));

	SERVER_TIME[0] = minrand(9, 16);
	SERVER_TIME[1] = minrand(0, 60);
	return 1;
}