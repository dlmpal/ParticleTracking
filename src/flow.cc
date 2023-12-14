#include "flow.h"

void ComputeFlowVelocity(const ParticleSystem::Particle &particle, const PhysicalProperties& prop, float u_c[])
{   
    float U = prop.U;
    u_c[0] = U * cos(particle.x[0]) * cos(particle.x[1]);
    u_c[1] = U * sin(particle.x[0]) * sin(particle.x[1]);
}

void ComputeFlowVelocityGradient(const ParticleSystem::Particle &particle, const PhysicalProperties& prop, float gradu_c[])
{   
    float U = prop.U;
    gradu_c[0 * 2 + 0] = -U * sin(particle.x[0]) * cos(particle.x[1]);
    gradu_c[0 * 2 + 1] = -U * cos(particle.x[0]) * sin(particle.x[1]);
    gradu_c[1 * 2 + 0] = U * cos(particle.x[0]) * sin(particle.x[1]);
    gradu_c[1 * 2 + 1] = U * sin(particle.x[0]) * cos(particle.x[1]);
}