#pragma once

#include "common.h"
#include "particle_system.h"

extern void ComputeFlowVelocity(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float u_c[]);
extern void ComputeFlowVelocityGradient(const ParticleSystem::Particle &particle, const PhysicalProperties &prop, float gradu_c[]);