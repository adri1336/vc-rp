VehicleModelHasInventory(modelid)
{
	new vehicle_cat = Model_GetCategory(modelid);
	switch(vehicle_cat)
	{
		case CATEGORY_AIRPLANES, CATEGORY_HELICOPTERS, CATEGORY_BIKES, CATEGORY_STATIONWAGONS, CATEGORY_BOATS, CATEGORY_TRAILERS, CATEGORY_UNIQUES:
		{
			return false;
		}
	}
	return true;
}

RemoveVehicleInvetoryItem(vehindex, index, amount = 1)
{
	if(Iter_Contains(VehicleInventory[vehindex], index))
	{
		if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ VehicleInventory[vehindex][index][vinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
		{
			if(VehicleInventory[vehindex][index][vinv_AMOUNT] > 1)
			{
				if(VehicleInventory[vehindex][index][vinv_AMOUNT] - amount <= 0)
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicle_inventory WHERE id = %d;", VehicleInventory[vehindex][index][vinv_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

					new tmp_VehicleInventory[E_VehicleInventory];
					VehicleInventory[vehindex][index] = tmp_VehicleInventory;
					Iter_Remove(VehicleInventory[vehindex], index);
				}
				else
				{
					VehicleInventory[vehindex][index][vinv_AMOUNT] -= amount;
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_inventory SET amount = %d WHERE id = %d;", VehicleInventory[vehindex][index][vinv_AMOUNT], VehicleInventory[vehindex][index][vinv_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
				}
			}
			else
			{
				amount = 1;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicle_inventory WHERE id = %d;", VehicleInventory[vehindex][index][vinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

				new tmp_VehicleInventory[E_VehicleInventory];
				VehicleInventory[vehindex][index] = tmp_VehicleInventory;
				Iter_Remove(VehicleInventory[vehindex], index);
			}
		}
		else
		{
			amount = 1;
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicle_inventory WHERE id = %d;", VehicleInventory[vehindex][index][vinv_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

			new tmp_VehicleInventory[E_VehicleInventory];
			VehicleInventory[vehindex][index] = tmp_VehicleInventory;
			Iter_Remove(VehicleInventory[vehindex], index);
		}
		return 1;
	}
	return 0;
}

MoveVInventoryItem(vehindex, index, to_index)
{
	if(index == to_index || (index >= 0 && index < MAX_VEHICLE_INVENTORY_SLOTS) && (to_index >= 0 && to_index < MAX_VEHICLE_INVENTORY_SLOTS))
	{
		if(Iter_Contains(VehicleInventory[vehindex], index))
		{
			if(Iter_Contains(VehicleInventory[vehindex], to_index))
			{
				new tmp_VehicleInventory[E_VehicleInventory];
				tmp_VehicleInventory = VehicleInventory[vehindex][to_index];
				VehicleInventory[vehindex][to_index] = VehicleInventory[vehindex][index];
				VehicleInventory[vehindex][index] = tmp_VehicleInventory;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_inventory SET position = %d WHERE id = %d;", to_index, VehicleInventory[vehindex][to_index][vinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_inventory SET position = %d WHERE id = %d;", index, VehicleInventory[vehindex][index][vinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
			}
			else
			{
				new tmp_VehicleInventory[E_VehicleInventory];
				VehicleInventory[vehindex][to_index] = VehicleInventory[vehindex][index];
				VehicleInventory[vehindex][index] = tmp_VehicleInventory;
				Iter_Remove(VehicleInventory[vehindex], index);
				Iter_Add(VehicleInventory[vehindex], to_index);

				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_inventory SET position = %d WHERE id = %d;", to_index, VehicleInventory[vehindex][to_index][vinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
			}
			return 1;
		}
	}
	return 0;
}

AddVehicleInventoryItem(vehindex, item_id, params[], amount = 1)
{
	if(IsValidItemId(item_id))
	{
		if(!(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_UNIQUE] && VehicleInvContainsItemType(vehindex, INV_ITEMS_Info[item_id][inv_item_TYPE])))
		{
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MULTIPLIABLE] && VehicleInvContainsItem(vehindex, item_id))
			{
				/* amount check */
				if(amount < 1)
				return 0;

				if(!INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
				amount = 1;
				
				new index = GetVehicleInvIndexByItem(vehindex, item_id, params);
				if(index == -1)
				{
					new inv_index = Iter_Free(VehicleInventory[vehindex]);
					if(inv_index != cellmin)
					{
						if(amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
						return 0;

						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO vehicle_inventory (vehicle_id, item_id, amount, params, position) VALUES ('%d', '%d', %d, '%e', %d);", VehicleInfo[vehindex][vinfo_ID], item_id, amount, params, inv_index);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "OnVehicleInvItemDBAdded", "dddsd", vehindex, inv_index, item_id, params, amount);
						return 1;
					}
				}
				else
				{
					new total_amount = VehicleInventory[vehindex][index][vinv_AMOUNT] + amount;
					if(total_amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
					return 0;

					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_inventory SET amount = %d WHERE id = '%d';", total_amount, VehicleInventory[vehindex][index][vinv_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "OnVehicleInvItemDBAdded", "dddsd", vehindex, index, item_id, params, amount);
					return 1;
				}
			}
			else
			{
				if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
				{
					if(amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
					return 0;
				}

				new index = Iter_Free(VehicleInventory[vehindex]);
				if(index != cellmin)
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO vehicle_inventory (vehicle_id, item_id, amount, params, position) VALUES ('%d', '%d', %d, '%e', %d);", VehicleInfo[vehindex][vinfo_ID], item_id, amount, params, index);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "OnVehicleInvItemDBAdded", "dddsd", vehindex, index, item_id, params, amount);
					return 1;
				}
			}
		}
	}
	return 0;
}

VehicleInvContainsItemType(vehindex, type_id)
{
	foreach(new i : VehicleInventory[vehindex])
	{
		if(INV_ITEMS_Info[ VehicleInventory[vehindex][i][vinv_ITEM_ID] ][inv_item_TYPE] == type_id)
		{
			return 1;
		}
	}
	return 0;
}

VehicleInvContainsItem(vehindex, item_id)
{
	foreach(new i : VehicleInventory[vehindex])
	{
		if(VehicleInventory[vehindex][i][vinv_ITEM_ID] == item_id)
		{
			return 1;
		}
	}
	return 0;
}

GetVehicleInvIndexByItem(vehindex, item_id, params[])
{
	foreach(new i : VehicleInventory[vehindex])
	{
		if(VehicleInventory[vehindex][i][vinv_ITEM_ID] == item_id && !strcmp(VehicleInventory[vehindex][i][vinv_PARAMS], params))
		{
			return i;
		}
	}
	return -1;	
}