#include <YSI\y_hooks>

hook OnScriptInit()
{
    Iter_Init(VC_NodesLinks);
    inline OnNodesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
                new Float:x, Float:y, Float:z;
				cache_get_value_name_float(i, "x", x);
				cache_get_value_name_float(i, "y", y);
				cache_get_value_name_float(i, "z", z);
                CreateMapNode(x, y, z, VC_Nodes[i][vcNode_MapNodeID]);
                if(IsValidMapNode(VC_Nodes[i][vcNode_MapNodeID]))
                {
                    cache_get_value_name_int(i, "id", VC_Nodes[i][vcNode_ID]);
                    VC_Nodes[i][vcNode_X] = x;
                    VC_Nodes[i][vcNode_Y] = y;
                    VC_Nodes[i][vcNode_Z] = z;
                    cache_get_value_name_int(i, "isCrossRoad", VC_Nodes[i][vcNode_IsCrossRoad]);
                    cache_get_value_name_float(i, "median", VC_Nodes[i][vcNode_Median]);
                    cache_get_value_name_int(i, "leftLanes", VC_Nodes[i][vcNode_LeftLanes]);
                    cache_get_value_name_int(i, "rightLanes", VC_Nodes[i][vcNode_RightLanes]);
                    cache_get_value_name_int(i, "speedLimit", VC_Nodes[i][vcNode_SpeedLimit]);
                    cache_get_value_name_int(i, "flags", VC_Nodes[i][vcNode_Flags]);
				    Iter_Add(VC_Nodes, i);
                }
			}
		}
	}
	mysql_tquery_inline(vc_map_db, "SELECT * FROM nodes LIMIT "#MAX_VICE_CITY_NODES";", using inline OnNodesLoad, "");

    inline OnQuery2Load()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new id_node, linked_to;
				cache_get_value_name_int(i, "id_node", id_node);
				cache_get_value_name_int(i, "linked_to", linked_to);

				new from_index = GetVcNodeIndexFromId(id_node);
                if(from_index != -1)
                {
                    new to_index = GetVcNodeIndexFromId(linked_to);
                    if(to_index != -1)
                    {
                        new link_index = Iter_Free(VC_NodesLinks[from_index]);
                        if(link_index != cellmin)
                        {
                            if(CreateConnection(VC_Nodes[from_index][vcNode_MapNodeID], VC_Nodes[to_index][vcNode_MapNodeID], VC_NodesLinks[from_index][link_index][vcNodeLink_ConnectionID]) == GPS_ERROR_NONE)
                            {
                                VC_NodesLinks[from_index][link_index][vcNodeLink_ToId] = linked_to;
                                VC_NodesLinks[from_index][link_index][vcNodeLink_ToIndex] = to_index;
                                Iter_Add(VC_NodesLinks[from_index], link_index);
                            }
                        }
                    }
                }
			}

            /*foreach(new i : VC_Nodes)
            {
                new string[256], Float:x, Float:y, Float:z;
				GetMapNodePos(VC_Nodes[i][vcNode_MapNodeID], x, y, z);
                format(string, 256, "{00CCFF}Id: %d\nNoideId: %d\nmedian: %f", VC_Nodes[i][vcNode_ID], _:VC_Nodes[i][vcNode_MapNodeID], VC_Nodes[i][vcNode_Median]);
                foreach(new j : VC_NodesLinks[i])
                {
                    format(string, 256, "%s\n%d", string, VC_NodesLinks[i][j][vcNodeLink_ToId]);
                }
                CreateDynamic3DTextLabel(string, -1, x, y, z, 50.0);
            }*/
		}
	}
	mysql_tquery_inline(vc_map_db, "SELECT * FROM nodes_links;", using inline OnQuery2Load, "");
    return 1;
}