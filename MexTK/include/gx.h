#ifndef GX_H
#define GX_H

typedef struct GXColor GXColor;

struct GXColor
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

struct GXRenderModeObj
{
    u32 viTVMode;             // 0x0
    u16 fbWidth;              // 0x4
    u16 efbHeight;            // 0x6
    u16 xfbHeight;            // 0x8
    u16 viXOrigin;            // 0xA
    u16 viYOrigin;            // 0xC
    u16 viWidth;              // 0xE
    u16 viHeight;             // 0x10
    u32 xfbMode;              // 0x14
    u8 field_rendering;       // 0x18
    u8 aa;                    // 0x19
    u8 sample_pattern[12][2]; // 0x1a
    u8 vfilter[7];
};

typedef struct GXPipe
{
    union
    {
        u8 U8;
        s8 S8;
        u16 U16;
        s16 S16;
        u32 U32;
        s32 S32;
        f32 F32;
    } d;
} GXPipe;

typedef enum GXBool
{
    GX_DISABLE,
    GX_ENABLE
} GXBool;

typedef enum GXCullMode
{
    GX_CULL_NONE,
    GX_CULL_FRONT,
    GX_CULL_BACK,
    GX_CULL_ALL
} GXCullMode;

typedef enum GXAttribute
{
    GX_VA_PNMTXIDX = 0,
    GX_VA_TEX0MTXIDX,
    GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX,
    GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX,
    GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX,
    GX_VA_POS,
    GX_VA_NRM,
    GX_VA_CLR0,
    GX_VA_CLR1,
    GX_VA_TEX0,
    GX_VA_TEX1,
    GX_VA_TEX2,
    GX_VA_TEX3,
    GX_VA_TEX4,
    GX_VA_TEX5,
    GX_VA_TEX6,
    GX_VA_TEX7,
    GX_POS_MTX_ARRAY,
    GX_NRM_MTX_ARRAY,
    GX_TEX_MTX_ARRAY,
    GX_LIGHT_ARRAY,
    GX_VA_NBT,
    GX_VA_MAX_ATTR,
    GX_VA_NULL = 255,
} GXAttribute;

typedef enum GXAttributeType
{
    GX_NONE = 0,
    GX_DIRECT,
    GX_INDEX8,
    GX_INDEX16,
} GXAttributeType;

typedef enum GXVtxFmt
{
    GX_VTXFMT0 = 0,
    GX_VTXFMT1,
    GX_VTXFMT2,
    GX_VTXFMT3,
    GX_VTXFMT4,
    GX_VTXFMT5,
    GX_VTXFMT6,
    GX_VTXFMT7,
    GX_MAX_VTXFMT,
} GXVtxFmt;

typedef enum GXComponentContents
{
    GX_POS_XY = 0,
    GX_POS_XYZ,
    GX_NRM_XYZ = 0,
    GX_NRM_NBT,
    GX_NRM_NBT3,
    GX_CLR_RGB = 0,
    GX_CLR_RGBA,
    GX_TEX_S = 0,
    GX_TEX_ST,
} GXComponentContents;

typedef enum GXComponentType
{
    GX_U8 = 0,
    GX_S8,
    GX_U16,
    GX_S16,
    GX_F32,
    GX_RGB565 = 0,
    GX_RGB8,
    GX_RGBX8,
    GX_RGBA4,
    GX_RGBA6,
    GX_RGBA8,
} GXComponentType;

typedef enum GXTexCoordID
{
    GX_TEXCOORD0 = 0,
    GX_TEXCOORD1,
    GX_TEXCOORD2,
    GX_TEXCOORD3,
    GX_TEXCOORD4,
    GX_TEXCOORD5,
    GX_TEXCOORD6,
    GX_TEXCOORD7,
    GX_MAX_TEXCOORD,
    GX_TEXCOORD_NULL = 255,
} GXTexCoordID;

typedef enum GXTexGenType
{
    GX_TG_MTX3x4 = 0,
    GX_TG_MTX2x4,
    GX_TG_BUMP0,
    GX_TG_BUMP1,
    GX_TG_BUMP2,
    GX_TG_BUMP3,
    GX_TG_BUMP4,
    GX_TG_BUMP5,
    GX_TG_BUMP6,
    GX_TG_BUMP7,
    GX_TG_SRTG,
} GXTexGenType;

typedef enum GXTexMtx
{
    GX_TEXMTX0 = 30,
    GX_TEXMTX1 = 33,
    GX_TEXMTX2 = 36,
    GX_TEXMTX3 = 39,
    GX_TEXMTX4 = 42,
    GX_TEXMTX5 = 45,
    GX_TEXMTX6 = 48,
    GX_TEXMTX7 = 51,
    GX_TEXMTX8 = 54,
    GX_TEXMTX9 = 57,
    GX_IDENTITY = 60,
} GXTexMtx;

typedef enum GXTexGenSrc
{
    GX_TG_POS = 0,
    GX_TG_NRM,
    GX_TG_BINRM,
    GX_TG_TANGENT,
    GX_TG_TEX0,
    GX_TG_TEX1,
    GX_TG_TEX2,
    GX_TG_TEX3,
    GX_TG_TEX4,
    GX_TG_TEX5,
    GX_TG_TEX6,
    GX_TG_TEX7,
    GX_TG_TEXCOORD0,
    GX_TG_TEXCOORD1,
    GX_TG_TEXCOORD2,
    GX_TG_TEXCOORD3,
    GX_TG_TEXCOORD4,
    GX_TG_TEXCOORD5,
    GX_TG_TEXCOORD6,
    GX_TG_COLOR0,
    GX_TG_COLOR1,
} GXTexGenSrc;

typedef enum GXPrimitive
{
    GX_QUADS = 128,
    GX_TRIANGLES = 144,
    GX_TRIANGLESTRIP = 152,
    GX_TRIANGLEFAN = 160,
    GX_LINES = 168,
    GX_LINESTRIP = 176,
    GX_POINTS = 184,
} GXPrimitive;

typedef enum GXChannelID
{
    GX_COLOR0 = 0,
    GX_COLOR1,
    GX_ALPHA0,
    GX_ALPHA1,
    GX_COLOR0A0,
    GX_COLOR1A1,
    GX_COLOR_ZERO,
    GX_ALPHA_BUMP,
    GX_ALPHA_BUMPN,
    GX_COLOR_NULL = 255,
} GXChannelID;

typedef enum GXTexFmt
{
    GX_TF_I4 = 0,
    GX_TF_I8,
    GX_TF_IA4,
    GX_TF_IA8,
    GX_TF_RGB565,
    GX_TF_RGB5A3,
    GX_TF_RGBA8,
    GX_TF_CMPR = 14,
    GX_CTF_R4 = 32,
    GX_CTF_RA4 = 34,
    GX_CTF_RA8,
    GX_CTF_YUVA8 = 38,
    GX_CTF_A8,
    GX_CTF_R8,
    GX_CTF_G8,
    GX_CTF_B8,
    GX_CTF_RG8,
    GX_CTF_GB8,
    GX_TF_Z8 = 17,
    GX_TF_Z16 = 19,
    GX_TF_Z24X8 = 22,
    GX_CTF_Z4 = 48,
    GX_CTF_Z8M = 57,
    GX_CTF_Z8L,
    GX_CTF_Z16L = 60,
    GX_TF_A8 = GX_CTF_A8,
} GXTexFmt;

typedef enum GXTexWrapMode
{
    GX_CLAMP = 0,
    GX_REPEAT,
    GX_MIRROR,
    GX_MAX_TEXWRAPMODE,
} GXTexWrapMode;

typedef enum GXTexMapID
{
    GX_TEXMAP0 = 0,
    GX_TEXMAP1,
    GX_TEXMAP2,
    GX_TEXMAP3,
    GX_TEXMAP4,
    GX_TEXMAP5,
    GX_TEXMAP6,
    GX_TEXMAP7,
    GX_MAX_TEXMAP,
    GX_TEXMAP_NULL = 255,
    GX_TEX_DISABLE,
} GXTexMapID;

typedef enum GXTevStageID
{
    GX_TEVSTAGE0 = 0,
    GX_TEVSTAGE1,
    GX_TEVSTAGE2,
    GX_TEVSTAGE3,
    GX_TEVSTAGE4,
    GX_TEVSTAGE5,
    GX_TEVSTAGE6,
    GX_TEVSTAGE7,
    GX_TEVSTAGE8,
    GX_TEVSTAGE9,
    GX_TEVSTAGE10,
    GX_TEVSTAGE11,
    GX_TEVSTAGE12,
    GX_TEVSTAGE13,
    GX_TEVSTAGE14,
    GX_TEVSTAGE15,
    GX_MAX_TEVSTAGE,
} GXTevStageID;

typedef enum GXTevMode
{
    GX_MODULATE = 0,
    GX_DECAL,
    GX_BLEND,
    GX_REPLACE,
    GX_PASSCLR,
} GXTevMode;

typedef enum GXCompare
{
    GX_NEVER = 0,
    GX_LESS,
    GX_EQUAL,
    GX_LEQUAL,
    GX_GREATER,
    GX_NEQUAL,
    GX_GEQUAL,
    GX_ALWAYS,
} GXCompare;

typedef enum GXAlphaOperation
{
    GX_AOP_AND = 0,
    GX_AOP_OR,
    GX_AOP_XOR,
    GX_AOP_XNOR,
    GX_MAX_ALPHAOP,
} GXAlphaOperation;

typedef enum GXBlendMode
{
    GX_BM_NONE = 0,
    GX_BM_BLEND,
    GX_BM_LOGIC,
    GX_BM_SUBTRACT,
    GX_MAX_BLENDMODE,
} GXBlendMode;

typedef enum GXBlendFactor
{
    GX_BL_ZERO = 0,
    GX_BL_ONE,
    GX_BL_SRCCLR,
    GX_BL_INVSRCCLR,
    GX_BL_SRCALPHA,
    GX_BL_INVSRCALPHA,
    GX_BL_DSTALPHA,
    GX_BL_INVDSTALPHA,
    GX_BL_DSTCLR = GX_BL_SRCCLR,
    GX_BL_INVDSTCLR = GX_BL_INVSRCCLR,
} GXBlendFactor;

typedef enum GXLogicOp
{
    GX_LO_CLEAR = 0,
    GX_LO_AND,
    GX_LO_REVAND,
    GX_LO_COPY,
    GX_LO_INVAND,
    GX_LO_NOOP,
    GX_LO_XOR,
    GX_LO_OR,
    GX_LO_NOR,
    GX_LO_EQUIV,
    GX_LO_INV,
    GX_LO_REVOR,
    GX_LO_INVCOPY,
    GX_LO_INVOR,
    GX_LO_NAND,
    GX_LO_SET,
} GXLogicOp;

typedef enum GXProjectionType
{
    GX_PERSPECTIVE = 0,
    GX_ORTHOGRAPHIC,
} GXProjectionType;

typedef enum GXPosNormMtx
{
    GX_PNMTX0 = 0,
    GX_PNMTX1 = 3,
    GX_PNMTX2 = 6,
    GX_PNMTX3 = 9,
    GX_PNMTX4 = 12,
    GX_PNMTX5 = 15,
    GX_PNMTX6 = 18,
    GX_PNMTX7 = 21,
    GX_PNMTX8 = 24,
    GX_PNMTX9 = 27,
} GXPosNormMtx;

typedef enum GXTexMtxType
{
    GX_MTX3x4 = 0,
    GX_MTX2x4,
} GXTexMtxType;

typedef enum GXColorSrc
{
    Register,
    Vertex
} GXColorSrc;


volatile GXPipe *gx_pipe;

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);

void GXSetColorUpdate(GXBool enable);

//void GXSetColor(GXColor *color);
//void GXSetLineWidth(u8 width, int tex_offsets);

void GXSetZMode(
    GXBool compare_enable,
    GXCompare func,
    GXBool update_enable);

void GXPixModeSync();
void GXInvalidateTexAll();
void GXSetAlphaCompare(
    GXCompare func0, u8 reference0,
    GXAlphaOperation operation,
    GXCompare func1, u8 reference1);
void GXSetBlendMode(
    GXBlendMode type, GXBlendFactor src_factor,
    GXBlendFactor dst_factor, GXLogicOp op);
void GXSetColorUpdate(GXBool enable);
void GXSetAlphaUpdate(GXBool enable);
void GXSetZCompLoc(GXBool enable);
void GXSetNumTexGens(u8 nTexGens);
void GX_blr(int, int);
void GXSetNumTevStages(u8 stages);
void GXSetTevOrder(
    GXTevStageID stage,
    GXTexCoordID coord,
    GXTexMapID map,
    GXChannelID color);
void GXSetTevOp(GXTevStageID stage, GXTevMode mode);
void GXSetNumChans(u8 nChans);
void GXSetChanCtrl(
    GXChannelID chan,
    GXBool enable,
    GXColorSrc amb_src,
    GXColorSrc mat_src,
    int light_mask,
    int diff_fn,
    int attn_fn);
void GXSetCullMode(GXCullMode cull_mode);
void GXClearVtxDesc();
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttribute attribute,
                     GXComponentContents contents, GXComponentType type, u8 fracBits);
void GXSetVtxDesc(GXAttribute attribute, GXAttributeType type);
void GXLoadPosMtxImm(Mtx, GXPosNormMtx);
void GXSetCurrentMtx(GXPosNormMtx);
u32 GXGetTexBufferSize(
    u16 width,
    u16 height,
    u32 format,
    GXBool mipmap,
    u8 max_lod);


/*---------------------------------------------*
 * GXVertex functions                          *
 *---------------------------------------------*/
void GXPosition3f32(f32 x, f32 y, f32 z)
{
    gx_pipe->d.F32 = x;
    gx_pipe->d.F32 = y;
    gx_pipe->d.F32 = z;
}
void GXPosition3u16(u16 x, u16 y, u16 z)
{
    gx_pipe->d.U16 = x;
    gx_pipe->d.U16 = y;
    gx_pipe->d.U16 = z;
}
void GXPosition3s16(s16 x, s16 y, s16 z)
{
    gx_pipe->d.S16 = x;
    gx_pipe->d.S16 = y;
    gx_pipe->d.S16 = z;
}
void GXPosition3u8(u8 x, u8 y, u8 z)
{
    gx_pipe->d.U8 = x;
    gx_pipe->d.U8 = y;
    gx_pipe->d.U8 = z;
}
void GXPosition3s8(s8 x, s8 y, s8 z)
{
    gx_pipe->d.S8 = x;
    gx_pipe->d.S8 = y;
    gx_pipe->d.S8 = z;
}
void GXPosition2f32(f32 x, f32 y)
{
    gx_pipe->d.F32 = x;
    gx_pipe->d.F32 = y;
}
void GXPosition2u16(u16 x, u16 y)
{
    gx_pipe->d.U16 = x;
    gx_pipe->d.U16 = y;
}
void GXPosition2s16(s16 x, s16 y)
{

    gx_pipe->d.S16 = x;
    gx_pipe->d.S16 = y;
}
void GXPosition2u8(u8 x, u8 y)
{
    gx_pipe->d.U8 = x;
    gx_pipe->d.U8 = y;
}
void GXPosition2s8(s8 x, s8 y)
{
    gx_pipe->d.S8 = x;
    gx_pipe->d.S8 = y;
}
void GXPosition1x16(u16 index)
{
    gx_pipe->d.U16 = index;
}
void GXPosition1x8(u8 index)
{
    gx_pipe->d.U8 = index;
}

void GXNormal3f32(f32 x, f32 y, f32 z)
{
    gx_pipe->d.F32 = x;
    gx_pipe->d.F32 = y;
    gx_pipe->d.F32 = z;
}
void GXNormal3s16(s16 x, s16 y, s16 z)
{
    gx_pipe->d.S16 = x;
    gx_pipe->d.S16 = y;
    gx_pipe->d.S16 = z;
}
void GXNormal3s8(s8 x, s8 y, s8 z)
{
    gx_pipe->d.S8 = x;
    gx_pipe->d.S8 = y;
    gx_pipe->d.S8 = z;
}
void GXNormal1x16(u16 index)
{
    gx_pipe->d.U32 = index;
}
void GXNormal1x8(u8 index)
{
    gx_pipe->d.U8 = index;
}

void GXColor4u8(u8 r, u8 g, u8 b, u8 a)
{
    gx_pipe->d.U8 = r;
    gx_pipe->d.U8 = g;
    gx_pipe->d.U8 = b;
    gx_pipe->d.U8 = a;
}
void GXColor3u8(u8 r, u8 g, u8 b)
{
    gx_pipe->d.U8 = r;
    gx_pipe->d.U8 = g;
    gx_pipe->d.U8 = b;
}
void GXColor1u32(u32 clr)
{
    gx_pipe->d.U32 = clr;
}
void GXColor1u16(u16 clr)
{
    gx_pipe->d.U16 = clr;
}
void GXColor1x16(u16 index)
{
    gx_pipe->d.U16 = index;
}
void GXColor1x8(u8 index)
{
    gx_pipe->d.U8 = index;
}

void GXTexCoord2f32(f32 s, f32 t)
{
    gx_pipe->d.F32 = s;
    gx_pipe->d.F32 = t;
}
void GXTexCoord2u16(u16 s, u16 t)
{
    gx_pipe->d.U16 = s;
    gx_pipe->d.U16 = t;
}
void GXTexCoord2s16(s16 s, s16 t)
{
    gx_pipe->d.S16 = s;
    gx_pipe->d.S16 = t;
}
void GXTexCoord2u8(u8 s, u8 t)
{
    gx_pipe->d.U8 = s;
    gx_pipe->d.U8 = t;
}
void GXTexCoord2s8(s8 s, s8 t)
{
    gx_pipe->d.S8 = s;
    gx_pipe->d.S8 = t;
}
void GXTexCoord1f32(f32 s, f32 t)
{
    gx_pipe->d.F32 = s;
    gx_pipe->d.F32 = t;
}
void GXTexCoord1u16(u16 s, u16 t)
{
    gx_pipe->d.U16 = s;
    gx_pipe->d.U16 = t;
}
void GXTexCoord1s16(s16 s, s16 t)
{
    gx_pipe->d.S16 = s;
    gx_pipe->d.S16 = t;
}
void GXTexCoord1u8(u8 s, u8 t)
{
    gx_pipe->d.U8 = s;
    gx_pipe->d.U8 = t;
}
void GXTexCoord1s8(s8 s, s8 t)
{
    gx_pipe->d.S8 = s;
    gx_pipe->d.S8 = t;
}
void GXTexCoord1x16(u16 index)
{
    gx_pipe->d.U16 = index;
}
void GXTexCoord1x8(u8 index)
{
    gx_pipe->d.U8 = index;
}



#endif