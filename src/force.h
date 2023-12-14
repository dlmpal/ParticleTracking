#pragma once

#include "particle_system.h"

void Buoyancy(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[]);
void StokesDrag(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[]);
void UndisturbedFlowStress(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[]);
void VirtualMass(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[]);
void BrownMotion(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float F[]);