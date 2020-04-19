stock ReturnSkinByPedStyle(PED_STYLES:style)
{
	switch(style)
	{
		case PED_STYLE_PLAYER: return 0;
		case PED_STYLE_FATMAN: return 5;
		case PED_STYLE_MAN: return 14;
		case PED_STYLE_WOMAN: return 11;
		case PED_STYLE_OLDFATWOMAN: return 10;
		case PED_STYLE_SEXYWOMAN: return 12;
		case PED_STYLE_GANG1: return 19;
		case PED_STYLE_GANG2: return 22;
		case PED_STYLE_OLDMAN: return 49;
		case PED_STYLE_OLDWOMAN: return 53;
		case PED_STYLE_PROSTITUTE: return 63;
		case PED_STYLE_JOGWOMAN: return 90;
		case PED_STYLE_SKATE: return 92;
		case PED_STYLE_JOGGER: return 96;
		case PED_STYLE_BUSYWOMAN: return 141;
		case PED_STYLE_SWAT: return 274;
	}
	return 0;
}