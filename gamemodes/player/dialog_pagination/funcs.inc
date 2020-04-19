GetDialogPages(total_items, max_items_per_page = DIALOG_PAGINATION_SIZE)
{
	return floatround(floatdiv(float(total_items), float(max_items_per_page)), floatround_ceil);
}

GetNextDialogPage(current_page, total_items)
{
	new total_pages = GetDialogPages(total_items),
		next_page = current_page + 1;

	if(next_page > total_pages - 1) next_page = 0;
	return next_page;
}

GetPreviousDialogPage(current_page, total_items)
{
	new previous_page = current_page - 1;
	if(previous_page < 0) previous_page = GetDialogPages(total_items) - 1;
	
	return previous_page;
}

GetLastDialogPage(total_items, max_items_per_page = DIALOG_PAGINATION_SIZE)
{
	if(total_items == 0) return 0;
	return floatround(floatdiv(float(total_items), float(max_items_per_page)), floatround_ceil) - 1;
}

IsValidPage(current_page, total_items)
{
	current_page += 1;
	if(current_page > GetDialogPages(total_items)) return 0;
	return 1;
}