#define GTA_SA_WIDTH 640.0
#define GTA_SA_HEIGHT 448.0

stock AR_Calc(aspect_ratio_width, aspect_ratio_height, Float:x, Float:size_x, bool:centered_sprite, &Float:result_x, &Float:result_size_x)
{
	size_x *= floatmul(floatdiv(float(aspect_ratio_height), float(aspect_ratio_width)), floatdiv(GTA_SA_WIDTH, GTA_SA_HEIGHT));
	if(centered_sprite) x -= size_x / 2;

	result_x = x;
	result_size_x = size_x;
	return 1;
}