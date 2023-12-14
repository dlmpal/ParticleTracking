#include "particle_system.h"

void ParticleSystem::UniformPlacement()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::uniform_real_distribution<float>> dist(DIM);
    for (auto i = 0; i < DIM; i++)
    {
        dist[i] = std::uniform_real_distribution<float>(bb.x_start[i], bb.x_end[i]);
    }

    particles.resize(config.n_part_init);
    for (auto &particle : particles)
    {
        particle.active = true;
        particle.D = prop.D_0;
        particle.T = prop.T_0;
        for (auto j = 0; j < DIM; j++)
        {
            particle.x[j] = dist[j](gen);
            particle.u[j] = prop.u_0[j];
        }
    }
}

void ParticleSystem::EmitParticle()
{
    if (particles.size() >= config.n_part_max)
        return;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::vector<std::uniform_real_distribution<float>> dist(DIM);
    for (auto i = 0; i < DIM; i++)
    {
        dist[i] = std::uniform_real_distribution<float>(bb.x_start[i], bb.x_end[i]);
    }

    Particle particle;
    particle.active = true;
    particle.D = prop.D_0;
    particle.T = prop.T_0;
    for (auto i = 0; i < DIM; i++)
    {
        particle.x[i] = dist[i](gen);
        particle.u[i] = prop.u_0[i];
    }
    particle.x[config.f_emit] = bb.x_start[config.f_emit];
    particles.push_back(particle);
}

void ParticleSystem::ToCSV(int t_idx)
{
    std::ofstream file(config.write_dir + "/state_" + std::to_string(t_idx) + ".csv");
    file << "x,y,u,v\n";

    for (auto const &particle : particles)
    {
        file << particle.x[0] << "," << particle.x[1] << "," << particle.u[0] << "," << particle.u[1] << "\n";
    }

    file.close();
}

void ParticleSystem::ToVTK(int t_idx)
{
    std::ofstream file(config.write_dir + "/state_" + std::to_string(t_idx) + ".vtk");
    file << "# vtk DataFile Version 2.0\n";
    file << "ParticleSimulation Time:" << t_idx << "\n";
    file << "ASCII\n";
    file << "DATASET UNSTRUCTURED_GRID\n";
    file << "POINTS " << particles.size() << " float\n";
    for (auto const &particle : particles)
    {
        for (auto j = 0; j < 3; j++)
            file << particle.x[j] << " ";
        file << "\n";
    }

    file << "CELLS " << particles.size() << " " << 2 * particles.size() << "\n";
    for (auto i = 0; i < particles.size(); i++)
        file << 1 << " " << i << "\n";

    file << "CELL_TYPES " << particles.size() << "\n";
    for (auto i = 0; i < particles.size(); i++)
        file << 1 << "\n";

    file << "POINT_DATA " << particles.size() << "\n";
    file << "VECTORS U float\n";
    for (auto const &particle : particles)
    {
        for (auto j = 0; j < 3; j++)
            file << particle.u[j] << " ";
        file << "\n";
    }
    file.close();
}

void ParticleSystem::ToFile(int t_idx)
{
    if (config.write_csv == true)
        ToCSV(t_idx);
    if (config.write_vtk == true)
        ToVTK(t_idx);
}

void ParticleSystem::AddForce(ForceType force)
{
    forces.push_back(force);
}

void ParticleSystem::OnBoundary(Particle &particle)
{
    bool exited = false;
    for (auto j = 0; j < DIM; j++)
    {
        if (particle.x[j] > bb.x_end[j])
        {
            particle.x[j] = particle.x[j] - bb.x_end[j] + bb.x_start[j];
            exited = true;
        }

        if (particle.x[j] < bb.x_start[j])
        {
            particle.x[j] = bb.x_end[j] - bb.x_start[j] + particle.x[j];
            exited = true;
        }
    }

    if (config.periodic_boundary == false && exited == true)
        particle.active = false;
}

void ParticleSystem::OnWall(Particle &particle)
{
    float r = ComputeRadialDistance(particle.x);
    if (r <= 0.5 * prop.D_cyl)
    {
        for (auto j = 0; j < DIM; j++)
        {
            particle.u[j] = -particle.u[j];
        }
    }
}

void ParticleSystem::UpdateParticles()
{
    for (auto &particle : particles)
    {
        if (particle.active == false)
            continue;

        float V_p = ComputeSphereVolume(particle.D);
        float m_p = prop.rho_p * V_p;
        if (config.virtual_mass)
            m_p += 0.5 * prop.rho_c * V_p;

        float F[DIM] = {0};
        for (auto force : forces)
            force(particle, prop, F);

        for (auto j = 0; j < DIM; j++)
        {
            particle.x[j] += config.dt * particle.u[j];
            particle.u[j] += config.dt * F[j] / m_p;
        }

        OnBoundary(particle);

        if (config.wall_collision)
            OnWall(particle);
    }
}

void ParticleSystem::Run()
{
    UniformPlacement();

    int t_idx = 0;
    float time = config.t_start;
    while (time <= config.t_end)
    {
        if (t_idx % config.n_emit == 0)
            EmitParticle();

        UpdateParticles();

        if (t_idx % config.n_write == 0)
        {
            ToFile(t_idx);
            if (config.verbose)
                std::cout << "Time: " << round(time * 100) / 100 << "\n";
        }

        t_idx++;
        time += config.dt;
    }
}