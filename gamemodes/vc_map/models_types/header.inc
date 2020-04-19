enum enum_Vc_Models_Types
{
	vc_model_type_ID,
	vc_model_type_NAME[32],
	Float:vc_model_type_STREAM_DISTANCE,
	vc_model_type_PRIORITY
};
#define MAX_VC_MODELS_TYPES 10
new Vc_Models_Types[MAX_VC_MODELS_TYPES][enum_Vc_Models_Types];
new Iterator:Vc_Models_Types<MAX_VC_MODELS_TYPES>;