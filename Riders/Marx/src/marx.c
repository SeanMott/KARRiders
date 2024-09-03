#include "../../../MexTK/include/kex.h"

typedef struct HatData
{
    JOBJ *parent_jobj;
} HatData;

HSDAllocStruct alloc_struct = 
{
    0,
    0,
    1,
    0,

    1,
    -1,
    0,
    -1,

    sizeof(HatData),
    4,
    0
};

/// 
/// 
/// 
void GXLink_Hat(GOBJ *gobj, int pri)
{
    if (pri == 0)
    {
        HatData *data = gobj->userdata;

        JOBJ *parent = data->parent_jobj;
        JOBJ *root = gobj->hsd_object;

        PSMTXCopy(&parent->rotMtx, &root->rotMtx);
        root->flags |= JOBJ_USER_DEFINED_MTX | JOBJ_MTX_INDEPEND_PARENT | JOBJ_MTS_INDEPEND_SRT;

        JOBJ_SetMtxDirtySub(root);

        GXLink_Common(gobj, pri);
    }
}

/// 
/// 
/// 
void Init_Physics_Hat(GOBJ *rider_gobj, int *jobj_desc)
{
    // create physics gobj
    GOBJ *gobj = GObj_Create(0xE, 0x7, 0);

    // add gx link
    GObj_AddGXLink(gobj, GXLink_Hat, 6, 1);

    // alloc data pointer
    HatData *data_ptr = HSD_Alloc(&alloc_struct);
    GObj_AddUserData(gobj, 0x11, 0x8018fda0, data_ptr);
    data_ptr->parent_jobj = GObj_GetJObjAtIndex(rider_gobj, 6);

    // load jobj
    JOBJ *hat_joint = JObj_LoadJoint(jobj_desc);
    GObj_AddObject(gobj, 2, hat_joint);
}


///
///
///
void OnInit(char *rider_data)
{
    OSReport("Initializing Marx %8X\n", rider_data);
    
    // get rope jobj desc
    char *rider_gobj = *(int *)(rider_data);
    char *rdData = *(int *)(rider_data + 0x18);
    char *model_data = *(int *)(rdData + 0x4);
    int *rope_jobj_desc = *(int *)(model_data + 0x30);
    
    OSReport("Hat Pointer %8X\n", model_data);

    Init_Physics_Hat(rider_gobj, rope_jobj_desc);
}
