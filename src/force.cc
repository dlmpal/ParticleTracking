#include "force.h"
#include "flow.h"

void Buoyancy(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[])
{
    F[prop.g_dir] += prop.g * ComputeSphereVolume(particle.D) * (prop.rho_c - prop.rho_p);
}

void StokesDrag(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[])
{
    float u_c[DIM];
    ComputeFlowVelocity(particle, prop, u_c);
    for (auto j = 0; j < DIM; j++)
    {
        F[j] += 3 * M_PI * prop.mu_c * particle.D * (u_c[j] - particle.u[j]);
    }
}

void UndisturbedFlowStress(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[])
{
    float m_c, u_c[DIM], gradu_c[DIM * DIM];
    m_c = prop.rho_c * ComputeSphereVolume(particle.D);
    ComputeFlowVelocity(particle, prop, u_c);
    ComputeFlowVelocityGradient(particle, prop, gradu_c);

    for (auto j = 0; j < DIM; j++)
        for (auto k = 0; k < DIM; k++)
            F[j] += m_c * u_c[k] * gradu_c[j * DIM + k];
}

void VirtualMass(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[])
{
    float m_c, gradu_c[DIM * DIM];
    m_c = prop.rho_c * ComputeSphereVolume(particle.D);
    ComputeFlowVelocityGradient(particle, prop, gradu_c);

    for (auto j = 0; j < DIM; j++)
        for (auto k = 0; k < DIM; k++)
            F[j] += m_c * particle.u[k] * gradu_c[j * DIM + k];
}

// void BrownMotion(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[])
// {
//     static const float Kb = 1.380649 * 1e-23;
//     float Kn = ComputeKnudsenNumber(prop.mu_c, prop.rho_c, prop.T_0, prop.L);
//     float C = 1 / (1 + Kn * (2.49 + 0.84 * exp(-1.74 / Kn)));
//     float B = C / (3 * M_PI * prop.mu_c * prop.D_0);
//     float S = (216 * prop.mu_c * Kb * prop.T_0) / (M_PI * M_PI * prop.rho_c * prop.rho_c * pow(prop.D_0, 5) * pow(prop.rho_p / prop.rho_c, 2) * C);

//     std::default_random_engine generator;
//     std::normal_distribution<float> dist(0.0, 1.0);
//     for (auto i = 0; i < particles.size(); i++)
//     {
//         float m_p = prop.rho_p * ComputeSphereVolume(particles[i].D);
//         float G;
//         for (auto j = 0; j < prop.dim; j++)
//         {
//             G = dist(generator);
//             F[i * prop.dim + j] += m_p * G * sqrt(M_PI * S / prop.dt) - 1 / B * particles[i].u[j];
//         }
//     }
// }