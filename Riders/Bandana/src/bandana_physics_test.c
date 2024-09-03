#include "../../../MexTK/include/kex.h"
#include "physics_verlet.h"

typedef struct PhysicsData
{
    JOBJ *parent_jobj;
    Manager physics;
} PhysicsData;

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

    sizeof(PhysicsData),
    4,
    0
};

///
///
///
void TestDraw(Vec3 *pos)
{
    // init GX
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, 0, GX_LO_CLEAR, GX_GREATER, 0);

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_DISABLE);
    GXSetNumTexGens(0);

    //GX_blr(0, 0);

    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, Register, Vertex, 0, 0, 2);
    GXSetCullMode(GX_CULL_NONE);

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    //OSReport("%8X\n", &COBJ_GetCurrent()->view_mtx);
    GXLoadPosMtxImm(COBJ_GetCurrent()->view_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    // draw quad
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(pos->X, pos->Y, pos->Z);
    GXColor4u8(255, 255, 255, 255);

    GXPosition3f32(pos->X + 5, pos->Y, pos->Z);
    GXColor4u8(255, 255, 255, 255);

    GXPosition3f32(pos->X + 5, pos->Y + 5, pos->Z);
    GXColor4u8(255, 255, 255, 255);

    GXPosition3f32(pos->X, pos->Y + 5, pos->Z);
    GXColor4u8(255, 255, 255, 255);

    // invalidate hsd state
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    HSD_ClearVtxDesc();
}

// void RenderPhysics(RopeSimulation *sim, Vec3 *pos)
// {
//     // init GX
//     GXSetColorUpdate(GX_ENABLE);
//     GXSetAlphaUpdate(GX_DISABLE);
//     GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
//     GXSetAlphaCompare(GX_GREATER, 0, GX_LO_CLEAR, GX_GREATER, 0);

//     GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
//     GXSetZCompLoc(GX_DISABLE);
//     GXSetNumTexGens(0);

//     //GX_blr(0, 0);

//     GXSetNumTevStages(1);
//     GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
//     GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

//     GXSetNumChans(1);
//     GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, Register, Vertex, 0, 0, 2);
//     GXSetCullMode(GX_CULL_NONE);

//     GXClearVtxDesc();
//     GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
//     GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
//     GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
//     GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

//     //OSReport("%8X\n", &COBJ_GetCurrent()->view_mtx);
//     GXLoadPosMtxImm(COBJ_GetCurrent()->view_mtx, GX_PNMTX0);
//     GXSetCurrentMtx(GX_PNMTX0);

//     // draw quad
//     GXBegin(GX_LINES, GX_VTXFMT0, (MAX_SPRING_LENGTH - 1) * 2);
// 	for (int a = 0; a < MAX_SPRING_LENGTH - 1; ++a)
// 	{
// 		Mass* mass1 = &sim->masses[a];
// 		Vec3* pos1 = &mass1->pos;

// 		Mass* mass2 = &sim->masses[a + 1];
// 		Vec3* pos2 = &mass2->pos;

//         GXPosition3f32(pos->X + pos1->X, pos->Y + pos1->Y, pos->Z + pos1->Z);
//         GXColor4u8(255, 255, 255, 255);
        
//         GXPosition3f32(pos->X + pos2->X, pos->Y + pos2->Y, pos->Z + pos2->Z);
//         GXColor4u8(255, 255, 255, 255);
// 	}

//     // invalidate hsd state
//     HSD_StateInvalidate(-1);
//     HSD_StateInitTev();
//     HSD_ClearVtxDesc();
// }

/*void GXLink_Physics(GOBJ *gobj, int pri)
{
    if (pri == 0)
    {
        PhysicsData *data = gobj->userdata;

        Vec3 pos;
        JObj_GetWorldPosition(data->parent_jobj, 0, &pos);
        pos.Y += 2;
        
        //data->physics.ropeConnectionPos = pos;

        float milliseconds = 33;
        float dt = milliseconds / 1000.0f;
        float maxPossible_dt = 0.002f;
        int numOfIterations = (int)(dt / maxPossible_dt) + 1;
        if (numOfIterations != 0)
            dt = dt / numOfIterations;

        data->physics.ropeConnectionVel = Vec3_Mult(Vec3_Sub(pos, data->physics.ropeConnectionPos), 10);

        for (int a = 0; a < numOfIterations; a++)
            Simulation_Operate(&data->physics, dt);

        Vec3 temp = {0, 0, 0};
        RenderPhysics(&data->physics, &temp);
    }
}*/

void RenderPhysics(Manager *manager)
{
    // init GX
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, 0, GX_LO_CLEAR, GX_GREATER, 0);

    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_DISABLE);
    GXSetNumTexGens(0);

    //GX_blr(0, 0);

    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, Register, Vertex, 0, 0, 2);
    GXSetCullMode(GX_CULL_NONE);

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    //OSReport("%8X\n", &COBJ_GetCurrent()->view_mtx);
    GXLoadPosMtxImm(COBJ_GetCurrent()->view_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    // draw quad
    GXBegin(GX_LINES, GX_VTXFMT0, manager->spring_num * 2);
	for (int a = 0; a < manager->spring_num; a++)
	{
		Vec3* pos1 = &manager->springs[a].p0->pos;
		Vec3* pos2 = &manager->springs[a].p1->pos;

        int is_axis = manager->springs[a].p0->axis || manager->springs[a].p1->axis;
        
        GXPosition3f32(pos1->X, pos1->Y, pos1->Z);
        if (is_axis)
        {
            GXColor4u8(255, 255, 255, 0);
        }
        else
        {
            GXColor4u8(255, 255, 255, 255);
        }
        
        GXPosition3f32(pos2->X, pos2->Y, pos2->Z);
        if (is_axis)
        {
            GXColor4u8(255, 255, 255, 0);
        }
        else
        {
            GXColor4u8(255, 255, 255, 255);
        }
	}

    // invalidate hsd state
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    HSD_ClearVtxDesc();
}

void GXLink_Hat(GOBJ *gobj, int pri)
{
    PhysicsData *data = gobj->userdata;

    JOBJ *parent = data->parent_jobj;
    JOBJ *root = gobj->hsd_object;
    //root->rot.Y = -1.5;

    if (pri == 0)
    {
        // Vec3 pos;
        // JObj_GetWorldPosition(parent, 0, &pos);

        // Manager_Update(&data->physics, &pos);

        // for (int i = 0; i < data->physics.mass_num - 1; i++)
        // {
        //     Mass *mass = data->physics.springs[i].p0;
        //     Mass *mass2 = data->physics.springs[i].p1;
            
        //     //angle = atan2(y2 - y, x2 - x);
        //     // create rotation
        //     //MTXRotRad(&bone->rotMtx, 'z', angle);

        //     Matrix *mtx = &root->rotMtx;
        //     PSMTXCopy(&parent->rotMtx, &root->rotMtx);

        //     if (i == 0)
        //     {
        //         //
        //         //Vec3 eye = { 0.f, 0.f, 0.f };
        //         //Vec3 target = { -1, 0.f, 0.f };
        //         //Vec3 upvec = { 0.f, 1.f, 0.f };
        //         //MTXLookAt(mtx, &eye, &upvec, &target);
        //     }
        //     else if (i > 2)
        //     {
        //         Vec3 upvec = { 0.f, 1.f, 0.f };
        //         MTXLookAt(mtx, &data->physics.springs[i].p1->pos, &upvec, &data->physics.springs[i].p0->pos);
                
        //         mtx->M03 = mass->pos.X;
        //         mtx->M13 = mass->pos.Y;
        //         mtx->M23 = mass->pos.Z;

        //         root->flags |= JOBJ_USER_DEFINED_MTX | JOBJ_MTX_INDEPEND_PARENT | JOBJ_MTS_INDEPEND_SRT;
        //     }else
        //     {
        //         // contrain mass to joint
        //         JObj_GetWorldPosition(root, 0, &mass->pos);
        //     }

        //     // set position
        //     //mtx->M03 = mass->pos.X;
        //     //mtx->M13 = mass->pos.Y;
        //     //mtx->M23 = mass->pos.Z;

        //     JOBJ_SetMtxDirtySub(root);

        //     root = root->child;
        // }
        
        // root = gobj->hsd_object;
        // PSMTXCopy(&parent->rotMtx, &root->rotMtx);
        // root->flags |= JOBJ_USER_DEFINED_MTX | JOBJ_MTX_INDEPEND_PARENT | JOBJ_MTS_INDEPEND_SRT;
        // JOBJ_SetMtxDirtySub(root);

        //GXLink_Common(gobj, pri);
        RenderPhysics(&data->physics);
    }
}


void Physics_SetJOBJ(Manager *manager, JOBJ *jobj)
{
    Mass *old = 0;
    int index = 0;
    while (jobj != 0)
    {
        // get base position
        Vec3 pos;
        JObj_GetWorldPosition(jobj, 0, &pos);

        // create mass for this bone
        Mass *new = Manager_CreateMass(manager, pos, 0.005);
        new->pinned = 1;
        new->axis = 0.4;

        // create axis spring
        Vec3 axisvec = pos;
        axisvec.X = 1;
        Mass *axis = Manager_CreateMass(manager, axisvec, 0);
        Spring_CalculateLength(Manager_CreateSpring(manager, new, axis));

        // connect to parent bone
        if (old != 0)
        {
            // create main bone spring
            Spring_CalculateLength(Manager_CreateSpring(manager, old, new));

            // link to old spring
            Spring_CalculateLength(Manager_CreateSpring(manager, old, axis));
        }

        // increment index
        index++;

        // move to next
        old = new;
        jobj = jobj->child;
    }

    // calculate the spring lengths
    /*Manager_RecalculateSpringLengths(manager);

    manager->masses[0].pinned = 1;
    manager->masses[1].pinned = 1;
    manager->masses[2].pinned = 1;

    Spring newSpring = 
    {
        .p0 = &manager->masses[1],
        .p1 = &manager->masses[3],
        .length = 1.2,
        .min_length = 1.2
    };
    Manager_AddSpring(manager, newSpring);

    Spring newSpring2 = 
    {
        .p0 = &manager->masses[0],
        .p1 = &manager->masses[4],
        .length = 1.7,
        .min_length = 1.7
    };
    Manager_AddSpring(manager, newSpring2);*/
}

///
///
///
void OnInit(char *rider_data)
{
    OSReport("Initializing Waddle Dee %8X\n", rider_data);

    // get rope jobj desc
    char *rider_gobj = *(int *)(rider_data);
    char *rdData = *(int *)(rider_data + 0x18);
    char *model_data = *(int *)(rdData + 0x4);
    int *rope_jobj_desc = *(int *)(model_data + 0x30);

    // create physics gobj
    GOBJ *gobj = GObj_Create(0xE, 0x7, 0);

    // add gx link
    GObj_AddGXLink(gobj, GXLink_Hat, 6, 1);

    // alloc data pointer
    PhysicsData *data_ptr = HSD_Alloc(&alloc_struct);
    GObj_AddUserData(gobj, 0x11, 0x8018fda0, data_ptr);
    data_ptr->parent_jobj = GObj_GetJObjAtIndex(rider_gobj, 6);
    //Manager_Init(&data_ptr->physics, 5);

    // load jobj
    JOBJ *hat_joint = JObj_LoadJoint(rope_jobj_desc);
    GObj_AddObject(gobj, 2, hat_joint);

    // load physics
    Physics_SetJOBJ(&data_ptr->physics, hat_joint);

    // add proc
    // HSD_GObj_AddProc(pHVar4,FUN_80281c3c,1);

    OSReport("PhysicsData %8X \n", &data_ptr->physics.masses[0]);
}

///
///
///
void OnInput(char *rider_data)
{
    int state = *(int *)(rider_data + 0x1C);
    int input = *(int *)(rider_data + 0x3E4);
    

    if (state == 0x71)
    {
        if (input & PAD_BUTTON_Y)
        {  
            Rider_StateChange(0.0, 1.0, rider_data, 400, -1, 0);
        }
        if (input & PAD_BUTTON_X)
        {  
            Rider_StateChange(0.0, 1.0, rider_data, 403, -1, 0);
        }
    }
    
    if (state >= 400 && state <= 402)
    {
        Rider_SetModelVisibility(rider_data, 2, 0);
        Rider_SetUnknownFlag(rider_data, 2);
    }
    else
    {
        Rider_SetModelVisibility(rider_data, 2, -1);
        Rider_SetUnknownFlag(rider_data, 2);
    }

    //int current_ability = *(int *)(rider_data + 0x454);

    /*if (input & PAD_BUTTON_Y)
    {
        if (current_ability == -1)
        {
            Kirby_GetCopyAbility(rider_data, 3);
        }
        else
        {
            *(int *)(rider_data + 0x91C) = 0;
        }
    }
    else
    if (input & PAD_TRIGGER_Z)
    {
        if (current_ability == -1)
        {
            Kirby_GetCopyAbility(rider_data, 0);
        }
        else
        {
            *(int *)(rider_data + 0x91C) = 0;
        }
    }*/

}

void AnimCB(int *rider_data)
{  
    if (Rider_CheckAnimationEnd(rider_data)) 
    {
        Rider_StateChange(0.0, 1.0, rider_data, 401, -1, 0);
    }
}
void AnimCB2(int *rider_data)
{  
    if (Rider_CheckAnimationEnd(rider_data)) 
    {
        Rider_StateChange(0.0, 1.0, rider_data, 402, -1, 0);
    }
}

__attribute__((used)) static struct StateLogic state_logic[] = 
{
    {
        236,
        0,
        AnimCB,
        0,
        0x801BAEA8,
        0x801BAEC8,
        0x801BAEF0,
        0x801BAEF4,
    },
    {
        237,
        0,
        AnimCB2,
        0,
        0x801BAEA8,
        0x801BAEC8,
        0x801BAEF0,
        0x801BAEF4,
    },
    {
        238,
        0,
        0x801BAC70,
        0,
        0x801BAEA8,
        0x801BAEC8,
        0x801BAEF0,
        0x801BAEF4,
    },
    {
        1,
        0,
        0x801BAC70,
        0,
        0x801BAEA8,
        0x801BAEC8,
        0x801BAEF0,
        0x801BAEF4,
    },
};
