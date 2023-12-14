#include "flow.h"

float CylinderPotential(float x, float y, float U, float D)
{
    float r = sqrt(x * x + y * y);
    if (r <= D)
        return U * 2 * x;
    else
        return U * (1 + (D / r) * (D / r)) * x;
}

void ComputeFlowVelocity(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float u_c[])
{
    constexpr float dx = 1e-3;
    float U = prop.U;
    float D_cyl = prop.D_cyl;

    u_c[0] = 0.5 / dx * (CylinderPotential(particle.x[0] + dx, particle.x[1], U, D_cyl) - CylinderPotential(particle.x[0], particle.x[1], U, D_cyl));
    if (u_c[0] > 2 * U)
        u_c[0] = 2 * U;

    u_c[1] = 0.5 / dx * (CylinderPotential(particle.x[0], particle.x[1] + dx, U, D_cyl) - CylinderPotential(particle.x[0], particle.x[1], U, D_cyl));
    if (u_c[1] > 2 * U)
        u_c[1] = 2 * U;
}

void ComputeFlowVelocityGradient(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float gradu_c[])
{
    // TODO
}