#include <YSI\y_hooks>

loadtext lang[real_estate];

public OnPlayerRequestRealEstate(playerid)
{
	if(CountPlayerBusiness(playerid) == 0 && CountPlayerProperties(playerid) == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_PROPERTIES);
	else
	{
		new	count, listitem_ids[MAX_PLAYER_PROPERTIES + MAX_PLAYER_BUSINESS][2],
			line_str[64], dialog_message[64 * (MAX_PLAYER_PROPERTIES + MAX_PLAYER_BUSINESS)];

		//ondialog
		inline OnPlayerDialog(pid, did, res, lis, string:inp[])
		{
			#pragma unused pid, did, inp
			if(res)
			{
				new index = listitem_ids[lis][1];
				if(listitem_ids[lis][0] == 0) //propiedad
				{
					new price = floatround(floatmul(float(PropertyInfo[index][property_PRICE]), property_depreciation));
					//property
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = NULL WHERE id = %d;", PropertyInfo[index][property_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
					PropertyInfo[index][property_ID_PLAYER] = 0;
					PropertyInfo[index][property_PLAYER_NAME][0] = EOS;
					DeletePropertyKeys(PropertyInfo[index][property_ID], false, index);
					//player
					GivePlayerMoneyEx(playerid, price);
					orm_update(PI[playerid][pi_ORM]);
					Text_Send(playerid, $GAMETEXT_INFO_PROPERTY_SOLD);
				}
				else //negocio
				{
					new price = floatround(floatmul(float(BusinessData[index][bdata_PRICE]), business_depreciation));
					//business
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business SET id_player = NULL WHERE id = %d;", BusinessData[index][bdata_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
					BusinessData[index][bdata_ID_PLAYER] = 0;
					BusinessData[index][bdata_PLAYER_NAME][0] = EOS;
					DeleteBusinessKeys(BusinessData[index][bdata_ID], index);
					ResetBusinessProducts(index);
					//player
					GivePlayerMoneyEx(playerid, price);
					orm_update(PI[playerid][pi_ORM]);
					Text_Send(playerid, $GAMETEXT_INFO_BUSINESS_SOLD);
				}
			}
		}

		//show dialog
		format(dialog_message, sizeof dialog_message, "%s", FormatRealEstateDialogHeader(playerid));
		foreach(new i : PlayerProperties<playerid>)
		{
			if(!IsPropertyForRent(i))
			{
				format(line_str, sizeof line_str, "%s #%d\t%d$\n", FormatRealEstateInfo(playerid, true), PropertyInfo[i][property_ID], floatround(floatmul(float(PropertyInfo[i][property_PRICE]), property_depreciation)));
				strcat(dialog_message, line_str);
				listitem_ids[count][0] = 0;
				listitem_ids[count][1] = i;
				count ++;
			}
		}
		foreach(new i : PlayerBusiness<playerid>)
		{
			format(line_str, sizeof line_str, "%s #%d\t%d$\n", FormatRealEstateInfo(playerid, false), BusinessData[i][bdata_ID], floatround(floatmul(float(BusinessData[i][bdata_PRICE]), business_depreciation)));
			strcat(dialog_message, line_str);
			listitem_ids[count][0] = 1;
			listitem_ids[count][1] = i;
			count ++;
		}
		Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST_HEADERS, FormatRealEstateDialogCaption(playerid), dialog_message, ">>", "X");
	}
	return 1;
}