#include "flow.h"

float CylinderPotential(float x, float y, float U, float D)
{
    float r = sqrt(x * x + y * y);
    if (r <= D)
        return U * 2 * x;
    else
        return U * (1 + (D / r) * (D / r)) * x;
}

void ComputeFlowVelocity(const ParticleSystem::Particle &particle, float U, float u_c[])
{
    u_c[0] = U * cos(particle.x[0]) * cos(particle.x[1]);
    u_c[1] = U * sin(particle.x[0]) * sin(particle.x[1]);
}

void ComputeFlowVelocityGradient(const ParticleSystem::Particle &particle, float U, float gradu_c[])
{
    gradu_c[0 * 2 + 0] = -U * sin(particle.x[0]) * cos(particle.x[1]);
    gradu_c[0 * 2 + 1] = -U * cos(particle.x[0]) * sin(particle.x[1]);
    gradu_c[1 * 2 + 0] = U * cos(particle.x[0]) * sin(particle.x[1]);
    gradu_c[1 * 2 + 1] = U * sin(particle.x[0]) * cos(particle.x[1]);
}