#pragma once
#include "common.h"

class ParticleSystem
{
public:
    struct Particle
    {
        /* Whether to simulate the particle */
        bool active = true;

        /* Diameter */
        float D = 0;

        /* Temperature */
        float T = 0;

        /* Position */
        float x[3] = {0};

        /* Velocity */
        float u[3] = {0};
    };

    struct Configuration
    {
        /* Number of particles */
        int n_particles = 1000;

        /* If true, particles that exit the bounding box re-enter periodically */
        bool periodic_boundary = true;

        /* If true, check for wall collisions */
        bool wall_collision = false;

        /* If true, include virtual mass */
        bool virtual_mass = true;

        /* Time-stepping */
        float t_start = 0;
        float t_end = 50;
        float dt = 1e-3;

        /* Write-control */
        int n_write = 100;
        bool write_vtk = true;
        bool write_csv = false;
        std::string write_dir = "data";
    };

    struct BoundingBox
    {
        float x_start[3] = {1.5, 0.0, 0.0};
        float x_end[3] = {8.0, 6.0, 0.0};
    };

    PhysicalProperties prop;
    Configuration config;
    BoundingBox bb;

    typedef std::function<void(const Particle &, const PhysicalProperties &, float F[])> ForceType;
    void AddForce(ForceType force);
    void Run();

private:
    void UniformInit();

    void UpdateParticles();
    void OnBoundary(Particle &particle);
    void OnWall(Particle &particle);

    void ToFile(int t_idx);
    void ToCSV(int t_idx);
    void ToVTK(int t_idx);

    std::vector<ForceType> forces;
    std::vector<Particle> particles;
    std::vector<float> rhs;
};