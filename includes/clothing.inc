// Clothing include by adri1

#if defined _inc_clothing
	#endinput
#endif
#define _inc_clothing

#include <YSI\y_hooks>

//db
new MySQL:clothing_db,
	CL_total_Models = 0;

forward OnCl_CharactersLoaded();

//0.3.DL
#define MAX_SKINS_MODELS_SLOTS 10000
#define FIRST_SKIN_MODEL_ID 20001

//clothes types
enum CLOTHES_TYPES
{
	CLOTHE_TYPE_DEFAULT = 0,
	CLOTHE_TYPE_BODY_1 = 1,
	CLOTHE_TYPE_BODY_2 = 2,
	CLOTHE_TYPE_BODY_3 = 3,
	CLOTHE_TYPE_BODY_4 = 4,
	CLOTHE_TYPE_BODY_5 = 5,
	CLOTHE_TYPE_BODY_6 = 6,
	CLOTHE_TYPE_POLICE = 7
};

//characters
#define CLOTHING_GENDER_MALE 0
#define CLOTHING_GENDER_FEMALE 1
#define MAX_CLOTHING_CHARACTERS 20
enum E_CL_Character
{
	//db
	cl_char_ID,
	cl_char_GENDER,
	cl_char_BASE_SKIN,
	cl_char_DFFPATH[128],
	cl_char_TXDPATH[128],
	//gta
	cl_char_MODELID
};
new CL_Character[MAX_CLOTHING_CHARACTERS][E_CL_Character],
	Iterator:CL_Character<MAX_CLOTHING_CHARACTERS>;

//characters clothes
#define MAX_CLOTHING_CLOTHES_PER_CHAR 10
enum E_CL_CharacterClothes
{
	//db
	CLOTHES_TYPES:cl_char_clothe_CLOTHE_TYPE,
	cl_char_clothe_BASE_SKIN,
	cl_char_clothe_DFFPATH[128],
	cl_char_clothe_TXDPATH[128],
	//gta
	cl_char_clothe_MODELID
};
new CL_CharacterClothes[MAX_CLOTHING_CHARACTERS][MAX_CLOTHING_CLOTHES_PER_CHAR][E_CL_CharacterClothes],
	Iterator:CL_CharacterClothes[MAX_CLOTHING_CHARACTERS]<MAX_CLOTHING_CLOTHES_PER_CHAR>;

//player
new CL_pCurrentCharIndex[MAX_PLAYERS] = {-1, ...},
	CL_pCurrentCharClotheIndex[MAX_PLAYERS] = {-1, ...};

//script
hook OnScriptInit()
{
	//iter init
	Iter_Init(CL_CharacterClothes);
	//db connect
	print("--- clothing.inc --- [MySQL] Conectando con la base de datos...");
	clothing_db = mysql_connect_file("clothing_db.ini");
	if(mysql_errno(clothing_db) == 0)
	{
		printf("--- clothing.inc --- [MySQL] Base de datos conectada (clothing) (%d)", _:clothing_db);
		//skins
		inline OnClothingCharactersLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				for(new i = 0; i != rows; i ++)
				{
					if(i >= MAX_CLOTHING_CHARACTERS)
					{
						printf("--- clothing.inc --- [ERROR] MAX_CLOTHING_CHARACTERS superado!");
						break;
					}
					cache_get_value_name_int(i, "id", CL_Character[i][cl_char_ID]);
					cache_get_value_name_int(i, "gender", CL_Character[i][cl_char_GENDER]);
					cache_get_value_name_int(i, "base_skin", CL_Character[i][cl_char_BASE_SKIN]);
					cache_get_value_name(i, "dffpath", CL_Character[i][cl_char_DFFPATH]);
					cache_get_value_name(i, "txdpath", CL_Character[i][cl_char_TXDPATH]);
					CL_Character[i][cl_char_MODELID] = FIRST_SKIN_MODEL_ID + CL_total_Models;
					AddCharModel(CL_Character[i][cl_char_BASE_SKIN], CL_Character[i][cl_char_MODELID], CL_Character[i][cl_char_DFFPATH], CL_Character[i][cl_char_TXDPATH]);
					CL_total_Models ++;
					Iter_Add(CL_Character, i);
					//clothes
					inline OnClCharacterClothesLoad()
					{
						new irows;
						if(cache_get_row_count(irows))
						{
							for(new j = 0; j != irows; j ++)
							{
								if(j >= MAX_CLOTHING_CLOTHES_PER_CHAR)
								{
									printf("--- clothing.inc --- [ERROR] MAX_CLOTHING_CLOTHES_PER_CHAR superado!");
									break;
								}
								cache_get_value_name_int(j, "id_clothe_type", _:CL_CharacterClothes[i][j][cl_char_clothe_CLOTHE_TYPE]);
								cache_get_value_name_int(j, "base_skin", CL_CharacterClothes[i][j][cl_char_clothe_BASE_SKIN]);
								cache_get_value_name(j, "dffpath", CL_CharacterClothes[i][j][cl_char_clothe_DFFPATH]);
								cache_get_value_name(j, "txdpath", CL_CharacterClothes[i][j][cl_char_clothe_TXDPATH]);
								CL_CharacterClothes[i][j][cl_char_clothe_MODELID] = FIRST_SKIN_MODEL_ID + CL_total_Models;
								AddCharModel(CL_CharacterClothes[i][j][cl_char_clothe_BASE_SKIN], CL_CharacterClothes[i][j][cl_char_clothe_MODELID], CL_CharacterClothes[i][j][cl_char_clothe_DFFPATH], CL_CharacterClothes[i][j][cl_char_clothe_TXDPATH]);
								CL_total_Models ++;
								Iter_Add(CL_CharacterClothes[i], j);
							}
						}
					}
					new query[128];
					mysql_format(clothing_db, query, sizeof query, "SELECT * FROM characters_clothes WHERE id_character = %d;", CL_Character[i][cl_char_ID]);
					mysql_tquery_inline(clothing_db, query, using inline OnClCharacterClothesLoad, "");
				}
				CallRemoteFunction("OnCl_CharactersLoaded", "");
			}
		}
		mysql_tquery_inline(clothing_db, "SELECT * FROM characters;", using inline OnClothingCharactersLoad, "");
	}
	else printf("--- clothing.inc --- [MySQL] No se pudo conectar con la base de datos (clothing) (%d)", mysql_errno(clothing_db));
	return 1;
}

hook OnScriptExit()
{
	mysql_close(clothing_db);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	CL_pCurrentCharIndex[playerid] = -1;
	CL_pCurrentCharClotheIndex[playerid] = -1;
	return 1;
}

//funcs
stock IsValidClotheType(CLOTHES_TYPES:id_clothe)
{
	if(id_clothe >= CLOTHE_TYPE_DEFAULT && id_clothe <= _:CLOTHES_TYPES)
	{
		return true;
	}
	return false;
}

stock GetCharacterIndexById(id_character)
{
	foreach(new i : CL_Character)
	{
		if(CL_Character[i][cl_char_ID] == id_character)
		{
			return i;
		}
	}
	return -1;
}

stock IsValidCharacter(id_character)
{
	if(GetCharacterIndexById(id_character) != -1)
	{
		return true;
	}
	return false;
}

stock GetCharacterClotheIndexById(index_character, CLOTHES_TYPES:id_clothe)
{
	foreach(new i : CL_CharacterClothes[index_character])
	{
		if(CL_CharacterClothes[index_character][i][cl_char_clothe_CLOTHE_TYPE] == id_clothe)
		{
			return i;
		}
	}
	return -1;
}

stock IsValidCharacterClothe(index_character, CLOTHES_TYPES:id_clothe)
{
	if(GetCharacterClotheIndexById(index_character, id_clothe) != -1)
	{
		return true;
	}
	return false;
}

stock GetCharacterIdByModelid(modelid)
{
	foreach(new i : CL_Character)
	{
		if(CL_Character[i][cl_char_MODELID] == modelid)
		{
			return CL_Character[i][cl_char_ID];
		}
	}
	return 0;
}

stock CLOTHES_TYPES:GetClotheIdByModelid(id_character, modelid)
{
	new index_character = GetCharacterIndexById(id_character);
	if(index_character != -1)
	{
		foreach(new i : CL_CharacterClothes[index_character])
		{
			if(CL_CharacterClothes[index_character][i][cl_char_clothe_MODELID] == modelid)
			{
				return CL_CharacterClothes[index_character][i][cl_char_clothe_CLOTHE_TYPE];
			}
		}
	}
	return CLOTHES_TYPES:-1;
}

stock GetClothingInfoFromModelid(id_character, modelid, &index_character, &index_clothe)
{
	index_character = GetCharacterIndexById(id_character);
	index_clothe = -1;
	if(index_character != -1)
	{
		if(CL_Character[index_character][cl_char_MODELID] == modelid) index_clothe = -1;
		else
		{
			foreach(new i : CL_CharacterClothes[index_character])
			{
				if(CL_CharacterClothes[index_character][i][cl_char_clothe_MODELID] == modelid)
				{
					index_clothe = i;
					break;
				}
			}
		}
	}
	return 1;
}

//player funcs
stock IsPlayerUsingCharacter(playerid)
{
	if(CL_pCurrentCharIndex[playerid] != -1)
	{
		return true;
	}
	return false;
}

stock IsPlayerUsingClothe(playerid)
{
	if(CL_pCurrentCharIndex[playerid] != -1 && CL_pCurrentCharClotheIndex[playerid] != -1)
	{
		return true;
	}
	return false;
}

stock GetPlayerClothingSkinModel(playerid)
{
	if(IsPlayerUsingCharacter(playerid))
	{
		if(IsPlayerUsingClothe(playerid))
		{
			return CL_CharacterClothes[CL_pCurrentCharIndex[playerid]][CL_pCurrentCharClotheIndex[playerid]][cl_char_clothe_MODELID];
		}
		else
		{
			return CL_Character[CL_pCurrentCharIndex[playerid]][cl_char_MODELID];
		}
	}
	return 0;
}

stock GetPlayerClothingInfo(playerid, &id_character, &CLOTHES_TYPES:id_clothe)
{
	if(IsPlayerUsingCharacter(playerid))
	{
		id_character = CL_Character[CL_pCurrentCharIndex[playerid]][cl_char_ID];
		if(IsPlayerUsingClothe(playerid)) id_clothe = CL_CharacterClothes[CL_pCurrentCharIndex[playerid]][CL_pCurrentCharClotheIndex[playerid]][cl_char_clothe_CLOTHE_TYPE];
		else id_clothe = CLOTHE_TYPE_DEFAULT;
		return 1;
	}
	return 0;
}

stock SetPlayerClothingInfo(playerid, id_character, CLOTHES_TYPES:id_clothe = CLOTHE_TYPE_DEFAULT)
{
	new index_character = GetCharacterIndexById(id_character);
	if(index_character != -1)
	{
		if(id_clothe == CLOTHE_TYPE_DEFAULT)
		{
			CL_pCurrentCharIndex[playerid] = index_character;
			CL_pCurrentCharClotheIndex[playerid] = -1;
			SetPlayerSkin(playerid, CL_Character[index_character][cl_char_MODELID]);
			return 1;
		}
		else
		{
			new index_clothe = GetCharacterClotheIndexById(index_character, id_clothe);
			if(index_clothe != -1)
			{
				CL_pCurrentCharIndex[playerid] = index_character;
				CL_pCurrentCharClotheIndex[playerid] = index_clothe;
				SetPlayerSkin(playerid, CL_CharacterClothes[index_character][index_clothe][cl_char_clothe_MODELID]);
				return 1;
			}
		}
	}
	return 0;
}

stock SetPlayerCharacter(playerid, id_character)
{
	new index_character = GetCharacterIndexById(id_character);
	if(index_character != -1)
	{
		CL_pCurrentCharIndex[playerid] = index_character;
		CL_pCurrentCharClotheIndex[playerid] = -1;
		SetPlayerSkin(playerid, CL_Character[index_character][cl_char_MODELID]);
		return 1;
	}
	return 0;
}

stock SetPlayerCharacterClothe(playerid, CLOTHES_TYPES:id_clothe)
{
	if(IsPlayerUsingCharacter(playerid))
	{
		if(id_clothe == CLOTHE_TYPE_DEFAULT)
		{
			CL_pCurrentCharClotheIndex[playerid] = -1;
			SetPlayerSkin(playerid, CL_Character[ CL_pCurrentCharIndex[playerid] ][cl_char_MODELID]);
		}
		else
		{
			new index_clothe = GetCharacterClotheIndexById(CL_pCurrentCharIndex[playerid], id_clothe);
			if(index_clothe != -1)
			{
				CL_pCurrentCharClotheIndex[playerid] = index_clothe;
				SetPlayerSkin(playerid, CL_CharacterClothes[ CL_pCurrentCharIndex[playerid] ][index_clothe][cl_char_clothe_MODELID]);
				return 1;
			}
		}
	}
	return 0;
}