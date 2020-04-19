#include <YSI\y_hooks>

hook OnCl_CharactersLoaded()
{
	maleCharactersMenu = CreatePreviewMenu("Skins");
	femaleCharactersMenu = CreatePreviewMenu("Skins");
	if(maleCharactersMenu != INVALID_MENU_ID && femaleCharactersMenu != INVALID_MENU_ID)
	{
		foreach(new i : CL_Character)
		{
			if(CL_Character[i][cl_char_GENDER] == CLOTHING_GENDER_MALE) AddModelToPreviewMenu(maleCharactersMenu, CL_Character[i][cl_char_MODELID], CHARACTER_CHANGE_PRICE, 0.0, 0.0, 0.0);
			else AddModelToPreviewMenu(femaleCharactersMenu, CL_Character[i][cl_char_MODELID], CHARACTER_CHANGE_PRICE, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}