Float:KMHtoMPH(Float:kmh)
{
	return kmh * 0.621371;
}

/*Float:GetAngleBetweenPoints(Float:x1, Float:y1, Float:x2, Float:y2) //By Babul
{
	new Float:angle = 90.0 + (atan2(y1 - y2, x1 - x2));
	//new Float:angle = atan2(y1 - y2, x1 - x2) * 180.0 / 3.141592653;
	return angle;
}*/

Float:FixRotation(Float:rotation, &Float:frotation = 0.0)
{
	frotation = rotation;
	while(frotation < 0.0) frotation += 360.0;
	while(frotation >= 360.0) frotation -= 360.0;
	return frotation;
}

GetCompassByAngle(Float:angle)
{
	new Float:fixed_angle;
	FixRotation(angle, fixed_angle);
	if((fixed_angle >= 337.5 && fixed_angle <= 360.0) || (fixed_angle >= 0.0 && fixed_angle <= 22.5)) return 0; //n
	else if(fixed_angle >= 22.5 && fixed_angle <= 67.5) return 1; //nw
	else if(fixed_angle >= 67.5 && fixed_angle <= 112.5) return 2; //w
	else if(fixed_angle >= 112.5 && fixed_angle <= 157.5) return 3; //sw
	else if(fixed_angle >= 157.5 && fixed_angle <= 202.5) return 4; //s
	else if(fixed_angle >= 202.5 && fixed_angle <= 247.5) return 5; //se
	else if(fixed_angle >= 247.5 && fixed_angle <= 292.5) return 6; //e
	else if(fixed_angle >= 292.5 && fixed_angle <= 337.5) return 7; //ne
	return -1;
}

Float:GetCameraFacingAngle(Float:vX, Float:vY)
{
	if((vX = -atan2(vX, vY)) < 0.0) return vX + 360.0;
	return vX;
}

getRandomLetter() 
{
	return 65 + random(25);
}

getDateTime(string[])
{
	new 
		Year, Month, Day,
		Hour, Minute, Second
	;
	getdate(Year, Month, Day);
	gettime(Hour, Minute, Second);
	
	format(string, 24, "%04d-%02d-%02d %02d:%02d:%02d", Year, Month, Day, Hour, Minute, Second);
	return 1;
}

getDateTimeDB()
{
	new string[24];
	new 
		Year, Month, Day,
		Hour, Minute, Second
	;
	getdate(Year, Month, Day);
	gettime(Hour, Minute, Second);
	
	format(string, 24, "'%04d-%02d-%02d %02d:%02d:%02d'", Year, Month, Day, Hour, Minute, Second);
	return string;
}

getRandomString(length)
{
	new string[65];
	for(new i = 0; i < length; i ++)
	{
		string[i] = random(2) ? (random(26) + (random(2) ? 'a' : 'A')) : (random(10) + '0');
	}
	return string;
}

IsValidRPName(const string[])
{
	new Regex:reg_exp = Regex_New("[A-Z][a-z]+_[A-Z][a-z]{1,3}[A-Z]?[a-z]*");
	new result = Regex_Check(string, reg_exp);
	Regex_Delete(reg_exp);
	return result;
}

IsValidEmail(const string[])
{
	new Regex:reg_exp = Regex_New("[a-zA-Z0-9_\\.]+@([a-zA-Z0-9\\-]+\\.)+[a-zA-Z]{2,4}"); 
	new result = Regex_Check(string, reg_exp); 
	Regex_Delete(reg_exp); 
	return result; 
}

/*FixTextdrawString(string[])
{
	new str_fixed[256];
	for(new pos = 0, j = strlen(string); pos <= j; pos++)
	{
		if(pos >= sizeof str_fixed) break;
		switch(string[pos])
		{
			case 'à': str_fixed[pos] = 151;
			case 'á': str_fixed[pos] = 152;
			case 'â': str_fixed[pos] = 153;
			case 'ä': str_fixed[pos] = 154;
			case 'À': str_fixed[pos] = 128;
			case 'Á': str_fixed[pos] = 129;
			case 'Â': str_fixed[pos] = 130;
			case 'Ä': str_fixed[pos] = 131;
			case 'è': str_fixed[pos] = 157;
			case 'é': str_fixed[pos] = 158;
			case 'ê': str_fixed[pos] = 159;
			case 'ë': str_fixed[pos] = 160;
			case 'È': str_fixed[pos] = 134;
			case 'É': str_fixed[pos] = 135;
			case 'Ê': str_fixed[pos] = 136;
			case 'Ë': str_fixed[pos] = 137;
			case 'ì': str_fixed[pos] = 161;
			case 'í': str_fixed[pos] = 162;
			case 'î': str_fixed[pos] = 163;
			case 'ï': str_fixed[pos] = 164;
			case 'Ì': str_fixed[pos] = 138;
			case 'Í': str_fixed[pos] = 139;
			case 'Î': str_fixed[pos] = 140;
			case 'Ï': str_fixed[pos] = 141;
			case 'ò': str_fixed[pos] = 165;
			case 'ó': str_fixed[pos] = 166;
			case 'ô': str_fixed[pos] = 167;
			case 'ö': str_fixed[pos] = 168;
			case 'Ò': str_fixed[pos] = 142;
			case 'Ó': str_fixed[pos] = 143;
			case 'Ô': str_fixed[pos] = 144;
			case 'Ö': str_fixed[pos] = 145;
			case 'ù': str_fixed[pos] = 169;
			case 'ú': str_fixed[pos] = 170;
			case 'û': str_fixed[pos] = 171;
			case 'ü': str_fixed[pos] = 172;
			case 'Ù': str_fixed[pos] = 146;
			case 'Ú': str_fixed[pos] = 147;
			case 'Û': str_fixed[pos] = 148;
			case 'Ü': str_fixed[pos] = 149;
			case 'ñ': str_fixed[pos] = 174;
			case 'Ñ': str_fixed[pos] = 173;
			case '¡': str_fixed[pos] = 64;
			case '¿': str_fixed[pos] = 175;
			case '`': str_fixed[pos] = 177;
			case '&': str_fixed[pos] = 38;
			default:  str_fixed[pos] = string[pos];
		}
	}
	return str_fixed;
}*/

TimeConvert(sec, &days, &hours, &minutes, &seconds)
{
	days = floatround(sec / 86400);
	hours = floatround((sec - (days * 86400)) / 3600);
	minutes = floatround((sec - (days * 86400) - (hours * 3600)) / 60);
	seconds = sec % 60;
	return 1;
}

is_open(hour, open, close)
{
	if(open > close)
	{
		if( ( (hour >= open) && (hour < 24) ) || ( (hour >= 0) && (hour < close) ) )
		{													
			return true;			
		}
		else
		{
			return false;
		}
	}
	else if(open < close)
	{
		if((hour >= open) && (hour < close))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

minrand(min, max) //By Alex "Y_Less" Cole
{
	return random(max - min) + min;
}

Float:GetDistanceBetweenPoints3D(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return VectorSize(x1 - x2, y1 - y2, z1 - z2);
}

space_rp_name(name[])
{
	for(new i = 0; i < 24; i ++)
	{
		if(name[i] == ' ') name[i] = '_';
	}
	return 1;
}

stock GetPlayerCameraLookAt(playerid, &Float:X, &Float:Y, &Float:Z)
{
	new Float:pos[6];
	GetPlayerCameraPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerCameraFrontVector(playerid, pos[3], pos[4], pos[5]);
	X = floatadd(pos[0], pos[3]);
	Y = floatadd(pos[1], pos[4]);
	Z = floatadd(pos[2], pos[5]);
	return 1;
}

stock GetIconTextdraw(iconid)
{
	new td_icon[24];
	switch(iconid)
	{
		case 2: td_icon = "hud:radar_centre";
		case 3: td_icon = "hud:arrow";
		case 4: td_icon = "hud:radar_north";
		case 5: td_icon = "hud:radar_airyard";
		case 6: td_icon = "hud:radar_ammugun";
		case 7: td_icon = "hud:radar_barbers";
		case 8: td_icon = "hud:radar_bigsmoke";
		case 9: td_icon = "hud:radar_boatyard";
		case 10: td_icon = "hud:radar_burgershot";
		case 11: td_icon = "hud:radar_bulldozer";
		case 12: td_icon = "hud:radar_catalinapink";
		case 13: td_icon = "hud:radar_cesarviapando";
		case 14: td_icon = "hud:radar_chicken";
		case 15: td_icon = "hud:radar_cj";
		case 16: td_icon = "hud:radar_crash1";
		case 17: td_icon = "hud:radar_diner";
		case 18: td_icon = "hud:radar_emmetgun";
		case 19: td_icon = "hud:radar_enemyattack";
		case 20: td_icon = "hud:radar_fire";
		case 21: td_icon = "hud:radar_girlfriend";
		case 22: td_icon = "hud:radar_hostpital";
		case 23: td_icon = "hud:radar_locosyndicate";
		case 24: td_icon = "hud:radar_maddog";
		case 25: td_icon = "hud:radar_mafiacasino";
		case 26: td_icon = "hud:radar_mcstrap";
		case 27: td_icon = "hud:radar_modgarage";
		case 28: td_icon = "hud:radar_ogloc";
		case 29: td_icon = "hud:radar_pizza";
		case 30: td_icon = "hud:radar_police";
		case 31: td_icon = "hud:radar_propertyg";
		case 32: td_icon = "hud:radar_propertyr";
		case 33: td_icon = "hud:radar_race";
		case 34: td_icon = "hud:radar_ryder";
		case 35: td_icon = "hud:radar_savegame";
		case 36: td_icon = "hud:radar_school";
		case 37: td_icon = "hud:radar_qmark";
		case 38: td_icon = "hud:radar_sweet";
		case 39: td_icon = "hud:radar_tattoo";
		case 40: td_icon = "hud:radar_thetruth";
		case 41: td_icon = "hud:radar_waypoint";
		case 42: td_icon = "hud:radar_toreno";
		case 43: td_icon = "hud:radar_triads";
		case 44: td_icon = "hud:radar_triadscasino";
		case 45: td_icon = "hud:radar_tshirt";
		case 46: td_icon = "hud:radar_woozie";
		case 47: td_icon = "hud:radar_zero";
		case 48: td_icon = "hud:radar_datedisco";
		case 49: td_icon = "hud:radar_datedrink";
		case 50: td_icon = "hud:radar_datefood";
		case 51: td_icon = "hud:radar_truck";
		case 52: td_icon = "hud:radar_cash";
		case 53: td_icon = "hud:radar_flag";
		case 54: td_icon = "hud:radar_gym";
		case 55: td_icon = "hud:radar_impound";
		case 56: td_icon = "hud:radar_light";
		case 57: td_icon = "hud:radar_runway";
		case 58: td_icon = "hud:radar_gangb";
		case 59: td_icon = "hud:radar_gangp";
		case 60: td_icon = "hud:radar_gangy";
		case 61: td_icon = "hud:radar_gangn";
		case 62: td_icon = "hud:radar_gangg";
		case 63: td_icon = "hud:radar_spray";
	}
	return td_icon;
}

isTextAlphanumeric(text[])
{
	for(new i = 0; i != strlen(text); i ++)
	{
		if((text[i] >= 91 && text[i] <= 96) || (text[i] >= 58 && text[i] <= 64) || (text[i] < 48 && text[i] != 32) || text[i] > 122)
		{
			return false;
		}
	}
	return true;
}