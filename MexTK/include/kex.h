#ifndef KEX_H
#define KEX_H

#include "hsd.h"

#define PAD_BUTTON_DPAD_LEFT    0x00000001
#define PAD_BUTTON_DPAD_RIGHT   0x00000002
#define PAD_BUTTON_DPAD_DOWN    0x00000004
#define PAD_BUTTON_DPAD_UP      0x00000008
#define PAD_TRIGGER_Z           0x00000010
#define PAD_TRIGGER_R           0x00000020
#define PAD_TRIGGER_L           0x00000040
#define PAD_BUTTON_A            0x00000100
#define PAD_BUTTON_B            0x00000200
#define PAD_BUTTON_X            0x00000400
#define PAD_BUTTON_Y            0x00000800
#define PAD_BUTTON_START        0x00001000
#define PAD_BUTTON_UP           0x00010000
#define PAD_BUTTON_DOWN         0x00020000
#define PAD_BUTTON_LEFT         0x00040000
#define PAD_BUTTON_RIGHT        0x00080000
#define PAD_C_UP                0x00100000
#define PAD_C_DOWN              0x00200000
#define PAD_C_LEFT              0x00400000
#define PAD_C_RIGHT             0x00800000

typedef struct StateLogic
{
    int anim_id;
    int flags;
    void *AnimCB;
    void *InputCB;
    void *Unk1CB;
    void *Unk2CB;
    void *FinalCB;
    void *CameraCB;
} StateLogic;

int OSReport(char *__format,...);

int Kirby_GetCopyAbility(int *rider_data, int ability_id);

void Rider_StateChange(float frame, float frame_speed, int *player_data, int state_id, int anim_id, int flags);
void Rider_SetModelVisibility(int param_1, int param_2, char param_3);
void Rider_SetUnknownFlag(int *param_1, int param_2);
int Rider_CheckAnimationEnd(int *param_1);

#endif