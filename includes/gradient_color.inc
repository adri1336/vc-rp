#if defined _inc_gradient_color
	#endinput
#endif
#define _inc_gradient_color

stock HexToRGBA(colour, &r, &g, &b, &a)
{
	r = (colour >> 24) & 0xFF;
	g = (colour >> 16) & 0xFF;
	b = (colour >> 8) & 0xFF;
	a = colour & 0xFF;
	return 1;
}

stock RGBAToHex(r, g, b, a)
{
	return (r<<24 | g<<16 | b<<8 | a);
}

stock GetGradientColor(zero_color, full_color, Float:percent)
{
	new zero_r, zero_g, zero_b, zero_a,
		full_r, full_g, full_b, full_a,
		color_r, color_g, color_b, color_a;

	HexToRGBA(zero_color, zero_r, zero_g, zero_b, zero_a);
	HexToRGBA(full_color, full_r, full_g, full_b, full_a);

	color_r = zero_r + floatround((percent * (full_r - zero_r)) / 100.0);
	color_g = zero_g + floatround((percent * (full_g - zero_g)) / 100.0);
	color_b = zero_b + floatround((percent * (full_b - zero_b)) / 100.0);
	color_a = zero_a + floatround((percent * (full_a - zero_a)) / 100.0);
	return RGBAToHex(color_r, color_g, color_b, color_a);
}