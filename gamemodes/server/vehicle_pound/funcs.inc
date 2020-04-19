IsValidVehicleModelidPound(modelid)
{
	new vehicle_cat = Model_GetCategory(modelid);
	switch(vehicle_cat)
	{
		case CATEGORY_BIKE: 
		{
			if(Model_IsManual(modelid))
			{
				return false;
			}
		}
		case CATEGORY_INDUSTRIAL:
		{
			if(Model_IsTruck(modelid))
			{
				return false;
			}
		}
		case CATEGORY_AIRPLANE, CATEGORY_HELICOPTER, CATEGORY_PUBLIC, CATEGORY_BOAT, CATEGORY_TRAILER, CATEGORY_RC:
		{
			return false;
		}
	}
	return true;
}