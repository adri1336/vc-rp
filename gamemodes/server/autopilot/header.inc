forward OnAutopilotPathCalculated(Path:pathid, vehicleid);
forward OnAutopilotPathFailed(forplayerid, vehicleid);

#define TAXIMETER_BASE_PAYMENT 3.0 //3$ cada 1km
#define FAKE_DRIVER_MODELID -1004
#define AP_DEFAULT_DESTROY_SECONDS 60

enum E_ApVehicleInfo
{
    Timer:apv_Timer,
    Timer:apv_DestroyTimer,
    bool:apv_InPath,
    bool:apv_Paused,
    apv_CreatedBy,
    apv_Passenger,
    apv_VehIndex,

    apv_PathSize,
    Path:apv_PathId,
    apv_CurrentPathIndex,

    Float:apv_GoX,
    Float:apv_GoY,
    Float:apv_GoZ,
    Float:apv_GoAngle,
    Float:apv_Angle,
    Float:apv_SpeedLimit,
    Float:apv_CurrSpeed,

    //taxi
    bool:apv_Taximeter,
    Float:apv_Distance,
    Float:apv_OldPos[3],
    
    //object
    apv_FakeDriver
};
new ApVehicleInfo[MAX_VEHICLES][E_ApVehicleInfo],
    Iterator:ApVehicleInfo<MAX_VEHICLES>;