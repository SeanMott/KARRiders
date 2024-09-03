#include "../../../MexTK/include/math.h"

#define MAX_POINTS 20

typedef struct Mass
{
    char pinned;
    char axis;
    Vec3 pos;
    Vec3 oldpos;
    float gravity;
    float friction;
} Mass;

/// 
/// Updates this masses point in space
/// 
void Mass_Update(Mass *mass)
{
    // process velocity
    Vec3 vel = Vec3_Sub(mass->pos, mass->oldpos);
    vel.X *= mass->friction;

    // update mass location
    mass->oldpos = mass->pos;
    mass->pos = Vec3_Add(mass->pos, vel);

    // process gravity
    if (!mass->pinned)
        mass->pos.Y -= mass->gravity;
}



typedef struct Spring
{
    Mass *p0;
    Mass *p1;
    float length;
    float min_length;
} Spring;

/// 
/// calculates length of spring base on current mass point distances
/// 
void Spring_CalculateLength(Spring *spring)
{
    spring->length = Vec3_Distance(spring->p0->pos, spring->p1->pos);
}

/// 
///  
/// 
void Spring_Update(Spring *spring)
{
    Vec3 dx = Vec3_Sub(spring->p1->pos, spring->p0->pos);
    float distance = Vec3_Distance(spring->p1->pos, spring->p0->pos);
    
    if (spring->min_length == 0 || distance < spring->min_length)
    {
        float diff = spring->length - distance;
        float percent = diff / distance / 2;
        Vec3 off = Vec3_Mult(dx, percent);

        if (!spring->p0->pinned)
            spring->p0->pos = Vec3_Sub(spring->p0->pos, off);

        if (!spring->p1->pinned)
            spring->p1->pos = Vec3_Add(spring->p1->pos, off);
    }
}


typedef struct Manager
{
    int mass_num;
    int spring_num;
    int iterations;
    Mass masses[MAX_POINTS + 1];
    Spring springs[MAX_POINTS];
} Manager;

///
///
///
Mass* Manager_CreateMass(Manager *manager, Vec3 pos, float gravity)
{
    Mass *mass = &manager->masses[manager->mass_num];
    mass->gravity = gravity; // 0.005;
    mass->friction = 0.99;
    mass->pos = pos;
    mass->oldpos = pos;
    manager->mass_num++;
    return mass;
}

///
///
///
Mass* Manager_AddMass(Manager *manager, Mass mass)
{
    manager->masses[manager->mass_num] = mass;
    manager->mass_num++;
    return &manager->masses[manager->mass_num - 1];
}

/// 
///
///
Spring* Manager_CreateSpring(Manager *manager, Mass *p0, Mass *p1)
{
    Spring *spring = &manager->springs[manager->spring_num];
    spring->p0 = p0;
    spring->p1 = p1;
    manager->spring_num++;
    return spring;
}

///
///
///
Spring* Manager_AddSpring(Manager *manager, Spring spring)
{
    manager->springs[manager->spring_num] = spring;
    manager->spring_num++;
    return &manager->springs[manager->spring_num - 1];
}

/// 
/// Initializes the manager
/// 
/*void Manager_Init(Manager *manager, int mass_num)
{
    if (mass_num > MAX_POINTS)
        mass_num = MAX_POINTS;

    manager->mass_num = mass_num;
    manager->spring_num = mass_num - 1;
    manager->iterations = 3;

    for (int i = 0; i < manager->mass_num; i++)
    {
        Mass *mass = &manager->masses[i];
        mass->gravity = 0.005;
        mass->friction = 0.99;
        mass->pos.X = 1 * i;
        mass->pos.Y = 0;
        mass->pos.Z = 0;
        mass->oldpos = mass->pos;
    }
    
    for (int i = 0; i < manager->spring_num; i++)
    {
        Spring *spring = &manager->springs[i];
        spring->length = 1;
        spring->p0 = &manager->masses[i];
        spring->p1 = &manager->masses[i + 1];
    }
}*/

///
///
///
void Manager_RecalculateSpringLengths(Manager *manager)
{
    for (int i = 0; i < manager->spring_num; i++)
    {
        Spring *spring = &manager->springs[i];
        spring->length = Vec3_Distance(spring->p0->pos, spring->p1->pos);
    }
}

/// 
/// Updates the manager for a new frame
/// 
void Manager_UpdateConstrains(Manager *manager, Vec3 *pos)
{
    // Update Springs
    for (int i = 0; i < manager->spring_num; i++)
    {
        Spring *spring = &manager->springs[i];
        Spring_Update(spring);
    }

    // Update Constrains
    for (int i = 0; i < manager->mass_num; i++)
    {
        Mass *mass = &manager->masses[i];

        // pin spring 0
        if (i == 0)
            mass->pos = *pos;
        
        // 
        if (i == 1)
        {
            
        }

    }
}

/// 
/// Updates the manager for a new frame
/// 
void Manager_Update(Manager *manager, Vec3 *pos)
{
    // Update Masses
    for (int i = 0; i < manager->mass_num; i++)
    {
        Mass *mass = &manager->masses[i];
        Mass_Update(mass);
    }

    for (int i = 0; i < manager->iterations; i++)
        Manager_UpdateConstrains(manager, pos);
}
