#include "../../../MexTK/include/math.h"

#define MAX_SPRING_LENGTH 10

typedef struct Mass
{
	float m;									// The mass value
	Vec3 pos;								// Position in space
	Vec3 vel;								// Velocity
	Vec3 force;								// Force applied on this mass at an instance
} Mass;

typedef struct Spring
{
    Mass *mass1;										//The first mass at one tip of the spring
	Mass *mass2;										//The second mass at the other tip of the spring
	float springConstant;								//A constant to represent the stiffness of the spring
	float springLength;									//The length that the spring does not exert any force
	float frictionConstant;								//A constant to be used for the inner friction of the spring
} Spring;

typedef struct RopeSimulation
{
	Spring springs[MAX_SPRING_LENGTH];
	Mass masses[MAX_SPRING_LENGTH + 1];
	Vec3 gravitation;
	Vec3 ropeConnectionTarget;
	Vec3 ropeConnectionPos;
	Vec3 ropeConnectionVel;
	float groundRepulsionConstant;
	float groundFrictionConstant;
	float groundAbsorptionConstant;
	float groundHeight;
	float airFrictionConstant;
    int init;
} RopeSimulation;


float Vec3_Length(Vec3 v)
{
    return sqrtf(v.X*v.X + v.Y*v.Y + v.Z*v.Z);
};

Vec3 Vec3_Add(Vec3 a, Vec3 b)
{
    Vec3 r =
    { 
        a.X + b.X, 
        a.Y + b.Y, 
        a.Z + b.Z 
    };
    return r;
}

Vec3 Vec3_Sub(Vec3 a, Vec3 b)
{
    Vec3 r =
    { 
        a.X - b.X, 
        a.Y - b.Y, 
        a.Z - b.Z 
    };
    return r;
}

Vec3 Vec3_Divide(Vec3 a, float v)
{
    Vec3 r =
    { 
        a.X / v, 
        a.Y / v, 
        a.Z / v 
    };
    return r;
}

Vec3 Vec3_Mult(Vec3 a, float v)
{
    Vec3 r =
    { 
        a.X * v, 
        a.Y * v, 
        a.Z * v 
    };
    return r;
}

void Mass_Init(Mass *mass)
{
    mass->force.X = 0;
    mass->force.Y = 0;
    mass->force.Z = 0;
}

void Mass_ApplyForce(Mass *mass, Vec3 force)
{
    // The external force is added to the force of the mass
    mass->force.X += force.X;
    mass->force.Y += force.Y;
    mass->force.Z += force.Z;	
}

void Mass_Simulate(Mass *mass, float dt)
{
    mass->vel = Vec3_Add(mass->vel, Vec3_Mult(Vec3_Divide(mass->force, mass->m), dt));
    // Change in velocity is added to the velocity.
    // The change is proportinal with the acceleration (force / m) and change in time

    mass->pos = Vec3_Add(mass->pos, Vec3_Mult(mass->vel, dt));						
    // Change in position is added to the position.
    // Change in position is velocity times the change in time
}

void Spring_Solve(Spring *spring)
{
    Vec3 springVector = Vec3_Sub(spring->mass1->pos, spring->mass2->pos);

    float r = Vec3_Length(springVector);

    Vec3 force = { 0, 0, 0 };

    if (r != 0)	
    {
        force.X = (springVector.X / r) * (r - spring->springLength) * (-spring->springConstant);
        force.Y = (springVector.Y / r) * (r - spring->springLength) * (-spring->springConstant);
        force.Z = (springVector.Z / r) * (r - spring->springLength) * (-spring->springConstant);
    }
	force = Vec3_Add(force, Vec3_Mult(Vec3_Mult(Vec3_Sub(spring->mass1->vel, spring->mass2->vel), -1), spring->frictionConstant));
    //OSReport("%f %f %f %f\n", r, force.X, force.Y, force.Z);

    // apply force
    Mass_ApplyForce(spring->mass1, force);

    // apply force in opposite direction
    Mass_ApplyForce(spring->mass2, Vec3_Mult(force, -1));
}

///
///
///
void Simulation_Init(RopeSimulation *sim)
{
    sim->gravitation.X = 0;
    sim->gravitation.Y = -9.81f;
    sim->gravitation.Z = 0;
	sim->airFrictionConstant = 0.02f;
	sim->groundFrictionConstant = 0.2f;
	sim->groundRepulsionConstant = 100.0f;
	sim->groundAbsorptionConstant = 2.0f;
	sim->groundHeight = -1.5f;

    float spring_length = 1;

    for (int i = 0; i < MAX_SPRING_LENGTH; i++)
    {
        sim->masses[i].m = 0.05f;
        sim->masses[i].pos.X = i * spring_length;
        sim->masses[i].pos.Y = 0;
        sim->masses[i].pos.Z = 0;
    }

    for (int i = 0; i < MAX_SPRING_LENGTH - 1; i++)
    {
        sim->springs[i].mass1 = &sim->masses[i];
        sim->springs[i].mass2 = &sim->masses[i + 1];
        sim->springs[i].springConstant = 10000.0f;
        sim->springs[i].springLength = spring_length;
        sim->springs[i].frictionConstant = 0.2f;
    }
}


void Simulation_Solve(RopeSimulation *sim)
{
    for (int a = 0; a < MAX_SPRING_LENGTH - 1; a++)
        Spring_Solve(&sim->springs[a]);

    for (int a = 0; a < MAX_SPRING_LENGTH; a++)
    {
        Mass *mass = &sim->masses[a];
        
        // gravity
        Mass_ApplyForce(mass, Vec3_Mult(sim->gravitation, mass->m));
        
        // air friction
        Mass_ApplyForce(mass, Vec3_Mult(Vec3_Mult(mass->vel, -1), sim->airFrictionConstant));
            
    }

}


void Simulation_Simulate(RopeSimulation *sim, float dv)
{
    // simulate masses
    for (int a = 0; a < MAX_SPRING_LENGTH; a++)
        Mass_Simulate(&sim->masses[a], dv);
    
    sim->ropeConnectionPos = Vec3_Add(sim->ropeConnectionPos, Vec3_Mult(sim->ropeConnectionVel, dv));

    sim->masses[0].pos = sim->ropeConnectionPos;
    sim->masses[0].vel = sim->ropeConnectionVel;
}


void Simulation_Operate(RopeSimulation *sim, float dv)
{
    // init force to 0
    for (int i = 0; i < MAX_SPRING_LENGTH; i++)
        Mass_Init(&sim->masses[i]);
    
    // calculate forces acting on masses
    Simulation_Solve(sim);

    // simulate physics
    Simulation_Simulate(sim, dv);
}