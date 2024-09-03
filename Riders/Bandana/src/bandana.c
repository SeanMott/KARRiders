#include "../../../MexTK/include/kex.h"
///
///
///
void OnInit(char *rider_data)
{
    OSReport("Initializing Waddle Dee %8X\n", rider_data);
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
