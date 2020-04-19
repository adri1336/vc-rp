#define MAX_VICE_CITY_NODES 4000
#define MAX_VICE_CITY_NODES_LINKS 4

enum E_VC_Nodes
{
    vcNode_ID,
    vcNode_IsCrossRoad,
    Float:vcNode_X,
    Float:vcNode_Y,
    Float:vcNode_Z,
    Float:vcNode_Median,
    vcNode_LeftLanes,
    vcNode_RightLanes,
    vcNode_SpeedLimit,
    vcNode_Flags,
    MapNode:vcNode_MapNodeID
};
new VC_Nodes[MAX_VICE_CITY_NODES][E_VC_Nodes],
    Iterator:VC_Nodes<MAX_VICE_CITY_NODES>;

enum E_VC_NodesLinks
{
    vcNodeLink_ToId,
    vcNodeLink_ToIndex,
    Connection:vcNodeLink_ConnectionID
};
new VC_NodesLinks[MAX_VICE_CITY_NODES][MAX_VICE_CITY_NODES_LINKS][E_VC_NodesLinks],
    Iterator:VC_NodesLinks[MAX_VICE_CITY_NODES]<MAX_VICE_CITY_NODES_LINKS>;