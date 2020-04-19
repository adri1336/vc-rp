CreateAutopilotVehicle(forplayerid, modelid, Float:x, Float:y, Float:z, color1 = -1, color2 = -1)
{
    //obtener el nodo mas cercano
    new MapNode:node;
    GetClosestMapNodeToPoint(x, y, z, node);
    if(!IsValidMapNode(node)) return INVALID_VEHICLE_ID;

    //sacar node index
    new NodeIndex = GetVcNodeIndexFromNodeId(node);
    if(NodeIndex == -1) return INVALID_VEHICLE_ID;

    //sacar el angulo con otro nodo
    if(!Iter_Contains(VC_NodesLinks[NodeIndex], 0)) return INVALID_VEHICLE_ID;
    if(!IsValidMapNode(VC_Nodes[ VC_NodesLinks[NodeIndex][0][vcNodeLink_ToIndex] ][vcNode_MapNodeID])) return INVALID_VEHICLE_ID;
    new Float:angle;
    GetAngleBetweenMapNodes(node, VC_Nodes[ VC_NodesLinks[NodeIndex][0][vcNodeLink_ToIndex] ][vcNode_MapNodeID], angle);
    angle -= 180.0;

    //calcular nueva pos
    GetMapNodePos(node, x, y, z);
    x += 4.5 * floatsin(-angle, degrees);
    y += 4.5 * floatcos(-angle, degrees);

    //crear veh
    new vehindex = CreateVehicleEx(VEHICLE_TYPE_AUTOPILOT, modelid, x, y, z, angle + 90.0, color1, color2);
    if(vehindex == INVALID_VEHICLE_INDEX) return INVALID_VEHICLE_ID;

    new vehicleid = VehicleInfo[vehindex][vinfo_VEHICLE_ID];
    ApVehicleInfo[vehicleid][apv_VehIndex] = vehindex;
    ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
    ApVehicleInfo[vehicleid][apv_DestroyTimer] = Timer:-1;
    ApVehicleInfo[vehicleid][apv_CreatedBy] = forplayerid;
    ApVehicleInfo[vehicleid][apv_PathId] = Path:INVALID_PATH_ID;
    
    //fake driver
    ApVehicleInfo[vehicleid][apv_FakeDriver] = CreateDynamicObject(FAKE_DRIVER_MODELID, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, ApVehicleInfo[vehicleid][apv_FakeDriver], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_FAKE_DRIVER);

    new Float:sx, Float:sy, Float:sz;
    GetVehicleModelInfo(VehicleInfo[vehindex][vinfo_MODELID], VEHICLE_MODEL_INFO_FRONTSEAT, sx, sy, sz);
    AttachDynamicObjectToVehicle(ApVehicleInfo[vehicleid][apv_FakeDriver], vehicleid, -sx, sy, sz, 0.0, 0.0, 0.0);

    //taximeter
    if(VehicleInfo[vehindex][vinfo_MODELID] == 420 || VehicleInfo[vehindex][vinfo_MODELID] == 438)
    {
        ApVehicleInfo[vehicleid][apv_Taximeter] = true;
    }
    Iter_Add(ApVehicleInfo, vehicleid);

    //destroy timer
    if(forplayerid != INVALID_PLAYER_ID)
    {
        pAutoPilotVehicleId[forplayerid] = vehicleid;
        ApVehicleInfo[vehicleid][apv_DestroyTimer] = defer OnAutopilotRequestDestroy[AP_DEFAULT_DESTROY_SECONDS * 1000](vehicleid);
    }
    return vehicleid;
}

DestroyAutoPilotVehicleInfo(vehicleid, bool:destroy = true)
{
    if(ApVehicleInfo[vehicleid][apv_Timer] != Timer:-1)
    {
        stop ApVehicleInfo[vehicleid][apv_Timer];
        ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
    }
    if(ApVehicleInfo[vehicleid][apv_DestroyTimer] != Timer:-1)
    {
        stop ApVehicleInfo[vehicleid][apv_DestroyTimer];
        ApVehicleInfo[vehicleid][apv_DestroyTimer] = Timer:-1;
    }
    if(ApVehicleInfo[vehicleid][apv_PathId] != Path:INVALID_PATH_ID)
    {
        DestroyPath(ApVehicleInfo[vehicleid][apv_PathId]);
        ApVehicleInfo[vehicleid][apv_PathId] = Path:INVALID_PATH_ID;
    }
    ApVehicleInfo[vehicleid][apv_InPath] = false;
    ApVehicleInfo[vehicleid][apv_Passenger] = INVALID_PLAYER_ID;
    ApVehicleInfo[vehicleid][apv_Distance] = 0.0;
    ApVehicleInfo[vehicleid][apv_Paused] = false;
    ApVehicleInfo[vehicleid][apv_PathSize] = 0;
    ApVehicleInfo[vehicleid][apv_CurrentPathIndex] = 0;
    ApVehicleInfo[vehicleid][apv_GoX] = 0.0;
    ApVehicleInfo[vehicleid][apv_GoY] = 0.0;
    ApVehicleInfo[vehicleid][apv_GoZ] = 0.0;
    ApVehicleInfo[vehicleid][apv_GoAngle] = 0.0;
    ApVehicleInfo[vehicleid][apv_Angle] = 0.0;
    ApVehicleInfo[vehicleid][apv_SpeedLimit] = 0.0;
    ApVehicleInfo[vehicleid][apv_CurrSpeed] = 0.0;
    ApVehicleInfo[vehicleid][apv_Distance] = 0.0;
    ApVehicleInfo[vehicleid][apv_OldPos] = Float:{0.0, 0.0, 0.0};
    if(destroy)
    {
        ApVehicleInfo[vehicleid][apv_Taximeter] = false;
        ApVehicleInfo[vehicleid][apv_CreatedBy] = INVALID_PLAYER_ID;
        ApVehicleInfo[vehicleid][apv_VehIndex] = INVALID_VEHICLE_INDEX;
        if(ApVehicleInfo[vehicleid][apv_FakeDriver] != INVALID_STREAMER_ID)
        {
            DestroyDynamicObject(ApVehicleInfo[vehicleid][apv_FakeDriver]);
            ApVehicleInfo[vehicleid][apv_FakeDriver] = INVALID_STREAMER_ID;
        }
        Iter_Remove(ApVehicleInfo, vehicleid);
    }
    return 1;
}

DestroyAutoPilotVehicle(vehicleid)
{
    if(ApVehicleInfo[vehicleid][apv_Passenger] != INVALID_PLAYER_ID)
    {
        HidePlayerAuxTextDraw(ApVehicleInfo[vehicleid][apv_Passenger]);
        pAutoPilotVehicleId[ ApVehicleInfo[vehicleid][apv_Passenger] ] = INVALID_VEHICLE_ID;
        if(pAutoPilotTimerLeft[ ApVehicleInfo[vehicleid][apv_Passenger] ] != Timer:-1)
        {
            stop pAutoPilotTimerLeft[ ApVehicleInfo[vehicleid][apv_Passenger] ];
            pAutoPilotTimerLeft[ ApVehicleInfo[vehicleid][apv_Passenger] ] = Timer:-1;
        }
    }
    if(ApVehicleInfo[vehicleid][apv_CreatedBy] != INVALID_PLAYER_ID) DestroyVehicleEx(ApVehicleInfo[vehicleid][apv_VehIndex]);
    else
    {
        DestroyAutoPilotVehicleInfo(vehicleid, false);
        SetVehicleToRespawn(vehicleid);
    }
    return 1;
}

ResumeVehicleAutoPilot(vehicleid)
{
    if(ApVehicleInfo[vehicleid][apv_Timer] != Timer:-1)
    {
        stop ApVehicleInfo[vehicleid][apv_Timer];
        ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
    }
    ApVehicleInfo[vehicleid][apv_Paused] = false;
    ApVehicleInfo[vehicleid][apv_Timer] = repeat OnAutopilotUpdate(vehicleid);
    return 1;
}

PauseVehicleAutoPilot(vehicleid)
{
    if(ApVehicleInfo[vehicleid][apv_Timer] != Timer:-1)
    {
        stop ApVehicleInfo[vehicleid][apv_Timer];
        ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
    }
    ApVehicleInfo[vehicleid][apv_Paused] = true;
    ApVehicleInfo[vehicleid][apv_CurrSpeed] = 0.0;
    
    new Float:x, Float:y, Float:z;
    x = ApVehicleInfo[vehicleid][apv_GoX] + (3.5 * floatsin(-(ApVehicleInfo[vehicleid][apv_Angle] - 180.0), degrees));
    y = ApVehicleInfo[vehicleid][apv_GoY] + (3.5 * floatcos(-(ApVehicleInfo[vehicleid][apv_Angle] - 180.0), degrees));
    z = ApVehicleInfo[vehicleid][apv_GoZ];
    SetVehiclePos(vehicleid, x, y, z);
    return 1;
}

AutoPilotVehicleGoTo(forplayerid, vehicleid, Float:x, Float:y, Float:z)
{
    new Float:vehicleX, Float:vehicleY, Float:vehicleZ;
    GetVehiclePos(vehicleid, vehicleX, vehicleY, vehicleZ);
    SetVehiclePos(vehicleid, vehicleX, vehicleY, vehicleZ + 1.0);

    new	MapNode:from_node, MapNode:to_node;
	GetClosestMapNodeToPoint(vehicleX, vehicleY, vehicleZ, from_node);
	GetClosestMapNodeToPoint(x, y, z, to_node);
	if(IsValidMapNode(from_node) && IsValidMapNode(to_node) && from_node != to_node)
	{
        if(pAutoPilotTimerLeft[forplayerid] != Timer:-1)
        {
            stop pAutoPilotTimerLeft[forplayerid];
            pAutoPilotTimerLeft[forplayerid] = Timer:-1;
        }
        pAutoPilotSecondsLeft[forplayerid] = DEFAULT_AUTOPILOT_SECONDS_LEFT;
        pAutoPilotVehicleId[forplayerid] = vehicleid;
        pAutoPilotTimerLeft[forplayerid] = repeat OnPlayerCheckAutopilotVeh(forplayerid, pAutoPilotVehicleId[forplayerid]);

        ApVehicleInfo[vehicleid][apv_InPath] = true;
        ApVehicleInfo[vehicleid][apv_CurrentPathIndex] = 0;
        ApVehicleInfo[vehicleid][apv_Passenger] = forplayerid;
        ApVehicleInfo[vehicleid][apv_Distance] = 0.0;
        GetVehiclePos(vehicleid, ApVehicleInfo[vehicleid][apv_OldPos][0], ApVehicleInfo[vehicleid][apv_OldPos][1], ApVehicleInfo[vehicleid][apv_OldPos][2]);
        
		FindPathThreaded(from_node, to_node, "OnAutopilotPathCalculated", "i", vehicleid);
		return 1;
	}
    else CallRemoteFunction("OnAutopilotPathFailed", "ii", forplayerid, vehicleid);
    return 0;
}

Float:atan2VehicleZ(Float:Xb,Float:Yb,Float:Xe,Float:Ye)
{
	new Float:a = floatabs(360.0 - atan2( Xe-Xb,Ye-Yb));
	if(360 > a > 180)return a;
	return a-360.0;
}

PullVehicleIntoDirection(vehicleid, Float:x, Float:y, Float:z, Float:speed)
{
	new
        Float:distance,
        Float:vehicle_pos[3];

    GetVehiclePos(vehicleid, vehicle_pos[0], vehicle_pos[1], vehicle_pos[2]);
	
	new Float: oz = atan2VehicleZ(vehicle_pos[0], vehicle_pos[1], x, y);
	new Float: vz;
	GetVehicleZAngle(vehicleid, vz);
	if(oz < vz-180) oz = oz+360;
	if(vz < oz-180) vz = vz+360;
	new Float: cz = floatabs(vz - oz);
	
    x -= vehicle_pos[0];
    y -= vehicle_pos[1];
    z -= vehicle_pos[2];
    
    distance = floatsqroot((x * x) + (y * y));
    x = (speed * x) / distance;
    y = (speed * y) / distance;
    GetVehicleVelocity(vehicleid, vehicle_pos[0], vehicle_pos[0], z);
    
	if(cz > 0)
 	{
		new Float: fz = cz*0.0015;
		if(vz < oz) SetVehicleAngularVelocity(vehicleid, 0.0, 0.0, fz);
		if(vz > oz) SetVehicleAngularVelocity(vehicleid, 0.0, 0.0, -fz);
	}
	
    SetVehicleVelocity(vehicleid, x, y, z - 0.01);
}

UpdateAutopilotGoCoords(vehicleid)
{
    if(ApVehicleInfo[vehicleid][apv_CurrentPathIndex] >= ApVehicleInfo[vehicleid][apv_PathSize] - 1)
    {
        ApVehicleInfo[vehicleid][apv_SpeedLimit] = 0.0;
        ApVehicleInfo[vehicleid][apv_GoX] += 6.0 * floatsin(-(ApVehicleInfo[vehicleid][apv_Angle] - 90.0), degrees);
        ApVehicleInfo[vehicleid][apv_GoY] += 6.0 * floatcos(-(ApVehicleInfo[vehicleid][apv_Angle] - 90.0), degrees);
    }
    else
    {
        new MapNode:currentNode, Float:x, Float:y, Float:z;
        GetPathNode(ApVehicleInfo[vehicleid][apv_PathId], ApVehicleInfo[vehicleid][apv_CurrentPathIndex], currentNode);
        GetMapNodePos(currentNode, x, y, z);
        
        //calcular angulo
        new Float:angle, Float:lastAngle;
        if(ApVehicleInfo[vehicleid][apv_PathSize] > ApVehicleInfo[vehicleid][apv_CurrentPathIndex] + 1)
        {
            new MapNode:nextNode;
            GetPathNode(ApVehicleInfo[vehicleid][apv_PathId], ApVehicleInfo[vehicleid][apv_CurrentPathIndex] + 1, nextNode);
            GetAngleBetweenMapNodes(currentNode, nextNode, angle);
        }
        else
        {
            new MapNode:prevNode;
            GetPathNode(ApVehicleInfo[vehicleid][apv_PathId], ApVehicleInfo[vehicleid][apv_CurrentPathIndex] - 1, prevNode);
            GetAngleBetweenMapNodes(currentNode, prevNode, angle);
        }
        if(ApVehicleInfo[vehicleid][apv_CurrentPathIndex] == 0) lastAngle = angle;
        else lastAngle = ApVehicleInfo[vehicleid][apv_Angle];

        //al lado derecho de la calzada
        if(floatabs(angle - lastAngle) >= 60.0) //saltar nodo
        {
            ApVehicleInfo[vehicleid][apv_Angle] = angle;
            ApVehicleInfo[vehicleid][apv_CurrentPathIndex] ++;
            UpdateAutopilotGoCoords(vehicleid);
            return 1;
        }
        lastAngle = angle;
        ApVehicleInfo[vehicleid][apv_Angle] = lastAngle;
        angle -= 180.0;

        new nodeIndex = GetVcNodeIndexFromNodeId(currentNode);
        if(nodeIndex != -1)
        {
            switch(VC_Nodes[nodeIndex][vcNode_SpeedLimit])
            {
                case 0: ApVehicleInfo[vehicleid][apv_SpeedLimit] = 0.4;
                case 1: ApVehicleInfo[vehicleid][apv_SpeedLimit] = 0.45;
                case 2: ApVehicleInfo[vehicleid][apv_SpeedLimit] = 0.5;
            }
            if(ApVehicleInfo[vehicleid][apv_CurrentPathIndex] >= ApVehicleInfo[vehicleid][apv_PathSize] - 2) //penultimo
            {
                ApVehicleInfo[vehicleid][apv_SpeedLimit] = 0.0;
                x += (VC_Nodes[nodeIndex][vcNode_Median] + 5.0) * floatsin(-angle, degrees);
                y += (VC_Nodes[nodeIndex][vcNode_Median] + 5.0) * floatcos(-angle, degrees);
            }
            else
            {
                x += (VC_Nodes[nodeIndex][vcNode_Median] + 2.5) * floatsin(-angle, degrees);
                y += (VC_Nodes[nodeIndex][vcNode_Median] + 2.5) * floatcos(-angle, degrees);
            }
        }
        ApVehicleInfo[vehicleid][apv_GoX] = x;
        ApVehicleInfo[vehicleid][apv_GoY] = y;
        ApVehicleInfo[vehicleid][apv_GoZ] = z;
    }
    return 1;
}