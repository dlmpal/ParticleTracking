#include "particle_system.h"
#include "force.h"

int main(int argc, char **argv)
{
    ParticleSystem system;

    system.prop.D_0 = 2e-4;
    system.prop.rho_p = 1;
    system.prop.rho_c = 1000;
    system.prop.U = 0.5;

    system.AddForce(Buoyancy);
    system.AddForce(StokesDrag);
    system.AddForce(UndisturbedFlowStress);
    system.AddForce(VirtualMass);
    system.config.virtual_mass = true;

    system.Run();

    return 0;
}