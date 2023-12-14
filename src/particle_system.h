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
        /* Initial number of particles */
        int n_part_init = 1000;

        /* Max number of particles */
        int n_part_max = 1000;

        /* Emit particles */
        int n_emit = 10;     // How often to emit particles
        int n_part_emit = 1; // How many particles to emit
        int f_emit = 0;      // From which face of the bounding box to emit

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
        bool verbose = true;

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
    /* Uniformly place particles inside of the bounding box */
    void UniformPlacement();

    /* Emit a particle */
    void EmitParticle();

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