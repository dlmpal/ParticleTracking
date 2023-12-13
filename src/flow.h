#pragma once

#include "common.h"
#include "particle_system.h"

extern void ComputeFlowVelocity(const ParticleSystem::Particle &particle, float U, float u_c[]);
extern void ComputeFlowVelocityGradient(const ParticleSystem::Particle &particle, float U, float gradu_c[]);