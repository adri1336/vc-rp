#define MAX_INTERIORS 200
enum enum_Interiors
{
	interior_ID,
	interior_NAME[45],
	interior_INTERIORID,
	Float:interior_X,
	Float:interior_Y,
	Float:interior_Z,
	Float:interior_ANGLE,
	Text3D:interior_INFO_LABEL
};
new Interiors[MAX_INTERIORS][enum_Interiors],
	Iterator:Interiors<MAX_INTERIORS>;