#include "particle_system.h"
#include "force.h"

void ParticlesAroundCylinder()
{
    ParticleSystem system;

    system.prop.L = 20;
    system.prop.U = 2.5;
    system.prop.D_cyl = 1.0;
    system.prop.D_0 = 2e-4;
    system.prop.rho_p = 1000;
    system.prop.rho_c = 1;

    /* Total particle emission time */
    float tau_emit = system.prop.L / system.prop.U;
    
    /* Total simulation time */
    float tau_sim = 2 * tau_emit;

    system.config.n_part_init = 0;
    system.config.n_part_max = 1e4;
    system.config.write_dir = ".";
    system.config.t_end = tau_sim * 4;
    system.config.n_emit = 10;
    system.config.n_part_emit = 1;
    system.config.f_emit = 0;

    system.bb.x_start[0] = -10;
    system.bb.x_start[1] = -6;
    system.bb.x_end[0] = 10;
    system.bb.x_end[1] = 6;

    system.AddForce(Buoyancy);
    system.AddForce(StokesDrag);
    //  system.AddForce(UndisturbedFlowStress);
    //  system.AddForce(VirtualMass);
    //  system.config.virtual_mass = true;

    system.Run();
}

int main(int argc, char **argv)
{
    ParticlesAroundCylinder();

    return 0;
}