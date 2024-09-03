#ifndef HSD_H
#define HSD_H

#include "math.h"
#include "gx.h"

#define JOBJ_SKELETON (1 << 0)
#define JOBJ_SKELETON_ROOT (1 << 1)
#define JOBJ_ENVELOPE_MODEL (1 << 2)
#define JOBJ_CLASSICAL_SCALING (1 << 3)
#define JOBJ_HIDDEN (1 << 4)
#define JOBJ_PTCL (1 << 5)
#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_LIGHTING (1 << 7)
#define JOBJ_TEXGEN (1 << 8)
#define JOBJ_BILLBOARD (1 << 9)
#define JOBJ_VBILLBOARD (2 << 9)
#define JOBJ_HBILLBOARD (3 << 9)
#define JOBJ_RBILLBOARD (4 << 9)
#define JOBJ_INSTANCE (1 << 12)
#define JOBJ_PBILLBOARD (1 << 13)
#define JOBJ_SPLINE (1 << 14)
#define JOBJ_FLIP_IK (1 << 15)
#define JOBJ_SPECULAR (1 << 16)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_OPA (1 << 18)
#define JOBJ_XLU (1 << 19)
#define JOBJ_TEXEDGE (1 << 20)
#define JOBJ_NULL (0 << 21)
#define JOBJ_JOINT1 (1 << 21)
#define JOBJ_JOINT2 (2 << 21)
#define JOBJ_EFFECTOR (3 << 21)
#define JOBJ_USER_DEFINED_MTX (1 << 23)
#define JOBJ_MTX_INDEPEND_PARENT (1 << 24)
#define JOBJ_MTS_INDEPEND_SRT (1 << 25)
#define JOBJ_GENERALFLAG (1 << 26)
#define JOBJ_GENERALFLAG2 (1 << 27)
#define JOBJ_ROOT_OPA (1 << 28)
#define JOBJ_ROOT_XLU (1 << 29)
#define JOBJ_ROOT_TEXEDGE (1 << 30)
#define JOBJ_31 (1 << 31)

typedef struct HSD_Obj HSD_Obj;
typedef struct GOBJ GOBJ;
typedef struct JOBJ JOBJ;
typedef struct DOBJ DOBJ;
typedef struct TOBJ TOBJ;
typedef struct MOBJ MOBJ;
typedef struct AOBJ AOBJ;
typedef struct COBJ COBJ;
typedef struct WOBJ WOBJ;
typedef struct HSD_Material HSD_Material;
typedef struct GOBJProc GOBJProc;
typedef struct JOBJDesc JOBJDesc;
typedef struct HSDAllocStruct HSDAllocStruct;

struct HSD_Material
{
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    float alpha;
    float shininess;
};

struct HSD_Obj
{
    void *parent;
    s16 ref_count;
    s16 ref_count_individual;
};

struct HSDAllocStruct
{
    int x00;
    int x04;
    int x08;
    int x0C;
    
    int x10;
    int x14;
    int x18;
    int x1c;
    
    int size;
    int x24;
    int x28;
};

struct GOBJ
{
    short entity_class;      // 0x0
    char p_link;             // 0x2
    char gx_link;            // 0x3. 0-63 are gx. 64+ are reserved for camera objects
    char p_priority;         // 0x4
    char gx_pri;             // 0x5
    char obj_kind;           // 0x6
    char data_kind;          // 0x7
    GOBJ *next;              // 0x8
    GOBJ *previous;          // 0xC
    GOBJ *nextOrdered;       // 0x10
    GOBJ *previousOrdered;   // 0x14
    GOBJProc *proc;          // 0x18
    void *gx_cb;             // 0x1C
    u64 cobj_links;          // 0x20. this is used to know which cobj to render to
    void *hsd_object;        // 0x28
    void *userdata;          // 0x2C
    int destructor_function; // 0x30
    int unk_linked_list;     // 0x34
};

struct GOBJProc
{
    GOBJ *parent;
    GOBJProc *next;
    GOBJProc *prev;
    char s_link;            // 0xC
    char flags;             // 0xD
    GOBJ *parentGOBJ;       // 0x10
    void (*cb)(GOBJ *gobj); // function callback
};

struct DOBJ
{
    int parent;
    DOBJ *next; //0x04
    MOBJ *mobj; //0x08
    int *pobj;  //0x0C
    AOBJ *aobj; //0x10
    u32 flags;  //0x14
    u32 unk;
};

struct JOBJ
{
    int hsd_info;     //0x0
    int class_parent; //0x4
    JOBJ *sibling;    //0x08
    JOBJ *parent;     //0x0C
    JOBJ *child;      //0x10
    int flags;        //0x14
    DOBJ *dobj;       //0x18
    Vec4 rot;         //0x1C 0x20 0x24 0x28
    Vec3 scale;       //0x2C
    Vec3 trans;       // 0x38
    Matrix rotMtx;       // 0x44
    Vec3 *VEC;        // 0x6C
    Matrix *MTX;         // 0x78
    AOBJ *aobj;       // 0x7C
    int *RObj;
    JOBJDesc *desc;
};

struct TOBJ
{
    HSD_Obj parent;
    TOBJ *next;
    u32 id;                           //GXTexMapID
    u32 src;                          //GXTexGenSrc 0x10
    u32 mtxid;                        // 0x14
    Vec4 rotate;                      // 0x18
    Vec3 scale;                       // 0x28
    Vec3 translate;                   // 0x34
    u32 wrap_s;                       // 0x40 GXTexWrapMode
    u32 wrap_t;                       // 0x44 GXTexWrapMode
    u8 repeat_s;                      // 0x48
    u8 repeat_t;                      // 0x49
    u16 anim_id;                      // 0x4A
    u32 flags;                        // 0x4C
    f32 blending;                     // 0x50
    u32 magFilt;                      // 0x54 GXTexFilter
    struct _HSD_ImageDesc *imagedesc; // 0x58
    struct _HSD_Tlut *tlut;           // 0x5C
    struct _HSD_TexLODDesc *lod;      // 0x60
    AOBJ *aobj;                       // 0x64
    struct _HSD_ImageDesc **imagetbl;
    struct _HSD_Tlut **tluttbl;
    u8 tlut_no;
    Mtx mtx;
    u32 coord; //GXTexCoordID
    struct _HSD_TObjTev *tev;
};

struct AOBJ
{
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
    f32 framerate;
    struct _HSD_FObj *fobj;
    struct _HSD_Obj *hsd_obj;
};

struct MOBJ
{
    int *parent;
    u32 rendermode;
    TOBJ *tobj;
    HSD_Material *mat;
    struct _HSD_PEDesc *pe;
    AOBJ *aobj;
    /*
    struct _HSD_TObj *ambient_tobj;
    struct _HSD_TObj *specular_tobj;
    */
    struct _HSD_TExpTevDesc *tevdesc;
    union _HSD_TExp *texp;

    struct _HSD_TObj *tobj_toon;
    struct _HSD_TObj *tobj_gradation;
    struct _HSD_TObj *tobj_backlight;
    f32 z_offset;
};

struct JOBJDesc
{
    char *class_name;       //0x00
    u32 flags;              //0x04
    struct JOBJDesc *child; //0x08
    struct JOBJDesc *next;  //0x0C
    union
    {
        struct _HSD_DObjDesc *dobjdesc;
        struct _HSD_Spline *spline;
        struct _HSD_SList *ptcl;
    } u;                            //0x10
    Vec3 rotation;                  //0x14 - 0x1C
    Vec3 scale;                     //0x20 - 0x28
    Vec3 position;                  //0x2C - 0x34
    Mtx mtx;                        //0x38
    struct _HSD_RObjDesc *robjdesc; //0x3C
};

struct COBJ
{
    HSD_Obj parent;      // 0x0
    u32 flags;           //0x08
    f32 viewport_left;   //0x0C
    f32 viewport_right;  //0x10
    f32 viewport_top;    //0x14
    f32 viewport_bottom; //0x18
    u16 scissor_left;    //0x1C
    u16 scissor_right;   //0x1E
    u16 scissor_top;     //0x20
    u16 scissor_bottom;  //0x22
    WOBJ *eye_position;  //0x24
    WOBJ *interest;      //0x28
    union
    {
        f32 roll; //0x28
        Vec3 up;  //0x28 - 0x34
    } u;
    f32 near; //0x3C
    f32 far;  //0x40
    union
    {
        struct
        {
            f32 fov;
            f32 aspect;
        } perspective;

        struct
        {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustrum;

        struct
        {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
    u8 projection_type; //0x50
    Mtx view_mtx;       //0x54
    AOBJ *aobj;         //0x84
    Mtx proj_mtx;       //0x88
};

struct WOBJ
{
    void *parent;
    u32 flags;  //0x08
    Vec3 pos;   //0xC
    AOBJ *aobj; //0x18
    void *robj; //0x1C
};

void HSD_StateInvalidate(int flags);
void HSD_StateInitTev();
void HSD_ClearVtxDesc();
void * HSD_Alloc(HSDAllocStruct *param_1);

COBJ *COBJ_GetCurrent();

int *JObj_LoadJoint(JOBJDesc *joint);
void JOBJ_SetMtxDirtySub(JOBJ *jobj);
int JObj_GetWorldPosition(JOBJ *source, Vec3 *add, Vec3 *dest);

GOBJ *GObj_Create(int type, int subclass, int flags);
void GObj_AddUserData(GOBJ *gobj, char userDataKind, void *destructor, void *userData);
void GObj_AddGXLink(GOBJ *gobj, void *cb, int gx_link, int gx_pri);
void GObj_AddObject(GOBJ *gobj, u8 unk, void *object);
JOBJ *GObj_GetJObjAtIndex(GOBJ *gobj, int index);
void GXLink_Common(GOBJ *gobj, int gx_pri);

#endif