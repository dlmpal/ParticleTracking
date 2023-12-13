#pragma once

#include "cmath"
#include "vector"
#include "array"
#include "string"
#include "fstream"
#include "iostream"
#include "functional"
#include "random"

#define DIM 2

struct PhysicalProperties
{
    /* characteristic flow velocity and length */
    float U = 2.5;
    float L = 10;

    /* Gravitational acceleration and direction */
    float g = 9.81;
    int g_dir = 1;

    /* Initial values of particle density, diameter, temperature and velocity */
    float rho_p = 997;
    float D_0 = 2e-5;
    float T_0 = 1200;
    float u_0[3] = {0};

    /* Carrier phase properties */
    float rho_c = 1.293;
    float mu_c = 1.81 * 1e-5;

    /* Other */
    float D_cyl = 1; // Cylinder diameter
};

inline float ComputeSphereVolume(float D)
{
    constexpr float c = M_PI / 6.0;
    return c * D * D * D;
}

inline float ComputeRadialDistance(float x[3])
{
    return sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
}

inline float ComputeStokesNumber(float D_p, float rho_p, float mu_c, float U, float L)
{
    float St = (rho_p * D_p * D_p * U) / (18 * mu_c * L);
    return St;
}

inline float ComputeKnudsenNumber(float mu_c, float rho_c, float T, float L)
{
    static const float gamma = 1.4;
    static const float R_gas = 2.87;
    float Kn = mu_c / sqrt(gamma * R_gas * T) / rho_c / L;
    return Kn;
}