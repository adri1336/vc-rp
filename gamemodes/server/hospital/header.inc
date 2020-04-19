#define MAX_HOSPITALS 4
new HospitalsEntrances[MAX_HOSPITALS],
	Iterator:HospitalsEntrances<MAX_HOSPITALS>;

enum enum_Hospital_Beds
{
	hbed_ID_ENTRANCE,
	bool:hbed_IN_USE,
	Float:hbed_X,
	Float:hbed_Y,
	Float:hbed_Z,
	Float:hbed_RZ
};
new Hospital_Beds[][enum_Hospital_Beds] =
{
	//Hospital West Haven
	{1, false, 1154.46936, -1332.51794, 2422.57373, 0.00000},
	{1, false, 1157.96936, -1332.51794, 2422.57373, 0.00000},
	{1, false, 1161.46936, -1332.51794, 2422.57373, 0.00000},
	{1, false, 1164.96936, -1332.51794, 2422.57373, 0.00000},
	//Hospital Ocean View
	{2, false, 2393.64746, 2655.07813, 8000.61621, 0.00000},
	{2, false, 2393.64746, 2648.57813, 8000.61621, 0.00000},
	{2, false, 2393.64746, 2642.07813, 8000.61621, 0.00000},
	{2, false, 2383.14063, 2642.22729, 8000.61621, 0.00000},
	{2, false, 2383.14063, 2648.72729, 8000.61621, 0.00000},
	{2, false, 2371.21655, 2654.98657, 8000.61621, 0.00000},
	{2, false, 2371.21655, 2648.48657, 8000.61621, 0.00000},
	{2, false, 2371.21655, 2642.48657, 8000.61621, 0.00000},
	{2, false, 2381.57886, 2642.16821, 8000.61621, 0.00000},
	{2, false, 2381.57886, 2648.66821, 8000.61621, 0.00000}
};